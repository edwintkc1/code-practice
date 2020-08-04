#pragma once
#include <iostream>
#include <string>
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager {
public:
	//construtor
	WorkerManager();
	//destructor
	~WorkerManager();

	//��ܵ��
	void show_Menu();

	// 0. �h�X
	void exitSystem();

	// 1. �W�[���u
	void add_Emp();

	// �x�s�s���u��txt��
	void save();

	// 2. ��ܭ��u
	void show_Emp();

	// 3. �R�����u
	void del_Emp();

	// �ˬdtxt��󤺬O�_���ӭ��u
	int emp_IsExist(int id);

	// 4. �ק���u�H��
	void mod_Emp();

	// 5. �d����u
	void find_Emp();

	// 6. �N���u�Ƨ� (�ھڭ��u�s��)
	void sort_Emp();

	// 7. �M��txt����
	void clean_File();

	//�{�����u�ƶq
	int m_EmpNum;

	//���u�Ʋ�
	Worker** m_EmpArray;

	//�ˬdtxt���O�_����
	bool m_FileIsEmpty;

	//�ˬdtxt��󤺭��u�ƶq
	int get_EmpNum();

	//���txt��󤺭��u�H��
	void init_Emp();
};
