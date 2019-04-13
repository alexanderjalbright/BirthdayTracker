#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char strUserFirstName[50][25];
char strUserLastName[50][25];
int intUserYear[50];
int intUserMonth[50];
int intUserDay[50];
int intNumPpl = 0;
int intPersonNum = 0;
int intMainMenu = 0;
int intDisplayNum = 0;
int intEarlierYear = 0;
int intEarlierMonth = 0;
int intEarlierDay = 0;
int intLaterYear = 0;
int intLaterMonth = 0;
int intLaterDay = 0;
int intCount = 0;
int intYear = 0;
int intMonth = 0;
int intDay = 0;

void main()
{
	time_t timer;
	struct tm* tm_info;
	char day[3];
	char month[3];
	char year[5];
	int intError = 0;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(day, 3, "%d", tm_info);
	strftime(month, 3, "%m", tm_info);
	strftime(year, 5, "%Y", tm_info);

	intYear = atoi(year);
	intMonth = atoi(month);
	intDay = atoi(day);
	printf("Welcome to DateTracker by Alex Albright!\nThis program was designed to track time since/till events.\n\n");

	Start: MainMenu(); //Display menu and allow user to choose next step

	switch (intMainMenu) {
	case 1:  AddData();  //Add birthdays
		break;
	case 2:  EditData();  //Edit birthdays
		break;
	case 3:  PrintData(); //Show all events
		break;
	case 4:  DeleteData(); //Remove events
		break;
	case 5:  //Show time remaining until a future event
		printf("Type the number of the person you would like to use:\n--> ");
		scanf("%d", &intDisplayNum);
		intPersonNum = intDisplayNum - 1;
		if(Count(intYear, intMonth, intDay, intUserYear[intPersonNum], intUserMonth[intPersonNum], intUserDay[intPersonNum], 1) != 0) { 
			printf("\nYou're too late. You missed it.\nTry again.\n");
		}
		break;
	case 6:  //Show time remaining until a future event
		printf("Type the number of the person you would like to use:\n--> ");
		scanf("%d", &intDisplayNum);
		intPersonNum = intDisplayNum - 1;
		if (Count(intUserYear[intPersonNum], intUserMonth[intPersonNum], intUserDay[intPersonNum], intYear, intMonth, intDay, 1) != 0) { 
			printf("\nThis person has not been born yet.\nTry again.\n");
		}
		break;
	case 7:  Save();  //Save database to local file
		break;
	case 8:  Restore();  //Restore previously saved database
		break;
	case 9:  Exit(); //Allow user to exit
		break;
	default: goto Start;
	}


	if (intMainMenu != 9) {
		goto Start;
	}
	else {
		End: return;
	}
}
	

int MainMenu()
{
	printf("\nMENU:\n");
	printf("1 - Add People\n");
	printf("2 - Edit People\n");
	printf("3 - Display All People\n");
	printf("4 - Delete People\n");
	printf("5 - Countdown\n");
	printf("6 - Countup\n");
	printf("7 - Save\n");
	printf("8 - Restore\n");
	printf("9 - Exit program\n");
	printf("--> ");
	scanf("%d", &intMainMenu);

	return 0;
}


