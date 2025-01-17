#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 99

typedef struct {
	int day, month, year;
} Date;

typedef struct {
	int hour, minute;
} Time;


// Validations
int choiceValidation(char check1[]);
int memberIDValidation(char check2[]);
int genderValidation(char check3[]);
int ICValidation(char check4[]);
int phoneValidation(char check5[]);
int emailValidation(char check6[]);
int dateValidation(int, int, int);
int FacilityIDValidation(char str1[]);
int OnlyLettersValidation(char str2[]);
int LettersnDigitsValidation(char str3[]);
int OnlyDigitsValidation(char str4[]);
void passwordPrompt(char staffPassword[]);
int passwordValidation(char password[]);
int BookingIDValidation(char str[]);
int timeValidation(int h, int m);