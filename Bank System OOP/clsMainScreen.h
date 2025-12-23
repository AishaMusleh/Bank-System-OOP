#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUserScreen.h"
#include "clsLogInRegisterScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueOption {
		ShowListClient = 1,
		AddNewClients = 2,
		DeleteClient = 3,
		Update_Client = 4,
		FindClient = 5,
		TransActions = 6,
		ManageUsers = 7,
		LogInRegister = 8,
		LogOut = 9
	};

	static void _GoBackToMainMenue() {
		cout << "\n\nPress any key to go back to Main Menue...";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowClientsListScreen() {
		clsClientListScreen::ShowClientsList();
	}

	static void _AddNewClientsScreen() {
		clsAddNewClientScreen::AddClient();
	}

	static void _DeleteClientScreen() {
		clsDeleteClient::DeleteClient();
	}

	static void _UpdateClientScreen() {
		clsUpdateClientScreen::UpdateClient();
	}

	static void _FindClientScreen() {
		clsFindClientScreen::FindCLient();
	}

	static void _TransActionsScreen() {
		clsTransactionScreen::ShowTransactionMenue();
	}

	static void _ManageUserScreen() {
		clsManageUserScreen::ShowManageUserScreen();
	}

	static void _LoginRegisterScreen() {
		clsLogInRegisterScreen::ShowLogInRegisterScreen();
	}

	static void _LogOutScreen() {
		CurrentUser = clsBankUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOption choose) {
		switch (choose)
		{
		case enMainMenueOption::ShowListClient:
			system("cls");
			_ShowClientsListScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::AddNewClients:
			system("cls");
			_AddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::DeleteClient:
			system("cls");
			_DeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::Update_Client:
			system("cls");
			_UpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::FindClient:
			system("cls");
			_FindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::TransActions:
			system("cls");
			_TransActionsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::ManageUsers:
			system("cls");
			_ManageUserScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::LogInRegister:
			system("cls");
			_LoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOption::LogOut:
			system("cls");
			_LogOutScreen();
			break;
		default:
			break;
		}
	}

	static short _ReadMainMenueOption() {
		short choose = clsInputValidate::ReadshortNumberBetween(1, 9, "Please Enter Number Between 1->9 : ");
		return choose;
	}

public:

	static void ShowMainMenue() {

		system("cls");

		_DrawScreenHeader("Main Screen");

		cout << "====================================\n";
		cout << "\tMain Menue\n";
		cout << "====================================\n";
		cout << "\t[1] Show Clients List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] LogIn Register.\n";
		cout << "\t[9] LogOut.\n";
		cout << "====================================\n";

		_PerformMainMenueOption((enMainMenueOption)_ReadMainMenueOption());

	}

};

