#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Common.h"
#include "Staff.h"
#include "Member.h"
#include "Facility.h"
#include "Booking.h"
#include "FacilityUsage.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
#pragma warning (disable: 4013)


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