int AddData()
{
	int intCurrentNum = intNumPpl;
	int intAddedNum=0;
	int intDayError = 0;

	printf("\nHow many people will you be adding to the database?\n--> ");
	scanf("%d", &intAddedNum);
	intNumPpl = intAddedNum + intCurrentNum;
	
	for (intPersonNum = intCurrentNum; intPersonNum < intNumPpl; intPersonNum++) {

		intDisplayNum = intPersonNum + 1;

		printf("PERSON #%d:\n", intDisplayNum);
		printf("Please input first name:\n--> ");
		scanf("%s", &strUserFirstName[intPersonNum]);

		printf("Please input Last name:\n--> ");
		scanf("%s", &strUserLastName[intPersonNum]);

		do {
			printf("Please input birth year:\n--> ");
			scanf("%d", &intUserYear[intPersonNum]);
			if (intUserYear[intPersonNum] < 0) {
				printf("Year cannont be less than 0. Try again.\n");
			}
		} while (intUserYear[intPersonNum] < 0);

		do {
			printf("Please input birth month by number:\n--> ");
			scanf("%d", &intUserMonth[intPersonNum]);
			if (intUserMonth[intPersonNum] < 1 || intUserMonth[intPersonNum] > 12){
				printf("Month must be between 1-12. Try again.\n");
			}
		} while (intUserMonth[intPersonNum] < 1 || intUserMonth[intPersonNum] > 12);

		do {
			printf("Please input birth day:\n--> ");
			scanf("%d", &intUserDay[intPersonNum]);
			if (intUserDay[intPersonNum] < 1) {
				intDayError = 1;
			}
			else if(intUserDay[intPersonNum] > 29 && intUserMonth[intPersonNum] == 2) {
				intDayError = 1;
			}
			else if (intUserDay[intPersonNum] > 30) {
				if (intUserMonth[intPersonNum] != 1 || intUserMonth[intPersonNum] != 3 || intUserMonth[intPersonNum] != 5 || intUserMonth[intPersonNum] != 7 || intUserMonth[intPersonNum] != 8 || intUserMonth[intPersonNum] != 10 || intUserMonth[intPersonNum] != 12) {
					intDayError = 1;
				}
			}
			else {
				intDayError = 0;
			}
			if (intDayError == 1) {
				printf("That day does not exist in that month. Try again.\n");
			}
			

		} while (intDayError == 1);
	}


	return 0;
}


int EditData()
{
	int intCurrentNum = intNumPpl;
	int intAddedNum = 0;
	char strEditConf[10];
	char strEditChoice[4][10];
	int intDayError = 0;

	printf("Type the number of the person you would like to edit:\n--> ");
	scanf("%d", &intDisplayNum);
	intPersonNum = intDisplayNum - 1;

	printf("\n%s %s born %d/%d/%d\n", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intUserMonth[intPersonNum], intUserDay[intPersonNum], intUserYear[intPersonNum]);

	printf("Is this the information you would like to change? (Yes/No)\n--> ");
	scanf("%s", &strEditConf); //get user input confirmation

	strcpy(strEditChoice[0], "Yes");
	strcpy(strEditChoice[1], "YES");
	strcpy(strEditChoice[2], "yes");
	strcpy(strEditChoice[3], strEditConf);

	if (strcmp(strEditChoice[3], strEditChoice[0]) != 0 && strcmp(strEditChoice[3], strEditChoice[1]) != 0 && strcmp(strEditChoice[3], strEditChoice[2]) != 0) {
		return 0;
	}


	printf("PERSON #%d:\n", intDisplayNum);
	printf("Please input first name:\n--> ");
	scanf("%s", &strUserFirstName[intPersonNum]);

	printf("Please input Last name:\n--> ");
	scanf("%s", &strUserLastName[intPersonNum]);

	do {
		printf("Please input birth year:\n--> ");
		scanf("%d", &intUserYear[intPersonNum]);
		if (intUserYear[intPersonNum] < 0) {
			printf("Year cannont be less than 0. Try again.\n");
		}
	} while (intUserYear[intPersonNum] < 0);

	do {
		printf("Please input birth month by number:\n--> ");
		scanf("%d", &intUserMonth[intPersonNum]);
		if (intUserMonth[intPersonNum] < 1 || intUserMonth[intPersonNum] > 12) {
			printf("Month must be between 1-12. Try again.\n");
		}
	} while (intUserMonth[intPersonNum] < 1 || intUserMonth[intPersonNum] > 12);

	do {
		printf("Please input birth day:\n--> ");
		scanf("%d", &intUserDay[intPersonNum]);
		if (intUserDay[intPersonNum] < 1) {
			intDayError = 1;
		}
		else if (intUserDay[intPersonNum] > 29 && intUserMonth[intPersonNum] == 2) {
			intDayError = 1;
		}
		else if (intUserDay[intPersonNum] > 30) {
			if (intUserMonth[intPersonNum] != 1 || intUserMonth[intPersonNum] != 3 || intUserMonth[intPersonNum] != 5 || intUserMonth[intPersonNum] != 7 || intUserMonth[intPersonNum] != 8 || intUserMonth[intPersonNum] != 10 || intUserMonth[intPersonNum] != 12) {
				intDayError = 1;
			}
		}
		else{
			intDayError = 0;
		}
		if (intDayError == 1) {
			printf("That day does not exist in that month. Try again.\n");
		}

	} while (intDayError == 1);


	return 0;
}


