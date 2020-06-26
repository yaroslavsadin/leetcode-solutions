#include <iostream>
#include <array>
#include <mutex>
#include <functional>
#include <future>
using namespace std;

// NOTE: this one needs -std=c++17 in order to work because of the std::scoped_lock
class DiningPhilosophers {
private:
    std::array<std::mutex,5> forks;
    std::pair<size_t,size_t> ForksFromId(int philosopher) const noexcept {
        if(philosopher == 0) {
            return {4,0};
        }
        return {philosopher,philosopher-1};
    }
public:
    DiningPhilosophers() {
        
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        auto forks_needed = ForksFromId(philosopher);
		std::scoped_lock locker(forks[forks_needed.first],forks[forks_needed.second]);
        pickLeftFork(); pickRightFork();
        eat();
        putLeftFork(); putRightFork();
    }
};