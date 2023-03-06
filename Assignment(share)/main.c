#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<stdbool.h>
#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)
#define SIZE 99

/* Structures */
// Staff
typedef struct {
	int day, month, year;
} Date;

struct StaffInfo
{
	char id[11], name[51], password[51], position[31], email[51], contactNo[12], recoveryPasswordAns[3][31];
	Date dateJoined;
};

// Facility
typedef struct {
	char facStatus[20], maxUsers[20], facRules[100];
} Remarks;

typedef struct {
	char facID[20], facType[20], facDesc[30], facCategory[20], facLocation[20];
	Remarks rem;
} Facilities;

// Member
typedef struct {
	char memID[6], memName[30], memSex, memIC[13], memPhoneNo[12], memEmail[36];
	Date dateJoined;
	Date expiredDate;
} Member;

// Booking
typedef struct {
	int hour, minute;
} Time;

typedef struct {
	char bookingId[10], memberId[10], facilityId[10];
	Date todayDate, bookingDate;
	Time bookingTimeS, bookingTimeE;
} Booking;

// Facility Usage
typedef struct {
	Date usageDate;
	Time t;
	char memberID[6], facilityID[4], facilityName[99], usageType[99];
	int bookingID, checkInHour, checkInMinutes, checkOutHour, checkOutMinutes;
} Usage;


/* Function Declaration */
// Staff Module
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

// Facility Module
void FacilityMenu();
void DisplayFacilitiesRecords(Facilities info[], int nRecords);
void AddFacilitiesRecords(Facilities info[], int nRecords);
void SearchFacilitiesRecords(Facilities info[], int nRecords);
void ModifyFacilitiesRecords(Facilities info[], int nRecords);
void DeleteFacilitiesRecords(Facilities info[], int nRecords);
void ClosedFacilitiesReport(Facilities info[], int nRecords);

// Member Information Module
void memberMenu();
void displayMember(Member member[], int);
void addMember(Member member[], int);
void searchMember(Member member[], int);
void modifyMember(Member member[], int);
void deleteMember(Member member[], int);
void expiredMemberReport(Member member[], int);

// Booking Module
void bookingMenu();
void addBooking();
void searchBooking(Booking book[], int recCount);
void displayBooking(Booking book[], int recCount);
void editBooking(Booking book[], int recCount);
void deleteBooking(Booking book[], int recCount);
void BookingReport(Booking book[], int recCount);

// Facility Usage Module
void FacilityUsageHeader();
void FacilityUsageMenu();
void FacilityUsageDisplay(Usage usage[], int recCount);
void FacilityUsageAdd();
void FacilityUsageSearch(Usage usage[], int recCount);
void FacilityUsageModify(Usage usage[], int recCount);
void FacilityUsageDelete(Usage usage[], int recCount);
void FacilityUsageReport(Usage usage[], int recCount);

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


/* Function Definition */
// Main function
void main()
{
	char mainChoice[50] = "", userID[11], username[51];
	int invalid, temp;

	if (StaffLogin(userID, username) == 1) {
		system("cls");

		FILE* fp = fopen("LoginDetails.txt", "a");

		if (!fp)
		{
			printf("\t< Error! Unable to open LoginDetails.txt file! >");
			printf("\n\nEnter any key to continue......");
			getch();
		}

		//get login time
		time_t summaryTime = time(NULL);
		struct tm loginTime = *localtime(&summaryTime);

		//save the user and login time to the file
		fprintf(fp, "| %-13s | %-20s | %02d/%02d/%4d | %02d:%02d | ", userID, username,
			loginTime.tm_mday, loginTime.tm_mon + 1, loginTime.tm_year + 1900, loginTime.tm_hour, loginTime.tm_min);

		// Infinite loop until user presses 0 to exit this program
		while (1 == 1)
		{
			temp = 0;
			printf("Welcome back! %s\n\n", username);

			printf(
				"0. Exit Program\n"
				"1. Staff Information\n"
				"2. Facility\n"
				"3. Member Information\n"
				"4. Booking\n"
				"5. Facility Usage\n"
				"6. Change Password\n\n"
			);

			printf("Enter your choice (0 to exit) > ");
			scanf(" %[^\n]", mainChoice); ;;

			// Validate for the choice selected
			invalid = choiceValidation(mainChoice);

			system("cls");

			if (invalid != 1)
			{
				switch (atoi(mainChoice))
				{
				case 0:
					temp = 1;
					break;
				case 1:
					StaffMenu();
					break;
				case 2:
					FacilityMenu();
					break;
				case 3:
					memberMenu();
					break;
				case 4:
					bookingMenu();
					break;
				case 5:
					FacilityUsageMenu();
					break;
				case 6:
					StaffChangePassword(userID);
					break;
				default:
					system("cls");
					printf("Please enter only (0 - 6)!\n");
					break;
				}
			}
			else
				printf("Invalid input! Please enter only (0 - 6)!\n");

			if (temp == 1)
			{
				//get logout time
				time_t endTime = time(NULL);
				struct tm logOut = *localtime(&endTime);

				//save the logout time to the file
				fprintf(fp, " %02d:%02d |\n", logOut.tm_hour, logOut.tm_min);

				printf("Program Exited. Thank you for using this program!\n");
				fclose(fp);
				exit(0);
			}
		}
	}
}


// Staff section
int StaffLogin(char id[], char name[]) //Login function
{
	char password[51], staffID[15];
	int nStaff = 0, temp = -1;
	struct StaffInfo staff[100];

	FILE* fp = fopen("staffdata.bin", "rb");

	/*error msg*/
	if (fp == NULL) {
		printf("\n\t< Error! Unable to open staffdata.bin! >");
		printf("\n\nEnter any key to exit......");
		getch();
		exit(-1);
	}

	//count the number of staff && read data into array of structure
	while (fread(&staff[nStaff], sizeof(struct StaffInfo), 1, fp) != 0) {
		++nStaff;
	}

	fclose(fp);

	do {
		system("cls");

		printf(
			"   ___          _ _ _ _             ___             _    _               __           _\n"
			"  / __\\_ _  ___(_) (_) |_ _   _    / __\\ ___   ___ | | _(_)_ __   __ _  / _\\_   _ ___| |_ ___ _ __ ___\n"
			" / _\\/ _` |/ __| | | | __| | | |  /__\\/// _ \\ / _ \\| |/ / | '_ \\ / _` | \\ \\| | | / __| __/ _ \\ '_ ` _ \\\n"
			"/ / | (_| | (__| | | | |_| |_| | / \\/  \\ (_) | (_) |   <| | | | | (_| | _\\ \\ |_| \\__ \\ ||  __/ | | | | |\n"
			"\\/   \\__,_|\\___|_|_|_|\\__|\\__, | \\_____/\\___/ \\___/|_|\\_\\_|_| |_|\\__, | \\__/\\__, |___/\\__\\___|_| |_| |_|\n"
			"                          |___/                                  |___/      |___/\n\n\n\n"
			"                                              S I G N   I N\n"
			"+======================================================================================================+\n"
		);

		if (temp == 0) {
			printf("%39s< PASSWORD OR ID IS WRONG >\n", "");
		}

		//prompt for staff ID
		StaffIDPrompt(staffID);

		//prompt for password
		temp = 0;

		printf(
			"\nEnter Password (Input '9' for password recovery)\n"
			"> "
		);
		rewind(stdin);
		passwordPrompt(password);

		if (strcmp(password, "9") == 0) {
			StaffPasswordRecovery(staff, nStaff); //go to password recovery function
			continue;
		}

		/*compare the id and password in staffdata.bin file*/
		for (int i = 0; i < nStaff; ++i) {

			if (strcmp(staffID, staff[i].id) == 0 && strcmp(password, staff[i].password) == 0) {

				strcpy(id, staff[i].id);
				strcpy(name, staff[i].name);

				temp = 1;

				return 1;
			}
		}
	} while (strcmp(password, "9") == 0 || temp == 0);
}

void StaffChangePassword(char id[]) //change password function
{
	struct StaffInfo staff[100];
	int nStaff = 0;

	FILE* fp = fopen("staffdata.bin", "r+b");

	/*error msg when file is not exist*/
	if (fp == NULL) {
		printf("\n\t< Error! Unable to open staffdata.bin! >\n\n");
		printf("\n\nEnter any key to back......");
		getch();
		return;
	}

	char confirmPass[51];

	/*read data into array of structure*/
	while (fread(&staff[nStaff], sizeof(struct StaffInfo), 1, fp) != 0) {
		++nStaff;
	}

	printf("Change Password\n");
	printf("***************\n\n");


	for (int i = 0; i < nStaff; ++i) {
		/*change password of the staff if id is found*/
		if (strcmp(staff[i].id, id) == 0) {
			do {
				printf("Enter new password > ");
				rewind(stdin);
				passwordPrompt(staff[i].password);

				/*Error msg*/
				if (passwordValidation(staff[i].password) == 1) {
					printf("\n\n\t< THE PASSWORD MUST AT LEAST 8 CHARACTER LONG >");
					printf("\n\t< AT LEAST 1 SPECIAL CHARACTER, 1 NUMBER, 1 UPPERCASE AND 1 LOWERCASE LETTER >\n\n");
					continue; //loop agn becuz no need confirmation password
				}

				printf("\nConfirm the new Password > ");
				passwordPrompt(confirmPass);

				/*comfirmation password*/
				if (strcmp(staff[i].password, confirmPass) != 0)
					printf("\n\n< The confirmation password is not match ! >\n");
			} while (passwordValidation(staff[i].password) == 1 || strcmp(staff[i].password, confirmPass) != 0);
		}
	}

	rewind(fp); //rewind file pointer

	/*rewrite the data into the file*/
	for (int i = 0; i < nStaff; ++i) {
		fwrite(&staff[i], sizeof(struct StaffInfo), 1, fp);
	}

	fclose(fp);

	printf("\n\n< Password Changed Successfully! >\n");
	system("pause");
	system("cls");
}

void StaffPasswordRecovery(struct StaffInfo staff[], int nStaff) //Password Recovery function - question and ans
{
	char ans[3][31], staffID[15], flag = 0, temp;

	system("cls");

	printf(
		"Please answer these following questions in order to reset your password\n"
		"***********************************************************************\n\n"
	);

	printf("Enter your Staff ID > ");
	scanf(" %[^\n]", staffID);

	for (int i = 0; i < nStaff; ++i) {

		if (strcmp(staffID, staff[i].id) == 0) {

			do {
				temp = '\0';

				//Ask 3 question and prompt for ans
				printf("\n1. What was your favorite subject in high school?\nAns > ");
				scanf(" %[^\n]", ans[0]);

				printf("\n2. Where did you go on your favorite vacation as a child?\nAns > ");
				scanf(" %[^\n]", ans[1]);

				printf("\n3. What was your childhood nickname?\nAns > ");
				scanf(" %[^\n]", ans[2]);

				//compare answer with his previous ans
				if (strcmp(ans[0], staff[i].recoveryPasswordAns[0]) == 0 && strcmp(ans[1], staff[i].recoveryPasswordAns[1]) == 0 && strcmp(ans[2], staff[i].recoveryPasswordAns[2]) == 0) {

					//change the staff password to "temp1234"
					strcpy(staff[i].password, "temp1234");

					//save into binary file
					FILE* fp = fopen("staffdata.bin", "wb");

					for (int j = 0; j < nStaff; ++j) {
						fwrite(&staff[j], sizeof(struct StaffInfo), 1, fp);
					}

					fclose(fp);

					//some message
					printf("\n< Your password has changed to \"temp1234\" >\n\n< PLEASE always remember your password! >\n\n");

					system("pause");
				}
				else {
					//Message for wrong ans
					printf("\nSome of the answers are wrong!\n\nTry again? (y = Yes)> ");
					rewind(stdin);
					scanf("%c", &temp);
				}

				system("cls");
			} while (toupper(temp) == 'Y');

			flag = 1;
		}
	}

	//Error message
	if (flag == 0) {
		printf("\n< Please enter a valid Staff ID! >\n\n");
		system("pause");
		system("cls");
	}
}

void StaffMenu() //Staff main interface
{
	int temp, nStaff;
	struct StaffInfo staff[100];
	FILE* fp;

	for (;;) {
		nStaff = 0; //initialize the number of staff = 0

		fp = fopen("staffdata.bin", "rb"); //open and read binary file

		/*error msg when file is not exist*/
		if (fp == NULL) {
			printf("\n\t< Error! Unable to open staffdata.bin! >\n\n");
			printf("\n\nEnter any key to back......");
			getch();
			return;
		}

		/*read data into array of structure*/
		while (fread(&staff[nStaff], sizeof(struct StaffInfo), 1, fp) != 0) {
			++nStaff; //count the number of staff
		}

		fclose(fp); // close file 

		system("cls");

		do {

			printf(
				"Staff Information\n"
				"******************\n\n"
			);

			printf(
				"0. Go Back Main Menu\n"
				"1. Display All Staff\n"
				"2. Add Staff\n"
				"3. Search Staff\n"
				"4. Modify Staff\n"
				"5. Delete Staff\n"
				"6. Staff Log In Report\n\n"
			);

			printf("Enter your choice > ");
			rewind(stdin);
			scanf("%d", &temp);

			system("cls");

			/*Staff menu function*/
			switch (temp) {
			case 0:
				return;
				break;
			case 1:
				StaffDisplay(staff, nStaff);
				break;
			case 2:
				StaffAdd(staff, nStaff);
				break;
			case 3:
				StaffSearch(staff, nStaff);
				break;
			case 4:
				StaffModify(staff, nStaff);
				break;
			case 5:
				StaffDelete(staff, nStaff);
				break;
			case 6:
				StaffReport(staff, nStaff);
				break;
			default:
				system("cls");
				printf("\n\t< PLEASE ENTER A VALID CHOICE! >\n\n");
			}
		} while (temp < 0 || temp > 6);
	}
}

void StaffAdd(struct StaffInfo currentStaff[], int nStaff) //Add staff function
{
	struct StaffInfo addstaff;
	char temp = '\0', ch;
	int count = 0, cont = 0, i;

	FILE* fp;

	do {
		system("cls");

		fp = fopen("staffdata.bin", "wb"); //open file to write binary

		/*Error msg*/
		if (fp == NULL) {
			printf("\t< Error! Unable to open staffdata.bin file! >");
			printf("\n\nEnter any key to back......");
			getch();
			return; //back to staff main function
		}

		printf("Add Staff (Enter \'0\' in \'Staff ID\' to back)\n");
		printf("***********************************************\n\n");

		/*START prompt for staff id(10 char long)*/
		do {
			cont = 0;

			StaffIDPrompt(addstaff.id);

			if (strcmp(addstaff.id, "0") == 0) {

				for (int i = 0; i < nStaff; ++i) {

					fwrite(&currentStaff[i], sizeof(struct StaffInfo), 1, fp); //write back to file, else it will be empty

				}

				fclose(fp);

				return;
			}

			/*prompt agn if the id is already available*/
			for (i = 0; i < nStaff; ++i) {

				if (strcmp(addstaff.id, currentStaff[i].id) == 0) {

					printf("\n\t< THIS ID ALREADY IN USE, PLEASE ENTER A NEW ID >\n\n");
					cont = 1;
					break;
				}
			}
		} while (cont != 0);


		/*START prompt for staff name*/
		StaffNamePrompt(addstaff.name);

		/*START prompt for staff position*/
		StaffPositionPrompt(addstaff.position);

		/*START Prompt for Joined date*/
		StaffJoinDatePrompt(&addstaff.dateJoined.day, &addstaff.dateJoined.month, &addstaff.dateJoined.year);

		/*START prompt for email*/
		StaffEmailPrompt(addstaff.email);

		/*START prompt for contact no (string length = 10/11) (must be numeric)*/
		StaffContactNumPrompt(addstaff.contactNo);

		char confirmPass[51];

		/*START prompt for password*/
		do {
			printf("Enter new password > ");
			rewind(stdin);
			passwordPrompt(addstaff.password);

			/*Error msg*/
			if (passwordValidation(addstaff.password) == 1) {
				printf("\n\n\t< THE PASSWORD MUST AT LEAST 8 CHARACTER LONG >");
				printf("\n\t< AT LEAST 1 SPECIAL CHARACTER, 1 NUMBER, 1 UPPERCASE AND 1 LOWERCASE LETTER >\n\n");
				continue; //loop agn becuz no need confirmation password
			}

			printf("\nConfirm the new Password > ");
			passwordPrompt(confirmPass);

			/*comfirmation password*/
			if (strcmp(addstaff.password, confirmPass) != 0) {
				printf("\n\n\t< The confirmation password is not match ! >\n\n");
			}

		} while (passwordValidation(addstaff.password) == 1 || strcmp(addstaff.password, confirmPass) != 0);
		/*END prompt for password*/


		/*START prompt for the recovery password answers*/
		printf("\n\n\t< Please answer these question carefully! >");
		printf("\n\t< This may help you to retrieve your password! >\n");

		printf("\n1. What was your favorite subject in high school?\nAns > "); //1st ques
		scanf(" %[^\n]", addstaff.recoveryPasswordAns[0]);

		printf("\n2. Where did you go on your favorite vacation as a child?\nAns > "); //2nd ques
		scanf(" %[^\n]", addstaff.recoveryPasswordAns[1]);

		printf("\n3. What was your childhood nickname?\nAns > "); //3rd ques
		scanf(" %[^\n]", addstaff.recoveryPasswordAns[2]);
		/*END prompt for the recovery password answers*/


		/*START write all results into the structure array*/
		currentStaff[nStaff] = addstaff;

		++nStaff; // +1 staff

		for (int i = 0; i < nStaff; ++i) {
			fwrite(&currentStaff[i], sizeof(struct StaffInfo), 1, fp); //Save the structure to the file
		}
		/*END write all results into the structure array*/


		++count; // record added +1

		/*ask whether continue to add record or not*/
		printf("\n\nContinue to add record? (y = yes) > ");
		rewind(stdin);
		scanf("%c", &temp);

	} while (toupper(temp) == 'Y');

	fclose(fp); //close file

	printf("\n\n\t< %d of record added sucessfully.... >", count);

	printf("\n\nEnter any key to back......");
	getch();
}

