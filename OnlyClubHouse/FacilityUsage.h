#pragma once

#include "Common.h"

typedef struct {
	Date usageDate;
	Time t;
	char memberID[6], facilityID[4], facilityName[99], usageType[99];
	int bookingID, checkInHour, checkInMinutes, checkOutHour, checkOutMinutes;
} Usage;

void FacilityUsageHeader();
void FacilityUsageMenu();
void FacilityUsageDisplay(Usage usage[], int recCount);
void FacilityUsageAdd();
void FacilityUsageSearch(Usage usage[], int recCount);
void FacilityUsageModify(Usage usage[], int recCount);
void FacilityUsageDelete(Usage usage[], int recCount);
void FacilityUsageReport(Usage usage[], int recCount);
