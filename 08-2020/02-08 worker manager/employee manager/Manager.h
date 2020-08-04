//經理文件
#pragma once
#include <iostream>
#include <string>
#include "Worker.h"
using namespace std;

class Manager : public Worker {
public:
	Manager(int id, string name, int deptID);

	void showInfo();
	string getDeptName();
};