#include "Employee.h"

Employee::Employee(int id, string name, int deptID) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptID;
}

void Employee::showInfo() {
	cout << "���u�s��: " << this->m_Id
		<< "\t�m�W: " << this->m_Name
		<< "\t¾��: " << this->getDeptName() << endl;

}

string Employee::getDeptName() {
	return "���u";
}