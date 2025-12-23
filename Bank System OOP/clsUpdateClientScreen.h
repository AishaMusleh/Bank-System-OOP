#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
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

	static void UpdateClient() {

		if (!_GetAccessRight(clsBankUser::pUpdateClient)) {
			return;
		}

		clsScreen::_DrawScreenHeader("Update Client Screen");

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("Enter the Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		char Answer = 'N';
		cout << "Are you sure you want update this client : Y/N ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			cout << "\n\nUpdate Client Info : \n\n";
			_ReadClientInfo(Client);

			clsBankClient::enSaveResult svResult;
			svResult = Client.Save();

			switch (svResult)
			{
			case clsBankClient::enSaveResult::svFiledEmptyObj:
				cout << "\nUpdated Filed. :-(\n\n";
				break;
			case clsBankClient::enSaveResult::svSucceeded:
				cout << "\nUpdated Succeeded. :-)\n\n";
				break;
			}
		}
		else {
			return;
		}
	}
};

