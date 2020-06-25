#include <iostream>
#include <mutex>
#include <functional>
#include <future>
using namespace std;

class Foo {
private:
    mutex mu;
    condition_variable run;
    enum class State { FIRST, SECOND, THIRD } state;
public:
    Foo() {
        state = State::FIRST;
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> locker(mu);
        run.wait(locker, [this]{ return state == State::FIRST; });
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        state = State::SECOND;
        run.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> locker(mu);
        run.wait(locker, [this]{ return state == State::SECOND; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        state = State::THIRD;
        run.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> locker(mu);
        run.wait(locker, [this]{ return state == State::THIRD; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

int main(void) {
    Foo f;
    auto t1 = async(launch::async,[&f](){ f.second([](){ std::cerr << "second" << std::endl; }); });
    auto t2 = async(launch::async,[&f](){ f.third([](){ std::cerr << "third" << std::endl; }); });
    auto t3 = async(launch::async,[&f](){ f.first([](){ std::cerr << "first" << std::endl; }); });
    t1.get();t2.get();t3.get();
    return 0;
}