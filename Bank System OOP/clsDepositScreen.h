#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositScreen :protected clsScreen
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

	static void DepositScreen() {

		_DrawScreenHeader("Deposit Screen");

		char Answer = 'N';
		double amount = 0.0;

		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString("Enter the Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nThe Account Number Is not exist please enter again: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		amount = clsInputValidate::ReadDoubleNumber("\n\nPlease enter deposit amount :  ");

		cout << "\n\nAre you sure you want to Deposit this amount Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			Client.Deposit(amount);
			cout << "\nDeposit Succeeded. :-)\n\n";
			cout << "\nNew Balance Is : " << Client.Balance << "\n";

		}
		else {
			cout << "\nDeposit Operation Was Canceled :-( \n\n";
		}

	}
};

