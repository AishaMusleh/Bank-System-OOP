#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsBankUser.h"

class clsManageUserScreen : protected clsScreen
{
private:

	enum _enManageUserMenueOption {
		ListUser = 1,
		AddNewUser = 2,
		DeleteUser = 3,
		UpdateUser = 4,
		FindUser = 5,
		MainMenue = 6
	};

	static void _GoBackToTransactionMenue() {
		cout << "\n\nPress any key to go back to Manage User Menue...";
		system("pause>0");
		ShowManageUserScreen();
	}

	static void _ShowListUserScreen() {
		clsListUsersScreen::ShowListUsersScreen();
	}
	static void _AddNewUserScreen() {
		clsAddNewUserScreen::AddNewUserScreen();
	}
	static void _DeleteUserScreen() {
		clsDeleteUserScreen::DeleteUserScreen();
	}
	static void _UpdateUserScreen() {
		clsUpdateUserScreen::UpdateUserScreen();
	}
	static void _FindUserScreen() {
		clsFindUserScreen::FindUserScreen();
	}

	static short _ReadManageUserMenueOption() {
		short choose = clsInputValidate::ReadshortNumberBetween(1, 6, "Please Enter Number Between 1->6 : ");
		return choose;
	}
	static void _PerformManageUserMenueOption(_enManageUserMenueOption choose) {
		switch (choose)
		{
		case clsManageUserScreen::ListUser:
			system("cls");
			_ShowListUserScreen();
			_GoBackToTransactionMenue();
			break;
		case clsManageUserScreen::AddNewUser:
			system("cls");
			_AddNewUserScreen();
			_GoBackToTransactionMenue();
			break;
		case clsManageUserScreen::DeleteUser:
			system("cls");
			_DeleteUserScreen();
			_GoBackToTransactionMenue();
			break;
		case clsManageUserScreen::UpdateUser:
			system("cls");
			_UpdateUserScreen();
			_GoBackToTransactionMenue();
			break;
		case clsManageUserScreen::FindUser:
			system("cls");
			_FindUserScreen();
			_GoBackToTransactionMenue();
			break;
		case clsManageUserScreen::MainMenue:
			break;
		default:
			break;
		}
	}

public:
	static void ShowManageUserScreen() {

		if (!_GetAccessRight(clsBankUser::pManage)) {
			return;
		}

		system("cls");
		_DrawScreenHeader("Manage Users Screen");

		cout << "====================================\n";
		cout << "\tManage Users Menue\n";
		cout << "====================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add New Users.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menue.\n";
		cout << "====================================\n";

		_PerformManageUserMenueOption((_enManageUserMenueOption)_ReadManageUserMenueOption());
	}
};

