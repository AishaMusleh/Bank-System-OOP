#pragma once
#include "clsString.h"
#include "clsUtil.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class clsLoginRegister
{

private:

	string _DateTime;
	string _UserName;
	string _Password;
	short _Permission;

	static clsLoginRegister _ConvertLineToLoginRegisterObject(string Line, string Separator = "#//#") {
		vector<string> splitLine = clsString::SplitString(Line, Separator);
		return clsLoginRegister(splitLine[0], splitLine[1], clsUtil::DecryptString(splitLine[2], 4), stoi(splitLine[3]));
	}

	static string _ConvertObjectLoginRegisterToLine(clsLoginRegister Rigester, string Separator = "#//#") {
		string convertRigester = "";
		convertRigester += Rigester._DateTime + Separator;
		convertRigester += Rigester._UserName + Separator;
		convertRigester += clsUtil::EncryptString(Rigester._Password, 4) + Separator;
		convertRigester += to_string(Rigester._Permission);
		return convertRigester;
	}

	static vector<clsLoginRegister> _LoadLoginRegistersInfoFromFile(string FileName = "Registers.txt") {
		vector <clsLoginRegister> vLoginRegisters;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsLoginRegister LoginRegister = _ConvertLineToLoginRegisterObject(Line);
				vLoginRegisters.push_back(LoginRegister);
			}
			MyFile.close();
		}
		return vLoginRegisters;
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Registers.txt", ios::out | ios::app);//write & append Mode
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertObjectLoginRegisterToLine(*this));
	}

public:

	clsLoginRegister(string DateTime, string UserName, string Password, short Permission) {

		_DateTime = DateTime;
		_UserName = UserName;
		_Password = Password;
		_Permission = Permission;
	}

	string GetDateTime() {
		return _DateTime;
	}

	string GetUserName() {
		return _UserName;
	}

	string GetPassword() {
		return _Password;
	}

	short GetPermission() {
		return _Permission;
	}

	static vector<clsLoginRegister> GetLoginRegistersList() {
		return _LoadLoginRegistersInfoFromFile();
	}

	void RegisterLogIn() {
		_AddNew();
	}
};

