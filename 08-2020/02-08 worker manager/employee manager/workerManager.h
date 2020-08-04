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

	//顯示菜單
	void show_Menu();

	// 0. 退出
	void exitSystem();

	// 1. 增加員工
	void add_Emp();

	// 儲存新員工到txt中
	void save();

	// 2. 顯示員工
	void show_Emp();

	// 3. 刪除員工
	void del_Emp();

	// 檢查txt文件內是否有該員工
	int emp_IsExist(int id);

	// 4. 修改員工信息
	void mod_Emp();

	// 5. 查找員工
	void find_Emp();

	// 6. 將員工排序 (根據員工編號)
	void sort_Emp();

	// 7. 清空txt文檔
	void clean_File();

	//現有員工數量
	int m_EmpNum;

	//員工數組
	Worker** m_EmpArray;

	//檢查txt文件是否為空
	bool m_FileIsEmpty;

	//檢查txt文件內員工數量
	int get_EmpNum();

	//獲取txt文件內員工信息
	void init_Emp();
};
