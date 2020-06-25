#include <iostream>
#include <mutex>
#include <functional>
#include <future>
using namespace std;

class FooBar {
private:
    int n;
    mutex mu;
    condition_variable run;
    bool bar_ = false;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        unique_lock<mutex> locker(mu);
        for (int i = 0; i < n; i++) {
            run.wait(locker,[this]{ return !bar_; });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            bar_ = true;
            run.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        unique_lock<mutex> locker(mu);
        for (int i = 0; i < n; i++) {
            run.wait(locker,[this]{ return bar_; });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            bar_ = false;
            run.notify_all();
        }
    }
};

int main(void) {
    FooBar f(100);
    auto t1 = async(launch::async,[&f](){ f.foo([](){ std::cerr << "foo"; }); });
    auto t2 = async(launch::async,[&f](){ f.bar([](){ std::cerr << "bar" << ' '; }); });
    t1.get();t2.get();
    return 0;
}