int PrintData()
{

	for (intPersonNum = 0; intPersonNum < intNumPpl; intPersonNum++) {

		intDisplayNum = intPersonNum + 1;
		
		printf("\nPERSON #%d:\n", intDisplayNum);

		printf("Name: %s, %s\n", strUserLastName[intPersonNum], strUserFirstName[intPersonNum]);

		printf("Birthday: %d/%d/%d\n\n", intUserMonth[intPersonNum], intUserDay[intPersonNum], intUserYear[intPersonNum]);

	}
	return 0;
}


int DeleteData()
{
	int intCurrentNum = intNumPpl;
	int intAddedNum = 0;
	char strEditConf[10];
	char strEditChoice[4][10];
	char strRemovedFName[25];
	char strRemovedLName[25];

	printf("Type the number of the person you would like to delete:\n--> ");
	scanf("%d", &intDisplayNum);
	intPersonNum = intDisplayNum - 1;

	printf("\n%s %s born %d/%d/%d\n", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intUserMonth[intPersonNum], intUserDay[intPersonNum], intUserYear[intPersonNum]);

	printf("Is this the information you would like to delete? (Yes/No)\n--> ");
	scanf("%s", &strEditConf); //get user input confirmation

	strcpy(strEditChoice[0], "Yes");
	strcpy(strEditChoice[1], "YES");
	strcpy(strEditChoice[2], "yes");
	strcpy(strEditChoice[3], strEditConf);

	if (strcmp(strEditChoice[3], strEditChoice[0]) != 0 && strcmp(strEditChoice[3], strEditChoice[1]) != 0 && strcmp(strEditChoice[3], strEditChoice[2]) != 0) {
		return 0;
	}

	strcpy(strRemovedFName, strUserFirstName[intPersonNum]);
	strcpy(strRemovedLName, strUserLastName[intPersonNum]);

	for (intPersonNum; intPersonNum < intNumPpl; intPersonNum++, intDisplayNum++) {
		strcpy(strUserFirstName[intPersonNum], strUserFirstName[intDisplayNum]);
		strcpy(strUserFirstName[intPersonNum], strUserFirstName[intDisplayNum]);
		intUserYear[intPersonNum] = intUserYear[intDisplayNum];
		intUserMonth[intPersonNum] = intUserMonth[intDisplayNum];
		intUserDay[intPersonNum] = intUserDay[intDisplayNum];
	}

	strcpy(strUserFirstName[intDisplayNum], "");
	strcpy(strUserLastName[intDisplayNum], "");
	intUserYear[intDisplayNum] = 0;
	intUserMonth[intDisplayNum] = 0;
	intUserDay[intDisplayNum] = 0;

	intNumPpl = intNumPpl - 1;
	
	printf("%s %s has been removed.", strRemovedFName, strRemovedLName);
	return 0;
}


