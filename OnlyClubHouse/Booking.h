#pragma once

#include "Common.h"

typedef struct {
	char bookingId[10], memberId[10], facilityId[10];
	Date todayDate, bookingDate;
	Time bookingTimeS, bookingTimeE;
} Booking;

void bookingMenu();
void addBooking();
void searchBooking(Booking book[], int recCount);
void displayBooking(Booking book[], int recCount);
void editBooking(Booking book[], int recCount);
void deleteBooking(Booking book[], int recCount);
void BookingReport(Booking book[], int recCount);