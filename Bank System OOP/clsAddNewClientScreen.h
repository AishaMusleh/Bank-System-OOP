#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client) {
		Client.FirstName = clsInputValidate::ReadString("Enter the First Name: ");
		Client.LastName = clsInputValidate::ReadString("Enter the Last Name: ");
		Client.Email = clsInputValidate::ReadString("Enter the Email: ");
		Client.Phone = clsInputValidate::ReadString("Enter the Phone: ");
		Client.PinCode = clsInputValidate::ReadString("Enter the PinCode: ");
		Client.Balance = clsInputValidate::ReadDoubleNumber("Enter the Balance: ");
	}

	static void _Print(clsBankClient& Client) {
		cout << "\nClient Card     : " << endl;
		cout << "---------------------------------";
		cout << "\nFirst Name      : " << Client.FirstName;
		cout << "\nLast Name       : " << Client.LastName;
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nEmail           : " << Client.Email;
		cout << "\nPhone           : " << Client.Phone;
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nPinCode         : " << Client.PinCode;
		cout << "\nBalance         : " << Client.Balance;
		cout << "\n---------------------------------" << endl;
	}

public:

	static void AddClient() {

		if (!_GetAccessRight(clsBankUser::pAddClient)) {
			return;
		}

		_DrawScreenHeader("Add New Client Screen");

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("\nEnter the Account Number: ");

		while (clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is exist please enter again: ");
		}

		clsBankClient NewClient = clsBankClient::GetAddNewCLientObject(AccountNumber);

		cout << "\n\nAdd New Client : \n\n";
		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult svResult;
		svResult = NewClient.Save();

		switch (svResult)
		{
		case clsBankClient::enSaveResult::svFiledEmptyObj:
			cout << "\nAdded Filed. :-(\n\n";
			break;
		case clsBankClient::enSaveResult::svFiledAccountNumberExist:
			cout << "\nField Account Number Exist. :-(\n\n";
			break;
		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nAdded Succeeded. :-)\n\n";
			_Print(NewClient);
			break;
		}
	}
};
