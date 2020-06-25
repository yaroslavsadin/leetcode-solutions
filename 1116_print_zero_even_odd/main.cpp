#include <iostream>
#include <functional>
#include <mutex>
#include <future>
#include <string>
#include <sstream>
#include <cassert>
#include "../test_runner.h"

using namespace std;

class ZeroEvenOdd {
private:
    int n;
    int counter;
    std::mutex mu;
    std::condition_variable run;
    bool print_zero;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        counter = 1;
        print_zero = 1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(1) {
            std::unique_lock<mutex> locker(mu);
            run.wait(locker,[this](){ 
                return print_zero || n + 1 == counter;
            });
            print_zero = false;
            if(n + 1 == counter) {
                run.notify_all();
                break;
            }
            printNumber(0);
            run.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while(1) {
            std::unique_lock<mutex> locker(mu);
            run.wait(locker,[this](){ 
                return (!print_zero && (counter % 2 == 0)) || n + 1 == counter;
            });
            print_zero = true;
            if(n + 1 == counter) {
                break;
            }
            printNumber(counter++);
            run.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(1) {
            std::unique_lock<mutex> locker(mu);
            run.wait(locker,[this](){ 
                return (!print_zero && (counter % 2)) || n + 1 == counter;
            });
            print_zero = true;
            if(n + 1 == counter) {
                break;
            }
            printNumber(counter++);
            run.notify_all();
        }
    }
};

void StressTest() {
    size_t num_tests = 1000;
    while(num_tests--) {
        srand(static_cast<unsigned int>(time(nullptr)));
        const auto n = (rand() % 200) + 1;
        std::string ref;

        for(size_t i = 1; i <= n; i++) {
            ref += "0" + std::to_string(i);
        }

        const auto order = (rand() % 3) + 1;
        std::future<void> a, b, c;
        
        ZeroEvenOdd dut(n);
        std::stringstream ss;
        if(order == 0) {
            a = std::async([&dut,&ss](){std::launch::async, dut.zero([&ss](int x){ ss << x ; }); });
            b = std::async([&dut,&ss](){std::launch::async, dut.odd([&ss](int x){ ss << x ; }); });
            c = std::async([&dut,&ss](){std::launch::async, dut.even([&ss](int x){ ss << x ; }); });
        } else if (order == 1) {
            b = std::async([&dut,&ss](){std::launch::async, dut.odd([&ss](int x){ ss << x ; }); });
            a = std::async([&dut,&ss](){std::launch::async, dut.zero([&ss](int x){ ss << x ; }); });
            c = std::async([&dut,&ss](){std::launch::async, dut.even([&ss](int x){ ss << x ; }); });
        } else if (order == 2) {
            c = std::async([&dut,&ss](){std::launch::async, dut.even([&ss](int x){ ss << x ; }); });
            a = std::async([&dut,&ss](){std::launch::async, dut.zero([&ss](int x){ ss << x ; }); });
            b = std::async([&dut,&ss](){std::launch::async, dut.odd([&ss](int x){ ss << x ; }); });
        } else {
            c = std::async([&dut,&ss](){std::launch::async, dut.even([&ss](int x){ ss << x ; }); });
            b = std::async([&dut,&ss](){std::launch::async, dut.odd([&ss](int x){ ss << x ; }); });
            a = std::async([&dut,&ss](){std::launch::async, dut.zero([&ss](int x){ ss << x ; }); });
        }

        a.get();
        b.get();
        c.get();

        ASSERT_EQUAL(ref, ss.str());

        std::cerr << "Good: " << ref << " == " << ss.str() << std::endl;
    }
}

int main(void) {    
    TestRunner tr;
    RUN_TEST(tr,StressTest);
    return 0;
}