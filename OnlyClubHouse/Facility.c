#include <stdio.h>
#include <stdlib.h>

#include "Facility.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

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

