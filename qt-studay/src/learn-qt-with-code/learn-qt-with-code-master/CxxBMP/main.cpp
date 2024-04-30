#include "BMP.h"
#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <fstream>
using namespace std;

void test_bmp_signal_color(void)
{
	//制作一个640x480大小，纯红色的图片，保存文件到指定目录
	int w = 640;
	int h = 480;
	BMP bmp(640, 480, 255, 0, 0);
	bmp.save_to("red.bmp");//注意你的机器有没有这个目录
}

void test_bmp_set_rgb(void)
{
	int w = 4;
	int h = 5;
	BMP bmp(w, h);
	vector<unsigned char> buffer{
		  0,  0,255,  0,  0,255,  0,  0,255,  0,  0,255,//blue
		  0,255,  0,  0,255,  0,  0,255,  0,  0,255,  0,//green
		255,  0,  0,255,  0,  0,255,  0,  0,255,  0,  0,//red
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,//black
		255,255,255,255,255,255,255,255,255,255,255,255,//white
	};

	bmp.set_rgb_data(buffer.data(), w * h * 3);
	bmp.save_to("123.bmp");
}

int main(void)
{
	test_bmp_signal_color();
	test_bmp_set_rgb();

	return 0;
}