int Count(int intEarlierYear, int intEarlierMonth, int intEarlierDay, int intLaterYear, int intLaterMonth, int intLaterDay, int intCount) {
	int intError = 0;
	int intCountDownYears = 0;
	int intCountDownMonths = 0;
	int intCountDownDays = 0;
	

	if (intEarlierDay <= intLaterDay && intEarlierMonth <= intLaterMonth && intEarlierYear <= intLaterYear) {
		intCountDownYears = intLaterYear - intEarlierYear;
		intCountDownMonths = intLaterMonth - intEarlierMonth;
		intCountDownDays = intLaterDay - intEarlierDay;
	}
	else if (intDay <= intLaterDay && intEarlierMonth > intLaterMonth && intEarlierYear <= intLaterYear) {
		intCountDownYears = intLaterYear - intEarlierYear - 1;
		intCountDownMonths = intLaterMonth + 12 - intEarlierMonth;
		intCountDownDays = intLaterDay - intEarlierDay;
	}
	else if (intEarlierDay > intLaterDay && intEarlierMonth < intLaterMonth && intEarlierYear <= intLaterYear) {
		intCountDownYears = intLaterYear - intEarlierYear;
		intCountDownMonths = intLaterMonth - intEarlierMonth;
		if (intLaterMonth == 1 || intLaterMonth == 2 || intLaterMonth == 4 || intLaterMonth == 6 || intLaterMonth == 8 || intLaterMonth == 9 || intLaterMonth == 11) {
			intCountDownDays = intLaterDay + 31 - intEarlierDay;
		}
		else if (intLaterMonth == 3 || intLaterMonth == 5 || intLaterMonth == 7 || intLaterMonth == 10 || intLaterMonth == 12) {
			intCountDownDays = intLaterDay + 30 - intEarlierDay;
		}
		else {
			intCountDownDays = intLaterDay + 28 - intEarlierDay;
		}
	}
	else if (intEarlierDay > intLaterDay && intEarlierMonth >= intLaterMonth && intEarlierYear < intLaterYear) {
		intCountDownYears = intLaterYear - intEarlierYear - 1;
		intCountDownMonths = intLaterMonth + 12 - intEarlierMonth;
		if (intLaterMonth == 1 || intLaterMonth == 2 || intLaterMonth == 4 || intLaterMonth == 6 || intLaterMonth == 8 || intLaterMonth == 9 || intLaterMonth == 11) {
			intCountDownDays = intLaterDay + 31 - intEarlierDay;
		}
		else if (intLaterMonth == 3 || intLaterMonth == 5 || intLaterMonth == 7 || intLaterMonth == 10 || intLaterMonth == 12) {
			intCountDownDays = intLaterDay + 30 - intEarlierDay;
		}
		else {
			intCountDownDays = intLaterDay + 28 - intEarlierDay;
		}
	}
	else {
		intError = 1;
	}

	if (intError == 1) {
		return intError;
	}
	else {
		
		printf("\n%s %s's event ", strUserFirstName[intPersonNum], strUserLastName[intPersonNum]);
		
		if (intCount = 1) {
			printf("is in", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intCountDownYears, intCountDownMonths, intCountDownDays);
		}
		else {
			printf("was", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intCountDownYears, intCountDownMonths, intCountDownDays);
		}
		
		printf(" %d years, %d months, and %d days", intCountDownYears, intCountDownMonths, intCountDownDays);
		
		if (intCount = 1) {
			printf(".\n", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intCountDownYears, intCountDownMonths, intCountDownDays);
		}
		else {
			printf(" ago.\n", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intCountDownYears, intCountDownMonths, intCountDownDays);
		}

		return intError;
	}
}


int Save() {
	FILE * DataFile = fopen("DateTrackerData.txt", "w");
	if (DataFile == NULL)
	{
		printf("DataTrackerData.txt could not be found.\n");
		return 0;
	}
	
	fprintf(DataFile, "%d\n", intNumPpl);
	
	for (intPersonNum = 0; intPersonNum < intNumPpl; intPersonNum++) {
		fprintf(DataFile, "%s\n%s\n%d\n%d\n%d\n", strUserFirstName[intPersonNum], strUserLastName[intPersonNum], intUserYear[intPersonNum], intUserMonth[intPersonNum], intUserDay[intPersonNum]);
	}
	 
	fclose(DataFile);

	printf("\n\nSAVED!!!!!!\n\n");
	return(0);
}


int Restore() {
	FILE * DataFile = fopen("DateTrackerData.txt", "r");
	if (DataFile == NULL)
	{
		printf("DataTrackerData.txt could not be found.\n");
		return 0;
	}
	fscanf(DataFile, "%d\n", &intNumPpl);

	for (intPersonNum = 0; intPersonNum < intNumPpl; intPersonNum++) {
		fscanf(DataFile, "%s\n%s\n%d\n%d\n%d\n", &strUserFirstName[intPersonNum], &strUserLastName[intPersonNum], &intUserYear[intPersonNum], &intUserMonth[intPersonNum], &intUserDay[intPersonNum]);
	}

	fclose(DataFile);

	printf("\n\nLOADED!!!!!!\n\n");
	return(0);
}


int Exit()
{
	char strExitChoice[4][10];
	char strExit[10];

	printf("\nWould you like to exit? (Yes/No)\n--> ");
	scanf("%s", &strExit); //wait for user input to exit program

	strcpy(strExitChoice[0], "No");
	strcpy(strExitChoice[1], "NO");
	strcpy(strExitChoice[2], "no");
	strcpy(strExitChoice[3], strExit);

	if (strcmp(strExitChoice[3], strExitChoice[0]) == 0 || strcmp(strExitChoice[3], strExitChoice[1]) == 0 || strcmp(strExitChoice[3], strExitChoice[2]) == 0) {
		intMainMenu = 0;
	}

	return 0;
}
