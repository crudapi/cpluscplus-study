// CMakePtsProject.cpp: 定义应用程序的入口点。
//

#include "CMakePtsProject.h"

#include<iostream>
#include <chrono>
#include <iomanip> /*std::put_time*/
using namespace std;
using namespace std::chrono;

#include <ctime>
#include <chrono>
using namespace std;
void print_now(void)
{
    using namespace std::chrono;
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    struct std::tm  valtm;
#ifdef  WIN32
    localtime_s(&valtm, &tt);
#else
    localtime_r(&tt, &valtm);
#endif //  WIN32
    cout << std::put_time(&valtm, "%Y-%m-%d %H:%M:%S %A") << endl;//2021-03-16 12:37:38
}

int main()
{
    //帧率
    int fps = 60;
    //帧间距 duration = 1.0 / fps;

    //起始时刻
    system_clock::time_point pts_start;//initalized by 0
    //生成一个从起始时刻开始的，帧间距为 duration 的 pts 序列
    for (size_t i = 0; i <= 60; i++)
    {
        /*以实数为单位计算，保持精度*/
        //以微妙为单位（实际的pts通常以百纳秒为单位，这里我们做了简化）
        // elapsed_micro_seconds = (duration * 1000 * 1000) * i 
        //为了保持精度，我们先集中计算乘法，最后算除法
        double elapsed_micro_seconds = (1 * 1000 * 1000) * i / 60;  /*(1) your code */;//请重新给这个变量赋合适的值

        long long ll_micro_duration = static_cast<long long>(elapsed_micro_seconds);
        //从起始时刻 start pt 加上 n * duration ，这样不会有累积误差
        //由于pts的单位是百纳秒，而我们的 duration 只计算到了微妙，所以导致百纳秒没有数据。百纳秒为0
        //计算每帧数据的 pts = 起始时间 + 走过的时间（微妙数）
        auto pts = pts_start + microseconds(ll_micro_duration);
        cout << "i = " << i << ", pts = " << pts.time_since_epoch().count() << ", ";
        //将time_point转换为毫秒数值输出
        cout << "distance from start = " << duration_cast<milliseconds>(pts - pts_start).count() << " ms" << endl;
    }

    print_now();

    return 0;
}
