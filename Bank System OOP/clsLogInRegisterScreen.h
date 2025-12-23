#pragma once
#include "clsScreen.h"
#include "clsLoginRegister.h"

class clsLogInRegisterScreen : protected clsScreen
{

private:

	static void _PrintRegisterInfo(clsLoginRegister Register) {
		cout << "| " << setw(20) << left << Register.GetDateTime();
		cout << "| " << setw(15) << left << Register.GetUserName();
		cout << "| " << setw(10) << left << Register.GetPassword();
		cout << "| " << setw(20) << left << Register.GetPermission() << endl;
	}

public:

	static void ShowLogInRegisterScreen() {

		if (!_GetAccessRight(clsBankUser::pShowLogRegister)) {
			return;
		}

		vector <clsLoginRegister> Registers = clsLoginRegister::GetLoginRegistersList();

		_DrawScreenHeader("LogIn Register Screen", "( " + to_string(Registers.size()) + " ) Register(s).");
		cout << "\n----------------------------------------------------------------------------------------------\n";
		cout << "| " << setw(20) << left << "Date/Time";
		cout << "| " << setw(15) << left << "User Name";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(20) << left << "Permission";
		cout << "\n----------------------------------------------------------------------------------------------\n";

		if (Registers.size() == 0) {
			cout << "\t\t\tNo Registers Record yet !!";
		}
		else {
			for (clsLoginRegister R : Registers) {
				_PrintRegisterInfo(R);
			}
		}
		cout << "\n----------------------------------------------------------------------------------------------\n";
	}
};

