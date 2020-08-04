#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker {
public:
	//顯示個人信息
	virtual void showInfo() = 0;
	//獲取部門ID
	virtual string getDeptName() = 0;

	//員工編號
	int m_Id;
	//姓名
	string m_Name;
	//部門編號
	int m_DeptId;
};