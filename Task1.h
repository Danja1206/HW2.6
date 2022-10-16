#pragma once
#include <sstream>
#include <mutex>
#include <iostream>

using namespace std;

mutex coutLock;

class pcout
{
public:
	pcout()
	{
		coutLock.lock();
	}
	~pcout()
	{
		coutLock.unlock();
	}

	template<typename T>
	pcout& operator<<(const T& t)
	{
		cout << t;
		return *this;
	}
	pcout& operator<<(ostream& (*fp)(ostream&))
	{
		cout << fp;
		return *this;
	}
};

