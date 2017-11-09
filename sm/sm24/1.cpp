#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int THR_N = 3, MAX = 1000000;

volatile double m[THR_N];

std::mutex mute;

void thread_fig(int which1, int which2, size_t what1, size_t what2) {
    for (int i = 0; i != MAX; ++i) {
        std::lock_guard<std::mutex> lock(mute);
        m[which1] += what1;
        m[which2] -= what2;
    }
}

int main() {
    std::thread thr1(thread_fig, 0, 1, 80, 90);
    std::thread thr2(thread_fig, 1, 2, 100, 110);
    std::thread thr3(thread_fig, 2, 0, 120, 130);
    thr1.join();
    thr2.join();
    thr3.join();
    std::cout << std::setprecision(10) << m[0] << ' ' << m[1] << ' ' << m[2] << '\n';
}
