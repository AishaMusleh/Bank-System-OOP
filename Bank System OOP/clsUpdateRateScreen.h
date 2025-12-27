#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include"clsInputValidate.h"

class clsUpdateRateScreen :protected clsScreen
{

private:

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

	static void ShowUpdateRateScreen() {

		clsScreen::_DrawScreenHeader("Update Currency Screen");

		string CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_Print(Currency);

		char Answer = 'N';
		cout << "Are you sure you want update the rate of this Currency : Y/N ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			cout << "\nUpdate Currency Rate:\n__________________________\n";
			double NewRate = clsInputValidate::ReadDoubleNumber("Enter New Rate : ");
			Currency.UpdateRate(NewRate);

			cout << "\n\nCurrency Updated successfully :-) .\n";
			_Print(Currency);
		}

		else {
			return;
		}
	}

};

