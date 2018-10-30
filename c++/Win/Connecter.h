#pragma once

#include <Windows.h>
#include <sstream>
#include <iostream>

using namespace std;

class Connecter
{
private:
	HANDLE port;

protected:
	Connecter();
	~Connecter();

	void write(string msg);

public:
	void connect(int port);
	void close();
};

