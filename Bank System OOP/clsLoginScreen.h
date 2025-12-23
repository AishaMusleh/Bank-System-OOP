#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsDate.h"
#include "clsMainScreen.h"
#include "clsLoginRegister.h"

class clsLoginScreen :protected clsScreen
{

private:

	static bool _Login() {

		bool LogInFaild = false;
		short LogInFaildTrials = 0;
		string UserName, Password;

		do {
			if (LogInFaild) {
				LogInFaildTrials++;
				printf("\nInvalid UserName/Password!\n\nYou have %d Trials to login\n\n", 3 - LogInFaildTrials);
			}

			if (LogInFaildTrials == 3) {
				printf("\nYou are locked After %d faild Trials \n", LogInFaildTrials);
				return false;
			}

			UserName = clsInputValidate::ReadString("Enter UserName : ");
			Password = clsInputValidate::ReadString("Enter Password : ");
			CurrentUser = clsBankUser::Find(UserName, Password);
			LogInFaild = CurrentUser.IsEmpty();

		} while (LogInFaild && LogInFaildTrials < 3);

		clsLoginRegister NewLogInRegister = clsLoginRegister(clsDate::GetSystemDateString(), CurrentUser.UserName, CurrentUser.Password, CurrentUser.Permission);
		NewLogInRegister.RegisterLogIn();

		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool LoginScreen() {

		system("cls");
		_DrawScreenHeader("Log in Screen");
		return _Login();

	}
};

