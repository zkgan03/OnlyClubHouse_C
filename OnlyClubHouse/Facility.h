#pragma once

#include "Common.h"

typedef struct {
	char facStatus[20], maxUsers[20], facRules[100];
} Remarks;

typedef struct {
	char facID[20], facType[20], facDesc[30], facCategory[20], facLocation[20];
	Remarks rem;
} Facilities;


void FacilityMenu();
void DisplayFacilitiesRecords(Facilities info[], int nRecords);
void AddFacilitiesRecords(Facilities info[], int nRecords);
void SearchFacilitiesRecords(Facilities info[], int nRecords);
void ModifyFacilitiesRecords(Facilities info[], int nRecords);
void DeleteFacilitiesRecords(Facilities info[], int nRecords);
void ClosedFacilitiesReport(Facilities info[], int nRecords);