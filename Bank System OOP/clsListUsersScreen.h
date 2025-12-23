#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include <vector>

class clsListUsersScreen : protected clsScreen
{

private:

	static void _ShowTitleUsersList() {
		cout << "\n--------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(15) << left << "User Name";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(25) << left << "Email";
		cout << "| " << setw(15) << left << "Phone";
		cout << "| " << setw(15) << left << "Password";
		cout << "| " << setw(5) << left << "Permission";
		cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	}

	static void _ShowUserListInfo(clsBankUser& User) {

		cout << "| " << setw(15) << left << User.UserName;
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(25) << left << User.Email;
		cout << "| " << setw(15) << left << User.Phone;
		cout << "| " << setw(15) << left << User.Password;
		cout << "| " << setw(5) << left << User.Permission;
	}

public:

	static void ShowListUsersScreen() {

		vector <clsBankUser> Users = clsBankUser::GetUsersList();
		_DrawScreenHeader("List User Screen", "Users List(" + to_string(Users.size()) + ") User(s)");
		_ShowTitleUsersList();

		if (Users.size() == 0)
			cout << "\t\tNo Users Available In this System yet !!\n";
		else {
			for (clsBankUser& U : Users) {
				_ShowUserListInfo(U);
				printf("\n");
			}
		}
		printf("--------------------------------------------------------------------------------------------------------------\n");
	}
};