void StaffDisplay(struct StaffInfo staff[], int nStaff) //display all staff
{
	system("cls");

	printf(
		"\t\t\t\t\t\t\tAll Staff Information\n"
		"\t\t\t\t\t\t\t*********************\n\n"
	);

	printf("\t===========================================================================================================================================\n");
	printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s | %-12s |\n", "Staff ID", "Staff Name", "Position", "Contact Number", "Email", "Date Joined");
	printf("\t===========================================================================================================================================\n");

	//print all the staff details
	for (int i = 0; i < nStaff; ++i) {

		printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s |  %02d/%02d/%4d  |\n", staff[i].id, strupr(staff[i].name), strupr(staff[i].position),
			staff[i].contactNo, staff[i].email, staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);
	}
	printf("\t===========================================================================================================================================\n");

	printf("\n\t< %d results are shown..... >\n\n", nStaff);

	printf("Enter any key to back......");
	getch();
}

void StaffSearch(struct StaffInfo staff[], int nStaff) //search for staff
{
	char staffID[15], staffName[51], cont;
	int temp, flag;

	do {
		strcpy(staffID, "\0");
		strcpy(staffName, "\0");

		temp = 0;
		flag = 0;

		system("cls");

		do {
			/*START Prompt for search method*/
			printf(
				"Search by : \n"
				"***********\n\n"
			);

			printf("0. Back\n1. Staff ID \n2. Staff Name\n\n Enter your choice > ");
			scanf("%d", &temp);

			/*END prompt for search method*/

			system("cls");

			printf(
				"Search Staff Information\n"
				"************************\n\n");

			switch (temp) {
			case 0:
				return;
			case 1:
				/*START prompt for staff id*/
				StaffIDPrompt(staffID);
				if (strcmp(staffID, "0") == 0) {
					return; //return
				}
				break;
			case 2:
				/*START prompt for staff name*/
				StaffNamePrompt(staffName);
				break;
			default:
				printf("\n\t< PLEASE ENTER A VALID CHOICE >\n\n"); //Error msg
			}

		} while (temp != 1 && temp != 2);


		printf("\n\n\t===========================================================================================================================================\n");
		printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s | %-12s |\n", "Staff ID", "Staff Name", "Position", "Contact Number", "Email", "Date Joined");
		printf("\t===========================================================================================================================================\n");

		for (int i = 0; i < nStaff; ++i) {

			/*make the name in structure to uppercase letter*/
			strupr(staff[i].name);

			/*show the staff information prompted*/
			if (strcmp(staff[i].name, staffName) == 0 || strcmp(staff[i].id, staffID) == 0) {

				printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s |  %02d/%02d/%4d  |\n", staff[i].id, staff[i].name, staff[i].position,
					staff[i].contactNo, staff[i].email, staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);

				flag = 1; //set flag to 1 if have result

			}
		}

		/*no results msg*/
		if (flag == 0) {
			printf("\n\t\t< NO RESULTS ! >\n\n");
		}

		printf("\t===========================================================================================================================================\n");

		/*ask whether continue to search record or not*/
		printf("\n\nContinue to search for staff information? (y = yes) > ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');
}

void StaffModify(struct StaffInfo staff[], int nStaff) //Modify staff
{
	struct StaffInfo newInfo;
	int temp, flag = 0;
	char cont, cont2;
	FILE* fp;

	system("cls");


	printf(
		"Modify Staff (Enter \'0\' in \'Staff ID\' to back)\n"
		"**********************************************\n\n"
	);

	/*START propmt for staff id*/
	StaffIDPrompt(newInfo.id);

	if (strcmp(newInfo.id, "0") == 0) {
		return;
	}

	for (int i = 0; i < nStaff; ++i) {

		/*compare the inputted id and structure id*/
		if (strcmp(newInfo.id, staff[i].id) == 0) {

			/*loop to edit same staff*/
			do {
				fp = fopen("staffdata.bin", "wb");

				if (fp == NULL) {
					printf("\n\t< Error! Unable to open staffdata.bin! >\n\n");
					printf("\n\nEnter any key to back......");
					getch();
					return;
				}

				temp = 0;

				/*copy to the new structure*/
				newInfo = staff[i];


				/*START choose Edit part*/
				do {
					system("cls");

					/*show the staff infomation*/
					printf("\nStaff information\n");
					printf("*******************\n\n");
					StaffInfoPrintf(newInfo);


					/*Choose edit part*/
					printf("\nModify / Edit\n");
					printf("*************\n\n");
					printf(
						"0. Back to Staff Main\n1. Staff Name\n2. Staff Position\n3. Staff Joined Date\n4. Staff Email\n"
						"5. Staff Contact Number\n6. All of above\n\nEnter your choice > "
					);
					scanf("%d", &temp);

					printf("\n\n");

					switch (temp) {
					case 0:

						/*Rewrite back to the file*/
						for (int j = 0; j < nStaff; ++j) {

							fwrite(&staff[j], sizeof(struct StaffInfo), 1, fp);

						}

						fclose(fp); //close file

						return;

					case 1:
						StaffNamePrompt(newInfo.name); //prompt for new name
						break;

					case 2:
						StaffPositionPrompt(newInfo.position); //prompt for new position
						break;

					case 3:
						StaffJoinDatePrompt(&newInfo.dateJoined.day, &newInfo.dateJoined.month, &newInfo.dateJoined.year); //prompt for new joined date
						break;

					case 4:
						StaffEmailPrompt(newInfo.email); //prompt for new email 
						break;

					case 5:
						StaffContactNumPrompt(newInfo.contactNo); //prompt for new conjtact no
						break;

					case 6:
						/*Prompt all of above*/
						StaffNamePrompt(newInfo.name);
						StaffPositionPrompt(newInfo.position);
						StaffJoinDatePrompt(&newInfo.dateJoined.day, &newInfo.dateJoined.month, &newInfo.dateJoined.year);
						StaffEmailPrompt(newInfo.email);
						StaffContactNumPrompt(newInfo.contactNo);
						break;

					default:
						printf("\n\t< PLEASE CHOOSE A VALID CHOICE >\n\n"); //Error message

					}
				} while (temp < 0 && temp > 6);

				system("cls");

				/*START show the new staff infomation*/
				printf("\nStaff New information\n");
				printf("**********************\n\n");

				StaffInfoPrintf(newInfo);


				/*Ask to confirm the change*/
				printf("\nAre you sure to save these new information? (y = Yes) > ");
				rewind(stdin);
				scanf("%c", &cont2);


				/*Save the structure back to the file*/
				if (toupper(cont2) == 'Y') {

					staff[i] = newInfo; //copy the new info back to the main structure array

					printf("\n\t< All information changed sucessfully! >\n");

				}
				else {
					printf("\n\t< All changes are discarded >\n");
				}

				/*Rewrite back to the file*/
				for (int j = 0; j < nStaff; ++j) {

					fwrite(&staff[j], sizeof(struct StaffInfo), 1, fp);

				}

				fclose(fp); //close file

				/*ask whether continue to modify/edit same staff record or not*/
				printf("\n\nContinue to modify/edit same staff record? (y = yes) > ");
				rewind(stdin);
				scanf("%c", &cont);

			} while (toupper(cont) == 'Y');

			return;
		}
	}

	if (flag == 0) {
		printf("\n< NO RESULTS ! >\n"); //no results msg

		printf("\n\nEnter any key to back......"); //back to staff main
		getch();
	}
}

void StaffDelete(struct StaffInfo staff[], int nStaff) //delete staff
{
	char staffID[15], cont;
	int flag = 0;
	FILE* fp;

	system("cls");

	printf(
		"Delete Staff (Enter \'0\' to back)\n"
		"********************************\n\n"
	);

	/*START prompt for staff id*/
	StaffIDPrompt(staffID);

	if (strcmp(staffID, "0") == 0) {

		return; //return
	}

	for (int i = 0; i < nStaff; ++i) {

		if (strcmp(staffID, staff[i].id) == 0) {

			fp = fopen("staffdata.bin", "wb");

			if (fp == NULL) {
				printf("\t< Error! Unable to open the file! >"); //error msg
				printf("\n\nEnter any key to back......");
				getch();
			}

			/*START print the staff detail going to deleted*/
			StaffInfoPrintf(staff[i]);

			/*confirm the deletion */
			printf("\n\nAre you sure you want to delete this staff from the record? (y = Yes) > ");
			rewind(stdin);
			scanf("%c", &cont);

			if (toupper(cont) == 'Y') {

				--nStaff; //-1 staff

				/*replace the value by the value after it in array*/
				for (int j = i; j < nStaff; ++j) {

					staff[j] = staff[j + 1];
				}

				printf("\n\t< Delete is completed....... >\n\n");

			}
			else {
				printf("\n\t< Delete discarded....... >\n\n");
			}

			/*rewrite the data into the file*/
			for (int j = 0; j < nStaff; ++j) {

				fwrite(&staff[j], sizeof(struct StaffInfo), 1, fp);

			}

			fclose(fp);  //close file

			printf("\n\nEnter any key to back......");
			getch();
			return; //back to the function
		}
	}

	if (flag == 0) {
		printf("\n< NO RESULTS ! >\n"); //no results msg
		printf("\n\nEnter any key to back......"); //back to staff main
		getch();
	}
}

void StaffReport() //Staff login information reporting
{
	Date date[9999];
	int hour[9999][2], min[9999][2], count = 0, temp;
	char staffName[9999][51], staffID[9999][11], cont;


	FILE* fp = fopen("LoginDetails.txt", "r");

	/*Error msg*/
	if (fp == NULL) {
		printf("\t< Error! Unable to open staffdata.bin file! >");
		printf("\n\nEnter any key to back......");
		getch();
		return; //back to staff main function
	}

	system("cls");

	printf(
		"\t\t\tStaff Log In Details\n"
		"\t\t\t********************\n");

	/*Ignore the heading in file*/
	fscanf(fp,
		"======================================================================\n"
		"| Staff ID | Staff Name | LogIn date | LogIn | LogOut |\n"
		"======================================================================\n");

	/*print heading*/
	printf("\t=======================================================================\n");
	printf("\t| %-13s | %-20s  | %10s | %5s | %6s |\n", "Staff ID", "Staff Name", "LogIn date", "LogIn", "LogOut");
	printf("\t=======================================================================\n");


	/*Read the text file and write the results*/
	while (fscanf(fp, "| %s | %[^|] | %d/%d/%d | %d:%d | %d:%d |\n", &staffID[count], &staffName[count], &date[count].day,
		&date[count].month, &date[count].year, &hour[0][count], &min[0][count], &hour[1][count], &min[1][count]) != EOF)
	{

		for (int i = strlen(staffName[count]) - 1; i >= 0 && isspace(staffName[count][i]); --i) {

			staffName[count][i] = '\0';  //remove the spaces follow by the string

		}

		printf("\t| %-13s | %-20s  | %02d/%02d/%4d | %02d:%02d |  %02d:%02d |\n", staffID[count], strupr(staffName[count]), date[count].day,
			date[count].month, date[count].year, hour[0][count], min[0][count], hour[1][count], min[1][count]);

		++count; //number of results++
	}

	fclose(fp);

	printf("\t=======================================================================\n");
	printf("\n\t < %d results are shown >\n", count);  //show number of results

	char staffIDSearch[15], staffNameSearch[51];
	Date dateSearch;
	int nResults;
	int flag;

	do {
		do {
			nResults = 0;
			strcpy(staffIDSearch, "\0");
			strcpy(staffNameSearch, "\0");
			dateSearch.day = 0;
			dateSearch.month = 0;
			dateSearch.year = 0;

			//filter data
			printf(
				"\n\nFilter data by\n"
				"*****************\n");

			printf(
				"0. Back\n"
				"1. Staff ID\n"
				"2. Staff Name\n"
				"3. LogIn date\n\n"
			);

			printf("Enter your choice > ");
			scanf("%d", &temp);
			printf("\n\n");

			switch (temp) {
			case 0:
				return; // back to staff main
				break;

			case 1:
				StaffIDPrompt(staffIDSearch); // prompt for staff id
				break;
			case 2:
				StaffNamePrompt(staffNameSearch); //prompt for staff name
				break;
			case 3:
				do {
					flag = 0;

					printf("Enter staff login date (dd/mm/yyyy) > ");
					rewind(stdin);

					if (scanf("%d/%d/%d", &dateSearch.day, &dateSearch.month, &dateSearch.year) != 3 || (dateValidation(dateSearch.day, dateSearch.month, dateSearch.year) == 1)) {
						printf("\n\t< PLEASE ENTER A VALID DATE >\n\n"); //error msg
						flag = 1;
					}

				} while (flag == 1); // prompt for staff joined date
				break;

			default:
				printf("\n\t< PLEASE ENTER A VALID CHOICE! >\n");
			}

			system("cls");

		} while (temp < 0 || temp > 3);

		/*print heading*/
		printf("\t=======================================================================\n");
		printf("\t| %-13s | %-20s  | %10s | %5s | %6s |\n", "Staff ID", "Staff Name", "LogIn date", "LogIn", "LogOut");
		printf("\t=======================================================================\n");


		/*compare input with data and print the results*/
		for (int i = 0; i <= count; ++i) {

			if (strcmp(staffIDSearch, staffID[i]) == 0 || strcmp(strupr(staffNameSearch), staffName[i]) == 0 ||
				(dateSearch.day == date[i].day && dateSearch.month == date[i].month && dateSearch.year == date[i].year))
			{

				printf("\t| %-13s | %-20s  | %02d/%02d/%4d | %02d:%02d |  %02d:%02d |\n", staffID[i], staffName[i], date[i].day,
					date[i].month, date[i].year, hour[0][i], min[0][i], hour[1][i], min[1][i]);

				++nResults;
			}
		}

		/*No results info*/
		if (nResults == 0) {
			printf("\n\n\t\t< NO RESULTS! >\n");
		}

		printf("\t=======================================================================\n");

		printf("\n\t < %d results are shown >\n", nResults); //show number of results

		/*ask whether continue to search record or not*/
		printf("\n\nContinue to search for staff information? (y = yes) > ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');
}

void StaffIDPrompt(char staffID[]) //prompt for staff id
{
	do {
		strcpy(staffID, "");

		printf("Enter Staff ID > ");
		rewind(stdin);
		scanf("%s", staffID);

		if (strcmp(staffID, "0") == 0) {
			return;
		}

		if (StaffIDValidation(staffID) != 0)
			printf("\n< PLEASE ENTER A VALID STAFF ID >\n"); //Error msg

	} while (StaffIDValidation(staffID) != 0);

}

void StaffNamePrompt(char staffName[]) //prompt for staff name
{
	printf("Enter Staff Name > ");
	scanf(" %[^\n]", staffName);

	//If the last character of staff name is a space, replace it by null
	if (staffName[strlen(staffName) - 1] == ' ') staffName[strlen(staffName) - 1] = '\0';

	strupr(staffName); //make the name inputted to uppercase letter
}

void StaffPositionPrompt(char position[]) //prompt for staff positon
{
	printf("Enter Staff Position > ");
	scanf(" %[^\n]", position);
}

void StaffJoinDatePrompt(int* dd, int* mm, int* yyyy)     // Prompt for Joined date
{
	int flag;

	do {
		flag = 0;

		printf("Enter new staff joined date > ");
		rewind(stdin);

		if (scanf("%d/%d/%d", dd, mm, yyyy) != 3 || (dateValidation(*dd, *mm, *yyyy) == 1)) {
			printf("\n\t< PLEASE ENTER A VALID DATE >\n\n"); //error msg
			flag = 1;
		}

	} while (flag == 1);
}

void StaffEmailPrompt(char email[]) 	// prompt staff email
{
	do {
		printf("Enter Staff Email > ");
		scanf(" %[^\n]", email);

		/*Email Validation and Error msg*/
		if (emailValidation(email) != 0) printf("\n\t< PLEASE ENTER A VALID EMAIL >\n\n");

	} while (emailValidation(email) != 0);

}

void StaffContactNumPrompt(char no[]) 	//prompt for contact number
{
	do {
		printf("Enter Staff Contact number (without '-') > ");
		rewind(stdin);
		scanf(" %[^\n]", no);

		/*Error message*/
		if (phoneValidation(no) != 0) {

			printf("\n\t< PLEASE ENTER A VALID PHONE NUMBER >\n\n");

		}

	} while (phoneValidation(no) != 0);
}

void passwordPrompt(char staffPassword[]) //prompt for password
{
	char ch;
	int i;

	for (i = 0; i < 50 && (ch = getch()) != 13; ++i) { //ASCII value

		//control character
		if ((ch > 0 && ch <= 31) || ch == 127) {
			if (i > 0) {
				if (ch == '\b') {
					printf("\b \b"); //erase the input if user input backspace
					i -= 2; //index -2 to get back to the previous index (eg index 2, 2-2 = 0 +1(in loop so +1) = index 1)
				}
				else --i;
			}
			else --i;
		}
		//arrow key and function key
		else if (ch == -32 || ch == 0) {
			getch(); // arrow gt 2 value
			--i;
		}
		else {

			staffPassword[i] = ch;

			//replace the input by '*'
			printf("*");
		}
	}

	//make the last index of the password == NULL
	staffPassword[i] = '\0';
}

void StaffInfoPrintf(struct StaffInfo staff) //print staff info
{
	printf("\t===========================================================================================================================================\n");
	printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s | %-12s |\n", "Staff ID", "Staff Name", "Position", "Contact Number", "Email", "Date Joined");
	printf("\t===========================================================================================================================================\n");

	printf("\t| %-13s | %-20s | %-20s | %-15s | %-40s |  %02d/%02d/%4d  |\n", staff.id, staff.name, strupr(staff.position),
		staff.contactNo, staff.email, staff.dateJoined.day, staff.dateJoined.month, staff.dateJoined.year);

	printf("\t===========================================================================================================================================\n");

}


// Facility section
void FacilityMenu()
{
	Facilities info[SIZE];
	int invalid = 0, nRecords;
	char subChoice[10], again;
	FILE* fpFacility;

	while (1 == 1)
	{
		nRecords = 0;
		fpFacility = fopen("facilitiyInfo.txt", "r");//open file reading

		if (!fpFacility)
		{
			printf("Error, unable to open the file \"facilitiyInfo.txt\" !");//check for file opening errors
			return;
		}

		// Read data in txt file into array of structure
		while (fscanf(fpFacility, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", info[nRecords].facID, info[nRecords].facType, info[nRecords].facDesc, info[nRecords].facCategory, info[nRecords].facLocation, info[nRecords].rem.facStatus, info[nRecords].rem.maxUsers, info[nRecords].rem.facRules) != EOF)
		{
			nRecords++;
		}

		fclose(fpFacility);//close file

		printf(
			"---------------------------\n"
			"       FACILITY MENU\n"
			"---------------------------\n\n"
			"0. Go Back Main Menu\n\n"
			"1. Display All Facilities\n\n"
			"2. Add New Facility\n\n"
			"3. Search Facility\n\n"
			"4. Modify Facility Details\n\n"
			"5. Delete Facility Records\n\n"
			"6. Facility Report\n\n"
		);

		//ask user to choose which function to use
		printf("Enter your choice > ");
		scanf(" %[^\n]", subChoice);
		invalid = choiceValidation(subChoice);//validate the choice selected

		system("cls");

		if (invalid != 1)//will proceed to switch statement if choice is valid
		{
			switch (atoi(subChoice))
			{
			case 0:
				return;
				break;
			case 1:
				DisplayFacilitiesRecords(info, nRecords);//function call
				break;
			case 2:
				AddFacilitiesRecords(info, nRecords);//function call
				nRecords++;
				break;
			case 3:
				SearchFacilitiesRecords(info, nRecords);//function call
				break;
			case 4:
				ModifyFacilitiesRecords(info, nRecords);//function call
				break;
			case 5:
				DeleteFacilitiesRecords(info, nRecords);//function call
				break;
			case 6:
				ClosedFacilitiesReport(info, nRecords);//function call
				break;
			default:
				printf("Please enter only (0 - 6)!\n\n");
				invalid = 1;
				break;
			}

			if (invalid != 1)
			{
				system("pause");
				system("cls");
			}
		}
		else
			printf("Please enter only (0 - 6)!\n\n");
	}
}

void DisplayFacilitiesRecords(Facilities info[], int nRecords)
{
	int totalRecords = 0;

	printf("\n\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	printf("\t\t\t\t\t\t\t\t\t\tF A C I L I T Y     D E T A I L S\n");
	printf("\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n\n");
	printf("\t==============================================================================================================================================================================================\n");
	printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
	printf("\t|| Facility ID |       Type       |      Description      |     Category     |      Venue Location       |    Status    | Users Allowed |               Rules and Regulations               ||\n");
	printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
	printf("\t==============================================================================================================================================================================================\n");



	if (nRecords < 1)
	{
		printf("\n\n\t\t\t\t\t\t\t\t\t\tN O    R E C O R D S    F O U N D\n\n");//show no message if no records are found inside txt file
	}
	else {
		//loop through txt file and display all the records in it
		for (int i = 0; i < nRecords; i++)
		{
			totalRecords++;
			printf("\t||   - %-7s | - %-14s |  - %-18s | - %-14s |  - %-22s |- %-11s |     - %-7s |- %-48s ||\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
			printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
			printf("\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
	}

	printf("\n\n\t<TOTAL OF %d RECORDS SHOWN>\n\n\n", totalRecords);//display the total number of records
}

void AddFacilitiesRecords(Facilities info[], int nRecords)
{
	char confirm;
	int addCount = 0, invalid = 0, sameID = 0, proceed = 0;

	FILE* fpFacility2 = fopen("facilitiyInfo.txt", "a");//open file for appending
	if (fpFacility2 == NULL)
	{
		printf("Error, unable to open the file \"facilitiyInfo.txt\" !");//check for file opening errors
		exit(-1);
	}

	do {
		addCount++;// count the total number of records that is added

		//to read new facility ID
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("FACILITY ID > ");
			rewind(stdin);
			scanf(" %[^\n]", info[nRecords].facID);
			strupr(info[nRecords].facID);//to convert the string entered to uppercase
			system("cls");

			invalid = FacilityIDValidation(info[nRecords].facID);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("\nFacility ID is entered with incorrect format! The ID consist of a 2-letter code and a digit at the back.\n\n\n");

			//to loop through text file and check if the new ID entered is identical with any ID in it
			for (int i = 0; i < nRecords; i++) {
				if (strcmp(info[nRecords].facID, info[i].facID) == 0) {
					printf("THE FACILITY ENTERED MATCHES WITH ANOTHER. PLEASE ENTER AGAIN!\n\n");//if found same id, print warning message
					sameID = 1;
					break;
				}
				else
					sameID = 0;
			}

		} while (invalid == 1 || sameID == 1);//loop will continue if the ID entered is invalid or is identical with another ID
		system("cls");

		//to read new facility type
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("FACILITY TYPE > ");
			scanf(" %[^\n]", info[nRecords].facType);
			strupr(info[nRecords].facType);//to convert the string entered to uppercase
			system("cls");

			invalid = OnlyLettersValidation(info[nRecords].facType);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("Facility Type is entered with incorrect format! It should consists of letters only.\n\n\n");

		} while (invalid == 1);//loop will continue if the type entered is invalid
		system("cls");

		//to read new facility description
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("FACILITY DESCRIPTION > ");
			scanf(" %[^\n]", info[nRecords].facDesc);
			strupr(info[nRecords].facDesc);//to convert the string entered to uppercase
			system("cls");

			invalid = LettersnDigitsValidation(info[nRecords].facDesc);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("Facility Description is entered with incorrect format! It should consists of letters and digits only.\n\n\n");

		} while (invalid == 1);//loop will continue if the description entered is invalid
		system("cls");

		//o read new facility category
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("FACILITY CATEGORY > ");
			scanf(" %[^\n]", info[nRecords].facCategory);
			strupr(info[nRecords].facCategory);//to convert the string entered to uppercase
			system("cls");

			invalid = OnlyLettersValidation(info[nRecords].facCategory);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("Facility Category is entered with incorrect format! It should consists of letters only.\n\n\n");

		} while (invalid == 1);//loop will continue if the category entered is invalid
		system("cls");

		//to read new facility location
		printf("PLEASE ENTER THE DATA BELOW :\n");
		printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

		printf("VENUE LOCATION > ");//prompt and read new facility location
		scanf(" %[^\n]", info[nRecords].facLocation);
		strupr(info[nRecords].facLocation);//to convert the string entered to uppercase
		system("cls");

		//to read new facility status
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("STATUS OF FACILITY > ");
			scanf(" %[^\n]", info[nRecords].rem.facStatus);
			strupr(info[nRecords].rem.facStatus);//to convert the string entered to uppercase
			system("cls");

			invalid = OnlyLettersValidation(info[nRecords].rem.facStatus);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("Status of Facility is entred with incorrect format! It should consists of letters only.\n\n\n");

		} while (invalid == 1);//loop will continue if the status entered is invalid
		system("cls");

		//to read new facility max users
		do {
			printf("PLEASE ENTER THE DATA BELOW :\n");
			printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

			printf("MAXIMUN ALLOWED USERS > ");
			rewind(stdin);
			scanf(" %s", info[nRecords].rem.maxUsers);
			system("cls");

			invalid = OnlyDigitsValidation(info[nRecords].rem.maxUsers);//check for validation

			if (invalid == 1)//if invalid, a warning message is prompted
				printf("Maximum Allowed Users is entred with incorrect format! It should consist of digits only.\n\n\n");

		} while (invalid == 1);//loop will continue if the max users entered is invalid
		system("cls");

		//to read new facility rules
		printf("PLEASE ENTER THE DATA BELOW :\n");
		printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");

		printf("FACILITY RULES (Rule 1, Rule 2, .....) > ");
		scanf(" %[^\n]", info[nRecords].rem.facRules);
		strupr(info[nRecords].rem.facRules);//to convert the string entered to uppercase
		system("cls");

		//to save all the new records in the text file
		fprintf(fpFacility2, "%s, %s, %s, %s, %s, %s, %s, %s\n", info[nRecords].facID, info[nRecords].facType, info[nRecords].facDesc, info[nRecords].facCategory, info[nRecords].facLocation, info[nRecords].rem.facStatus, info[nRecords].rem.maxUsers, info[nRecords].rem.facRules);


		do {
			printf("\nDO YOU WISH TO ADD ANYMORE RECORDS ? (Y/N)  > ");//to ask user if they want to continue to add more records
			rewind(stdin);
			scanf(" %c", &confirm);
			system("cls");

			if (confirm == 'Y' || confirm == 'y')
				proceed = 1;
			else if (confirm == 'N' || confirm == 'n')
				proceed = 0;
			else
				printf("CHOOSE ONLY Y OR N !\n\n");

		} while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');//loop will continue if user entered anything other than y,n,Y,N

	} while (proceed == 1);//loop will continue if user enter y or Y

	printf("\n<%d RECORDS ADDED.>\n\n\n", addCount);//to show the total number of records added

	fclose(fpFacility2);//close file
}

void SearchFacilitiesRecords(Facilities info[], int nRecords)
{
	char facIDSearch[100], facTypeSearch[100], facCategorySearch[100], facStatusSearch[100], searchChoice[20], confirm;
	int invalid = 0, searchRecFound = 0, loopSC = 0, proceed = 0;
	do {
		do {
			do {
				//to reset the searching information to avoid showing the old records when multiples searches are done
				strcpy(facIDSearch, "");
				strcpy(facTypeSearch, "");
				strcpy(facCategorySearch, "");
				strcpy(facStatusSearch, "");

				printf("SELECT A FIELD CODE TO START SEARCHING :\n\n");
				printf("1) FACILITY ID\n\n");
				printf("2) FACILITY TYPE\n\n");
				printf("3) FACILITY CATEGORY\n\n");
				printf("4) STATUS\n\n");
				printf("[ENTER 5 TO RETURN BACK]\n\n");

				//asking user based on what criteria they want to search
				printf("ENTER YOUR CHOICE > ");
				scanf(" %[^\n]", searchChoice);
				invalid = choiceValidation(searchChoice);//validate the choice selected

				system("cls");

				switch (atoi(searchChoice))//changes the number in the string into integer
				{
				case 1:
					do {
						printf("\nENTER FACILITY ID > ");
						scanf(" %[^\n]", facIDSearch);
						strupr(facIDSearch);//to convert the strings entered to uppercase
						invalid = FacilityIDValidation(facIDSearch);//validate ID

						system("cls");
						if (invalid == 1)
							printf("\nFacility ID is entered with incorrect format! The ID consist of a 2-letter code and a digit at the back.\n\n");
						loopSC = 0;
					} while (invalid == 1);//loop will continue if the ID is not in the correct format
					break;
				case 2:
					do {
						printf("\nENTER FACILITY TYPE > ");
						rewind(stdin);
						scanf(" %[^\n]", facTypeSearch);
						strupr(facTypeSearch);//to convert the strings entered to uppercase
						invalid = OnlyLettersValidation(facTypeSearch);//validate Type

						system("cls");
						if (invalid == 1)
							printf("\nFacility Type is entered with incorrect format! It should consists of letters only.\n\n");
						loopSC = 0;
					} while (invalid == 1);//loop will continue if the Type is not in the correct format
					break;
				case 3:
					do {
						printf("\nENTER FACILITY CATEGORY > ");
						scanf(" %[^\n]", facCategorySearch);
						strupr(facCategorySearch);//to convert the strings entered to uppercase
						invalid = OnlyLettersValidation(facCategorySearch);//validate Category

						system("cls");
						if (invalid == 1)
							printf("\nFacility Category is entered with incorrect format! It should consists of letters only.\n\n");
						loopSC = 0;
					} while (invalid == 1);//loop will continue if the Category is not in the correct format
					break;
				case 4:
					do {
						printf("\nENTER STATUS OF FACILITY > ");
						scanf(" %[^\n]", facStatusSearch);
						strupr(facStatusSearch);//to convert the strings entered to uppercase
						invalid = OnlyLettersValidation(facStatusSearch);//validate Status

						system("cls");
						if (invalid == 1)
							printf("\nStatus of Facility is entred with incorrect format! It should consists of letters only.\n\n");
						loopSC = 0;
					} while (invalid == 1);//loop will continue if the Status is not in the correct format
					break;
				case 5:
				{
					printf("GOING BACK TO MENU . . . . .\n\n\n");
					return;//return to main menu
				}
				default:
					printf("CODE NOT IDENTIFIED! PLEASE RE-TYPE CHOICE TO CONTINUE.\n\n");
					loopSC = 1;
					break;
				}

			} while (loopSC != 0);//loop will continue if loopSC is 1

			searchRecFound = 0;

			//loop through txt file
			for (int i = 0; i < nRecords; i++)
			{
				if (strcmp(facIDSearch, info[i].facID) == 0 || strcmp(facTypeSearch, info[i].facType) == 0 || strcmp(facCategorySearch, info[i].facCategory) == 0 || strcmp(facStatusSearch, info[i].rem.facStatus) == 0)
				{
					searchRecFound = 1;
				}
			}
			system("cls");

			if (searchRecFound == 1)
			{
				//display the search result if the record is found in the text file
				printf("\n\t\t\t\t\t\t\t\t\t\t\tS E A R C H  +  R E S U L T S\n\n");
				printf("\t==============================================================================================================================================================================================\n");
				printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
				printf("\t|| Facility ID |       Type       |      Description      |     Category     |      Venue Location       |    Status    | Users Allowed |               Rules and Regulations               ||\n");
				printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
				printf("\t==============================================================================================================================================================================================\n");

				for (int i = 0; i < nRecords; i++)
				{
					if (strcmp(facIDSearch, info[i].facID) == 0 || strcmp(facTypeSearch, info[i].facType) == 0 || strcmp(facCategorySearch, info[i].facCategory) == 0 || strcmp(facStatusSearch, info[i].rem.facStatus) == 0)
					{
						printf("\t||   - %-7s | - %-14s |  - %-18s | - %-14s |  - %-22s |- %-11s |     - %-7s |- %-48s ||\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					}
				}
			}
			else if (searchRecFound == 0)
				printf("\nINCORRECT! THE INFORMATION ENTERED IS NOT IDENTIFIED. PLEASE TRY AGAIN.\n\n");//show incorrect message if no records are found in txt file

		} while (searchRecFound == 0);//loop will repeat if no records are found

		do {
			printf("\nDO YOU WISH TO SEARCH ANYMORE RECORDS ? (Y/N)  > ");//to ask user if they want to continue to search any more records
			rewind(stdin);
			scanf(" %c", &confirm);
			system("cls");

			if (confirm == 'Y' || confirm == 'y')
				proceed = 1;
			else if (confirm == 'N' || confirm == 'n')
				proceed = 0;
			else
				printf("CHOOSE ONLY Y OR N !\n\n");

		} while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');//loop will continue if user entered anything other than y,n,Y,N

	} while (proceed == 1);
}

void ModifyFacilitiesRecords(Facilities info[], int nRecords)
{
	char facIDMod[99], modChoice[10], confirm;
	int invalid = 0, modRecFound = 0, loopCode = 0, sameID = 0, proceed = 0, stopModify = 0;

	Facilities newData;
	FILE* fpFacility3 = fopen("facilitiyInfo.txt", "w");//open file for writing
	if (fpFacility3 == NULL)
	{
		printf("Error, unable to open and read the file \"facilitiyInfo.txt\" !");//check for file opening errors
		exit(-1);
	}

	do {
		do {
			do {
				printf("START MODIFYING DETAILS BY ENTERING THE FACILITY ID :\n");
				printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");
				//Ask users which records they want to modify based on the facility ID
				printf("FACILITY ID > ");
				scanf(" %[^\n]", facIDMod);
				strupr(facIDMod);//to convert the string entered to uppercase

				invalid = FacilityIDValidation(facIDMod);//validate the ID entered
				system("cls");

				if (invalid == 1)//if id invalid, a warning message is prompted
					printf("Facility ID is entered with incorrect format! The ID consist of a 2-letter code and a digit at the back.\n\n");
			} while (invalid == 1);

			modRecFound = 0;

			//loop through all the records in the txt file
			for (int i = 0; i < nRecords; i++)
			{
				if (strcmp(facIDMod, info[i].facID) == 0)
				{
					modRecFound = 1;
					//if the record is found, then display that record
					do {
						loopCode = 0;
						printf("\n\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
						printf("\t\t\t\t\t\t\t\t\t\tR E C O R D   T O   B E   M O D I F I E D\n");
						printf("\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n");
						printf("\t==============================================================================================================================================================================================\n");
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t|| Facility ID |       Type       |      Description      |     Category     |      Venue Location       |    Status    | Users Allowed |               Rules and Regulations               ||\n");
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t==============================================================================================================================================================================================\n");

						printf("\t||   - %-7s | - %-14s |  - %-18s | - %-14s |  - %-22s |- %-11s |     - %-7s |- %-48s ||\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");

						//if the id matches, prompt the user to select what to modify
						printf("CHOOSE CODE TO MODIFY :\n\n1) ID\n\n2) TYPE\n\n3) DESCRIPTION\n\n4) CATEGORY\n\n5) LOCATION\n\n6) STATUS\n\n7) NUM OF USERS\n\n8) RULES\n\n[ENTER 9 TO RETURN BACK]\n\n");

						printf("ENTER YOUR CHOICE > ");
						scanf(" %[^\n]", modChoice);


						invalid = choiceValidation(modChoice);//validate the choice entered

						system("cls");

						switch (atoi(modChoice))//changes the number inside string into integer
						{
						case 1:
							do {
								printf("ENTER NEW FACILITY ID > ");
								scanf(" %[^\n]", newData.facID);
								strupr(newData.facID);//convert string to all uppercase
								system("cls");

								invalid = FacilityIDValidation(newData.facID);//validate the new ID

								if (invalid == 1)
									printf("Facility ID is entered with incorrect format! The ID consist of a 2-letter code and a digit at the back.\n\n");

								//loop through the txt file and find if any ID matches with the new ID entered
								for (int i = 0; i < nRecords; i++) {
									if (strcmp(newData.facID, info[i].facID) == 0) {
										printf("THE FACILITY ENTERED MATCHES WITH ANOTHER. PLEASE ENTER AGAIN!\n\n");//if found same id, print warning message
										sameID = 1;
										break;
									}
									else
									{
										sameID = 0;
									}
								}
							} while (invalid == 1 || sameID == 1);//loop will repeat if Id is invalid or if the IDs are same

							strcpy(info[i].facID, newData.facID);//copy the new ID to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 2:
							do {
								printf("ENTER NEW FACILITY TYPE > ");
								scanf(" %[^\n]", newData.facType);
								strupr(newData.facType);//convert string to all uppercase
								system("cls");

								invalid = OnlyLettersValidation(newData.facType);//validate the new type

								if (invalid == 1)
									printf("Facility Type is entered with incorrect format! It should consists of letters only.\n\n");

							} while (invalid == 1);//loop will repeat if the type is invalid

							strcpy(info[i].facType, newData.facType);//copy the new type to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 3:
							do {
								printf("ENTER NEW FACILITY DESCRIPTION > ");
								scanf(" %[^\n]", newData.facDesc);//
								strupr(newData.facDesc);//convert string to all uppercase
								system("cls");

								invalid = LettersnDigitsValidation(newData.facDesc);//validate the new desc

								if (invalid == 1)
									printf("Facility Description is entered with incorrect format! It should consists of letters and digits only.\n\n");

							} while (invalid == 1);//loop will repeat if the desc is invalid

							strcpy(info[i].facDesc, newData.facDesc);//copy the new desc to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 4:
							do {
								printf("ENTER NEW FACILITY CATEGORY > ");
								scanf(" %[^\n]", newData.facCategory);
								strupr(newData.facCategory);//convert string to all uppercase
								system("cls");

								invalid = OnlyLettersValidation(newData.facCategory);//validate the new category

								if (invalid == 1)
									printf("Facility Category is entered with incorrect format! It should consists of letters only.\n\n");

							} while (invalid == 1);//loop will repeat if the category is invalid

							strcpy(info[i].facCategory, newData.facCategory);//copy the new category to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 5:
							printf("ENTER NEW FACILITY LOCATION > ");
							scanf(" %[^\n]", newData.facLocation);
							strupr(newData.facLocation);//convert string to all uppercase
							system("cls");

							strcpy(info[i].facLocation, newData.facLocation);//copy the new location to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 6:
							do {
								printf("ENTER NEW STATUS OF FACILITY > ");
								scanf(" %[^\n]", newData.rem.facStatus);
								strupr(newData.rem.facStatus);//convert string to all uppercase
								system("cls");

								invalid = OnlyLettersValidation(newData.rem.facStatus);//validate the new status

								if (invalid == 1)
									printf("Status of Facility is entred with incorrect format! It should consists of letters only.\n\n");

							} while (invalid == 1);//loop will repeat if the status is invalid

							strcpy(info[i].rem.facStatus, newData.rem.facStatus);//copy the new status to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 7:
							do {
								printf("ENTER NEW NUMBER OF USERS ALLOWED > ");
								scanf(" %[^\n]", newData.rem.maxUsers);
								system("cls");

								invalid = OnlyDigitsValidation(newData.rem.maxUsers);//validate the new max users

								if (invalid == 1)
									printf("Maximum Allowed Users is entred with incorrect format! It should consist of digits only.\n\n");

							} while (invalid == 1);//loop will repeat if the max users is invalid

							strcpy(info[i].rem.maxUsers, newData.rem.maxUsers);//copy the new max users to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 8:
							printf("ENTER NEW RULES OF FACILITY > ");
							scanf(" %[^\n]", newData.rem.facRules);
							strupr(newData.rem.facRules);//convert string to all uppercase
							system("cls");

							strcpy(info[i].rem.facRules, newData.rem.facRules);//copy the new rules to the structure array
							printf("DATA SUCCESSFULLY UPDATED.\n\n");
							break;
						case 9:
							printf("GOING BACK TO MENU . . . . .\n\n\n");
							stopModify = 1;
							break;
						default:
							printf("CODE NOT IDENTIFIED! PLEASE RE-TYPE CODE TO CONTINUE.\n\n");
							loopCode = 1;
							break;
						}
					} while (loopCode == 1);
				}
			}

			if (modRecFound == 0)
				printf("INCORRECT! THE INFORMATION ENTERED IS NOT IDENTIFIED. PLEASE TRY AGAIN.\n\n\n");//incorrect message is shown if no records are found in txt file


		} while (modRecFound == 0);//loop will repeat if no records are found inside txt file

		proceed = 0;

		if (stopModify == 0) {
			do {
				printf("\nDO YOU WISH TO MODIFY ANYMORE RECORDS ? (Y/N)  > ");//to ask user if they want to continue to modify any more records
				rewind(stdin);
				scanf(" %c", &confirm);
				system("cls");

				if (confirm == 'Y' || confirm == 'y')
					proceed = 1;
				else if (confirm == 'N' || confirm == 'n')
					proceed = 0;
				else
					printf("CHOOSE ONLY Y OR N !\n\n");

			} while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');//loop will continue if user entered anything other than y,n,Y,N
		}
	} while (proceed == 1);

	for (int i = 0; i < nRecords; i++) {
		fprintf(fpFacility3, "%s, %s, %s, %s, %s, %s, %s, %s\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
	}

	fclose(fpFacility3);//close file
}

void DeleteFacilitiesRecords(Facilities info[], int nRecords)
{
	char delFacID[99], confirm;
	int sameID = 0, invalid = 0, idFound = 0, proceed = 0, searchAgain = 0, loop = 0, rowPosition = 0, deleteChoice = 0;

	FILE* fpFacility4 = fopen("facilitiyInfo.txt", "w");//open file for writing
	if (fpFacility4 == NULL)
	{
		printf("Error, unable to open and read the file \"facilitiyInfo.txt\" !");//check for file opening errors
		exit(-1);
	}

	do {
		do {
			do {
				printf("ENTER A FACILITY ID TO DELETE THE RECORDS > ");
				rewind(stdin);
				scanf(" %[^\n]", delFacID);//prompt and read the facility ID to delete its records
				strupr(delFacID);//convert string to uppercase
				system("cls");

				invalid = FacilityIDValidation(delFacID);//to validate the facility ID entered

				if (invalid == 1)
					printf("Facility ID is entered with incorrect format! The ID consist of a 2-letter code and a digit at the back.\n\n");
			} while (invalid == 1);//loop will repeat if the ID is invalid 


			//to loop through txt file
			for (int i = 0; i < nRecords; i++) {
				//the ID entered matches with one in text file
				if (strcmp(delFacID, info[i].facID) == 0) {
					idFound = 1;
					rowPosition = i;

					do {
						//display the record that user want to delete
						printf("\n\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
						printf("\t\t\t\t\t\t\t\t\t\tR E C O R D   T O   B E   D E L E T E D\n");
						printf("\t\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n");
						printf("\t==============================================================================================================================================================================================\n");
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t|| Facility ID |       Type       |      Description      |     Category     |      Venue Location       |    Status    | Users Allowed |               Rules and Regulations               ||\n");
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t==============================================================================================================================================================================================\n");

						printf("\t||   - %-7s | - %-14s |  - %-18s | - %-14s |  - %-22s |- %-11s |     - %-7s |- %-48s ||\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
						printf("\t||             |                  |                       |                  |                           |              |               |                                                   ||\n");
						printf("\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


						printf("\n\n\nARE YOU SURE YOU WANT TO DELETE THIS ? (Y/N) > ");
						rewind(stdin);
						scanf("%c", &confirm);//to confirm with user if they really want to delete this record
						system("cls");


						if (confirm == 'Y' || confirm == 'y')
						{
							proceed = 1;
						}
						else if (confirm == 'N' || confirm == 'n')
						{
							proceed = 2;
						}
						else
						{
							printf("PLEASE CHOOSE ONLY Y OR N !!!\n\n\n");
							proceed = 0;
						}
					} while (proceed == 0);//loop will repeat if user enter anything other than y, Y, n or N
					break;
				}
				else
					idFound = 0;//idFound is 0 is no records are found
			}

			searchAgain = 0;

			if (proceed == 1)//if user entered y or Y
			{
				//to delete the record based on their position in the txt file
				for (int i = rowPosition; i < nRecords; i++)
				{
					info[i] = info[i + 1];
				}
				nRecords--;//to update count
				printf("FACILITY DELETED SUCCESFULLY\n\n");

				//to update the existing txt file with 1 less records
				for (int i = 0; i < nRecords; i++) {
					fprintf(fpFacility4, "%s, %s, %s, %s, %s, %s, %s, %s\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
				}
			}
			else if (proceed == 2)//if user entered n or N
			{
				do {
					loop = 0;
					//user entered n/N previously, then user need to choose one option to continue
					printf("CHOOSE 1 TO SEARCH OTHER RECORDS TO DELETE.\n\nCHOOSE 2 TO RETURN BACK TO MENU.\n\n\nYOUR CHOICE > ");
					rewind(stdin);
					scanf("%d", &deleteChoice);
					system("cls");

					switch (deleteChoice)
					{
					case 1:
						searchAgain = 1;//user select 1 to search a new facility ID to delete the record
						break;
					case 2:
						printf("GOING BACK ....\n\n");//user select 2 to return back to main menu

						//to cancel the delete and save back original records
						for (int i = 0; i < nRecords; i++) {
							fprintf(fpFacility4, "%s, %s, %s, %s, %s, %s, %s, %s\n", info[i].facID, info[i].facType, info[i].facDesc, info[i].facCategory, info[i].facLocation, info[i].rem.facStatus, info[i].rem.maxUsers, info[i].rem.facRules);
						}
						break;
					default:
						printf("PLEASE CHOOSE ONLY 1 OR 2\n\n");
						loop = 1;
						break;
					}
				} while (loop == 1);//loop will repeat when user select other than 1 or 2
			}
		} while (searchAgain == 1);//loop will repeat when user entered 1

		if (idFound == 0)
			printf("INCORRECT! THE INFORMATION ENTERED IS NOT IDENTIFIED. PLEASE TRY AGAIN.\n\n\n");//incorrect message is shown if no same ID is found within the txt file


	} while (idFound == 0);

	fclose(fpFacility4);//close file
}

void ClosedFacilitiesReport(Facilities info[], int nRecords)
{
	int closeFacCount = 0, proceed = 0;
	char confirm;

	FILE* fpFacility5 = fopen("facilityReport.txt", "w");//open file for appending
	if (fpFacility5 == NULL)
	{
		printf("Error, unable to open and read the file \"facilitiyReport.txt\" !");//check for file opening errors
		exit(-1);
	}

	do {
		printf("\n\t\t\t\t\t\t C L O S E D   F A C I L I T I E S   R E P O R T\n");
		printf("\t\t\t\t\t\t. . . . . . . . . . . . . . . . . . . . . . . . . .\n\n\n");
		printf("\t\t\t ------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t        Facility ID               Description              Venue Location\n");
		printf("\t\t\t ------------------------------------------------------------------------------------------------\n\n");

		//loop through the txt file to find the records with the status CLOSED, then display it out
		for (int i = 0; i < nRecords; i++) {
			if (strcmp(info[i].rem.facStatus, "CLOSED") == 0)
			{
				closeFacCount++;
				printf("\t\t\t\t            %-14s       %-18s         %-19s\n\n", info[i].facID, info[i].facDesc, info[i].facLocation, info[i].rem.facStatus);
			}
		}
		printf("\n\t\t\t ------------------------------------------------------------------------------------------------");
		printf("\n\n\t\t\t\tNumber of Facilities Not Operating =  %d\n\n", closeFacCount);
		printf("\t\t\t\tThe Facilities Above Are Closed Due To Unhygienic Reasons. Please Take Action\n\t\t\t\tTo Expedite The Maintenance Cleaning To Allow Customer Usage.\n\n");
		printf("\t\t\t ------------------------------------------------------------------------------------------------\n\n");

		printf("\nDO YOU WANT TO SAVE THIS INTO TXT FILE (Y/N) > ");
		rewind(stdin);
		scanf("%c", &confirm);//to confirm with user if they really want to delete this record
		system("cls");


		if (confirm == 'Y' || confirm == 'y')
		{
			proceed = 1;
		}
		else if (confirm == 'N' || confirm == 'n')
		{
			proceed = 2;
		}
		else
		{
			printf("PLEASE CHOOSE ONLY Y OR N !!!\n\n\n");
			proceed = 0;
		}
	} while (proceed == 0);//loop will repeat if user enter anything other than y, Y, n or N

	if (proceed == 1)
	{

		fprintf(fpFacility5, "\t\t\t   C L O S E D   F A C I L I T I E S   R E P O R T\n");
		fprintf(fpFacility5, "\t\t\t . . . . . . . . . . . . . . . . . . . . . . . . . .\n\n\n");
		fprintf(fpFacility5, "-------------------------------------------------------------------------------\n");
		fprintf(fpFacility5, "       Facility ID               Description              Venue Location\n");
		fprintf(fpFacility5, "-------------------------------------------------------------------------------\n\n");
		for (int i = 0; i < nRecords; i++)
		{
			if (strcmp(info[i].rem.facStatus, "CLOSED") == 0)
			{
				fprintf(fpFacility5, "           %-14s       %-18s         %-19s\n\n", info[i].facID, info[i].facDesc, info[i].facLocation, info[i].rem.facStatus);
			}
		}
		fprintf(fpFacility5, "\n-------------------------------------------------------------------------------");
		fprintf(fpFacility5, "\n\nNumber of Facilities Not Operating =  %d\n\n", closeFacCount);
		fprintf(fpFacility5, "The Facilities Above Are Closed Due To Unhygienic Reasons. Please Take Action\nTo Expedite The Maintenance Cleaning To Allow Customer Usage.\n\n");
		fprintf(fpFacility5, "-------------------------------------------------------------------------------");
	}
	fclose(fpFacility5);//close file
}


// Member section
void memberMenu()
{
	FILE* fpMember;
	Member member[200];
	char subChoice[50] = "";
	int invalid, recCount = 0;

	// Infinite loop until user chooses 0
	while (1 == 1)
	{
		recCount = 0;
		if (!(fpMember = fopen("membersInfo.bin", "rb")))
		{
			printf("Error in reading membersInfo.bin!\n");
			return;
		}

		// Read data in bin file into array of structure to be passed to other functions to use
		while (fread(&member[recCount], sizeof(Member), 1, fpMember) != 0)
		{
			recCount++;
		}

		fclose(fpMember);

		printf(
			"---------------------------\n"
			"        MEMBER MENU\n"
			"---------------------------\n\n"
			"0. Go Back Main Menu\n"
			"1. Display All Members\n"
			"2. Add New Member\n"
			"3. Search Member\n"
			"4. Modify Member Details\n"
			"5. Delete Member Record\n"
			"6. Member Expiration Report\n\n"
		);

		printf("Enter your choice > ");
		scanf(" %[^\n]", subChoice);
		invalid = choiceValidation(subChoice);

		system("cls");

		if (invalid != 1)
		{
			switch (atoi(subChoice))
			{
			case 0:
				return;
			case 1:
				displayMember(member, recCount);
				break;
			case 2:
				addMember(member, recCount);
				break;
			case 3:
				searchMember(member, recCount);
				break;
			case 4:
				modifyMember(member, recCount);
				break;
			case 5:
				deleteMember(member, recCount);
				break;
			case 6:
				expiredMemberReport(member, recCount);
				break;
			default:
				printf("Please enter only (0 - 6)!\n");
				invalid = 1;
				break;
			}

			if (invalid != 1)
			{
				system("pause");
				system("cls");
			}
		}
		else
			printf("Please enter only (0 - 6)!\n");
	}
}

void displayMember(Member member[], int recCount)
{
	int count = 0;

	if (recCount > 0)
	{
		printf(
			"%63sMEMBERS INFORMATION\n"
			"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
			"| ID    | Name                          | Gender | IC Number    | Phone No.   | Email                              | Date Joined | Expired Date |\n"
			"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n",
			""
		);

		for (int i = 0; i < recCount; i++)
		{
			printf(
				"| %s | %-29s | %c      | %s | %11s | %-34s | %02d/%02d/%d  | %02d/%02d/%d   |\n",
				member[i].memID, member[i].memName, member[i].memSex, member[i].memIC, member[i].memPhoneNo, member[i].memEmail, member[i].dateJoined.day, member[i].dateJoined.month, member[i].dateJoined.year, member[i].expiredDate.day, member[i].expiredDate.month, member[i].expiredDate.year
			);
			count++;
		}

		printf(
			"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
			" %d records found.\n",
			count
		);
	}
	else
		printf("No records found.\n");
}

void addMember(Member member[], int recCount)
{
	Member memberToAdd;
	char cont[50] = "Y", addContent[99];
	int i, invalid, addedCount = 0, isExist = 0;
	FILE* fpMember;

	if (!(fpMember = fopen("membersInfo.bin", "ab")))
	{
		printf("Error in opening membersInfo.bin!\n");
		return;
	}

	while (toupper(cont[0]) == 'Y')
	{
		// Member ID
		do
		{
			isExist = 0;

			printf("Enter member's ID > ");
			scanf(" %[^\n]", addContent);

			// Validate member ID inputted by user
			invalid = memberIDValidation(addContent);

			// If correct format, check again if the same ID already exists.
			if (invalid == 1)
			{
				system("cls");
				printf("Invalid member ID format! Please enter a correct format again! (e.g. M9999)\n");
			}
			else
			{
				addContent[0] = toupper(addContent[0]);

				for (i = 0; i < recCount; i++)
				{
					if (strcmp(addContent, member[i].memID) == 0)
					{
						isExist = 1;
						system("cls");
						printf("Member ID <%s> already exists!\n", addContent);
						break;
					}
				}
				if (isExist == 0)
				{
					strcpy(memberToAdd.memID, addContent);
					system("cls");
				}
			}
		} while (invalid == 1 || isExist == 1);

		// Member Name
		printf("Enter member's name > ");
		scanf(" %[^\n]", addContent);
		strcpy(memberToAdd.memName, strupr(addContent));
		system("cls");

		// Member Gender
		do
		{
			printf("Enter member's gender (M/F) > ");
			scanf(" %[^\n]", addContent);

			// Validate gender inputted by user
			invalid = genderValidation(strupr(addContent));
			if (invalid == 1)
			{
				system("cls");
				printf("Please enter M or F only!\n");
			}
			else
			{
				memberToAdd.memSex = addContent[0];
				system("cls");
			}
		} while (invalid == 1);

		// Member IC No.
		do
		{
			isExist = 0;

			printf("Enter member's IC number (without '-') > ");
			scanf(" %[^\n]", addContent);

			// Validate IC No. inputted by user
			invalid = ICValidation(addContent);

			// If correct format, check again if the same IC No. already exists.
			if (invalid == 1)
			{
				system("cls");
				printf("Invalid IC number format! Please enter a correct format again! (e.g. 010203141234)\n");
			}
			else
			{
				for (i = 0; i < recCount; i++)
				{
					if (strcmp(addContent, member[i].memIC) == 0)
					{
						isExist = 1;
						system("cls");
						printf("IC No. <%s> already exists!\n", addContent);
						break;
					}
				}
				if (isExist == 0)
				{
					strcpy(memberToAdd.memIC, addContent);
					system("cls");
				}
			}
		} while (invalid == 1 || isExist == 1);

		// Member Phone No.
		do
		{
			isExist = 0;

			printf("Enter member's phone number (without '-') > ");
			scanf(" %[^\n]", addContent);

			// Validate phone number inputted by user
			invalid = phoneValidation(addContent);

			// If correct format, check again if the same phone number already exists.
			if (invalid == 1)
			{
				system("cls");
				printf("Invalid phone number format! Please enter a correct format again! (e.g. 0123456789)\n");
			}
			else
			{
				for (i = 0; i < recCount; i++)
				{
					if (strcmp(addContent, member[i].memPhoneNo) == 0)
					{
						isExist = 1;
						system("cls");
						printf("Phone number <%s> already exists!\n", addContent);
						break;
					}
				}
				if (isExist == 0)
				{
					strcpy(memberToAdd.memPhoneNo, addContent);
					system("cls");
				}
			}
		} while (invalid == 1 || isExist == 1);

		// Member Email
		do
		{
			isExist = 0;

			printf("Enter member's email > ");
			scanf(" %[^\n]", addContent);

			// Validate email inputted by user
			invalid = emailValidation(addContent);

			// If correct format, check again if the same email already exists.
			if (invalid == 1)
			{
				system("cls");
				printf("Invalid email address format! Please enter a correct format again! (e.g. okok@gmail.com)\n");
			}
			else
			{
				for (i = 0; i < recCount; i++)
				{
					if (strcmp(addContent, member[i].memEmail) == 0)
					{
						isExist = 1;
						system("cls");
						printf("Email address <%s> already exists!\n", addContent);
						break;
					}
				}
				if (isExist == 0)
				{
					strcpy(memberToAdd.memEmail, addContent);
					system("cls");
				}
			}
		} while (invalid == 1 || isExist == 1);

		// Member's Date Joined
		do
		{
			printf("Enter member's date joined (DD/MM/YYYY) > ");
			rewind(stdin);

			if (scanf("%d/%d/%d", &memberToAdd.dateJoined.day, &memberToAdd.dateJoined.month, &memberToAdd.dateJoined.year) == 3)
				// Validate date inputted by user
				invalid = dateValidation(memberToAdd.dateJoined.day, memberToAdd.dateJoined.month, memberToAdd.dateJoined.year);
			else
				invalid = 1;

			system("cls");

			if (invalid == 1)
				printf("Invalid date or format! Please enter a correct date again!\n");
		} while (invalid == 1);

		// Member's Expiration Date is set by default one year from date joined
		memberToAdd.expiredDate = memberToAdd.dateJoined;
		memberToAdd.expiredDate.year++;
		if (memberToAdd.dateJoined.day == 29 && memberToAdd.dateJoined.month == 2) // If date joined is 29/2, then expiration date is 1/3 next year
		{
			memberToAdd.expiredDate.day = 1;
			memberToAdd.expiredDate.month = 3;
		}

		// Appending record
		fwrite(&memberToAdd, sizeof(Member), 1, fpMember);
		addedCount++;

		do {
			printf("Anymore Records? (Y/N) > ");
			scanf(" %[^\n]", cont);
			printf("\n");
			strupr(cont);

			if (cont[0] != 'Y' && cont[0] != 'N' || strlen(cont) != 1)
				printf("Please enter Y or N only!\n");
		} while (cont[0] != 'Y' && cont[0] != 'N' || strlen(cont) != 1);
	}

	fclose(fpMember);

	printf("%d record(s) added successfully.\n", addedCount);
}

void searchMember(Member member[], int recCount)
{
	int invalid, i, searchCount, found, exist;
	char choice[50], searchContent[99];

	while (1 == 1)
	{
		searchCount = 0;
		exist = 0;
		system("cls");

		// Search menu
		do
		{
			printf(
				"Search By:\n"
				"1. ID\n"
				"2. Name\n"
				"3. IC Number\n"
				"4. Phone Number\n\n"
			);

			printf("Enter your choice (0 to go back) > ");
			scanf(" %[^\n]", choice);

			invalid = choiceValidation(choice);

			if (atoi(choice) != 0)
				system("cls");

			if (invalid != 1)
			{
				switch (atoi(choice))
				{
				case 0:
					return;
				case 1:
					printf("Enter ID > ");
					break;
				case 2:
					printf("Enter name > ");
					break;
				case 3:
					printf("Enter IC number > ");
					break;
				case 4:
					printf("Enter phone number > ");
					break;
				default:
					printf("Please enter only (0 - 4)!\n");
					invalid = 1;
					break;
				}

				if (invalid != 1)
					scanf(" %[^\n]", searchContent);
			}
			else
				printf("Please enter only (0 - 4)!\n");
		} while (invalid == 1);

		// Display records based on searches
		for (i = 0; i < recCount; i++)
		{
			switch (atoi(choice))
			{
			case 1:
				found = (strcmp(strupr(searchContent), member[i].memID) == 0) ? 1 : 0;
				break;
			case 2:
				found = (strcmp(strupr(searchContent), member[i].memName) == 0) ? 1 : 0;
				break;
			case 3:
				found = (strcmp(searchContent, member[i].memIC) == 0) ? 1 : 0;
				break;
			case 4:
				found = (strcmp(searchContent, member[i].memPhoneNo) == 0) ? 1 : 0;
				break;
			}

			if (found == 1)
			{
				printf(
					"%63sMEMBERS INFORMATION\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
					"| ID    | Name                          | Gender | IC Number    | Phone No.   | Email                              | Date Joined | Expired Date |\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n",
					""
				);

				printf(
					"| %s | %-29s | %c      | %s | %11s | %-34s | %02d/%02d/%d  | %02d/%02d/%d   |\n",
					member[i].memID, member[i].memName, member[i].memSex, member[i].memIC, member[i].memPhoneNo, member[i].memEmail, member[i].dateJoined.day, member[i].dateJoined.month, member[i].dateJoined.year, member[i].expiredDate.day, member[i].expiredDate.month, member[i].expiredDate.year
				);

				exist = 1;
				searchCount++;
			}
		}

		if (exist == 1)
		{
			printf(
				"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
				" %d records found.\n",
				searchCount
			);
		}
		else
			printf("No records found.\n");

		system("pause");
	}
}

void modifyMember(Member member[], int recCount)
{
	FILE* fpModifyMem;
	Date newDate;
	int invalid = 0, i, notFound = 0, position = 0, isExist, numYear;
	char choice[50], targetID[99], modifyContent[99], confirmation[50];

	if (!(fpModifyMem = fopen("membersInfo.bin", "wb")))
	{
		printf("Error in reading membersInfo.bin!\n");
		return;
	}

	// Search by member ID first, then only choose what criteria to be modified
	do {
		invalid = 0;

		printf("Enter a member's ID to modify his/her details (X to exit) > ");
		scanf(" %[^\n]", targetID);
		strupr(targetID);

		if (strcmp(targetID, "X") == 0)
			break;

		// Get the index of the member's ID selected from the array of structure
		for (i = 0; i < recCount; i++)
		{
			notFound = 0;

			if (strcmp(targetID, member[i].memID) == 0)
			{
				position = i;
				break;
			}
			else
				notFound = 1;
		}

		if (notFound == 0)
		{
			while (1 == 1)
			{
				printf(
					"\n+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
					"| ID    | Name                          | Gender | IC Number    | Phone No.   | Email                              | Date Joined | Expired Date |\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n"
					"| %s | %-29s | %c      | %s | %11s | %-34s | %02d/%02d/%d  | %02d/%02d/%d   |\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+--------------+\n",
					member[position].memID, member[position].memName, member[position].memSex, member[position].memIC, member[position].memPhoneNo, member[position].memEmail, member[position].dateJoined.day, member[position].dateJoined.month, member[position].dateJoined.year, member[position].expiredDate.day, member[position].expiredDate.month, member[position].expiredDate.year
				);

				printf(
					"\n\nModify Member's:\n"
					"1. ID\n"
					"2. Name\n"
					"3. Gender\n"
					"4. IC Number\n"
					"5. Phone Number\n"
					"6. Email\n"
					"7. Date Joined\n"
					"8. Expiration Date\n\n"
				);

				do
				{
					printf("Enter your choice (0 to go back) > ");
					scanf(" %[^\n]", choice);

					invalid = choiceValidation(choice);
					if (invalid == 1)
						printf("Please enter only (0 - 8)!\n\n");
				} while (invalid == 1);

				system("cls");

				switch (atoi(choice))
				{
				case 0:
					break;
				case 1:
					do
					{
						isExist = 0;

						printf("Enter new member ID > ");
						scanf(" %[^\n]", modifyContent);

						invalid = memberIDValidation(modifyContent);

						if (invalid == 1)
						{
							system("cls");
							printf("Invalid member ID format! Please enter a correct format again! (e.g. M9999)\n");
						}
						else
						{
							strupr(modifyContent);

							for (i = 0; i < recCount; i++)
							{
								if (i != position && (strcmp(modifyContent, member[i].memID) == 0))
								{
									isExist = 1;
									system("cls");
									printf("Member ID <%s> already exists!\n", modifyContent);
									break;
								}
							}
							if (isExist == 0)
							{
								strcpy(member[position].memID, modifyContent);
								system("cls");
							}
						}
					} while (invalid == 1 || isExist == 1);
					break;
				case 2:
					printf("Enter new member's name > ");
					scanf(" %[^\n]", modifyContent);

					strupr(modifyContent);
					strcpy(member[position].memName, modifyContent);
					system("cls");
					break;
				case 3:
					do
					{
						printf("Enter new gender > ");
						scanf(" %[^\n]", modifyContent);

						strupr(modifyContent);
						invalid = genderValidation(modifyContent);

						if (invalid == 1)
						{
							system("cls");
							printf("Please enter M or F only!\n");
						}
						else
							member[position].memSex = modifyContent[0];
					} while (invalid == 1);
					break;
				case 4:
					do
					{
						isExist = 0;

						printf("Enter new IC number > ");
						scanf(" %[^\n]", modifyContent);

						invalid = ICValidation(modifyContent);

						if (invalid == 1)
						{
							system("cls");
							printf("Invalid IC number format! Please enter a correct format again! (e.g. 010203141234)\n");
						}
						else
						{
							for (i = 0; i < recCount; i++)
							{
								if (i != position && (strcmp(modifyContent, member[i].memIC) == 0))
								{
									isExist = 1;
									system("cls");
									printf("IC No. <%s> already exists!\n", modifyContent);
									break;
								}
							}
							if (isExist == 0)
							{
								strcpy(member[position].memIC, modifyContent);
								system("cls");
							}
						}
					} while (invalid == 1 || isExist == 1);
					break;
				case 5:
					do
					{
						isExist = 0;

						printf("Enter new phone number > ");
						scanf(" %[^\n]", modifyContent);

						invalid = phoneValidation(modifyContent);

						if (invalid == 1)
						{
							system("cls");
							printf("Invalid phone number format! Please enter a correct format again! (e.g. 0123456789)\n");
						}
						else
						{
							for (i = 0; i < recCount; i++)
							{
								if (i != position && (strcmp(modifyContent, member[i].memPhoneNo) == 0))
								{
									isExist = 1;
									system("cls");
									printf("Phone number <%s> already exists!\n", modifyContent);
									break;
								}
							}
							if (isExist == 0)
							{
								strcpy(member[position].memPhoneNo, modifyContent);
								system("cls");
							}
						}
					} while (invalid == 1 || isExist == 1);
					break;
				case 6:
					do
					{
						isExist = 0;

						printf("Enter new email > ");
						scanf(" %[^\n]", modifyContent);

						invalid = emailValidation(modifyContent);

						if (invalid == 1)
						{
							system("cls");
							printf("Invalid email address format! Please enter a correct format again! (e.g. okok@gmail.com)\n");
						}
						else
						{
							for (i = 0; i < recCount; i++)
							{
								if (i != position && (strcmp(modifyContent, member[i].memEmail) == 0))
								{
									isExist = 1;
									system("cls");
									printf("Email address <%s> already exists!\n", modifyContent);
									break;
								}
							}
							if (isExist == 0)
							{
								strcpy(member[position].memEmail, modifyContent);
								system("cls");
							}
						}
					} while (invalid == 1 || isExist == 1);
					break;
				case 7:
					do
					{
						printf("Enter new date joined (DD/MM/YYYY) > ");
						rewind(stdin);

						if (scanf("%d/%d/%d", &member[position].dateJoined.day, &member[position].dateJoined.month, &member[position].dateJoined.year) == 3)
							invalid = dateValidation(member[position].dateJoined.day, member[position].dateJoined.month, member[position].dateJoined.year);
						else
							invalid = 1;

						system("cls");

						if (invalid == 1)
							printf("Invalid date or format! Please enter a correct date again!\n");
						else
						{
							member[position].expiredDate = member[position].dateJoined;
							member[position].expiredDate.year++;
							if (member[position].dateJoined.day == 29 && member[position].dateJoined.month == 2) // If date joined is 29/2, then expiration date is 1/3 next year
							{
								member[position].expiredDate.day = 1;
								member[position].expiredDate.month = 3;
							}
						}
					} while (invalid == 1);
					break;
				case 8:
					do
					{
						invalid = 0;

						printf("Enter the number of years for membership renewal (min: 1, max: 5) > ");
						rewind(stdin);
						if (scanf("%d", &numYear) == 1)
						{
							if (numYear >= 1 && numYear <= 5)
							{
								do
								{
									printf("Are you sure? (Y/N) > ");
									scanf(" %[^\n]", confirmation);
									strupr(confirmation);

									if (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1)
										printf("\nPlease enter Y or N only!\n");
								} while (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1);

								if (confirmation[0] == 'Y')
									member[position].expiredDate.year += numYear;
								else
									break;

								system("cls");
							}
							else
							{
								system("cls");
								invalid = 1;
								printf("Please enter only (1 - 5)!\n");
							}
						}
						else
						{
							system("cls");
							invalid = 1;
							printf("Please enter digits only!\n");
						}
					} while (invalid == 1);
					break;
				default:
					printf("Please enter only (0 - 8)!\n");
					invalid = 1;
					break;
				}

				if (atoi(choice) == 0 || invalid == 1)
					break;
			}
		}
		else
		{
			system("cls");
			printf("Member ID <%s> not found!\n", targetID);
		}
	} while (invalid == 1 || notFound == 1);

	// Rewriting whole updated structure back into binary file
	fwrite(&member[0], sizeof(Member), recCount, fpModifyMem);
	fclose(fpModifyMem);
}

void deleteMember(Member member[], int recCount)
{
	FILE* fpDeleted;
	int i, notFound = 0, position = 0, invalid = 0;
	char targetID[99], confirmation[50] = "Y";

	if (!(fpDeleted = fopen("membersInfo.bin", "wb")))
	{
		printf("Error! Unable to open membersInfo.bin!\n");
		return;
	}

	do
	{
		// Get the index of member's ID selected from the array of structure 
		printf("Enter a member's ID to delete his/her record (X to exit) > ");
		scanf(" %[^\n]", targetID);
		strupr(targetID);

		if (strcmp(targetID, "X") == 0)
			break;

		for (i = 0; i < recCount; i++)
		{
			notFound = 0;

			if (strcmp(targetID, member[i].memID) == 0)
			{
				position = i;
				break;
			}
			else
				notFound = 1;
		}

		// If there is a record, display out and prompt for confirmation to delete the record
		if (notFound == 0)
		{
			do {
				printf(
					"\n+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+\n"
					"| ID    | Name                          | Gender | IC Number    | Phone No.   | Email                              | Date Joined |\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+\n"
					"| %s | %-29s | %c      | %s | %11s | %-34s | %02d/%02d/%d  |\n"
					"+-------+-------------------------------+--------+--------------+-------------+------------------------------------+-------------+\n\n",
					member[position].memID, member[position].memName, member[position].memSex, member[position].memIC, member[position].memPhoneNo, member[position].memEmail, member[position].dateJoined.day, member[position].dateJoined.month, member[position].dateJoined.year
				);

				if (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1)
					printf("Please enter Y or N only!\n");

				printf("Are you sure to remove this record? (Y/N) > ");
				scanf(" %[^\n]", confirmation);
				strupr(confirmation);
				system("cls");
			} while (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1);

			if (toupper(confirmation[0]) == 'Y')
			{
				for (i = position; i < recCount; i++)
				{
					member[i] = member[i + 1];
				}

				recCount--;
				printf("Member deleted succesfully.\n");
			}
		}
		else
		{
			system("cls");
			printf("Member ID <%s> not found!\n", targetID);
		}
	} while (notFound == 1);

	fwrite(&member[0], sizeof(Member), recCount, fpDeleted);
	fclose(fpDeleted);
}

void expiredMemberReport(Member member[], int recCount)
{
	FILE* fpReport;
	Member expiredMember[200];
	int count = 0, i, j = 0;
	char confirmation[50];
	time_t timeNow;
	time(&timeNow);
	struct tm expired;
	expired = *localtime(&timeNow);

	printf(
		"%44sEXPIRED MEMBERS LIST\n"
		"+-------+-------------------------------+-------------+------------------------------------+--------------+\n"
		"| ID    | Name                          | Phone No.   | Email                              | Expired Date |\n"
		"+-------+-------------------------------+-------------+------------------------------------+--------------+\n",
		""
	);

	// Filter out and display those expired members compared with the realtime date
	for (i = 0; i < recCount; i++)
	{
		expired.tm_year = member[i].expiredDate.year - 1900;
		expired.tm_mon = member[i].expiredDate.month;
		expired.tm_mday = member[i].expiredDate.day;

		if ((difftime(timeNow, mktime(&expired)) / 86400) > 0)
		{
			expiredMember[j] = member[i];
			j++;

			printf(
				"| %s | %-29s | %11s | %-34s | %02d/%02d/%d   |\n",
				member[i].memID, member[i].memName, member[i].memPhoneNo, member[i].memEmail, member[i].expiredDate.day, member[i].expiredDate.month, member[i].expiredDate.year
			);
			count++;
		}
	}

	printf(
		"+-------+-------------------------------+-------------+------------------------------------+--------------+\n"
		" %d records found.\n",
		count
	);

	// Save report into text file
	do {
		printf("Do you want to save the report? (Y/N) > ");
		scanf(" %[^\n]", confirmation);
		printf("\n");
		strupr(confirmation);

		if (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1)
			printf("Please enter Y or N only!\n");
	} while (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1);

	if (confirmation[0] == 'Y')
	{
		if ((fpReport = fopen("MemberExpirationReport.txt", "w")) == NULL)
			printf("Error! Unable to open MemberExpirationReport.txt for writing!\n");
		else
		{
			fprintf(fpReport,
				"%44sEXPIRED MEMBERS LIST\n"
				"+-------+-------------------------------+-------------+------------------------------------+--------------+\n"
				"| ID    | Name                          | Phone No.   | Email                              | Expired Date |\n"
				"+-------+-------------------------------+-------------+------------------------------------+--------------+\n",
				""
			);

			for (i = 0; i < j; i++)
			{
				fprintf(fpReport, "| %s | %-29s | %11s | %-34s | %02d/%02d/%d   |\n",
					expiredMember[i].memID, expiredMember[i].memName, expiredMember[i].memPhoneNo, expiredMember[i].memEmail, expiredMember[i].expiredDate.day, expiredMember[i].expiredDate.month, expiredMember[i].expiredDate.year);
			}

			fprintf(fpReport,
				"+-------+-------------------------------+-------------+------------------------------------+--------------+\n"
				" %d records found.\n",
				count
			);

			printf("The report is saved in 'MemberExpirationReport.txt' under the same directory with this program.\n\n");

			do {
				printf("Do you want to open the saved report? (Y/N) > ");
				scanf(" %[^\n]", confirmation);
				printf("\n");
				strupr(confirmation);

				if (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1)
					printf("Please enter Y or N only!\n");
			} while (confirmation[0] != 'Y' && confirmation[0] != 'N' || strlen(confirmation) != 1);
		}

		fclose(fpReport);

		// Open the text file
		if (confirmation[0] == 'Y')
			system("MemberExpirationReport.txt");
	}
}


// Booking section
void bookingMenu() {
	FILE* rBookingRec;
	Booking book[500];
	char subChoice[50] = "";
	int invalid, recCount = 0;
	while (1 == 1)
	{
		recCount = 0;
		rBookingRec = fopen("bookingRec.txt", "r");
		if (rBookingRec == NULL) {
			printf("Error ! unable to open the bookingRec.txt file");
			return;
		}

		while (fscanf(rBookingRec, "%[^,], %[^,], %s %d %d %d %d %d %d %d\n", book[recCount].bookingId, book[recCount].memberId, book[recCount].facilityId, &book[recCount].bookingTimeS.hour, &book[recCount].bookingTimeS.minute, &book[recCount].bookingTimeE.hour, &book[recCount].bookingTimeE.minute, &book[recCount].bookingDate.day, &book[recCount].bookingDate.month, &book[recCount].bookingDate.year) != EOF) {
			recCount++;
		}
		fclose(rBookingRec);
		//display menu
		printf(
			"0. Go Back Main Menu\n"
			"\n"
			"1. Display All Bookings\n"
			"\n"
			"2. Add New Booking\n"
			"\n"
			"3. Search Booking Details\n"
			"\n"
			"4. Edit Booking Details\n"
			"\n"
			"5. Delete Booking\n"
			"\n"
			"6. Booking Report\n"
			"\n"
		);
		//reading menu choice
		printf("Enter your choice > ");
		scanf(" %[^\n]", subChoice);
		invalid = choiceValidation(subChoice);
		system("cls");

		if (invalid != 1)
		{
			switch (atoi(subChoice))
			{
			case 0:
				return;
			case 1:
				displayBooking(book, recCount);
				break;
			case 2:
				addBooking();
				break;
			case 3:
				searchBooking(book, recCount);
				break;
			case 4:
				editBooking(book, recCount);
				break;
			case 5:
				deleteBooking(book, recCount);
				break;
			case 6:
				BookingReport(book, recCount);
				break;
			default:
				printf("Please enter only (0 - 4)!\n");
				invalid = 1;
				break;
			}

			if (invalid != 1)
			{
				system("pause");
				system("cls");
			}
		}
		else
			printf("Please enter only (0 - 6)!\n");
	}
}

void displayBooking(Booking book[], int recCount) {

	//Header
	printf("=======================================================================================================================================================================================\n");
	printf("\n");
	printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
	printf("=======================================================================================================================================================================================\n");
	for (int i = 0; i < recCount; i++)
	{
		printf("\n");
		printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
		printf("\n");
		printf("=======================================================================================================================================================================================\n");


	}
}

void searchBooking(Booking book[], int recCount) {
	char searchBookingId[10], searchMemberId[10], searchFacilityId[4];
	int searchChoice, invalid = 0;
	printf(
		"1.Search by Booking ID\n"
		"\n"
		"2.Search by Member ID\n"
		"\n"
		"3.Search by Facility ID\n"
		"\n"
	);
	printf("Enter your choice > ");
	scanf("%d", &searchChoice);
	switch (searchChoice)
	{
	case 1:
		system("cls");
		//searching booking ID
		do {
			printf("Search Booking ID >");
			rewind(stdin);
			scanf("%s", searchBookingId);

			invalid = BookingIDValidation(searchBookingId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid booking ID !!!\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(searchBookingId, book[i].bookingId) == 0) {

				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");
			}

		}
		break;
	case 2:
		system("cls");
		//searching Member ID
		do {
			rewind(stdin);
			printf("Search Member ID >");
			scanf("%s", searchMemberId);
			invalid = memberIDValidation(searchMemberId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid Member ID\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		for (int i = 0; i < recCount; i++)
		{
			if (strcmp(searchMemberId, book[i].memberId) == 0) {
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");
			}

		}
		break;

	case 3:
		system("cls");
		//searching Facility ID
		do {
			printf("Search Facility ID >");
			rewind(stdin);
			scanf("%s", searchFacilityId);
			invalid = FacilityIDValidation(searchFacilityId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid facility id !!!\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		for (int i = 0; i < recCount; i++)
		{
			if (strcmp(searchFacilityId, book[i].facilityId) == 0) {
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");
			}

		}
		break;
	default:
		system("cls");
		printf("Please enter only (1 - 3)!\n");

		break;
	}
}

void editBooking(Booking book[], int recCount) {
	char search[10], newBookingId[10], newMemberId[10], newFacilityId[10];
	Time newBookingTimeS, newBookingTimeE;
	Date newBookDate;
	FILE* mBookingRec;
	mBookingRec = fopen("bookingRec.txt", "w");
	if (mBookingRec == NULL) {
		printf("Error ! unable to open the bookingRec.txt file");
		return;
	}
	int modifyChoice, invalid;
	printf(
		"Choose a section to edit\n"
		"1.Booking ID\n"
		"\n"
		"2.Member ID\n"
		"\n"
		"3.Facility ID\n"
		"\n"
		"4.Booking Time\n"
		"\n"
		"5.Booking Date\n"
		"\n"
	);
	scanf("%d", &modifyChoice);
	switch (modifyChoice)
	{

	case 1:
		system("cls");
		//searching booking ID
		do {
			printf("Search by Booking ID >");
			rewind(stdin);
			scanf("%s", search);
			system("cls");
			invalid = BookingIDValidation(search);
			if (invalid == 1) {
				printf("Please Enter a valid booking ID !!!\n");
			}

		} while (invalid == 1);
		//accepting new booking id
		do {
			printf("Please Enter new Booking ID >");
			rewind(stdin);
			scanf("%s", newBookingId);
			system("cls");
			invalid = BookingIDValidation(newBookingId);
			if (invalid == 1) {
				printf("Please Enter a valid booking ID !!!\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		//modifying booking data
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(search, book[i].bookingId) == 0) {
				strcpy(book[i].bookingId, newBookingId);
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");

			}
			fprintf(mBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);

		}

		break;
	case 2:
		system("cls");
		//searching booking ID
		do {
			printf("Search by Booking ID >");
			rewind(stdin);
			scanf("%s", search);
			system("cls");
			invalid = BookingIDValidation(search);
			if (invalid == 1) {
				printf("Please Enter a valid booking ID !!!\n");
			}
		} while (invalid == 1);
		rewind(stdin);
		//accepting new Member ID
		do {
			rewind(stdin);
			printf("Enter new Member ID >");
			scanf("%s", newMemberId);
			invalid = memberIDValidation(newMemberId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid Member ID\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		//modifying member id
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(search, book[i].bookingId) == 0) {
				strcpy(book[i].memberId, newMemberId);
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");
			}
			fprintf(mBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
		}

		break;
	case 3:
		system("cls");
		//searching booking ID
		do {
			printf("Search by Booking ID >");
			rewind(stdin);
			scanf("%s", search);
			system("cls");
			invalid = BookingIDValidation(search);
			if (invalid == 1) {
				printf("Please Enter a valid booking ID !!!\n");
			}

		} while (invalid == 1);
		//accepting new facility ID
		do {
			printf("Enter new Facility ID >");
			rewind(stdin);
			scanf("%s", newFacilityId);
			invalid = FacilityIDValidation(newFacilityId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid facility id !!!\n");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		//modifying facility id
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(search, book[i].bookingId) == 0) {
				strcpy(book[i].facilityId, newFacilityId);
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");
			}
			fprintf(mBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
		}
		break;
	case 4:
		system("cls");
		//searching booking ID
		printf("Search by Booking ID to edit >");
		rewind(stdin);
		scanf("%s", search);
		//acepting new time
		do {
			printf("Enter new New Time \n");
			printf("From (hh:mm)>");
			rewind(stdin);
			if (scanf("%d:%d", &newBookingTimeS.hour, &newBookingTimeS.minute) == 2) {
				invalid = timeValidation(newBookingTimeS.hour, newBookingTimeS.minute);
				if (invalid == 1) {
					system("cls");
					printf("invalid time or format ! Please Enter a correct time\n ");
				}
			}
			else {
				system("cls");
				printf("invalid time or format ! Please Enter a correct time\n ");
			}
		} while (invalid == 1);
		do {
			printf("Until (hh:mm)>");
			rewind(stdin);
			if (scanf("%d:%d", &newBookingTimeE.hour, &newBookingTimeE.minute) == 2) {
				invalid = timeValidation(newBookingTimeE.hour, newBookingTimeE.minute);
				if (invalid == 1) {
					system("cls");
					printf("invalid time or format ! Please Enter a correct time\n ");
				}
			}
			else {
				system("cls");
				printf("invalid time or format ! Please Enter a correct time\n ");
			}
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		//modify time
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(search, book[i].bookingId) == 0) {
				book[i].bookingTimeS.hour = newBookingTimeS.hour;
				book[i].bookingTimeS.minute = newBookingTimeS.minute;
				book[i].bookingTimeE.hour = newBookingTimeE.hour;
				book[i].bookingTimeE.minute = newBookingTimeE.minute;
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");

			}
			fprintf(mBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
		}
		break;
	case 5:
		system("cls");
		//searching booking ID
		printf("Search by Booking ID to edit >");
		rewind(stdin);
		scanf("%s", search);
		//accepting new date
		do {
			printf("Enter new Booking Date(dd/mm/yy) > ");
			rewind(stdin);
			if (scanf("%d/%d/%d", &newBookDate.day, &newBookDate.month, &newBookDate.year) == 3) {
				invalid = dateValidation(newBookDate.day, newBookDate.month, newBookDate.year);

				if (invalid == 1) {
					system("cls");
					printf("invalid date or format ! Please Enter a  correct date\n ");
				}
			}
			else
				invalid = 1;
		} while (invalid == 1);
		//Header
		printf("=======================================================================================================================================================================================\n");
		printf("\n");
		printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
		printf("=======================================================================================================================================================================================\n");
		for (int i = 0; i < recCount; i++)
		{

			if (strcmp(search, book[i].bookingId) == 0) {
				book[i].bookingDate.day = newBookDate.day;
				book[i].bookingDate.month = newBookDate.month;
				book[i].bookingDate.year = newBookDate.year;
				printf("=======================================================================================================================================================================================\n");
				printf("\n");
				printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
				printf("\n");
				printf("=======================================================================================================================================================================================\n");

			}
			fprintf(mBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
		}
		break;

	default:
		system("cls");
		printf("Please enter only (1 - 5)!\n");
		break;
	}
	fclose(mBookingRec);
}

void addBooking() {
	int invalid;
	char moreRec;
	Booking bookingAdd;
	FILE* aBookingRec;

	aBookingRec = fopen("bookingRec.txt", "a");

	if (aBookingRec == NULL) {
		printf("Error ! unable to open the bookingRec.txt file");
		return;
	}

	do {
		do {
			//getting record data
			printf("Enter Booking ID >");
			rewind(stdin);
			scanf("%s", &bookingAdd.bookingId);
			invalid = BookingIDValidation(bookingAdd.bookingId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid booking ID !!!\n");
			}
		} while (invalid == 1);
		do {
			rewind(stdin);
			printf("Enter Member ID >");
			scanf("%s", &bookingAdd.memberId);
			invalid = memberIDValidation(bookingAdd.memberId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid Member ID!!!\n");
			}
		} while (invalid == 1);
		do {
			printf("Enter Facility ID >");
			rewind(stdin);
			scanf("%s", &bookingAdd.facilityId);
			invalid = FacilityIDValidation(bookingAdd.facilityId);
			if (invalid == 1) {
				system("cls");
				printf("Please Enter a valid facility id !!!\n");
			}
		} while (invalid == 1);


		do {
			printf("Enter Booking Date(dd/mm/yyyy) > ");
			rewind(stdin);
			if (scanf("%d/%d/%d", &bookingAdd.bookingDate.day, &bookingAdd.bookingDate.month, &bookingAdd.bookingDate.year) == 3) {
				invalid = dateValidation(bookingAdd.bookingDate.day, bookingAdd.bookingDate.month, bookingAdd.bookingDate.year);

				if (invalid == 1) {
					system("cls");
					printf("invalid date or format ! Please Enter a  correct date\n ");
				}
			}
			else {
				invalid = 1;
			}
		} while (invalid == 1);
		do {
			printf("Enter Start Time(hh:mm) >");
			rewind(stdin);
			if (scanf("%d:%d", &bookingAdd.bookingTimeS.hour, &bookingAdd.bookingTimeS.minute) == 2) {
				invalid = timeValidation(bookingAdd.bookingTimeS.hour, bookingAdd.bookingTimeS.minute);

				if (invalid == 1) {
					system("cls");
					printf("invalid time or format ! Please Enter a correct time\n ");
				}
			}
			else {
				system("cls");
				printf("invalid time or format ! Please Enter a correct time\n ");
				invalid = 1;
			}
		} while (invalid == 1);

		do {
			printf("Enter End Time(hh:mm) >");
			rewind(stdin);
			if (scanf("%d:%d", &bookingAdd.bookingTimeE.hour, &bookingAdd.bookingTimeE.minute) == 2) {
				invalid = timeValidation(bookingAdd.bookingTimeE.hour, bookingAdd.bookingTimeE.minute);

				if (invalid == 1) {
					system("cls");
					printf("invalid time or format ! Please Enter a correct time\n ");
				}
			}
			else {
				system("cls");
				printf("invalid time or format ! Please Enter a correct time\n ");
				invalid = 1;
			}

			printf("Do you want to add more record ?(Y/N) >");
			rewind(stdin);
			scanf("%c", &moreRec);
			system("cls");
		} while (invalid == 1);

		fprintf(aBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", bookingAdd.bookingId, bookingAdd.memberId, bookingAdd.facilityId, bookingAdd.bookingTimeS.hour, bookingAdd.bookingTimeS.minute, bookingAdd.bookingTimeE.hour, bookingAdd.bookingTimeE.minute, bookingAdd.bookingDate.day, bookingAdd.bookingDate.month, bookingAdd.bookingDate.year);
	} while (toupper(moreRec) == 'Y');

	fclose(aBookingRec);
}

void deleteBooking(Booking book[], int recCount) {
	FILE* dBookingRec;
	char search[10], dConfirm;
	int notFound = 0, position = 0, i, invalid = 0;

	dBookingRec = fopen("bookingRec.txt", "w");

	if (dBookingRec == NULL) {
		printf("Error ! unable to open the bookingRec.txt file");
		return;
	}

	//search for the record that wanted to be delete
	do {
		printf("Search Booking ID to delete >");
		rewind(stdin);
		scanf("%s", search);
		invalid = BookingIDValidation(search);
		if (invalid == 1) {
			system("cls");
			printf("Please Enter a valid booking ID !!!\n");
		}
	} while (invalid == 1);

	for (i = 0; i < recCount; i++) {
		notFound = 0;
		if (strcmp(search, book[i].bookingId) == 0)
		{
			position = i;
			break;
		}
		else
			notFound = 1;
	}

	if (notFound == 0) {
		do {
			//display the record that going to be deleted
			printf("=======================================================================================================================================================================================\n");
			printf("\n");
			printf("Booking ID%30sMember ID%30sfacility ID%29sbooking time%29sbooking date\n", "", "", "", "");
			printf("=======================================================================================================================================================================================\n");
			printf("\n");
			printf("%8s%38s%40s%36.2d:%.2d-%.2d:%.2d%33.2d/%.2d/%.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);

			printf("\n");
			printf("=======================================================================================================================================================================================\n");
			//delete confirmation
			printf("Are you sure to delete the record above ?(Y/N) >");
			rewind(stdin);
			scanf("%c", &dConfirm);

			if (toupper(dConfirm) == 'Y') {
				for (i = position; i < recCount; i++) {
					book[i] = book[i + 1];
				}
				--recCount;
				printf("Booking deleted sucessfully.\n");
			}
			else if (dConfirm == 'N') {
				printf("The delete had been canceled.\n");
			}
			else {
				system("cls");
				invalid = 1;
				printf("Please Enter Y/N only !!\n");
			}
		} while (invalid == 1);
	}
	else {
		system("cls");
		printf("Booking ID <%s> not found !\n", search);
	}

	for (i = 0; i < recCount; i++) {
		fprintf(dBookingRec, "%s,%s,%s %.2d %.2d %.2d %.2d %.2d %.2d %.2d\n", book[i].bookingId, book[i].memberId, book[i].facilityId, book[i].bookingTimeS.hour, book[i].bookingTimeS.minute, book[i].bookingTimeE.hour, book[i].bookingTimeE.minute, book[i].bookingDate.day, book[i].bookingDate.month, book[i].bookingDate.year);
	}

	fclose(dBookingRec);
}

void BookingReport(Booking book[], int recCount) {
	int jan = 0, feb = 0, mar = 0, apr = 0, may = 0, jun = 0, jul = 0, aug = 0, sep = 0, oct = 0, nov = 0, dec = 0;
	FILE* bookReport;
	bookReport = fopen("Bookingreport.txt", "w");
	if (bookReport == NULL) {
		printf("Error ! unable to open the BookingReport.txt file");
		return;
	}


	//counting record
	for (int i = 0; i < recCount; i++)
	{
		if (book[i].bookingDate.month == 1)
			jan++;
		else if (book[i].bookingDate.month == 2)
			feb++;
		else if (book[i].bookingDate.month == 3)
			mar++;
		else if (book[i].bookingDate.month == 4)
			apr++;
		else if (book[i].bookingDate.month == 5)
			may++;
		else if (book[i].bookingDate.month == 6)
			jun++;
		else if (book[i].bookingDate.month == 7)
			jul++;
		else if (book[i].bookingDate.month == 8)
			aug++;
		else if (book[i].bookingDate.month == 9)
			sep++;
		else if (book[i].bookingDate.month == 10)
			oct++;
		else if (book[i].bookingDate.month == 11)
			nov++;
		else if (book[i].bookingDate.month == 12)
			dec++;
	}
	//display booking report
	printf("\t\t\t\t    Booking Record Report");
	printf("\n");
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on January : %d\t\t\t\t", jan);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on February : %d\t\t\t\t", feb);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on March : %d\t\t\t\t", mar);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on April : %d\t\t\t\t", apr);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on May : %d\t\t\t\t\t", may);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on June : %d\t\t\t\t", jun);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on July : %d\t\t\t\t", jul);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on August : %d\t\t\t\t", aug);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on September : %d\t\t\t\t", sep);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on October : %d\t\t\t\t", oct);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on November : %d\t\t\t\t", nov);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\t\t\t\tBooking made on December : %d\t\t\t\t", dec);
	printf("\n");
	printf("==========================================================================================\n");
	printf("\n");
	printf("Total %d record  \n", recCount);

	fprintf(bookReport,
		"%32sBooking Record Report"
		"\n"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on January : %-28d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on February : %-27d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on March : %-30d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on April : %-30d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on May : %-32d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on June : %-31d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on July : %-31d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on August : %-29d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on September : %-26d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on October : %-28d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on November : %-27d"
		"\n"
		"=======================================================================================\n"
		"%31sBooking made on December : %-27d"
		"\n"
		"=======================================================================================\n"
		"\n"
		"Total %d record  \n", "", "", jan, "", feb, "", mar, "", apr, "", may, "", jun, "", jul, "", aug, "", sep, "", oct, "", nov, "", dec, recCount
	);
}


// Facility usage section
void FacilityUsageMenu() {

	FILE* fpUsage;
	Usage usage[500];
	char subChoice[50] = "";
	int invalid, recCount = 0;

	//Loop Menu
	while (1 == 1)
	{
		recCount = 0;
		fpUsage = fopen("UsageModuleRec.txt", "r");

		//Check whether file open successfully
		if (fpUsage == NULL)
		{
			printf("Error! Unable to open facility Usage file!");
			return;
		}

		//Read data in txt file into array of structure
		while (fscanf(fpUsage, "%d/%d/%d|%d:%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%d:%d|%d:%d|\n", &usage[recCount].usageDate.day, &usage[recCount].usageDate.month, &usage[recCount].usageDate.year, &usage[recCount].t.hour, &usage[recCount].t.minute, &usage[recCount].memberID, &usage[recCount].facilityID, &usage[recCount].facilityName, &usage[recCount].bookingID, &usage[recCount].usageType, &usage[recCount].checkInHour, &usage[recCount].checkInMinutes, &usage[recCount].checkOutHour, &usage[recCount].checkOutMinutes) != EOF)
		{
			recCount++;
		}

		fclose(fpUsage);

		FacilityUsageHeader();

		printf(
			"\t\t\t0. Go Back Main Menu\n"
			"\t\t\t1. Display Facility Usage Details\n"
			"\t\t\t2. Add Facility Usage Details\n"
			"\t\t\t3. Search Facility Usage Details\n"
			"\t\t\t4. Modify Facility Usage Details\n"
			"\t\t\t5. Delete Facility Usage Details\n"
			"\t\t\t6. Most Use Facility Report\n\n"
		);

		printf("\tEnter your choice > ");
		scanf(" %[^\n]", subChoice);

		//Check validation
		invalid = choiceValidation(subChoice);

		system("cls");

		if (invalid != 1)
		{
			switch (atoi(subChoice))
			{
			case 0:
				return;
				break;
			case 1:
				FacilityUsageDisplay(usage, recCount);
				break;
			case 2:
				FacilityUsageAdd();
				break;
			case 3:
				FacilityUsageSearch(usage, recCount);
				break;
			case 4:
				FacilityUsageModify(usage, recCount);
				break;
			case 5:
				FacilityUsageDelete(usage, recCount);
				break;
			case 6:
				FacilityUsageReport(usage, recCount);
				break;
			default:
				printf("\tPlease enter only (0 - 6)!\n");
				invalid = 1;
				break;
			}

			if (invalid != 1)
			{
				system("pause");
				system("cls");
			}
		}
		else
			printf("\tPlease enter only (0 - 6)!\n");
	}
}

void FacilityUsageHeader() {
	printf("\t\t   000000                  00  00  00     00\n");
	printf("\t\t   00     0000000  000000      00      00000000\n");
	printf("\t\t   00000  00   00  00      00  00  00     00    00   00\n");
	printf("\t\t   00     0000000  00      00  00  00     00    00   00\n");
	printf("\t\t   00          00  000000  00  00  00     00    0000000\n");
	printf("\t\t                                                     00\n");
	printf("\t  00    00  0000000      0000      000000000   00000000      00\n");
	printf("\t  00    00  00          00  00     00          00        00  00\n");
	printf("\t  00    00  0000000    00    00    00  00000   00000000   0000\n");
	printf("\t  00    00       00   0000000000   00     00   00\n");
	printf("\t  00000000  0000000  00        00  000000000   00000000\n\n");
}

void FacilityUsageDisplay(Usage usage[], int recCount)
{
	printf("\n\t\t\t\t\t\t\t**Facility Usage Details**\n");
	printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
	printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
	printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

	//Print facility details
	for (int i = 0; i < recCount; i++)
	{
		printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
	}

	printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
}

void FacilityUsageAdd() {

	FILE* fpUsage;
	FILE* fpFacility;
	FILE* rBookingRec;
	FILE* fpMember;

	Facilities info[SIZE];
	Booking book[500];
	Member member[200];

	fpUsage = fopen("UsageModuleRec.txt", "a");
	fpFacility = fopen("facilitiyInfo.txt", "r");
	rBookingRec = fopen("bookingRec.txt", "r");
	fpMember = fopen("membersInfo.bin", "r");

	//Check whether file open successfully
	if (fpUsage == NULL)
	{
		printf("Error! Unable to open facility Usage file!");
		return;
	}

	//Check whether file open successfully
	if (rBookingRec == NULL)
	{
		printf("Error! Unable to open booking file!");
		return;
	}

	//Check whether file open successfully
	if (fpFacility == NULL)
	{
		printf("Error! Unable to open facility file!");
		return;
	}


	//Check whether file open successfully
	if (!(fpMember = fopen("membersInfo.bin", "rb")))
	{
		printf("Error in reading membersInfo.bin!\n");
		return;
	}

	int dayAdded, monthAdded, yearAdded, hourAdded, minutesAdded, checkInHourAdded, checkInMinutesAdded, checkOutHourAdded, checkOutMinutesAdded, count = 0, invalid, nRecords = 0, recCount = 0, rec = 0;
	char memberIDAdded[99], facilityIDAdded[99], facilityNameAdded[99], usageTypeAdded[99], confirm, facilityID[4], facilityName[99], bookingIDAdded[99];

	//Loop FacilityUsageAdd
	do {
		//Booking Date
		system("cls");

		do {
			printf("\tEnter booking date (DD/MM/YYYY) > ");
			if (scanf("%d/%d/%d", &dayAdded, &monthAdded, &yearAdded) == 3)
			{
				//Validation date input
				invalid = dateValidation(dayAdded, monthAdded, yearAdded);

				if (invalid == 1)
				{
					printf("\tInvalid date or format! Please enter a correct date again!\n\n");
				}
			}
			else
			{
				printf("\tInvalid date or format! Please enter a correct date again!\n\n");
				invalid = 1;
			}

		} while (invalid == 1);

		//Booked Time
		do {
			printf("\tBooked Time (e.g. 10:30) > ");
			if (scanf("%d:%d", &hourAdded, &minutesAdded))
			{
				//Validation time input
				invalid = timeValidation(hourAdded, minutesAdded);

				if (invalid == 1)
				{
					printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				}
			}
			else
			{
				printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				invalid = 1;
			}

		} while (invalid == 1);

		//Member ID
		do {
			printf("\tMember ID > ");
			rewind(stdin);
			if (scanf("%[^\n]", &memberIDAdded) == 1)
			{
				//Check validation
				invalid = memberIDValidation(memberIDAdded);
				if (invalid == 1)
				{
					printf("\tInvalid Member ID format!\n");
				}

				//To check whether the Member ID exist
				while (fread(&member[rec], sizeof(Member), 1, fpMember) != 0)
				{
					if (strcmp(memberIDAdded, member[rec].memID) == 0)
					{
						invalid = 0;
						break;
					}
					else
					{
						invalid = 1;
					}

					rec++;
				}

				if (invalid == 1)
				{
					printf("\tThis Member ID doesn't exist! Please enter a correct Member ID again!\n\n");
				}

			}
		} while (invalid == 1);

		//Facility ID
		do {
			printf("\tFacility ID > ");
			rewind(stdin);
			if (scanf("%[^\n]", &facilityIDAdded))
			{
				//Check Validation
				invalid = FacilityIDValidation(facilityIDAdded);
				if (invalid == 1)
				{
					printf("\tInvalid Facility ID format!\n");
				}

				//To check whether the Facility ID exist
				while (fscanf(fpFacility, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", info[nRecords].facID, info[nRecords].facType, info[nRecords].facDesc, info[nRecords].facCategory, info[nRecords].facLocation, info[nRecords].rem.facStatus, info[nRecords].rem.maxUsers, info[nRecords].rem.facRules) != EOF)
				{

					nRecords++;
				}

				for (int i = 0; i < nRecords; i++)
				{
					if (strcmp(facilityIDAdded, info[i].facID) == 0) {
						invalid = 0;
						break;
					}
					else
					{
						invalid = 1;
					}

				}

				if (invalid == 1)
				{
					printf("\tThis Facility ID doesn't exist! Please enter a correct Facility ID again!\n\n");
				}

			}
		} while (invalid == 1);


		//Compare Facility ID to find Facility Name
		for (int j = 0; j < nRecords; j++) {
			if (strcmp(facilityIDAdded, info[j].facID) == 0)
			{
				strcpy(facilityNameAdded, info[j].facDesc);
			}
		}

		//Booking ID
		do
		{
			printf("\tBooking ID > ");
			if (scanf(" %[^\n]", &bookingIDAdded));
			{
				//To check whether the Booking ID exist
				while (fscanf(rBookingRec, "%[^,], %[^,], %s %d %d %d %d %d %d %d\n", book[recCount].bookingId, book[recCount].memberId, &book[recCount].facilityId, &book[recCount].bookingTimeS.hour, &book[recCount].bookingTimeS.minute, &book[recCount].bookingTimeE.hour, &book[recCount].bookingTimeE.minute, &book[recCount].bookingDate.day, &book[recCount].bookingDate.month, &book[recCount].bookingDate.year) != EOF)
				{
					recCount++;
				}

				for (int i = 0; i < recCount; i++)
				{
					if (strcmp(bookingIDAdded, book[i].bookingId) == 0) {
						invalid = 0;
						break;
					}
					else
					{
						invalid = 1;
					}
				}

				if (invalid == 1)
				{
					printf("\tThis Booking ID doesn't exist! Please enter a correct Booking ID again!\n\n");
				}
			}

		} while (invalid == 1);

		//Usage Type
		do {
			printf("\tUsage Type (booked/walk-in) > ");
			rewind(stdin);
			if (scanf(" %[^\n]", &usageTypeAdded) == 1)
			{
				if (strcmp(usageTypeAdded, "booked") == 0 || strcmp(usageTypeAdded, "walk-in") == 0)
				{
					invalid = 0;
				}
				else
				{
					invalid = 1;
					printf("\tInvalid usage type! Please enter booked/walk-in only!\n\n");
				}
			}
		} while (invalid == 1);

		//Check In
		do {
			printf("\tCheck In Time (e.g. 10:30) > ");
			if (scanf("%d:%d", &checkInHourAdded, &checkInMinutesAdded))
			{
				//Validation time input
				invalid = timeValidation(checkInHourAdded, checkInMinutesAdded);

				if (invalid == 1)
				{
					printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				}
			}
			else
			{
				printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				invalid = 1;
			}

		} while (invalid == 1);

		//Check Out
		do {
			printf("\tCheck Out Time (e.g. 10:30) > ");
			if (scanf("%d:%d", &checkOutHourAdded, &checkOutMinutesAdded))
			{
				//Validation time input
				invalid = timeValidation(checkOutHourAdded, checkOutMinutesAdded);

				if (invalid == 1)
				{
					printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				}
			}
			else
			{
				printf("\tInvalid time or format! Please enter a correct time again!\n\n");
				invalid = 1;
			}

		} while (invalid == 1);

		//write into file
		fprintf(fpUsage, "%02d/%02d/%d|%02d:%02d|%s|%s|%s|%s|%s|%02d:%02d|%02d:%02d|\n", dayAdded, monthAdded, yearAdded, hourAdded, minutesAdded, memberIDAdded, facilityIDAdded, facilityNameAdded, bookingIDAdded, usageTypeAdded, checkInHourAdded, checkInMinutesAdded, checkOutHourAdded, checkOutMinutesAdded);

		count++;

		printf("\tAdd another record (Y = yes)? > ");
		rewind(stdin);
		scanf("%c", &confirm);

	} while (toupper(confirm) == 'Y');

	//Show the quantity of records have been added in file
	printf("\n\t%d records have been added to UsageModuleRec.txt\n\n", count);

	fclose(fpUsage);
	fclose(fpFacility);
	fclose(rBookingRec);
	fclose(fpMember);
}

void FacilityUsageSearch(Usage usage[], int recCount) {

	int invalid, searchCount = 0;
	char choice[50], searchContent[99], confirm;

	do {
		searchCount = 0;

		system("cls");

		// Search
		do {
			printf("\n\t1. Member ID\n"
				"\t2. Facility ID\n"
				"\t3. Usage Type\n");

			printf("\tEnter your choice to search(0 to exit) > ");
			scanf(" %[^\n]", choice);

			//Check validation
			invalid = choiceValidation(choice);

			if (invalid != 1)
			{
				switch (atoi(choice))
				{
				case 0:
					return;
					break;
				case 1:
					printf("\tEnter Member ID (e.g. M1234)> ");
					break;
				case 2:
					printf("\tEnter Facility ID (e.g. KA1)> ");
					break;
				case 3:
					printf("\tEnter Usage Type (e.g. booked/walk-in)> ");
					break;
				default:
					printf("\tPlease enter only (0 - 3)!\n");
					invalid = 1;
					break;
				}

				//Read user's input for search
				if (invalid != 1)
					scanf(" %[^\n]", searchContent);
			}
			else
				printf("\tPlease enter only (0 - 3)!\n");

		} while (invalid != 0);

		//Display the particular detail that user search
		printf("\n\t\t\t\t\t\t\t**Facility Usage Search Details**\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
		printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

		for (int i = 0; i < recCount; i++)
		{
			if ((strcmp(usage[i].memberID, searchContent)) == 0 || (strcmp(usage[i].facilityID, searchContent)) == 0 || (strcmp(usage[i].usageType, searchContent)) == 0)
			{
				printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);

				searchCount++;
			}
		}

		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

		printf("\tTotal %d Search Result\n\n", searchCount);

		printf("\tDo you want to search again (Y = yes) ?");
		rewind(stdin);
		scanf("%c", &confirm);

	} while (toupper(confirm) == 'Y');
}

void FacilityUsageModify(Usage usage[], int recCount) {
	FILE* fpUsage;
	FILE* fpFacility;
	FILE* rBookingRec;
	FILE* fpMember;

	Facilities info[SIZE];
	Booking book[500];
	Member member[200];

	int newDay, newMonth, newYear, newHour, newMinutes, newCheckInHour, newCheckInMinutes, newCheckOutHour, newCheckOutMinutes, oldBookingID, newBookingID, invalid, search, nRecords = 0, rec = 0, recC = 0;
	char newMemberID[6], newFacilityID[4], newUsageType[99], modifyChoice[50], confirmation, modifyCheck = 0, confirm, facilityID[4], facilityName[99];

	fpUsage = fopen("UsageModuleRec.txt", "w");
	fpFacility = fopen("facilitiyInfo.txt", "r");
	rBookingRec = fopen("bookingRec.txt", "r");
	fpMember = fopen("membersInfo.bin", "r");

	//Check whether file open successfully
	if (fpUsage == NULL)
	{
		printf("Error! Unable to open facility Usage file!");
		return;
	}

	//Check whether file open successfully
	if (fpFacility == NULL)
	{
		printf("Error! Unable to open facility file!");
		return;
	}

	//Check whether file open successfully
	if (rBookingRec == NULL)
	{
		printf("Error! Unable to open booking file!");
		return;
	}

	//Check whether file open successfully
	if (!(fpMember = fopen("membersInfo.bin", "rb")))
	{
		printf("Error in reading membersInfo.bin!\n");
		return;
	}

	//Display Facility Usage Record 
	FacilityUsageDisplay(usage, recCount);

	printf("\n\t1. Date Booked\n"
		"\t2. Time Booked\n"
		"\t3. Member ID\n"
		"\t4. Facility ID\n"
		"\t5. Booking ID\n"
		"\t6. Usage Type\n"
		"\t7. Check In\n"
		"\t8. Check Out\n");

	printf("\tEnter your choice (0 to exit) > ");
	scanf(" %[^\n]", modifyChoice);

	//Check validation
	invalid = choiceValidation(modifyChoice);

	if (invalid != 1)
	{
		switch (atoi(modifyChoice))
		{
		case 0:
			break;

			//Date Booked
		case 1:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{

				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							modifyCheck = 0;
							printf("\tEnter a new Date Booked(DD/MM/YYYY) > ");
							if (scanf("%d/%d/%d", &newDay, &newMonth, &newYear) == 3)
							{
								//Validation date input
								invalid = dateValidation(newDay, newMonth, newYear);

								if (invalid == 1)
								{
									printf("\tInvalid date or format! Please enter a correct date again!\n");
								}
							}
							else
							{
								printf("\tInvalid date or format! Please enter a correct date again!\n");
								invalid = 1;
							}

						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying the day,month,year
						if (toupper(confirmation) == 'Y')
						{
							usage[i].usageDate.day = newDay;
							usage[i].usageDate.month = newMonth;
							usage[i].usageDate.year = newYear;
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Date Booked again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Time Booked
		case 2:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new Time Booked (e.g. 10:30) > ");
							if (scanf("%d:%d", &newHour, &newMinutes))
							{
								//Validation time input
								invalid = timeValidation(newHour, newMinutes);

								if (invalid == 1)
								{
									printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								}
							}
							else
							{
								printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								invalid = 1;
							}

						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying hour and minutes
						if (toupper(confirmation) == 'Y')
						{
							usage[i].t.hour = newHour;
							usage[i].t.minute = newMinutes;
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Time Booked again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Member ID
		case 3:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new member ID > ");
							rewind(stdin);
							if (scanf("%[^\n]", &newMemberID) == 1)
							{
								//Check validation
								invalid = memberIDValidation(newMemberID);
								if (invalid == 1)
								{
									printf("\tInvalid Member ID format!\n");
								}

								//To check whether the Member ID exist
								while (fread(&member[rec], sizeof(Member), 1, fpMember) != 0)
								{
									if (strcmp(newMemberID, member[rec].memID) == 0)
									{
										invalid = 0;
										break;
									}
									else
									{
										invalid = 1;
									}

									rec++;
								}

								if (invalid == 1)
								{
									printf("\tThis Member ID doesn't exist! Please enter a correct Member ID again!\n\n");
								}
							}
						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Member ID
						if (toupper(confirmation) == 'Y')
						{
							strcpy(usage[i].memberID, newMemberID);
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}
				printf("\tDo you want to modify Member ID again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Facility ID
		case 4:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new Facility ID > ");
							rewind(stdin);
							if (scanf("%[^\n]", &newFacilityID))
							{
								//Check validation
								invalid = FacilityIDValidation(newFacilityID);
								if (invalid == 1)
								{
									printf("\tInvalid Facility ID format!\n");
								}

								//To check whether the Facility ID exist
								while (fscanf(fpFacility, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", info[nRecords].facID, info[nRecords].facType, info[nRecords].facDesc, info[nRecords].facCategory, info[nRecords].facLocation, info[nRecords].rem.facStatus, info[nRecords].rem.maxUsers, info[nRecords].rem.facRules) != EOF)
								{

									nRecords++;
								}

								for (int i = 0; i < nRecords; i++)
								{
									if (strcmp(newFacilityID, info[i].facID) == 0) {
										invalid = 0;
										break;
									}
									else
									{
										invalid = 1;
									}

								}

								if (invalid == 1)
								{
									printf("\tThis Facility ID doesn't exist! Please enter a correct Facility ID again!\n\n");
								}
							}
						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Facility ID
						if (toupper(confirmation) == 'Y')
						{
							strcpy(usage[i].facilityID, newFacilityID);
							modifyCheck = 1;
						}

						//Compare Facility ID to find Facility Name
						for (int j = 0; j < nRecords; j++)
						{
							if (strcmp(usage[i].facilityID, info[j].facID) == 0)
							{
								strcpy(usage[i].facilityName, info[j].facDesc);
							}
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Facility ID again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Booking ID
		case 5:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tEnter a Booking ID to be modified > ");
				scanf("%d", &oldBookingID);


				for (int i = 0; i < recCount; i++)
				{
					if (oldBookingID == usage[i].bookingID)
					{
						do
						{
							printf("\tEnter a new Booking ID > ");
							scanf("%d", &newBookingID);


							//To check whether the Booking ID exist
							while (fscanf(rBookingRec, "%[^,], %[^,], %s %d %d %d %d %d %d %d\n", book[recC].bookingId, book[recC].memberId, &book[recC].facilityId, &book[recC].bookingTimeS.hour, &book[recC].bookingTimeS.minute, &book[recC].bookingTimeE.hour, &book[recC].bookingTimeE.minute, &book[recC].bookingDate.day, &book[recC].bookingDate.month, &book[recC].bookingDate.year) != EOF)
							{
								recC++;
							}

							for (int i = 0; i < recCount; i++)
							{
								if (newBookingID == atoi(book[i].bookingId))
								{
									invalid = 0;
									break;
								}
								else
								{
									invalid = 1;
								}
							}

							if (invalid == 1)
							{
								printf("\tThis Booking ID doesn't exist! Please enter a correct Booking ID again!\n\n");
							}
						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Booking ID
						if (toupper(confirmation) == 'Y')
						{
							usage[i].bookingID = newBookingID;
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Booking ID again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Usage Type
		case 6:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new Usage Type (booked/walk-in)> ");
							rewind(stdin);
							if (scanf(" %[^\n]", &newUsageType) == 1)
							{
								if (strcmp(newUsageType, "booked") == 0 || strcmp(newUsageType, "walk-in") == 0)
								{
									invalid = 0;
								}
								else
								{
									invalid = 1;
									printf("\tInvalid usage type! Please enter booked/walk-in only!\n\n");
								}
							}
						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Usage Type
						if (toupper(confirmation) == 'Y')
						{
							strcpy(usage[i].usageType, newUsageType);
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Usage Type again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Check In
		case 7:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new Check In Time (e.g. 10:30) > ");
							if (scanf("%d:%d", &newCheckInHour, &newCheckInMinutes))
							{
								//Validation time input
								invalid = timeValidation(newCheckInHour, newCheckInMinutes);

								if (invalid == 1)
								{
									printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								}
							}
							else
							{
								printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								invalid = 1;
							}

						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Check in hour and minutes
						if (toupper(confirmation) == 'Y')
						{
							usage[i].checkInHour = newCheckInHour;
							usage[i].checkInMinutes = newCheckInMinutes;
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Check In Time again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

			//Check Out
		case 8:
			system("cls");

			//Display Facility Usage Record
			FacilityUsageDisplay(usage, recCount);

			do
			{
				printf("\tSearch by Booking ID to edit >");
				scanf("%d", &search);

				for (int i = 0; i < recCount; i++)
				{
					if (search == usage[i].bookingID)
					{
						do {
							printf("\tEnter a new Check Out Time (e.g. 10:30) > ");
							if (scanf("%d:%d", &newCheckOutHour, &newCheckOutMinutes))
							{
								//Validation time input
								invalid = timeValidation(newCheckOutHour, newCheckOutMinutes);

								if (invalid == 1)
								{
									printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								}
							}
							else
							{
								printf("\tInvalid time or format! Please enter a correct time again!\n\n");
								invalid = 1;
							}

						} while (invalid == 1);

						printf("\tSure to modify (Y = yes)? > ");
						rewind(stdin);
						scanf("%c", &confirmation);

						//Modifying Check out hour and minutes
						if (toupper(confirmation) == 'Y')
						{
							usage[i].checkOutHour = newCheckOutHour;
							usage[i].checkOutMinutes = newCheckOutMinutes;
							modifyCheck = 1;
						}

						//Display the particular new result
						if (modifyCheck = 1)
						{
							printf("\n\t\t\t\t\t\t\t**Modification result**\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
							printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
							printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

							if (toupper(confirmation) == 'Y')
							{
								printf("\tSuccessfully modified.\n\n");
							}
							else
							{
								printf("\tData remain unchanged.\n\n");
							}
						}
						else
						{
							printf("\tRecord was not modified.\n");
						}

					}

				}

				printf("\tDo you want to modify Check Out Time again? ('Y'=yes/'N'=no) > ");
				rewind(stdin);
				scanf("%c", &confirm);

			} while (toupper(confirm) == 'Y');

			break;

		default:
			invalid = 1;
			printf("\tPlease enter only (0 - 8)!\n");
			break;
		}

	}
	else
	{
		printf("\tPlease enter only (0 - 8)!\n");
	}

	//Write new result into file
	for (int i = 0; i < recCount; i++)
	{
		fprintf(fpUsage, "%02d/%02d/%d|%02d:%02d|%s|%s|%s|%04d|%s|%02d:%02d|%02d:%02d|\n", usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].facilityID, usage[i].facilityName, usage[i].bookingID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
	}

	fclose(fpUsage);
	fclose(fpFacility);
	fclose(rBookingRec);
	fclose(fpMember);
}

void FacilityUsageDelete(Usage usage[], int recCount) {
	FILE* fpUsage;
	char confirmation, confirm;//, search[4]
	int deleteCount = 0, search;

	fpUsage = fopen("UsageModuleRec.txt", "w");

	//Check whether file open successfully
	if (fpUsage == NULL)
	{
		printf("Error! Unable to open facility Usage file!");
		return;
	}

	do
	{
		system("cls");
		//Display Facility Usage Record
		printf("\n\t\t\t\t\t\t\t**Facility Usage Details**\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
		printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

		//Print facility details
		for (int i = 0; i < recCount; i++)
		{
			printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
		}

		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");

		printf("\n\tEnter a Booking ID to delete the row > ");
		scanf("%d", &search);

		//Display record that need to delete
		printf("\n\t\t\t\t\t\t\t**Facility Usage Details**\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
		printf("\t|Booking ID  |Facility ID  |Facility Name    |Date Booked  |Time Booked  |Member ID  |Usage Type  |Check In  |Check Out  |\n");
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n");
		for (int i = 0; i < recCount; i++)
		{
			if (search == usage[i].bookingID)
			{
				printf("\t|%04d%8s|%-13s|%-17s|%2d/%2d/%-7d|%2d:%-10.2d|%-11s|%-12s|%2d:%-7.2d|%2d:%-8.2d|\n", usage[i].bookingID, "", usage[i].facilityID, usage[i].facilityName, usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
			}

		}
		printf("\t+------------+-------------+-----------------+-------------+-------------+-----------+------------+----------+-----------+\n\n");

		//Confirm Deletion
		printf("\tAre you sure you want to delete these records ('Y'=yes) > ");
		rewind(stdin);
		scanf("%c", &confirmation);
		if (toupper(confirmation) == 'Y')
		{
			for (int i = 0; i < recCount; i++)
			{
				if (search == usage[i].bookingID)
				{
					for (int j = i; j < recCount; j++)
					{
						usage[j] = usage[j + 1];
					}
					recCount--;
					printf("\tDelete Successful.\n\n");
					deleteCount++;
				}
			}
		}

		printf("\tDelete another record (Y = yes) ? ");
		rewind(stdin);
		scanf("%c", &confirm);

	} while (toupper(confirm) == 'Y');

	//Display total delete
	printf("\n\t%d record(s) have been deleted\n", deleteCount);

	//Write all details again into file
	for (int i = 0; i < recCount; i++)
	{
		fprintf(fpUsage, "%02d/%02d/%d|%02d:%02d|%s|%s|%s|%04d|%s|%02d:%02d|%02d:%02d|\n", usage[i].usageDate.day, usage[i].usageDate.month, usage[i].usageDate.year, usage[i].t.hour, usage[i].t.minute, usage[i].memberID, usage[i].facilityID, usage[i].facilityName, usage[i].bookingID, usage[i].usageType, usage[i].checkInHour, usage[i].checkInMinutes, usage[i].checkOutHour, usage[i].checkOutMinutes);
	}

	fclose(fpUsage);
}

void FacilityUsageReport(Usage usage[], int recCount) {

	FILE* ffUsage;
	FILE* fgUsage;
	ffUsage = fopen("MostUseFacility.txt", "w+");
	fgUsage = fopen("MostUseFacilityReport.txt", "w+");

	int counted = 0, rec = 0, frequency[99], temp1;
	char facilityID[99][4], facilityName[99][99], facility[99][4], temp2[4], temp3[99];

	//Check whether file open successfully
	if (ffUsage == NULL)
	{
		printf("Error! Unable to open most use facility file!");
		return;
	}

	//Check whether file open successfully
	if (fgUsage == NULL)
	{
		printf("Error! Unable to open most use facility file!");
		return;
	}

	//printf("%d", recCount);

	for (int i = 0; i < recCount; i++)
	{
		// Check to see if the Facility ID at index i has already been counted
		bool already_counted = false;
		for (int j = 0; j < counted; j++)
			if (strcmp(usage[i].facilityID, facility[j]) == 0)
				already_counted = true;

		// If the Facility ID has already been counted, skip ahead to the next 
		if (already_counted) continue;

		// Count it now if we haven't already counted the Facility ID
		int count = 0;
		for (int j = 0; j < recCount; j++)
			if (strcmp(usage[i].facilityID, usage[j].facilityID) == 0) {
				count++;
			}

		// output the count to MostUseFacility.txt
		fprintf(ffUsage, "%s|%s|%d|\n", usage[i].facilityID, usage[i].facilityName, count);

		// add the Facility ID to the array of facility we've found so far
		strcpy(facility[counted], usage[i].facilityID);
		counted++;
	}

	rewind(ffUsage);
	//Read the result of each Facility ID repeat how many times
	while (fscanf(ffUsage, "%[^|]|%[^|]|%d|\n", &facilityID[rec], &facilityName[rec], &frequency[rec]) != EOF)
	{
		rec++;
	}

	//Making the frequency become descending order, to show the highest frequency to lowest frequency of Facility ID
	for (int i = 0; i < rec; i++)
	{

		for (int j = i + 1; j < rec; j++)
		{
			if (frequency[j] > frequency[i])
			{
				temp1 = frequency[i];
				strcpy(temp2, facilityID[i]);
				strcpy(temp3, facilityName[i]);

				frequency[i] = frequency[j];
				strcpy(facilityID[i], facilityID[j]);
				strcpy(facilityName[i], facilityName[j]);

				frequency[j] = temp1;
				strcpy(facilityID[j], temp2);
				strcpy(facilityName[j], temp3);

			}
		}
	}

	printf("\t\t**Most Use Facility Report**\n");
	printf("\t+-------------+-----------------+-----------+\n");
	printf("\t|Facility ID  |Facility Name    |Frequency  |\n");
	printf("\t+-------------+-----------------+-----------+\n");

	for (int i = 0; i < rec; i++)
	{
		printf("\t|%-13s|%-17s|%-11d|\n", facilityID[i], facilityName[i], frequency[i]);
		printf("\t+-------------+-----------------+-----------+\n");
	}


	//Write report into Most Use Facility Report txt file
	fprintf(fgUsage, "         **Most Use Facility Report**\n");
	fprintf(fgUsage, "+-------------+-----------------+-----------+\n");
	fprintf(fgUsage, "|Facility ID  |Facility Name    |Frequency  |\n");
	fprintf(fgUsage, "+-------------+-----------------+-----------+\n");
	for (int i = 0; i < rec; i++)
	{
		fprintf(fgUsage, "|%-13s|%-17s|%-11d|\n", facilityID[i], facilityName[i], frequency[i]);
		fprintf(fgUsage, "+-------------+-----------------+-----------+\n");
	}

	fclose(fgUsage);
	fclose(ffUsage);
}


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
