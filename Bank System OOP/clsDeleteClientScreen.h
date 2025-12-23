#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsDeleteClient : protected clsScreen
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

	static void DeleteClient() {

		if (!_GetAccessRight(clsBankUser::pDeleteClient)) {
			return;
		}

		clsScreen::_DrawScreenHeader("Delete Client Screen");

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("Enter the Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		char Answer = 'N';
		cout << "Are you sure you want delete this client : Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			Client.Delete();
			_Print(Client);
		}
		else {
			return;
		}
	}
};

