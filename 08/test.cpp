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

std::string foo4(std::string s1, std::string s2) {
    return s1 + s2;
}

void TestWork() {
	ThreadPool pool(2);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	task2.get();
}

void TestStrings() {
	ThreadPool pool(3);
	std::vector<std::future<std::string>> new_futures;
	new_futures.push_back(pool.exec(foo4, "str1", "str2"));
	new_futures.push_back(pool.exec(foo4, "str3", "str4"));
	std::string first = new_futures[0].get();
	std::string second = new_futures[1].get();
    new_futures.push_back(pool.exec(foo4, first, second));
    assert(new_futures[2].get() =="str1str2str3str4");
}

int main() {
	TestWork();
	TestStrings();

	ThreadPool new_pool(10);
	std::vector<int> vect(1000000, 1);
	std::vector<std::future<int>> futures;

	for (size_t i = 0; i < vect.size(); i += vect.size() / 10)
		futures.push_back(new_pool.exec(sum, vect, i, i + vect.size() / 10));

	int thread_sum = 0;
	for (std::future<int>& elem: futures)
		thread_sum += elem.get();

	assert(sum(vect, 0, vect.size()) == thread_sum);
}
