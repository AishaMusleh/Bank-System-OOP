#pragma once
#include "string.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include"clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen :protected clsScreen
{

private:

	static clsCurrency _FindByCode(string Massage) {

		string CurrencyCode = clsInputValidate::ReadString(Massage);
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency Code Is not Exist ";
			CurrencyCode = clsInputValidate::ReadString("Please Enter again : ");
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;

	}

	static void Convert(clsCurrency CurrencyFrom, clsCurrency CurrencyTo, double Amount) {

		double ConvertingToUSD = CurrencyFrom.ConvertCurrencyToUSD(Amount);

		if (CurrencyFrom.GetCurrencyCode() == "USD") {
			_Print(CurrencyTo, "\n\n\nConverting From USD To " + CurrencyTo.GetCurrencyCode() + " : ");
			cout << Amount << " USD " << " = " << Amount * CurrencyTo.GetRate() << " " << CurrencyTo.GetCurrencyCode();
		}
		else if (CurrencyTo.GetCurrencyCode() != "USD") {

			_Print(CurrencyFrom, "\nConvert From   : ");
			cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = " << ConvertingToUSD << " USD ";
			_Print(CurrencyTo, "\n\n\nConverting From USD To " + CurrencyTo.GetCurrencyCode());
			cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = " << CurrencyFrom.ConvertCurrencyToAnother(Amount, CurrencyTo) << " " << CurrencyTo.GetCurrencyCode();
		}
		else {
			_Print(CurrencyFrom, "\nConvert From   : ");
			cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = " << ConvertingToUSD << " " << CurrencyTo.GetCurrencyCode();
		}
	}

	static void _Print(clsCurrency& Currency, string Title) {
		cout << Title << endl;
		cout << "---------------------------------";
		cout << "\nCountry      : " << Currency.GetCountryName();
		cout << "\nCode         : " << Currency.GetCurrencyCode();
		cout << "\nName         : " << Currency.GetCurrencyName();
		cout << "\nRate/(1$)    = " << Currency.GetRate();
		cout << "\n---------------------------------" << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen() {

		char Answer = 'Y';

		while (toupper(Answer) == 'Y') {

			system("cls");

			clsScreen::_DrawScreenHeader("Calculator Currency Screen");

			clsCurrency CurrencyFrom = _FindByCode("\nPlease Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _FindByCode("\nPlease Enter Currency2 Code: ");

			double Amount = clsInputValidate::ReadDoubleNumber("\nEnter Amount To Exchange : ");

			Convert(CurrencyFrom, CurrencyTo, Amount);

			cout << "\n\n\nDo you want to perform another calcolation Y/N ? ";
			cin >> Answer;
		}

	}
};

