#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPool
{
	std::vector <std::thread> threads;
	std::queue <std::function <void()>> tasks;
	std::atomic <bool> in_process;
	std::condition_variable thread_check;
	std::mutex lock_tasks;

public:
	explicit ThreadPool(size_t poolSize);
	
	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

	~ThreadPool();
};

ThreadPool::ThreadPool(size_t poolSize) {
	for (size_t i = 0; i < poolSize; i++) {
		threads.emplace_back([this]() {
			while(true) {
				std::unique_lock <std::mutex> lock(lock_tasks);
				thread_check.wait(lock, [this] { return !(in_process && tasks.empty());});
				if (!tasks.empty() || in_process) {
					std::function <void()> task = std::move(tasks.front());
					tasks.pop();
					lock.unlock();
					task();
				} else {
					return;
				}
			}
		});
	}
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
	using result_type = decltype(func(args...));
	auto future_task = std::make_shared<std::packaged_task<result_type()>>(std::packaged_task<result_type()>(std::move(std::bind(func, args...))));
	std::unique_lock <std::mutex> lock(lock_tasks);
	tasks.emplace([future_task](){ (*future_task)(); });
	lock.unlock();
	thread_check.notify_one();
	return future_task->get_future();
}

ThreadPool::~ThreadPool() {
	in_process = false;
	thread_check.notify_all();
	for (std::thread &elem: threads)
		elem.join();
}
