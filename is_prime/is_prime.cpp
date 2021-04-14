#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <thread>
#include <mutex>
#include <vector>

std::mutex mutex1;
std::mutex mutex;
bool notFound = true;

void Finish ()
{
    notFound = false;
    mutex.unlock();
}

bool isFinish ()
{
    if (mutex.try_lock() == false)
        return false;

    puts("*** FINIHED ***");
    mutex.unlock();
    return true;
}

void CheckPrime (int start, int step, uint64_t x)
{
    for (; start <= sqrt(x); start += step) {
        if (x % start == 0) {
            Finish();
            break;
        }

        if (isFinish()) {
            break;
        }
    }
}

bool IsPrime (uint64_t x)
{
    size_t threads_count = std::thread::hardware_concurrency();
    mutex.lock();

    if (x <= 1) {
        return false;
    }

    std::vector<std::thread> workers;

    for (size_t i = 0; i < threads_count; ++i) {
        workers.emplace_back([=] () {
            CheckPrime(i + 2, threads_count, x);
        });
    }

    for (size_t i = 0; i < threads_count; ++i) {
        workers[i].join();
    }

    return !notFound;
}


TEST_CASE ("Is Prime") {
    CHECK(IsPrime(2));
    CHECK_FALSE(IsPrime(1));
    CHECK_FALSE(IsPrime(0));
    CHECK(IsPrime(17239));
    CHECK_FALSE(IsPrime(9));

    int mul = 100 * 100 * 100 + 3;
    CHECK(IsPrime(mul));
    CHECK_FALSE(IsPrime(static_cast<uint64_t>(mul) * mul));
}
