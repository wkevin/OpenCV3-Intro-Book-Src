
//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序41
//		程序描述：用morphologyEx进行图像膨胀
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
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//载入原始图   
	Mat image = imread("1.jpg",IMREAD_REDUCED_COLOR_2);  //工程目录下应该有一张名为1.jpg的素材图
	//创建窗口   
	namedWindow("【原始图】膨胀");  
	//显示原始图  
	imshow("【原始图】膨胀", image);  
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	Mat out1, out2, out3, out4, out5, out6, out7, out8;
	morphologyEx(image, out1, MORPH_ERODE,    element);
	morphologyEx(image, out2, MORPH_DILATE,   element);
	morphologyEx(image, out3, MORPH_OPEN,     element);
	morphologyEx(image, out4, MORPH_CLOSE,    element);
	morphologyEx(image, out5, MORPH_GRADIENT, element);
	morphologyEx(image, out6, MORPH_TOPHAT,   element);
	morphologyEx(image, out7, MORPH_BLACKHAT, element);
	imshow("MORPH_ERODE,    ", out1);
	imshow("MORPH_DILATE,   ", out2);
	imshow("MORPH_OPEN,     ", out3);
	imshow("MORPH_CLOSE,    ", out4);
	imshow("MORPH_GRADIENT, ", out5);
	imshow("MORPH_TOPHAT,   ", out6);
	imshow("MORPH_BLACKHAT, ", out7);

	waitKey(0);  

	return 0;  
}
