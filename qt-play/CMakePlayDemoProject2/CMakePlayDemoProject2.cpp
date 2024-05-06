// CMakePlayDemoProject2.cpp: 定义应用程序的入口点。
//

#include "CMakePlayDemoProject2.h"

#include <iostream>
#include <thread>
#include <list>
#include <string>
using namespace std;

//下文代码都需要考虑并发，并发代码没写是为了清晰思路
typedef void* handle_t;

struct h264_package
{
    int data_length = 0;//1个音频包，或者视频包的字节数
};

struct yuv_package
{
};

//从mp4文件里读到的数据
list<h264_package> h264_package_list;
//解码h264得到的yuv数据
list<yuv_package> yuv_package_list;

handle_t read_mp4_file(string file_name) {}
//从头到尾，依次读取视频帧，音频帧
h264_package read_from_mp4_by_ffmpeg(handle_t handle)
{
    return h264_package();
}
yuv_package decode_h264_by_ffmpeg(h264_package package)
{
    return yuv_package();
}
void opengl_rander_yuv(yuv_package package)
{
}

void read_file_thread_fun(void* handle)
{
    h264_package package;
    while (true)
    {
        package = read_from_mp4_by_ffmpeg(handle);
        if (package.data_length == 0)
        {
            break;//读取mp4文件结束
        }
        h264_package_list.push_back(package);//这里需要考虑并发
    }
}
void decode_h264_thread_fun(void)
{
    while (true)
    {
        if (!h264_package_list.empty())
        {
            h264_package package;
            auto package = h264_package_list.front();
            h264_package_list.pop_front();

            auto yuv = decode_h264_by_ffmpeg(package);

            yuv_package_list.push_back(yuv);
        }
    }
}
void rendering_thread_fun(void)
{
    while (true)
    {
        if (!yuv_package_list.empty())
        {
            auto package = yuv_package_list.front();
            yuv_package_list.pop_front();
            //把数据通过OpenGL接口传递给显卡，使用显卡将yuv数据转换为RGB数据渲染到显卡输出
            // ，显卡输出连接显示器显示
            opengl_rander_yuv(package);
        }
    }
}
int main(void)
{
    auto handle = read_mp4_file("av.mp4");

    thread read_frame_thread(read_file_thread_fun, handle);
    thread decode_h246_thread(decode_h264_thread_fun);
    thread rendering_thread(rendering_thread_fun);

    rendering_thread.join();
    decode_h246_thread.join();
    read_frame_thread.join();

    return 0;
}