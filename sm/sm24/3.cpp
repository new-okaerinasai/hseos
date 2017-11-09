#include <cstdint>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::pair<int, int> async_fig(int now, int total) {
    int good = 0;
    std::pair<int, int> ans;
    for (int i = 0; i != total; ++i) {
        int x = rand_r(now) - RAND_MAX / 2;
        int y = rand_r(now) - RAND_MAX / 2;
        if ((long long)x*x + (long long)y*y < (long long)RAND_MAX / 2) {
            ++good;
        }
    }
    ans.first = good;
    ans.second = total;
    return ans;
}

int main(int argc, char* argv[]) {
    int count = std::atoi(argv[1]);
    int iter = std::atoi(argv[2]);
    std::vector<std::future<std::pair<int, int>>> f (count, std::future<std::pair<int, int>>());
    for (int i = 0; i != count; ++i) {
        f[i] = std::async(std::launch::async, async_fig, i, iter);
    }
    int good = 0;
    int total = 0;
    for (int i = 0; i != count; ++i) {
        std::pair<int, int> ans = f[i].get();
        good += ans.first;
        total += ans.second;
    }
    std::cout << good / total << '\n';
}