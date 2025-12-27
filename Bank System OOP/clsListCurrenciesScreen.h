#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>

class clsListCurrenciesScreen : protected clsScreen
{

private:

	static void _ShowTitleCurrencyList() {
		cout << "\n--------------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(15) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << "\n--------------------------------------------------------------------------------------------------------------\n";
	}

	static void _ShowCurrencyListInfo(clsCurrency& Currency) {

		cout << "| " << left << setw(30) << Currency.GetCountryName();
		cout << "| " << left << setw(15) << Currency.GetCurrencyCode();
		cout << "| " << left << setw(40) << Currency.GetCurrencyName();
		cout << "| " << left << setw(10) << Currency.GetRate();
	}

public:

	static void ShowListCurrenciesScreen() {

		vector <clsCurrency> Currencies = clsCurrency::GetCurrencysList();

		_DrawScreenHeader("List Currencies Screen", "Currencies List(" + to_string(Currencies.size()) + ") Currency(s)");
		_ShowTitleCurrencyList();

		if (Currencies.size() == 0)
			cout << "\t\tNo Currencies Available In this System yet !!\n";
		else {
			for (clsCurrency& C : Currencies) {
				_ShowCurrencyListInfo(C);
				printf("\n");
			}
		}
		printf("--------------------------------------------------------------------------------------------------------------\n");
	}
};

