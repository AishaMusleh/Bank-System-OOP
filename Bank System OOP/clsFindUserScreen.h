#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
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

	static void FindUserScreen() {
		_DrawScreenHeader("Find User Screen");

		string UserName = "";
		UserName = clsInputValidate::ReadString("\nEnter the User Name: ");

		while (!clsBankUser::IsUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("\nThe User Not found please try again: ");
		}

		clsBankUser User = clsBankUser::Find(UserName);
		cout << "User Found :-)\n";
		_Print(User);
	}
};

