#include <iostream>
#include "workerManager.h"
using namespace std;

int main() {
	WorkerManager wm;
	int choice = 0;
	while (1) {
		//show menu
		wm.show_Menu();
		cout << "½Ð¿é¤J¿ï¾Ü: ";
		cin >> choice;

		switch (choice) {
		case 0 :
			wm.exitSystem();
			break;
		case 1:
			wm.add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.del_Emp();
			break;
		case 4:
			wm.mod_Emp();
			break;
		case 5:
			wm.find_Emp();
			break;
		case 6:
			wm.sort_Emp();
			break;
		case 7:
			wm.clean_File();
			break;
		default:
			system("cls");
			break;
		}

	}


	system("pause");
	return 0;
}