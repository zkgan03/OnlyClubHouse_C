#include <stdio.h>
#include <stdlib.h>

#include "Booking.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)

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
