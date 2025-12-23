#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class clsLogRegister
{
private:
	
	string _Date;
	string _UserName;
	string _Password;
	short _Permission;

	static string _ConvertRegisterObjectToLine(clsLogRegister Register, string Separator = "#//#") {
		string convertRegister = "";
		convertRegister += Register._Date + Separator;
		convertRegister += Register._UserName + Separator;
		convertRegister += Register._Password + Separator;
		convertRegister += to_string(Register._Permission);
		return convertRegister;
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Registers.txt", ios::out | ios::app);//write & append Mode
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

public:

	clsLogRegister(string Date, string UserName, string Password, short Permission)
	{
		_Date = Date;
		_UserName = UserName;
		_Password = Password;
		_Permission = Permission;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}
	string GetUserName() {
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Balance;

	void SetPermission(short Permission) {
		_Permission = Permission;
	}
	short GetPermission() {
		return _Permission;
	}
	__declspec(property(get = GetPermission, put = SetPermission)) short Permission;

	void AddNewRigister() {
		_AddDataLineToFile(_ConvertRegisterObjectToLine(*this));
	}
};

