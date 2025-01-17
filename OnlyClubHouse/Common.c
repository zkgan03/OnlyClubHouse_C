#include <stdio.h>
#include <stdlib.h>

#include "Common.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

// Validations
int choiceValidation(char check1[]) {
	int invalid = 0;

	/* If not 1 character, directly rejected;
	If 1 character but not digit, rejected also */
	if (strlen(check1) != 1)
		invalid = 1;
	else if (!isdigit(check1[0]))
		invalid = 1;

	return invalid;
}

int memberIDValidation(char check2[])
{
	int invalid = 0;

	/* If not 5 characters, directly rejected;
	If 5 characters, but:
	- Not start with 'M', rejected;
	- After 'M' are not digits, rejected  */
	if (strlen(check2) != 5)
		invalid = 1;
	else
	{
		if (toupper(check2[0]) != 'M')
			invalid = 1;
		else
			for (int i = 1; i < 5; i++)
			{
				if (!isdigit(check2[i]))
				{
					invalid = 1;
					break;
				}
			}
	}

	return invalid;
}

int genderValidation(char check3[])
{
	int invalid = 0;

	if (strlen(check3) != 1)
		invalid = 1;
	else
	{
		if (check3[0] != 'M' && check3[0] != 'F')
			invalid = 1;
	}

	return invalid;
}

int ICValidation(char check4[])
{
	int invalid = 0;

	/* If not 12 characters, directly rejected;
	If 12 characters, but:
	- Got at least 1 not digit, rejected  */
	if (strlen(check4) != 12)
		invalid = 1;
	else
	{
		for (int i = 0; i < 12; i++)
		{
			if (!isdigit(check4[i]))
			{
				invalid = 1;
				break;
			}
		}
	}

	return invalid;
}

int phoneValidation(char check5[])
{
	int invalid = 0, length;

	/* If not start with 01, directly rejected;
	If start with 011 AND not 11 characters, rejected;
	If not start with 011 AND not 10 characters, rejected;
	If got at least 1 not digit, rejected */
	if (check5[0] != '0' && check5[1] != '1')
		invalid = 1;
	else
	{
		if (check5[2] == '1' && strlen(check5) != 11)
			invalid = 1;
		else if (check5[2] != '1' && strlen(check5) != 10)
			invalid = 1;
		else
		{
			length = (check5[2] == '1') ? 11 : 10;
			for (int i = 0; i < length; i++)
			{
				if (!isdigit(check5[i]))
				{
					invalid = 1;
					break;
				}
			}
		}
	}

	return invalid;
}

int emailValidation(char check6[])
{
	int invalid = 0, alias = 0, dot = 0;

	/* Must start with an alphabet;
	Must have '@' and '.' somewhere;
	'@' must be located before existence of '.';
	Must have alphabet before and after the dot;
	Cannot have any space */
	if (isalpha(check6[0]))
	{
		for (int i = 1; i < strlen(check6); i++)
		{
			if (check6[i] == '@')
			{
				if (dot == 1)
				{
					invalid = 1;
					break;
				}
				alias = 1;
			}
			else if (check6[i] == '.')
			{
				if (!(alias == 1 && isalpha(check6[i - 1]) && isalpha(check6[i + 1])))
				{
					invalid = 1;
					break;
				}
				dot = 1;
			}
			else if (check6[i] == ' ')
			{
				invalid = 1;
				break;
			}
		}
	}
	else
		invalid = 1;

	if (alias == 0 || dot == 0)
		invalid = 1;

	return invalid;
}

