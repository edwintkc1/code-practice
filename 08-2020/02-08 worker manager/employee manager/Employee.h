//普通員工文件
#pragma once
#include <iostream>
#include <string>
#include "Worker.h"
using namespace std;

class Employee : public Worker {
public:
	Employee(int id, string name, int deptID);

	void showInfo();
	string getDeptName();
};