#include "Manager.h"

Manager::Manager(int id, string name, int deptID) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptID;
}

void Manager::showInfo() {
	cout << "員工編號: " << this->m_Id
		<< "\t姓名: " << this->m_Name
		<< "\t職位: " << this->getDeptName() << endl;

}

string Manager::getDeptName() {
	return "經理";
}