#pragma once
#include "clsString.h"
#include "clsUtil.h"
#include <string>
#include <fstream>

class clsCurrency
{
private:

	enum _enMode {
		EmptyMode = 0, UpdateMode = 1
	};

	_enMode _Mode;
	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(_enMode::EmptyMode, "", "", "", 0);
	}

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {
		vector<string> splitLine = clsString::SplitString(Line, Separator);
		return clsCurrency(_enMode::UpdateMode, splitLine[0], splitLine[1], splitLine[2], stod(splitLine[3]));
	}

	static string _ConvertObjectCurrencyToLine(clsCurrency Currency, string Separator = "#//#") {
		string convertCurrency = "";
		convertCurrency += Currency.GetCountryName() + Separator;
		convertCurrency += Currency.GetCurrencyCode() + Separator;
		convertCurrency += Currency.GetCurrencyName() + Separator;
		convertCurrency += to_string(Currency.GetRate());
		return convertCurrency;
	}

	static vector<clsCurrency> _LoadCurrencysInfoFromFile(string FileName = "Currencies.txt") {
		vector <clsCurrency> vCurrencys;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencys.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencys;
	}

	static void _SaveCurrencysInfoToFile(vector<clsCurrency> vCurrencys) {
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);//write Mode
		if (MyFile.is_open()) {
			for (clsCurrency U : vCurrencys) {
				string Line = _ConvertObjectCurrencyToLine(U);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}

	void _Update() {
		fstream MyFile;
		vector <clsCurrency> vCurrencys = _LoadCurrencysInfoFromFile();
		for (clsCurrency& U : vCurrencys) {
			if (U.GetCurrencyCode() == GetCurrencyCode()) {
				U = *this;
				break;
			}
		}
		_SaveCurrencysInfoToFile(vCurrencys);
	}


public:

	clsCurrency(_enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, double Rate)
	{
		_Mode = Mode;
		_CountryName = CountryName;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountryName() {
		return _CountryName;
	}

	string GetCurrencyCode() {
		return _CurrencyCode;
	}

	string GetCurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(double Rate) {
		_Rate = Rate;
		_Update();
	}
	double GetRate() {
		return _Rate;
	}


	bool IsEmpty() {
		return (_Mode == _enMode::EmptyMode);
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.GetCurrencyCode() == clsString::CabitalAllLetter(CurrencyCode)) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
			return _GetEmptyCurrencyObject();
		}
	}

	static clsCurrency FindByCountry(string CountryName) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::CabitalAllLetter(Currency.GetCountryName()) == clsString::CabitalAllLetter(CountryName)) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
			return _GetEmptyCurrencyObject();
		}
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrencysList() {
		return _LoadCurrencysInfoFromFile();
	}

	double ConvertCurrencyToUSD(double Amount) {
		return (Amount / GetRate());
	}

	double ConvertCurrencyToAnother(double Amount, clsCurrency CurrencyTo) {
		double Converting = ConvertCurrencyToUSD(Amount);
		return (Converting * CurrencyTo.GetRate());
	}

};

