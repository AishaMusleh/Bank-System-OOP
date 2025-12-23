#pragma once
#pragma once
#include "clsString.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class clsTransferLog
{

private:

	string _DateTime;
	string _SourceAccountNumber;
	string _DestinationAccountNumber;
	double _Amount;
	double _SourceBalance;
	double _DestinationBalance;
	string _UserName;

	static clsTransferLog _ConvertLineToTransferLogObject(string Line, string Separator = "#//#") {
		vector<string> splitLine = clsString::SplitString(Line, Separator);
		return clsTransferLog(splitLine[0], splitLine[1], splitLine[2], stod(splitLine[3]), stod(splitLine[4]), stod(splitLine[5]), splitLine[6]);
	}

	static string _ConvertObjectTransferLogToLine(clsTransferLog Transfer, string Separator = "#//#") {
		string convertTransfer = "";
		convertTransfer += Transfer._DateTime + Separator;
		convertTransfer += Transfer._SourceAccountNumber + Separator;
		convertTransfer += Transfer._DestinationAccountNumber + Separator;
		convertTransfer += to_string(Transfer._Amount) + Separator;
		convertTransfer += to_string(Transfer._SourceBalance) + Separator;
		convertTransfer += to_string(Transfer._DestinationBalance) + Separator;
		convertTransfer += Transfer._UserName;
		return convertTransfer;
	}

	static vector<clsTransferLog> _LoadTransferLogInfoFromFile(string FileName = "TransferLog.txt") {
		vector <clsTransferLog> vTransferLog;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsTransferLog TransferLog = _ConvertLineToTransferLogObject(Line);
				vTransferLog.push_back(TransferLog);
			}
			MyFile.close();
		}
		return vTransferLog;
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);//write & append Mode
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertObjectTransferLogToLine(*this));
	}

public:

	clsTransferLog(string DateTime, string SourceAccountNumber, string DestinationAccountNumber, double Amount, double SourceBalance, double DestinationBalance, string UserName) {

		_DateTime = DateTime;
		_SourceAccountNumber = SourceAccountNumber;
		_DestinationAccountNumber = DestinationAccountNumber;
		_Amount = Amount;
		_SourceBalance = SourceBalance;
		_DestinationBalance = DestinationBalance;
		_UserName = UserName;
	}

	string GetDateTime() {
		return _DateTime;
	}

	string GetSourceAccountNumber() {
		return _SourceAccountNumber;
	}

	string GetDestinationAccountNumber() {
		return _DestinationAccountNumber;
	}

	double GetAmount() {
		return _Amount;
	}

	double GetSourceBalance() {
		return _SourceBalance;
	}

	double GetDestinationBalance() {
		return _DestinationBalance;
	}

	string GetUserName() {
		return _UserName;
	}

	static vector<clsTransferLog> GetTransferLogList() {
		return _LoadTransferLogInfoFromFile();
	}

	void RegisterTransfer() {
		_AddNew();
	}

};

