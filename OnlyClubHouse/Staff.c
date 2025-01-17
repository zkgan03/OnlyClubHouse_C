#include <stdio.h>
#include <stdlib.h>

#include "Staff.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

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

		printf("number of staff = %d\n", nStaff);

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

