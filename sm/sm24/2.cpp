#include <cstdint>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<std::promise<uint64_t>> p;

bool isprime(uint64_t a) {
    if (a == 1) {
        return false;
    }
    if (a == 0) {
        return false;
    }
    if (a == 2) {
        return true;
    }
    if (a % 2 == 0) {
        return false;
    }
    for (uint64_t i = 3; i * i <= a; i += 2) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

void thread_fig(uint64_t low, uint64_t high, uint64_t count) {
    uint64_t k = 0;
    try {
        for (uint64_t i = low; i <= high; ++i) {
            if (isprime(i)) {
                p[k].set_value(i);
                ++k;
                if (k == count) {
                    break;
                }
            }
        }
        if (k < count) {
            throw high;
        } 
    } catch (...) {
        p[k].set_exception(std::current_exception());
    }
}

int main() {
    uint64_t high, low, count;
    std::cin >> low >> high >> count;
    for (uint64_t i = 0; i != count; ++i) {
        p.push_back(std::promise<uint64_t>());
    }
    std::thread thr(thread_fig, low, high, count);
    try {
        for (uint64_t i = 0; i != count; ++i) {
            auto f = p[i].get_future();
            auto val = f.get();
            std::cout << val << '\n';
        }
    } catch (uint64_t high) {
        std::cout << high << '\n';
    }
    thr.join();
}