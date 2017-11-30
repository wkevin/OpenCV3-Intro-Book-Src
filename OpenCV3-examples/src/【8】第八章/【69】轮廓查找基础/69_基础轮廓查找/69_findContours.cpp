
//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序69
//		程序描述：基础轮廓查找——findContours+drawContours
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
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

//-----------------------------------【main( )函数】--------------------------------------------

//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	// 【1】载入原始图，且必须以二值图模式载入
	Mat srcImage=imread("1.jpg", 0);
	imshow("原始图",srcImage);

	//【2】初始化结果图
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	Mat dstImage1 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	Mat dstImage2 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//【3】srcImage取大于阈值119的那部分
	srcImage = srcImage > 119;
	imshow( "取阈值后的原始图", srcImage );

	//【4】定义轮廓和层次结构
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//【5】查找轮廓
	//此句代码的OpenCV2版为：
	//findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//此句代码的OpenCV3版为：
	findContours( srcImage, contours, hierarchy,RETR_TREE, CHAIN_APPROX_SIMPLE );

	// 【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		printf("(%d:%d/%d/%d/%d)  ",index,hierarchy[index][0],hierarchy[index][1],hierarchy[index][2],hierarchy[index][3]);
		Scalar color( rand()&255, rand()&255, rand()&255 );
		drawContours( dstImage, contours, index, color, FILLED, 8, hierarchy );
		drawContours( dstImage1, contours, index, color, 1, 8, hierarchy );
	}

	printf("\n\n");

	// 画有内嵌的轮廓
	Scalar white( 255, 255, 255 );
	Scalar red  ( 0, 0, 255 );
	Scalar green( 0, 255, 0 );
	Scalar blue ( 255, 0, 0 );
	int hsize = hierarchy.size();
	int i=0;
	int single=0;
	int father=0;
	int son=0;
	for(index = 0; index<hsize;index++)
	{
		// draw single
		if(hierarchy[index][2]==-1) 
		{
			printf("(%d:%d/%d/%d/%d)  ",index,hierarchy[index][0],hierarchy[index][1],hierarchy[index][2],hierarchy[index][3]);
			drawContours( dstImage2, contours, index, red, 1, 8, hierarchy );
			single++;
			continue;
		}

		// draw father
		printf("(%d:%d/%d/%d/%d)\n\n----------------------\n",index,hierarchy[index][0],hierarchy[index][1],hierarchy[index][2],hierarchy[index][3]);
		drawContours( dstImage2, contours, index, green, 1, 8, hierarchy );
		father++;
		
		// draw son
		i = hierarchy[index][2] ;
		int temp = index;
		for( ; hierarchy[i][3] > 0; i = hierarchy[i][0] )
		{
			index = i;
			printf("<%d:%d/%d/%d/%d>  ",i,hierarchy[i][0],hierarchy[i][1],hierarchy[i][2],hierarchy[i][3]);
			drawContours( dstImage2, contours, i, blue, 1, 8, hierarchy );
			son++;
		}

		printf("\n----------------------\n\n");
	}
	printf("\nhierarchy.size: %ld ; single:%d; father:%d; son:%d\n",hierarchy.size(),single,father,son);
	//【7】显示最后的轮廓图
	imshow( "轮廓图-Filled", dstImage );
	imshow( "轮廓图-line", dstImage1 );
	imshow( "轮廓图-line.by.RGB", dstImage2 );

	waitKey(0);

}