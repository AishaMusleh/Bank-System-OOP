#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsTransferLog.h"

class clsTransferScreen : protected clsScreen
{
private:

	static void _Print(clsBankClient& Client) {
		cout << "\nClient Card     : " << endl;
		cout << "---------------------------------";
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nBalance         : " << Client.Balance;
		cout << "\n---------------------------------" << endl;
	}

public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("Transfer Screen");

		string AccountNumber = "";
		char Answer = 'N';
		double amount = 0.0;

		/*==================================================*/

		AccountNumber = clsInputValidate::ReadString("Enter the Account Number To Transfer From: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient ClientFrom = clsBankClient::Find(AccountNumber);
		_Print(ClientFrom);

		/*==================================================*/

		AccountNumber = clsInputValidate::ReadString("Enter the Account Number To Transfer To: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient ClientTo = clsBankClient::Find(AccountNumber);
		_Print(ClientTo);

		/*==================================================*/

		amount = clsInputValidate::ReadNumberBetween(0.0, ClientFrom.Balance, "\n\nEnter Transfer amount :  ", "Amount Exceeds the Balance Please enter again : ");

		cout << "\n\nAre you sure you want to Transfer this amount Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			ClientFrom.Transfer(amount, ClientTo);
			cout << "\nTransfer done Successfully. :-)\n\n";
			clsTransferLog NewTransferLog = clsTransferLog(clsDate::GetSystemDateString(), ClientFrom.AccountNumber(), ClientTo.AccountNumber(), amount, ClientFrom.Balance, ClientTo.Balance, CurrentUser.UserName);
			NewTransferLog.RegisterTransfer();
			_Print(ClientFrom);
			_Print(ClientTo);
		}

		else {
			cout << "\nTransfer Operation Was Canceled :-( \n\n";
		}

	}
};

