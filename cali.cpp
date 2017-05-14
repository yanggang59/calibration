#include "opencv2/core/core.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/calib3d/calib3d.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <fstream>  
  
using namespace cv;  
using namespace std;  
  
void main()   
{  
    ifstream fin("calibdata.txt"); /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    ofstream fout("caliberation_result.txt");  /* ¿?¿?¿?¿?¿?¿?¿?¿?¿? */    
    //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?   
    cout<<"¿?¿?¿?¿?¿?¿?¿¿¿¿¿¿"<<endl;  
    int image_count=0;  /* ¿?¿?¿?¿? */  
    Size image_size;  /* ¿?¿?¿?¿?¿? */  
    Size board_size = Size(9,6);    /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<Point2f> image_points_buf;  /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<vector<Point2f>> image_points_seq; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    string filename;  
   // int count= -1 ;//¿?¿?¿?¿?¿?¿?¿?¿?¿?  
    while ( getline(fin,filename) )  
    {  
		if(filename=="end")             //¿?¿?¿?¿?end¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?
			break;
		
        image_count++;        
        // ¿?¿?¿?¿?¿?¿?¿?¿?  
        cout<<"     image_count = "<<image_count<<endl;          
        /* ¿?¿?¿?¿?*/  
        //cout<<"-->count = "<<count;        
        Mat imageInput=imread(filename);  
        if (image_count == 1)  //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
        {  
            image_size.width = imageInput.cols;  
            image_size.height =imageInput.rows;           
            cout<<"   image_size.width = "<<image_size.width<<endl;  
            cout<<"   image_size.height = "<<image_size.height<<endl;  
        }  
  
        /* ¿?¿?¿?¿? */  
        if (0 == findChessboardCorners(imageInput,board_size,image_points_buf))  
        {             
            cout<<"can not find chessboard corners!\n"; //¿?¿?¿?¿?¿?  
            exit(1);  
        }   
        else   
        {  
            Mat view_gray;  
            cvtColor(imageInput,view_gray,CV_RGB2GRAY);  
            /* ¿?¿?¿?¿?¿?¿? */  
            find4QuadCornerSubpix(view_gray,image_points_buf,Size(5,5)); //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
            //cornerSubPix(view_gray,image_points_buf,Size(5,5),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));  
            image_points_seq.push_back(image_points_buf);  //¿?¿?¿?¿?¿?¿?¿?  
            /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
            drawChessboardCorners(view_gray,board_size,image_points_buf,false); //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
            imshow("Camera Calibration",view_gray);//¿?¿?¿?¿?  
            waitKey(500);//¿?¿?0.5S         
        }  
    }  
    int total = image_points_seq.size();  
    cout<<"total = "<<total<<endl;  
    int CornerNum=board_size.width*board_size.height;  //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
    for (int ii=0 ; ii<total ;ii++)  
    {  
        if (0 == ii%CornerNum)// 24 ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?   
        {     
            int i = -1;  
            i = ii/CornerNum;  
            int j=i+1;  
            cout<<"--> ¿? "<<j <<"¿?¿?¿?¿?¿? --> : "<<endl;  
        }  
        if (0 == ii%3)  // ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
        {  
            cout<<endl;  
        }  
        else  
        {  
            cout.width(10);  
        }  
        //¿?¿?¿?¿?¿?¿?¿?  
        cout<<" -->"<<image_points_seq[ii][0].x;  
        cout<<" -->"<<image_points_seq[ii][0].y;  
    }     
    cout<<"¿?¿?¿?¿?¿?¿?¿?\n";  
  
    //¿?¿?¿?¿?¿?¿?¿?¿?  
    cout<<"¿?¿?¿?¿?¿¿¿¿¿¿";  
    /*¿?¿?¿?¿?¿?¿?*/  
    Size square_size = Size(10,10);  /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<vector<Point3f>> object_points; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    /*¿?¿?¿?¿?*/  
    Mat cameraMatrix=Mat(3,3,CV_32FC1,Scalar::all(0)); /* ¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<int> point_counts;  // ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
    Mat distCoeffs=Mat(1,5,CV_32FC1,Scalar::all(0)); /* ¿?¿?¿?¿?5¿?¿?¿?¿?¿?¿?k1,k2,p1,p2,k3 */  
    vector<Mat> tvecsMat;  /* ¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<Mat> rvecsMat; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    int i,j,t;  
    for (t=0;t<image_count;t++)   
    {  
        vector<Point3f> tempPointSet;  
        for (i=0;i<board_size.height;i++)   
        {  
            for (j=0;j<board_size.width;j++)   
            {  
                Point3f realPoint;  
                /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?z=0¿?¿?¿?¿? */  
                realPoint.x =(float) i*square_size.width;  
                realPoint.y = (float)j*square_size.height;  
                realPoint.z = (float)0;  
                tempPointSet.push_back(realPoint);  
            }  
        }  
        object_points.push_back(tempPointSet);  
    }  
    /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    for (i=0;i<image_count;i++)  
    {  
        point_counts.push_back(board_size.width*board_size.height);  
    }     
    /* ¿?¿?¿?¿? */  
    calibrateCamera(object_points,image_points_seq,image_size,cameraMatrix,distCoeffs,rvecsMat,tvecsMat,0);  
    cout<<"¿?¿?¿?¿?¿?\n";  
    //¿?¿?¿?¿?¿?¿?¿?¿?¿?  
    cout<<"¿?¿?¿?¿?¿?¿?¿?¿?¿¿¿¿¿¿\n";  
    double total_err = 0.0; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    double err = 0.0; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    vector<Point2f> image_points2; /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    cout<<"\t¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?\n";  
    fout<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?\n";  
    for (i=0;i<image_count;i++)  
    {  
        vector<Point3f> tempPointSet=object_points[i];  
        /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
        projectPoints(tempPointSet,rvecsMat[i],tvecsMat[i],cameraMatrix,distCoeffs,image_points2);  
        /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?*/  
        vector<Point2f> tempImagePoint = image_points_seq[i];  
        Mat tempImagePointMat = Mat(1,tempImagePoint.size(),CV_32FC2);  
        Mat image_points2Mat = Mat(1,image_points2.size(), CV_32FC2);  
        for (int j = 0 ; j < tempImagePoint.size(); j++)  
        {  
            image_points2Mat.at<Vec2f>(0,j) = Vec2f(image_points2[j].x, image_points2[j].y);  
            tempImagePointMat.at<Vec2f>(0,j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);  
        }  
        err = norm(image_points2Mat, tempImagePointMat, NORM_L2);  
        total_err += err/=  point_counts[i];     
        std::cout<<"¿?"<<i+1<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?"<<err<<"¿?¿?"<<endl;     
        fout<<"¿?"<<i+1<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?"<<err<<"¿?¿?"<<endl;     
    }     
    std::cout<<"¿?¿?¿?¿?¿?¿?¿?"<<total_err/image_count<<"¿?¿?"<<endl;     
    fout<<"¿?¿?¿?¿?¿?¿?¿?"<<total_err/image_count<<"¿?¿?"<<endl<<endl;     
    std::cout<<"¿?¿?¿?¿?¿?"<<endl;    
    //¿?¿?¿?¿?¿?¿?      
    std::cout<<"¿?¿?¿?¿?¿?¿?¿?¿?¿¿¿¿¿¿"<<endl;         
    Mat rotation_matrix = Mat(3,3,CV_32FC1, Scalar::all(0)); /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */  
    fout<<"¿?¿?¿?¿?¿?¿?¿?¿?"<<endl;     
    fout<<cameraMatrix<<endl<<endl;     
    fout<<"¿?¿?¿?¿?¿?\n";     
    fout<<distCoeffs<<endl<<endl<<endl;     
    for (int i=0; i<image_count; i++)   
    {   
        fout<<"¿?"<<i+1<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?"<<endl;     
        fout<<tvecsMat[i]<<endl;      
        /* ¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿? */     
        Rodrigues(tvecsMat[i],rotation_matrix);     
        fout<<"¿?"<<i+1<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?"<<endl;     
        fout<<rotation_matrix<<endl;     
        fout<<"¿?"<<i+1<<"¿?¿?¿?¿?¿?¿?¿?¿?¿?"<<endl;     
        fout<<rvecsMat[i]<<endl<<endl;     
    }     
    std::cout<<"¿?¿?¿?¿?"<<endl;   
    fout<<endl;  
    /************************************************************************   
    ¿?¿?¿?¿?¿?¿?   
    *************************************************************************/  
    Mat mapx = Mat(image_size,CV_32FC1);  
    Mat mapy = Mat(image_size,CV_32FC1);  
    Mat R = Mat::eye(3,3,CV_32F);  
    std::cout<<"¿?¿?¿?¿?¿?¿?"<<endl;  
    string imageFileName;  
    std::stringstream StrStm;  
    for (int i = 0 ; i != image_count ; i++)  
    {  
		
        std::cout<<"Frame #"<<i+1<<"..."<<endl;  
        initUndistortRectifyMap(cameraMatrix,distCoeffs,R,cameraMatrix,image_size,CV_32FC1,mapx,mapy);        
        StrStm.clear();  
        imageFileName.clear();  
        string filePath="E:\\cali_pic1\\";  //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?E:\\cali_pic1\\¿?
        StrStm<<i+1;							 //¿?¿?¿?¿?¿?¿?
        StrStm>>imageFileName;  
        filePath+=imageFileName;  
        filePath+=".png";  
        Mat imageSource = imread(filePath);  
        Mat newimage = imageSource.clone();  
        //¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?¿?  
        //undistort(imageSource,newimage,cameraMatrix,distCoeffs);  
        remap(imageSource,newimage,mapx, mapy, INTER_LINEAR);         
        StrStm.clear();  
        filePath.clear();  
        StrStm<<i+1;  
        StrStm>>imageFileName;  
        imageFileName += "_d.jpg";  
        imwrite(imageFileName,newimage);  
		
    }  
    std::cout<<"¿?¿?¿?¿?"<<endl;      
    return ;  
}  


