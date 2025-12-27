#pragma once
#include "clsScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen :protected clsScreen
{
private:

	enum enCurrencyExchangeMenueOption {
		ListCurrencies = 1,
		FindCurrency = 2,
		UpdateRate = 3,
		CurrencyCalculator = 4,
		MainMenue = 5
	};

	static void _GoBackToTransactionMenue() {
		cout << "\n\nPress any key to go back to Currency Exchange Menue...";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _ListCurrenciesScreen() {
		clsListCurrenciesScreen::ShowListCurrenciesScreen();
	}

	static void _FindCurrencyScreen() {
		clsFindCurrencyScreen::FindCurrency();
	}

	static void _UpdateRateeScreen() {
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _CurrencyCalculatorScreen() {
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOption choose) {
		switch (choose)
		{
		case enCurrencyExchangeMenueOption::ListCurrencies:
			system("cls");
			_ListCurrenciesScreen();
			_GoBackToTransactionMenue();
			break;
		case enCurrencyExchangeMenueOption::FindCurrency:
			system("cls");
			_FindCurrencyScreen();
			_GoBackToTransactionMenue();
			break;
		case enCurrencyExchangeMenueOption::UpdateRate:
			system("cls");
			_UpdateRateeScreen();
			_GoBackToTransactionMenue();
			break;
		case enCurrencyExchangeMenueOption::CurrencyCalculator:
			system("cls");
			_CurrencyCalculatorScreen();
			_GoBackToTransactionMenue();
			break;
		case enCurrencyExchangeMenueOption::MainMenue:
			break;
		default:
			break;
		}
	}

	static short _ReadCurrencyExchangeMenueOption() {
		short choose = clsInputValidate::ReadshortNumberBetween(1, 5, "Please Enter Number Between 1->5 : ");
		return choose;
	}

public:

	static void ShowCurrencyExchangeScreen() {

		system("cls");

		_DrawScreenHeader("Currency Exchange Main Screen");

		cout << "====================================\n";
		cout << "\tCurrency Exchange Menue\n";
		cout << "====================================\n";
		cout << "\t[1] List Currencies.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Rate.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] Main Menue.\n";
		cout << "====================================\n";

		_PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOption)_ReadCurrencyExchangeMenueOption());

	}

};

