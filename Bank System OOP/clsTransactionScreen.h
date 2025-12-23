#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsWithdrawScreen.h"
#include "clsBankUser.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionScreen :protected clsScreen
{
private:

	enum enTransactionMenueOption {
		Deposit = 1,
		Withdraw = 2,
		TotalBalance = 3,
		Transfer = 4,
		TransferLog = 5,
		MainMenue = 6
	};

	static void _GoBackToTransactionMenue() {
		cout << "\n\nPress any key to go back to Transaction Menue...";
		system("pause>0");
		ShowTransactionMenue();
	}

	static void _DepositScreen() {
		clsDepositScreen::DepositScreen();
	}

	static void _WithdrawScreen() {
		clsWithdrawScreen::WithdrawScreen();
	}

	static void _TotalBalanceScreen() {
		clsTotalBalanceScreen::ShowTotalBalance();
	}

	static void _TransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}

	static void _TransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionMenueOption(enTransactionMenueOption choose) {
		switch (choose)
		{
		case enTransactionMenueOption::Deposit:
			system("cls");
			_DepositScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionMenueOption::Withdraw:
			system("cls");
			_WithdrawScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionMenueOption::TotalBalance:
			system("cls");
			_TotalBalanceScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionMenueOption::Transfer:
			system("cls");
			_TransferScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionMenueOption::TransferLog:
			system("cls");
			_TransferLogScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionMenueOption::MainMenue:
			break;
		default:
			break;
		}
	}

	static short _ReadTransactionMenueOption() {
		short choose = clsInputValidate::ReadshortNumberBetween(1, 6, "Please Enter Number Between 1->6 : ");
		return choose;
	}

public:

	static void ShowTransactionMenue() {

		if (!_GetAccessRight(clsBankUser::pTransaction)) {
			return;
		}

		system("cls");

		_DrawScreenHeader("Transactions Screen");

		cout << "====================================\n";
		cout << "\tTransactions Menue\n";
		cout << "====================================\n";
		cout << "\t[1] Deposit.\n";
		cout << "\t[2] Withdraw.\n";
		cout << "\t[3] Total Balance.\n";
		cout << "\t[4] Transfer.\n";
		cout << "\t[5] Transfer Log.\n";
		cout << "\t[6] Main Menue.\n";
		cout << "====================================\n";

		_PerformTransactionMenueOption((enTransactionMenueOption)_ReadTransactionMenueOption());

	}
};

