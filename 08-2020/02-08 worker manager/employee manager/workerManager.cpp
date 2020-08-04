#include "workerManager.h"

WorkerManager::WorkerManager() {
	this->m_EmpNum = 0;
	this->m_EmpArray = NULL;

	//測試txt文件存不存在，不存在重設各varibales
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//如果txt文件存在，測試是否為空，為空重設所有variables
	char ch;
	ifs >> ch;     //如果為空 eof return true
	if (ifs.eof()) {
		cout << "文件為空!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	this->m_EmpNum = this->get_EmpNum();   //更新員工數量屬性

	//將txt文件中的數據 存放到數組中
	//首先開闢空間
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//存放數據
	this->init_Emp();
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManager::show_Menu() {
	int num = this->get_EmpNum();
	cout << "員工數量為: " << num << endl;
	cout << "********************************************" << endl;
	cout << "*********  歡迎使用員工管理系統！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加員工信息  *************" << endl;
	cout << "*************  2.顯示員工信息  *************" << endl;
	cout << "*************  3.刪除離職員工  *************" << endl;
	cout << "*************  4.修改員工信息  *************" << endl;
	cout << "*************  5.查找員工信息  *************" << endl;
	cout << "*************  6.按照編號排序  *************" << endl;
	cout << "*************  7.清空所有文檔  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "歡迎下次使用\n";
	system("pause");
	exit(0);
}

// 1. 加入新員工
void WorkerManager::add_Emp() { 
	cout << "請輸入增加數量: ";	
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//計算新大小
		int newSize = this->m_EmpNum + addNum;

		//開闢新空間
		Worker** newSpace = new Worker * [newSize];

		//將原空間下資料copy到新空間
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//清理原空間
		delete[] this->m_EmpArray;

		//開始加入新員工
		for (int i = 0; i < addNum; i++) {
			//首先要求用戶輸入員工id,name, dept ID
			int id;
			string name;
			int dSelect;

			cout << "請輸入第 " << i + 1 << " 個員工編號: ";
			cin >> id;
			cout << "請輸入第 " << i + 1 << " 個員工姓名: ";
			cin >> name;
			cout << "請輸入職位: \n";
			cout << "1. 員工\n";
			cout << "2. 經理\n";
			cout << "3. 老闆\n";
			cin >> dSelect;

			//所有數據準備完畢，開始創建worker object
			Worker* worker = NULL;

			//根據輸入的部門選擇創建Employee，Manager，Boss
			switch (dSelect) {
			case 1:  //Employee
				worker = new Employee(id, name, 1);
				break;
			case 2:  //Manager
				worker = new Manager(id, name, 2);
				break;
			case 3:  //Boss
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//worker已經創建完畢，加入到array中
			//當前index = 現在擁有的員工數量+i
			newSpace[ this->m_EmpNum + i ] = worker;
		}

		//更新array的指向
		this->m_EmpArray = newSpace;

		//更新員工數量
		this->m_EmpNum = newSize;

		//提示成功
		cout << "添加" << addNum << "名新員工成功！\n";

		//將file is empty設定為false
		this->m_FileIsEmpty = false;

		//保存員工
		this->save();
	}
	else
	{
		cout << "輸入錯誤，請重新輸入: ";
	}
	system("pause");
	system("cls");

}

//儲存新員工到txt中
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id
			<<" "<< this->m_EmpArray[i]->m_Name
			<<" "<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//檢查txt文件內員工數量
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int empNum = 0;
	string temp;
	while (getline(ifs, temp)) {
		empNum++;
	}

	ifs.close();
	return empNum;
}

//獲取txt文件內員工信息
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int arrIndex = 0;    //員工數組的index

	//創建員工
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		default:
			break;
		}
		//存放到array
		this->m_EmpArray[arrIndex] = worker;
		arrIndex++;
	}
}

// 2 . 顯示員工
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者為空!" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");

}

//檢查txt文件內是否有該員工，沒有return -1
int WorkerManager::emp_IsExist(int id) {
	int index = -1;
	
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
	// index 為該名員工在數組中的index
}

