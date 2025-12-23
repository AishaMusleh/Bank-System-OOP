#pragma once
#include "clsScreen.h"
#include "clsTransferLog.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferRecordInfo(clsTransferLog TransferRecord) {
		cout << "| " << setw(20) << left << TransferRecord.GetDateTime();
		cout << "| " << setw(10) << left << TransferRecord.GetSourceAccountNumber();
		cout << "| " << setw(10) << left << TransferRecord.GetDestinationAccountNumber();
		cout << "| " << setw(10) << left << TransferRecord.GetAmount();
		cout << "| " << setw(10) << left << TransferRecord.GetSourceBalance();
		cout << "| " << setw(10) << left << TransferRecord.GetDestinationBalance();
		cout << "| " << setw(10) << left << TransferRecord.GetUserName() << endl;
	}

public:

	static void ShowTransferLogScreen() {

		vector <clsTransferLog> TransfersLog = clsTransferLog::GetTransferLogList();

		_DrawScreenHeader("Transfer Log Screen", "( " + to_string(TransfersLog.size()) + " ) Record(s).");
		cout << "\n----------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(20) << left << "Date/Time";
		cout << "| " << setw(10) << left << "s.Account";
		cout << "| " << setw(10) << left << "d.Account";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(10) << left << "User";
		cout << "\n----------------------------------------------------------------------------------------------\n";

		if (TransfersLog.size() == 0) {
			cout << "\t\t\tNo Transfer Log Record yet !!";
		}
		else {
			for (clsTransferLog T : TransfersLog) {
				_PrintTransferRecordInfo(T);
			}
		}
		cout << "\n----------------------------------------------------------------------------------------------\n";
	}
};

