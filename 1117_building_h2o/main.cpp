#include <iostream>
#include <array>
#include <mutex>
#include <functional>
#include <future>
using namespace std;

class H2O {
private:
    int h_count;
    mutex mu;
    condition_variable cond;

public:
    H2O() : h_count(0) {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<mutex> locker(mu);
        cond.wait(locker,[this]{ return h_count < 2; });
        h_count++;
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        cond.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        std::unique_lock<mutex> locker(mu);
        cond.wait(locker,[this]{ return h_count == 2; });
        h_count = 0;
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        cond.notify_all();
    }
};