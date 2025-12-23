#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

	static void WithdrawScreen() {

		_DrawScreenHeader("Withdraw Screen");

		char Answer = 'N';
		double amount = 0.0;

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("Enter the Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		amount = clsInputValidate::ReadNumberBetween(0.0, Client.Balance, "\n\nPlease enter Withdraw amount :  ", "Amount Exceeds the Balance Please enter again : ");

		cout << "\n\nAre you sure you want to Withdraw this amount Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			Client.Withdraw(amount);
			cout << "\nWithdraw Succeeded. :-)\n\n";
			cout << "\nNew Balance Is : " << Client.Balance << "\n";
		}

		else {
			cout << "\nWithdraw Operation Was Canceled :-( \n\n";
		}
	}
};

