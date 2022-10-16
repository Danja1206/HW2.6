#include <iostream>
#include "Task1.h";
#include "Task2.h";
#include "Task3.h";

using namespace std;

void L1()
{

	const size_t countThreads = 10;

	vector<thread> threads;
	threads.reserve(countThreads);

	for (size_t i = 0; i < countThreads; i++)
	{
		threads.emplace_back([=]() {
			cout << "начало потока " << i << " номер потока: " << this_thread::get_id() << std::endl;
			});
	}
	for (auto& i : threads) i.join();

	cout << endl;

	threads.clear();

	for (size_t i = 0; i < countThreads; i++)
	{
		threads.emplace_back([=]() {
			pcout{} << "начало потока " << i << " номер потока: " << this_thread::get_id() << endl;
			});
	}
	for (auto& i : threads) i.join();
	cout << endl;
}

void L2()
{
	int number;
	cin >> number;
	startTasks(number);
}

void L3()
{
	startTasks();
}

int main()
{
	setlocale(0, "rus");

	L1();
	L2();
	L3();

	return 0;
}

