#pragma once

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class JobSystem {
public:
    static void init(size_t threads);
    static void shutdown();
    static void submit(const std::function<void()>& job);

private:
    static void worker();

    static std::vector<std::thread> workers;
    static std::queue<std::function<void()>> jobs;
    static std::mutex mutex;
    static std::condition_variable cv;
    static bool running;
};