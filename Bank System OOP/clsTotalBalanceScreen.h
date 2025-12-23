#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTotalBalanceScreen : clsScreen
{
private:

	static void _PrintBalanceInfo(clsBankClient client) {
		cout << "| " << setw(20) << left << client.AccountNumber();
		cout << "| " << setw(25) << left << client.FullName();
		cout << "| " << setw(20) << left << client.Balance << endl;
	}

public:

	static void ShowTotalBalance() {

		vector <clsBankClient> Clients = clsBankClient::GetClientsList();
		double TotalBalance = clsBankClient::GetTotalBalance();

		_DrawScreenHeader("Total Balance Screen", "(" + to_string(Clients.size()) + ") Client (s).");

		cout << "\n----------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(20) << left << "Account Number";
		cout << "| " << setw(25) << left << "Client Name";
		cout << "| " << setw(20) << left << "Balance";
		cout << "\n----------------------------------------------------------------------------------------------\n";

		if (Clients.size() == 0) {
			cout << "\t\t\tNo Clients Record yet !!";
		}
		else {
			for (clsBankClient C : Clients) {
				_PrintBalanceInfo(C);
			}
		}
		cout << "\n----------------------------------------------------------------------------------------------\n";
		cout << "\t\t\t Total Balance = " << TotalBalance << endl;
		cout << "\t\t\t( " << clsUtil::NumberToText(TotalBalance) << ")" << endl;
	}
};

