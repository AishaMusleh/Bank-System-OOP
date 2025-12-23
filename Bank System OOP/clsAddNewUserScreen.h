#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:

	static short _ReadPermissionToSet() {
		char Answer;
		short Permission = 0;

		cout << "Do you want give the user full permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			return -1;

		cout << "\nShow List Clients Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pShowClient;

		cout << "\nAdd Clients Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pAddClient;

		cout << "\nDelete Clients Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pDeleteClient;

		cout << "\nUpdate Clients Info Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pUpdateClient;

		cout << "\nFind Clients Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pFindClient;

		cout << "\nTransactions Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pTransaction;

		cout << "\nManage Users Permission ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pManage;

		cout << "\nShow Log Registers List ? Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission += clsBankUser::enPermission::pShowLogRegister;

		return Permission;
	}

	static void _ReadUserInfo(clsBankUser& User) {
		User.FirstName = clsInputValidate::ReadString("Enter the First Name: ");
		User.LastName = clsInputValidate::ReadString("Enter the Last Name: ");
		User.Email = clsInputValidate::ReadString("Enter the Email: ");
		User.Phone = clsInputValidate::ReadString("Enter the Phone: ");
		User.Password = clsInputValidate::ReadString("Enter the Password: ");
		User.Permission = _ReadPermissionToSet();
	}

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

	static void AddNewUserScreen() {

		_DrawScreenHeader("Add User Screen");
		string UserName = "";
		UserName = clsInputValidate::ReadString("\nEnter the User Name: ");

		while (clsBankUser::IsUserExist(UserName)) {
			UserName = clsInputValidate::ReadString("\nThe User Name Is exist please enter again: ");
		}

		clsBankUser NewUser = clsBankUser::GetAddNewUserObject(UserName);

		cout << "\n\nAdd New User : \n\n";
		_ReadUserInfo(NewUser);

		clsBankUser::enSaveResult svResult;
		svResult = NewUser.Save();

		switch (svResult)
		{
		case clsBankUser::enSaveResult::svFiledEmptyObj:
			cout << "\nAdded Filed. :-(\n\n";
			break;
		case clsBankUser::enSaveResult::svFiledUserNameExist:
			cout << "\nField User Name Exist. :-(\n\n";
			break;
		case clsBankUser::enSaveResult::svSucceeded:
			cout << "\nAdded Succeeded. :-)\n\n";
			_Print(NewUser);
			break;
		}
	}
};
