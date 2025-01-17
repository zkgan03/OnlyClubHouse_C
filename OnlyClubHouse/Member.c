#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Member.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

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

