#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankUser.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

	static void _Print(clsBankUser& User) {
		cout << "\nUser Card       : " << endl;
		cout << "---------------------------------";
		cout << "\nFirst Name      : " << User.FirstName;
		cout << "\nLast Name       : " << User.LastName;
		cout << "\nFull Name       : " << User.FullName();
		cout << "\nEmail           : " << User.Email;
		cout << "\nPhone           : " << User.Phone;
		cout << "\nUser Name       : " << User.UserName;
		cout << "\nPassword        : " << User.Password;
		cout << "\nPermission      : " << User.Permission;
		cout << "\n---------------------------------" << endl;
	}

public:

	static void DeleteUserScreen() {
		_DrawScreenHeader("Delete User Screen");

		char Answer;
		string UserName = "";
		UserName = clsInputValidate::ReadString("\nEnter the User Name: ");

		while (!clsBankUser::IsUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("\nThe User Name Is not exist please enter again: ");
		}

		clsBankUser User = clsBankUser::Find(UserName);
		_Print(User);

		cout << "Are you sure you want to delete this User ? Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			User.Delete();
			cout << "User Deleted Succesfully :-)\n";
			_Print(User);
		}
	}

};

