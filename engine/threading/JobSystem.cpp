#include "JobSystem.hpp"

std::vector<std::thread> JobSystem::workers;
std::queue<std::function<void()>> JobSystem::jobs;
std::mutex JobSystem::mutex;
std::condition_variable JobSystem::cv;
bool JobSystem::running = false;

void JobSystem::init(size_t threads) {
    running = true;
    for (size_t i = 0; i < threads; i++) {
        workers.emplace_back(worker);
    }
}

void JobSystem::shutdown() {
    {
        std::unique_lock lock(mutex);
        running = false;
    }
    cv.notify_all();
    for (auto& w : workers) w.join();
}

void JobSystem::submit(const std::function<void()>& job) {
    {
        std::unique_lock lock(mutex);
        jobs.push(job);
    }
    cv.notify_one();
}

void JobSystem::worker() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock lock(mutex);
            cv.wait(lock, [] { return !jobs.empty() || !running; });
            if (!running && jobs.empty()) return;
            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}