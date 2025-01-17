#pragma once

#include "Common.h"

// Staff
struct StaffInfo
{
	char id[11], name[51], password[51], position[31], email[51], contactNo[12], recoveryPasswordAns[3][31];
	Date dateJoined;
};

int StaffLogin(char id[], char name[]);
void StaffPasswordRecovery(struct StaffInfo currentStaff[], int nStaff);
void StaffChangePassword(char id[]);
void StaffMenu();
void StaffAdd(struct StaffInfo currentStaff[], int nStaff);
void StaffDisplay(struct StaffInfo staff[], int nStaff);
void StaffSearch(struct StaffInfo staff[], int nStaff);
void StaffModify(struct StaffInfo staff[], int nStaff);
void StaffDelete(struct StaffInfo staff[], int nStaff);
void StaffReport();
void StaffIDPrompt(char staffID[]);
void StaffNamePrompt(char staffName[]);
void StaffPositionPrompt(char position[]);
void StaffJoinDatePrompt(int* dd, int* mm, int* yyyy);
void StaffEmailPrompt(char email[]);
void StaffContactNumPrompt(char no[]);
void passwordPrompt(char staffPassword[]);
void StaffInfoPrintf(struct StaffInfo staff);