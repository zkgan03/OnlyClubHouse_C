#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "FacilityUsage.h"
#include "Facility.h"
#include "Booking.h"
#include "Member.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

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
