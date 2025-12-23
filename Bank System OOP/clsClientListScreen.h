#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsBankUser.h"
#include <iomanip>

class clsClientListScreen : protected clsScreen
{
private:

	static void _PrintClientInfo(clsBankClient client) {
		cout << "| " << setw(20) << left << client.AccountNumber();
		cout << "| " << setw(15) << left << client.FullName();
		cout << "| " << setw(10) << left << client.Phone;
		cout << "| " << setw(20) << left << client.Email;
		cout << "| " << setw(10) << left << client.PinCode;
		cout << "| " << setw(10) << left << client.Balance << endl;
	}

public:

	static void ShowClientsList() {

		if (!_GetAccessRight(clsBankUser::pShowClient)) {
			return;
		}

		vector <clsBankClient> Clients = clsBankClient::GetClientsList();

		_DrawScreenHeader("Clients List Screen", "( " + to_string(Clients.size()) + " ) Client(s).");

		cout << "\n----------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(20) << left << "Account Number";
		cout << "| " << setw(15) << left << "Client Name";
		cout << "| " << setw(10) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Pin Code";
		cout << "| " << setw(10) << left << "Balance";
		cout << "\n----------------------------------------------------------------------------------------------\n";

		if (Clients.size() == 0) {
			cout << "\t\t\tNo Clients Record yet !!";
		}
		else {
			for (clsBankClient C : Clients) {
				_PrintClientInfo(C);
			}
		}
		cout << "\n----------------------------------------------------------------------------------------------\n";
	}
};

