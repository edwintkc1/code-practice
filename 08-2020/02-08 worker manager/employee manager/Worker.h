#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker {
public:
	//��ܭӤH�H��
	virtual void showInfo() = 0;
	//�������ID
	virtual string getDeptName() = 0;

	//���u�s��
	int m_Id;
	//�m�W
	string m_Name;
	//�����s��
	int m_DeptId;
};