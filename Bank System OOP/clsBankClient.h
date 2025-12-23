#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include <fstream>

class clsBankClient : public clsPerson
{
private:

	enum enMode {
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enMode _Mode;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector<string> splitLine = clsString::SplitString(Line, Separator);
		return clsBankClient(enMode::UpdateMode, splitLine[0], splitLine[1], splitLine[2], splitLine[3], splitLine[4], splitLine[5], stod(splitLine[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		string convertClient = "";
		convertClient += Client.FirstName + Separator;
		convertClient += Client.LastName + Separator;
		convertClient += Client.Email + Separator;
		convertClient += Client.Phone + Separator;
		convertClient += Client._AccountNumber + Separator;
		convertClient += Client._PinCode + Separator;
		convertClient += to_string(Client._Balance);
		return convertClient;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsInfoFromFile(string FileName = "Clients.txt") {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveClientsInfoToFile(vector<clsBankClient> vClients) {
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);//write Mode
		if (MyFile.is_open()) {
			for (clsBankClient C : vClients) {
				if (C.MarkForDelete == false) {
					string Line = _ConvertClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}
		}
		MyFile.close();
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);//write & append Mode
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _Update() {
		fstream MyFile;
		vector <clsBankClient> vClients = _LoadClientsInfoFromFile();
		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}
		_SaveClientsInfoToFile(vClients);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double Balance)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetBalance(double Balance) {
		_Balance = Balance;
	}
	double GetBalance() {
		return _Balance;
	}
	__declspec(property(get = GetBalance, put = SetBalance)) double Balance;

	void SetMarkForDelete(bool MarkForDelete) {
		_MarkForDelete = MarkForDelete;
	}
	bool GetMarkForDelete() {
		return _MarkForDelete;
	}
	__declspec(property(get = GetMarkForDelete, put = SetMarkForDelete)) bool MarkForDelete;

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
			return _GetEmptyClientObject();
		}
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
			return _GetEmptyClientObject();
		}
	}

	enum enSaveResult {
		svFiledEmptyObj = 0,
		svSucceeded = 1,
		svFiledAccountNumberExist = 2
	};

	enSaveResult Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResult::svFiledEmptyObj;
			break;
		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResult::svFiledAccountNumberExist;
				break;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
				break;
			}
		}
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewCLientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector<clsBankClient> vClients;
		vClients = _LoadClientsInfoFromFile();

		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == _AccountNumber)
				C.MarkForDelete = true;
		}
		_SaveClientsInfoToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsInfoFromFile();
	}

	static double GetTotalBalance() {
		vector <clsBankClient> Clients = _LoadClientsInfoFromFile();
		double TotalBalance = 0;
		for (clsBankClient C : Clients) {
			TotalBalance += C.Balance;
		}
		return TotalBalance;
	}

	void Deposit(double Amount) {
		_Balance += Amount;
		Save();
	}

	void Withdraw(double Amount) {
		_Balance -= Amount;
		Save();
	}

	void Transfer(double Amount, clsBankClient& DestinationClient) {
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
	}
};