// 3. 刪除員工
// 將後面的員工前移，例如刪除2號，只需將3號及之後的員工覆蓋前面一個
void WorkerManager::del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者為空!" << endl;
	}
	else {
		cout << "請輸入刪除的員工編號: ";
		int id = 0;
		cin >> id;

		int index = this->emp_IsExist(id);  //如果該員工不存在return -1
		if (index != -1) {  //員工存在，顯示其個人信息，並再次詢問
			this->m_EmpArray[index]->showInfo();
			cout << "是否確定刪除? (1. 是  2. 否): ";
			int input = 0;
			cin >> input;
			if (input == 1) {
				for (int i = index; i < this->m_EmpNum - 1; i++) {
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;
				this->save();  //將新array保存到txt
				cout << "刪除成功!" << endl;
			}
			else if (input == 2) {
				system("cls");
				return;
			}

		}
		else
		{
			cout << "刪除失敗，未找到該員工" << endl;
		}
	}
	system("pause");
	system("cls");
}

// 4. 修改員工信息
void WorkerManager::mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者為空!" << endl;
	}
	else {
		cout << "請輸入要修改的員工編號" << endl;
		int id;
		cin >> id;

		int ret = emp_IsExist(id);   //return -1 if the employee does not exists
		if (ret != -1)  // exists
		{
			this->m_EmpArray[ret]->showInfo();
			delete this->m_EmpArray[ret];
			int newId;
			string newName;
			int newDeptId;

			cout << "請輸入新的員工編號: ";
			cin >> newId;
			cout << "請輸入新的姓名: ";
			cin >> newName;
			cout << "請輸入新的部門 (1. 員工  2. 經理  3. 老闆): ";
			cin >> newDeptId;

			Worker* worker = NULL;
			switch (newDeptId) {
			case 1:  //Employee
				worker = new Employee(newId, newName, 1);
				break;
			case 2:  //Manager
				worker = new Manager(newId, newName, 2);
				break;
			case 3:  //Boss
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			//加入到數組中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功! " << endl;
			cout << "新信息為: " << endl;
			this->m_EmpArray[ret]->showInfo();

			//保存到txt
			this->save();

		}
		else
		{
			cout << "此員工不存在! " << endl;
		}

	}
	system("pause");
	system("cls");

}

// 5. 查找員工
void WorkerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者為空!" << endl;
	}
	else {
		cout << "請輸入查找方式: " << endl;
		cout << "1. 員工編號" << endl;
		cout << "2. 員工姓名" << endl;
		int input;
		cin >> input;
		if (input == 1)
		{
			cout << "請輸入員工編號: ";
			int num = 0;
			cin >> num;
			int ret = emp_IsExist(num);
			if (ret != -1)  //查到
			{
				this->m_EmpArray[ret]->showInfo();  //顯示資料
			}
			else
			{
				cout << "編號為" << input << "的員工不存在" << endl;
			}
		}
		else if (input == 2)
		{
			cout << "請輸入員工姓名: ";
			string name;
			cin >> name;
			bool flag = false;   //查到與否的flag

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (name == this->m_EmpArray[i]->m_Name)
				{
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "姓名為" << name << "的員工不存在" << endl;
			}
		}
		else
		{
			cout << "輸入錯誤，請重新輸入" << endl;
			return;
		}
		system("pause");
		system("cls");

	}

}

// 6. 員工排序
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者為空!" << endl;
	}
	else
	{
		cout << "請選擇排序方式: " << endl;
		cout << "1. 按員工編號升序排列" << endl;
		cout << "2. 按員工編號降序排列" << endl;
		
		int select = 0;
		cin >> select;

		if (select == 1) {
			for (int i = 0; i < m_EmpNum - 1; i++) {
				for (int j = 0; j < m_EmpNum - 1 - i; j++) {
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id) {
						swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
					}
				}
			}
		}
		else if (select == 2) {
			for (int i = 0; i < m_EmpNum - 1; i++) {
				for (int j = 0; j < m_EmpNum - 1 - i; j++) {
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id) {
						swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
					}
				}
			}
		}
		cout << "排序成功，結果如下: " << endl;
		this->save();
		this->show_Emp();
	}
}

// 7. 清空txt
void WorkerManager::clean_File()
{
	cout << "是否確認清空?" << endl;
	cout << "1. 是\n2. 否\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		// ios::trunc 是清空文檔
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		// 清空worker ** array
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this ->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功!" << endl;
	}
	else if (select == 2)
	{
		system("pause");
		system("cls");
		this->show_Menu();
	}
	else
	{
		cout << "輸入錯誤，請重新輸入" << endl;
	}
	system("pause");
	system("cls");
}