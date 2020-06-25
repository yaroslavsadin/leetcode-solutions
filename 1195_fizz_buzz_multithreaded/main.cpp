#include <iostream>
#include <mutex>
#include <functional>
#include <future>
using namespace std;

class FizzBuzz {
private:
    int n;
    int cnt;
    mutex mu;
    condition_variable run;

public:
    FizzBuzz(int n) {
        this->n = n;
        cnt = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        unique_lock<mutex> locker(mu);
        while(1) {
            run.wait(locker,[this]{ return cnt == n + 1 || (cnt % 3 == 0 && cnt % 5); });
            if(cnt == n + 1) {
                run.notify_all();
                return;
            }
            printFizz();
            cnt++;
            run.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        unique_lock<mutex> locker(mu);
        while(1) {
            run.wait(locker,[this]{ return cnt == n + 1 || (cnt % 3 && cnt % 5 == 0); });
            if(cnt == n + 1) {
                run.notify_all();
                return;
            }
            printBuzz();
            cnt++;
            run.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        unique_lock<mutex> locker(mu);
        while(1) {
            // p is divisible by 3 and 5 if and only if it is divisable by 15
            run.wait(locker,[this]{ return cnt == n + 1 || (cnt % 15 == 0); });
            if(cnt == n + 1) {
                run.notify_all();
                return;
            }
            printFizzBuzz();
            cnt++;
            run.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        unique_lock<mutex> locker(mu);
        while(1) {
            run.wait(locker,[this]{ return cnt == n + 1 || (cnt % 3 && cnt % 5); });
            if(cnt == n + 1) {
                run.notify_all();
                return;
            }
            printNumber(cnt++);
            run.notify_all();
        }
    }
};

int main(void) {
    FizzBuzz f(100);
    auto t1 = async(launch::async,[&f](){ f.fizz([](){ std::cerr << "fizz" << ' '; }); });
    auto t2 = async(launch::async,[&f](){ f.fizzbuzz([](){ std::cerr << "fizzbuzz" << ' '; }); });
    auto t3 = async(launch::async,[&f](){ f.buzz([](){ std::cerr << "buzz" << ' '; }); });
    auto t4 = async(launch::async,[&f](){ f.number([](int x){ std::cerr << x << ' '; }); });
    t1.get();t2.get();t3.get();t4.get();
    return 0;
}