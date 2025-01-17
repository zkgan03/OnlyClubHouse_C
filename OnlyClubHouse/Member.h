#pragma once

#include "Common.h"

typedef struct {
	char memID[6], memName[30], memSex, memIC[13], memPhoneNo[12], memEmail[36];
	Date dateJoined;
	Date expiredDate;
} Member;

void memberMenu();
void displayMember(Member member[], int);
void addMember(Member member[], int);
void searchMember(Member member[], int);
void modifyMember(Member member[], int);
void deleteMember(Member member[], int);
void expiredMemberReport(Member member[], int);