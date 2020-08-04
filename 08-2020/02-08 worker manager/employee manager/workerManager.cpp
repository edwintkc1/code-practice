#include "workerManager.h"

WorkerManager::WorkerManager() {
	this->m_EmpNum = 0;
	this->m_EmpArray = NULL;

	//����txt���s���s�b�A���s�b���]�Uvaribales
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		cout << "��󤣦s�b!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�p�Gtxt���s�b�A���լO�_���šA���ŭ��]�Ҧ�variables
	char ch;
	ifs >> ch;     //�p�G���� eof return true
	if (ifs.eof()) {
		cout << "��󬰪�!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	this->m_EmpNum = this->get_EmpNum();   //��s���u�ƶq�ݩ�

	//�Ntxt��󤤪��ƾ� �s���Ʋդ�
	//�����}�P�Ŷ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//�s��ƾ�
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
	cout << "���u�ƶq��: " << num << endl;
	cout << "********************************************" << endl;
	cout << "*********  �w��ϥέ��u�޲z�t�ΡI **********" << endl;
	cout << "*************  0.�h�X�޲z�{��  *************" << endl;
	cout << "*************  1.�W�[���u�H��  *************" << endl;
	cout << "*************  2.��ܭ��u�H��  *************" << endl;
	cout << "*************  3.�R����¾���u  *************" << endl;
	cout << "*************  4.�ק���u�H��  *************" << endl;
	cout << "*************  5.�d����u�H��  *************" << endl;
	cout << "*************  6.���ӽs���Ƨ�  *************" << endl;
	cout << "*************  7.�M�ũҦ�����  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "�w��U���ϥ�\n";
	system("pause");
	exit(0);
}

// 1. �[�J�s���u
void WorkerManager::add_Emp() { 
	cout << "�п�J�W�[�ƶq: ";	
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//�p��s�j�p
		int newSize = this->m_EmpNum + addNum;

		//�}�P�s�Ŷ�
		Worker** newSpace = new Worker * [newSize];

		//�N��Ŷ��U���copy��s�Ŷ�
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�M�z��Ŷ�
		delete[] this->m_EmpArray;

		//�}�l�[�J�s���u
		for (int i = 0; i < addNum; i++) {
			//�����n�D�Τ��J���uid,name, dept ID
			int id;
			string name;
			int dSelect;

			cout << "�п�J�� " << i + 1 << " �ӭ��u�s��: ";
			cin >> id;
			cout << "�п�J�� " << i + 1 << " �ӭ��u�m�W: ";
			cin >> name;
			cout << "�п�J¾��: \n";
			cout << "1. ���u\n";
			cout << "2. �g�z\n";
			cout << "3. ����\n";
			cin >> dSelect;

			//�Ҧ��ƾڷǳƧ����A�}�l�Ы�worker object
			Worker* worker = NULL;

			//�ھڿ�J��������ܳЫ�Employee�AManager�ABoss
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
			//worker�w�g�Ыا����A�[�J��array��
			//��eindex = �{�b�֦������u�ƶq+i
			newSpace[ this->m_EmpNum + i ] = worker;
		}

		//��sarray�����V
		this->m_EmpArray = newSpace;

		//��s���u�ƶq
		this->m_EmpNum = newSize;

		//���ܦ��\
		cout << "�K�[" << addNum << "�W�s���u���\�I\n";

		//�Nfile is empty�]�w��false
		this->m_FileIsEmpty = false;

		//�O�s���u
		this->save();
	}
	else
	{
		cout << "��J���~�A�Э��s��J: ";
	}
	system("pause");
	system("cls");

}

//�x�s�s���u��txt��
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

//�ˬdtxt��󤺭��u�ƶq
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

//���txt��󤺭��u�H��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int arrIndex = 0;    //���u�Ʋժ�index

	//�Ыح��u
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
		//�s���array
		this->m_EmpArray[arrIndex] = worker;
		arrIndex++;
	}
}

// 2 . ��ܭ��u
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�Ϊ̬���!" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");

}

//�ˬdtxt��󤺬O�_���ӭ��u�A�S��return -1
int WorkerManager::emp_IsExist(int id) {
	int index = -1;
	
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
	// index ���ӦW���u�b�Ʋդ���index
}

