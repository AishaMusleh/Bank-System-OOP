#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include"clsInputValidate.h"
#include "clsBankUser.h"

class clsFindClientScreen : protected clsScreen
{
private:

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

	static void FindCLient() {

		if (!_GetAccessRight(clsBankUser::pFindClient)) {
			return;
		}

		clsScreen::_DrawScreenHeader("Find Client Screen");

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("Enter the Account Number: ");

		if (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nClient Is not Found :-(.\n";
		}
		else {
			cout << "\nClient Found :-).\n\n";
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_Print(Client);
		}
	}
};

