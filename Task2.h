#pragma once
#include <queue>
#include <mutex>
#include <iostream>
using namespace std;

mutex mut;
queue<int> data_prime;
condition_variable data_lock;


bool is_prime_rec(int inputValue, int checker)
{
	bool outputValue;
	if (checker == 1 || checker == 0)
		outputValue = true;
	else
		outputValue = ((inputValue % checker) != 0) && is_prime_rec(inputValue, checker - 1);

	return outputValue;
}

bool is_prime(int inputValue)
{
	return is_prime_rec(inputValue, inputValue - 1);
}

int next_prime(int inputValue)
{
	if (is_prime(inputValue + 1))
		return inputValue + 1;
	else
		next_prime(inputValue + 1);
}

int get_prime(int inputValue)
{
	int outputValue;
	if (inputValue == 0)
		return 2;
	else
		return next_prime(get_prime(inputValue - 1));
}

void take_prime(int inputValue)
{
	unique_lock<mutex> lock(mut);
	data_prime.push(get_prime(inputValue));
	data_lock.notify_one();
	lock.unlock();
}

void output_prime()
{
	unique_lock<mutex> lock(mut);
	data_lock.wait(lock, [] {return !data_prime.empty(); });
	int data = data_prime.front();
	data_prime.pop();
	cout << data << endl;
	lock.unlock();
}

void startTasks(int inputValue)
{
	thread t1(take_prime, inputValue);
	thread t2(output_prime);
	t1.join();
	t2.join();
}