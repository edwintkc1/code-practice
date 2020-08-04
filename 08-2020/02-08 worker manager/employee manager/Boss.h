//Boss¤å¥ó
#pragma once
#include <iostream>
#include <string>
#include "Worker.h"
using namespace std;

class Boss : public Worker {
public:
	Boss(int id, string name, int deptID);

	void showInfo();
	string getDeptName();
};