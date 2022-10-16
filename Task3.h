#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <thread>
#include <future>

using namespace std;

vector<int> items;

void Owner()
{
	this_thread::sleep_for(1000ms);
	srand(time(0));
	items.push_back(1 + rand() % (30 - 1 + 1));
	for (auto i : items)
		cout << i << " ";
	cout << endl;

	Owner();
}

void Thief()
{
	this_thread::sleep_for(500ms);
	auto max = max_element(items.begin(), items.end());
	if (items.size() > 2)
	{
		items.erase(max);
		for (auto i : items)
			cout << i << " ";
		cout << endl;
	}

	Thief();
}

void startTasks()
{
	auto firstTask = async(
		[]() {
			Owner();
		}
	);

	auto secondTask = async(
		[]() {
			Thief();
		}
	);
}