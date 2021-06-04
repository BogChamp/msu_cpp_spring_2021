#include "threadpool.hpp"
#include <iostream>
#include <cassert>

struct A {};

void foo(const A&) {}

int sum(const std::vector<int>& v, size_t begin, size_t end) {
	int result = 0;
	for (size_t i = begin; i < end; ++i) {
		result += v[i];
	}
	return result;
}

int main() {
	ThreadPool pool(2);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	task2.get();

	ThreadPool new_pool(10);
	std::vector<int> vect(1000000, 1);
	std::vector<std::future<int>> futures;

	for (size_t i = 0; i < vect.size(); i += vect.size() / 10)
		futures.push_back(new_pool.exec(sum, vect, i, i + vect.size() / 10));
	
	int thread_sum = 0;
	for (std::future<int>& elem: futures)
		thread_sum += elem.get();

	assert(sum(vect, 0, vect.size()) == thread_sum);
	return 0;
}
