//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序61
//		程序描述：HoughLines函数用法示例
//		开发测试所用操作系统： Windows 7 64bit
//		开发测试所用IDE版本：Visual Studio 2010
//		开发测试所用OpenCV版本：	3.0 beta
//		2014年11月 Created by @浅墨_毛星云
//		2014年12月 Revised by @浅墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【头文件、命名空间包含部分】----------------------------
//		描述：包含程序所使用的头文件和命名空间
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int g_threshold = 10;
#define WINNAME "【原始图】"
void on_ThresHold(int, void *);
Mat midImage,dstImage1,dstImage2,dstImage3;//临时变量和目标图的定义
vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【1】载入原始图和Mat变量定义   
	Mat srcImage = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图

	//【5】显示原始图  
	namedWindow(WINNAME,WINDOW_AUTOSIZE);
	createTrackbar("threshold",WINNAME,&g_threshold,1000,on_ThresHold);

	imshow(WINNAME, srcImage);  

	//【2】进行边缘检测和转化为灰度图
	Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测
	//【6】边缘检测后的图 
	imshow("【边缘检测后的图（供霍夫变换）】", midImage);  
	on_ThresHold(0,0);
	//轮询获取按键信息，若按下Q，程序退出
	while((char(waitKey(1)) != 'q')) {}
	
	return 0;
}

void on_ThresHold(int, void *)
{
	//【3】进行霍夫线变换
	HoughLines(midImage, lines, 1, CV_PI/180, g_threshold, 0, 0 );
	
	//【4】依次在图中绘制出每条线段
	dstImage1 = Mat::ones(midImage.rows, midImage.cols,CV_8U)*200;
	dstImage2 = Mat::zeros(midImage.rows, midImage.cols,CV_8U);
	cvtColor(midImage,dstImage3, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图
	printf("Lines count: %d\n",(int)lines.size());
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 - 1000*b);
		pt1.y = cvRound(y0 + 1000*a);
		pt2.x = cvRound(x0 + 1000*b);
		pt2.y = cvRound(y0 - 1000*a);
		//此句代码的OpenCV2版为:
		//line( dstImage, pt1, pt2, Scalar(55,100,195), 1, CV_AA);
		//此句代码的OpenCV3版为:
		line( dstImage1, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
		line( dstImage2, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
		line( dstImage3, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
	}

	//【7】显示效果图  
	imshow("【效果图1】", dstImage1);  
	imshow("【效果图2】", dstImage2);  
	imshow("【效果图3】", dstImage3);  

}


