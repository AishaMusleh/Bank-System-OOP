#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <string>
#include <fstream>

class clsBankUser : public clsPerson
{
private:

	enum _enMode {
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

	_enMode _Mode;
	string _UserName;
	string _Password;
	short _Permission;
	bool _MarkForDelete = false;

	static clsBankUser _GetEmptyUserObject() {
		return clsBankUser(_enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankUser _ConvertLineToUserObject(string Line, string Separator = "#//#") {
		vector<string> splitLine = clsString::SplitString(Line, Separator);
		return clsBankUser(_enMode::UpdateMode, splitLine[0], splitLine[1], splitLine[2], splitLine[3], splitLine[4], clsUtil::DecryptString(splitLine[5], 4), stod(splitLine[6]));
	}

	static string _ConvertObjectUserToLine(clsBankUser User, string Separator = "#//#") {
		string convertUser = "";
		convertUser += User.FirstName + Separator;
		convertUser += User.LastName + Separator;
		convertUser += User.Email + Separator;
		convertUser += User.Phone + Separator;
		convertUser += User.UserName + Separator;
		convertUser += clsUtil::EncryptString(User.Password, 4) + Separator;
		convertUser += to_string(User.Permission);
		return convertUser;
	}

	static vector<clsBankUser> _LoadUsersInfoFromFile(string FileName = "Users.txt") {
		vector <clsBankUser> vUsers;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersInfoToFile(vector<clsBankUser> vUsers) {
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);//write Mode
		if (MyFile.is_open()) {
			for (clsBankUser U : vUsers) {
				if (U.MarkForDelete == false) {
					string Line = _ConvertObjectUserToLine(U);
					MyFile << Line << endl;
				}
			}
		}
		MyFile.close();
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);//write & append Mode
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _Update() {
		fstream MyFile;
		vector <clsBankUser> vUsers = _LoadUsersInfoFromFile();
		for (clsBankUser& U : vUsers) {
			if (U.UserName == UserName) {
				U = *this;
				break;
			}
		}
		_SaveUsersInfoToFile(vUsers);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertObjectUserToLine(*this));
	}

public:
	clsBankUser(_enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, short Permission)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
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
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermission(short Permission) {
		_Permission = Permission;
	}
	short GetPermission() {
		return _Permission;
	}
	__declspec(property(get = GetPermission, put = SetPermission)) short Permission;

	void SetMarkForDelete(bool MarkForDelete) {
		_MarkForDelete = MarkForDelete;
	}
	bool GetMarkForDelete() {
		return _MarkForDelete;
	}
	__declspec(property(get = GetMarkForDelete, put = SetMarkForDelete)) bool MarkForDelete;


	bool IsEmpty() {
		return (_Mode == _enMode::EmptyMode);
	}

	static clsBankUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}

	static clsBankUser Find(string UserName, string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}

	static bool IsUserExist(string UserName) {
		clsBankUser User = Find(UserName);
		return (!User.IsEmpty());
	}

	static vector<clsBankUser> GetUsersList() {
		return _LoadUsersInfoFromFile();
	}

	enum enSaveResult {
		svFiledEmptyObj = 0,
		svSucceeded = 1,
		svFiledUserNameExist = 2
	};

	enSaveResult Save() {
		switch (_Mode) {
		case _enMode::EmptyMode:
			return enSaveResult::svFiledEmptyObj;
			break;
		case _enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;
		case _enMode::AddNewMode:
			if (clsBankUser::IsUserExist(_UserName)) {
				return enSaveResult::svFiledUserNameExist;
				break;
			}
			else {
				_AddNew();
				_Mode = _enMode::UpdateMode;
				return enSaveResult::svSucceeded;
				break;
			}
		}
	}

	static clsBankUser GetAddNewUserObject(string UserName) {
		return clsBankUser(_enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete() {
		vector<clsBankUser> vUsers;
		vUsers = _LoadUsersInfoFromFile();

		for (clsBankUser& U : vUsers) {
			if (U.UserName == UserName)
				U.MarkForDelete = true;
		}
		_SaveUsersInfoToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static 	enum enPermission {
		pAll = -1,
		pShowClient = 1,
		pAddClient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransaction = 32,
		pManage = 64,
		pShowLogRegister = 128
	};

	bool CheakAccessPermission(enPermission Permission) {
		if (this->Permission == enPermission::pAll)
			return true;
		if ((Permission & this->Permission) == Permission)
			return true;
		return false;
	}

};