// 3. �R�����u
// �N�᭱�����u�e���A�Ҧp�R��2���A�u�ݱN3���Τ��᪺���u�л\�e���@��
void WorkerManager::del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�Ϊ̬���!" << endl;
	}
	else {
		cout << "�п�J�R�������u�s��: ";
		int id = 0;
		cin >> id;

		int index = this->emp_IsExist(id);  //�p�G�ӭ��u���s�breturn -1
		if (index != -1) {  //���u�s�b�A��ܨ�ӤH�H���A�æA���߰�
			this->m_EmpArray[index]->showInfo();
			cout << "�O�_�T�w�R��? (1. �O  2. �_): ";
			int input = 0;
			cin >> input;
			if (input == 1) {
				for (int i = index; i < this->m_EmpNum - 1; i++) {
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;
				this->save();  //�N�sarray�O�s��txt
				cout << "�R�����\!" << endl;
			}
			else if (input == 2) {
				system("cls");
				return;
			}

		}
		else
		{
			cout << "�R�����ѡA�����ӭ��u" << endl;
		}
	}
	system("pause");
	system("cls");
}

// 4. �ק���u�H��
void WorkerManager::mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�Ϊ̬���!" << endl;
	}
	else {
		cout << "�п�J�n�ק諸���u�s��" << endl;
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

			cout << "�п�J�s�����u�s��: ";
			cin >> newId;
			cout << "�п�J�s���m�W: ";
			cin >> newName;
			cout << "�п�J�s������ (1. ���u  2. �g�z  3. ����): ";
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

			//�[�J��Ʋդ�
			this->m_EmpArray[ret] = worker;
			cout << "�ק令�\! " << endl;
			cout << "�s�H����: " << endl;
			this->m_EmpArray[ret]->showInfo();

			//�O�s��txt
			this->save();

		}
		else
		{
			cout << "�����u���s�b! " << endl;
		}

	}
	system("pause");
	system("cls");

}

// 5. �d����u
void WorkerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�Ϊ̬���!" << endl;
	}
	else {
		cout << "�п�J�d��覡: " << endl;
		cout << "1. ���u�s��" << endl;
		cout << "2. ���u�m�W" << endl;
		int input;
		cin >> input;
		if (input == 1)
		{
			cout << "�п�J���u�s��: ";
			int num = 0;
			cin >> num;
			int ret = emp_IsExist(num);
			if (ret != -1)  //�d��
			{
				this->m_EmpArray[ret]->showInfo();  //��ܸ��
			}
			else
			{
				cout << "�s����" << input << "�����u���s�b" << endl;
			}
		}
		else if (input == 2)
		{
			cout << "�п�J���u�m�W: ";
			string name;
			cin >> name;
			bool flag = false;   //�d��P�_��flag

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (name == this->m_EmpArray[i]->m_Name)
				{
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "�m�W��" << name << "�����u���s�b" << endl;
			}
		}
		else
		{
			cout << "��J���~�A�Э��s��J" << endl;
			return;
		}
		system("pause");
		system("cls");

	}

}

// 6. ���u�Ƨ�
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�Ϊ̬���!" << endl;
	}
	else
	{
		cout << "�п�ܱƧǤ覡: " << endl;
		cout << "1. �����u�s���ɧǱƦC" << endl;
		cout << "2. �����u�s�����ǱƦC" << endl;
		
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
		cout << "�ƧǦ��\�A���G�p�U: " << endl;
		this->save();
		this->show_Emp();
	}
}

// 7. �M��txt
void WorkerManager::clean_File()
{
	cout << "�O�_�T�{�M��?" << endl;
	cout << "1. �O\n2. �_\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		// ios::trunc �O�M�Ť���
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		// �M��worker ** array
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
		cout << "�M�Ŧ��\!" << endl;
	}
	else if (select == 2)
	{
		system("pause");
		system("cls");
		this->show_Menu();
	}
	else
	{
		cout << "��J���~�A�Э��s��J" << endl;
	}
	system("pause");
	system("cls");
}