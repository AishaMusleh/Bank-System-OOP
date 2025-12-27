#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include"clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	enum enFindOption {
		ByCode = 1,
		ByCountry = 2
	};

	static clsCurrency _FindByCode() {
		string CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static clsCurrency _FindByCountry() {
		string Country = clsInputValidate::ReadString("\nPlease Enter Country Name: ");
		clsCurrency Currency = clsCurrency::FindByCountry(Country);
		return Currency;
	}

	static clsCurrency _PerformCurrencyFindOption(enFindOption choose) {
		switch (choose)
		{
		case enFindOption::ByCode:
			return _FindByCode();
			break;
		case enFindOption::ByCountry:
			return _FindByCountry();
			break;
		default:
			break;
		}
	}

	static short _ReadCurrencyFindOption() {
		short choose = clsInputValidate::ReadshortNumberBetween(1, 2, "Find By: [1] Code or [2] Country ? ");
		return choose;
	}

	static void _Print(clsCurrency& Currency) {
		cout << "\nCurrency Card     : " << endl;
		cout << "---------------------------------";
		cout << "\nCountry      : " << Currency.GetCountryName();
		cout << "\nCode         : " << Currency.GetCurrencyCode();
		cout << "\nName         : " << Currency.GetCurrencyName();
		cout << "\nRate/(1$)    = " << Currency.GetRate();
		cout << "\n---------------------------------" << endl;
	}

public:

	static void FindCurrency() {

		clsScreen::_DrawScreenHeader("Find Currency Screen");

		clsCurrency Currency = _PerformCurrencyFindOption((enFindOption)_ReadCurrencyFindOption());

		if (Currency.IsEmpty()) {
			cout << "\nCurrency Is not Found :-(.\n";
		}
		else {
			cout << "\nCurrency Found :-).\n";
			_Print(Currency);
		}
	}
};