int dateValidation(int dd, int mm, int yy)
{
	int invalid = 0;

	// Check year
	if (yy >= 1900 && yy <= 2122)
	{
		// Check month and its respective days
		if (mm >= 1 && mm <= 12)
		{
			if (!(
				((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)) ||
				((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) ||
				((dd >= 1 && dd <= 28) && mm == 2) ||
				(dd == 29 && mm == 2 && yy % 4 == 0)
				))
				invalid = 1;
		}
		else
			invalid = 1;
	}
	else
		invalid = 1;

	return invalid;
}

int FacilityIDValidation(char str1[])
{
	int invalid = 0;

	//if not 3 character, directly rejected; if first 2 charcter is an alphabet and third charcter is a digit, then it is valid; if not, then it is rejected
	if (strlen(str1) == 3)
	{
		if (isalpha(str1[0]) && isalpha(str1[1]) && isdigit(str1[2]))
			invalid = 0;
		else
			invalid = 1;
	}
	else
	{
		invalid = 1;
	}

	return invalid;
}

int OnlyLettersValidation(char str2[])
{
	int invalid = 0, isSpace = 0, isAlpha = 0;

	//if one of the charcter in the string contains a digit or a punctiation, directly rejected
	for (int i = 0; i < strlen(str2); i++)
	{
		if (isdigit(str2[i]) || (ispunct(str2[i])))
			invalid = 1;
		else if (isspace(str2[i]))
			isSpace = 1;
		else
			isAlpha = 1;
	}

	//if the string contains a space but no alphabet, then it is rejected
	(isSpace == 1 && isAlpha == 0) ? invalid = 1 : 0;

	return invalid;
}

int LettersnDigitsValidation(char str3[])
{
	int invalid = 0, isSpace = 0, isAlphaNum = 0;

	//if one of the character in the string contains a pucntuation, directly rejected
	for (int i = 0; i < strlen(str3); i++)
	{
		if ((isalnum(str3[i])))
			isAlphaNum = 1;
		else if (isspace(str3[i]))
			isSpace = 1;
		else
			invalid = 1;
	}

	//if the string contains only space and no alphabet nor digits, then it is rejected
	(isSpace == 1 && isAlphaNum == 0) ? invalid = 1 : 0;

	return invalid;
}

int OnlyDigitsValidation(char str4[])
{
	int invalid = 0;

	//if the string does not contains only digits, then directly rejected
	for (int i = 0; i < strlen(str4); i++)
	{
		if (!(isdigit(str4[i])))
			invalid = 1;
	}

	return invalid;
}

int StaffIDValidation(char ID[])
{
	int invalid = 0;

	//Staff ID must 10char long and include letter in character 3, 4, 5
	if (strlen(ID) != 10 || isalpha(ID[2]) == 0 || isalpha(ID[3]) == 0 || isalpha(ID[4]) == 0) {
		invalid = 1;
	}

	return invalid;
}

int passwordValidation(char password[])
{

	int nSChar = 0, nNum = 0, nLCase = 0, nUCase = 0, invalid = 0;

	for (int i = 0; i < strlen(password); ++i) {

		//count for number of special character
		if ((password[i] >= 32 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126)) {
			++nSChar;
		}

		//count for number of numbers 
		else if (password[i] >= 48 && password[i] <= 57) {
			++nNum;
		}

		//count for number of lowercase letter
		else if (password[i] >= 97 && password[i] <= 122) {
			++nLCase;
		}

		//count for number of uppercase letter
		else if (password[i] >= 65 && password[i] <= 90) {
			++nUCase;
		}
	}

	if (strlen(password) < 8 || nSChar == 0 || nNum == 0 || nLCase == 0 || nUCase == 0) {
		invalid = 1;
	}

	return invalid;
}

int timeValidation(int h, int m) {
	int invalid = 0;

	if (((h > 23) || (h < 0)) || ((m > 59) || (m < 0)))
		invalid = 1;

	return invalid;
}

int BookingIDValidation(char str[])
{
	//check booking ID,ex: 1678
	int invalid = 0;

	if (strlen(str) == 4)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if (isdigit(str[0]) && isdigit(str[1]) && isdigit(str[2]) && isdigit(str[3]))
				invalid = 0;
			else
				invalid = 1;
		}
	}
	else
	{
		invalid = 1;
	}

	return invalid;
}
