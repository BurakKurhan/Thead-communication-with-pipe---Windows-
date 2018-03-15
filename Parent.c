//Ýsmail Burak Kurhan
//220201055
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>


#define NO_OF_PROCESS 7
#define BUFSIZE 1000 
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	STARTUPINFO si[NO_OF_PROCESS];
	PROCESS_INFORMATION pi[NO_OF_PROCESS];
	SECURITY_ATTRIBUTES sa[NO_OF_PROCESS];

	HANDLE writePipe[NO_OF_PROCESS];
	HANDLE readPipe[NO_OF_PROCESS];

	HANDLE writePipe2[NO_OF_PROCESS];
	HANDLE readPipe2[NO_OF_PROCESS];

	HANDLE processHandles[NO_OF_PROCESS];

	char* lpCommandLine[NO_OF_PROCESS] = { "Child.exe 4 ","Child.exe 4 ","Child.exe 4 ","Child.exe 4 ","Child.exe 4 ","Child.exe 4 ","Child.exe 4 " };
	int i = 0;

	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		SecureZeroMemory(&sa[i], sizeof(SECURITY_ATTRIBUTES));
		sa[i].bInheritHandle = TRUE;
		sa[i].lpSecurityDescriptor = NULL;
		sa[i].nLength = sizeof(SECURITY_ATTRIBUTES);

		if (!CreatePipe(&readPipe2[i], &writePipe2[i], &sa[i], 0))
		{
			system("pause");
			exit(0);
		}

		if (!CreatePipe(&readPipe[i], &writePipe[i], &sa[i], 0))
		{
			system("pause");
			exit(0);
		}
		SecureZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		si[i].hStdInput = readPipe[i];
		si[i].hStdOutput = writePipe2[i];
		si[i].hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si[i].dwFlags = STARTF_USESTDHANDLES;

		SecureZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));
		if (!CreateProcess(NULL,
			lpCommandLine[i],
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si[i],
			&pi[i]))
		{
			system("pause");
			ExitProcess(0);
		}
		else
		{

			printf("Child proccess created by number with %d\n", (i));
			char array1[100];
			int bytesWritten = 0;

			sprintf(array1, "%d", i + 1);
			if (!WriteFile(writePipe[i], array1, 1024, &bytesWritten, NULL))
				processHandles[i] = pi[i].hProcess;
			CloseHandle(writePipe[i]);
		}


	}

	WaitForMultipleObjects(NO_OF_PROCESS, processHandles, TRUE, INFINITE);

	int totalNumberOfchips = 0;
	int totalNumberOfMilk = 0;
	int totalNumberOfCoke = 0;
	int totalNumberOfBiscuits = 0;

	int numberOfChipsForDay;
	int numberOfMilkForDay;
	int numberOfCokeForDay;
	int numberOfBiscuitForDay;

	for (i = 0; i < NO_OF_PROCESS; i++) {

		char readBuf[100];
		int bytesToWrite;
		int bytesWritten = 0;
		bytesToWrite = strlen(readBuf);
		bytesToWrite++;

		ReadFile(readPipe2[i], readBuf, bytesToWrite, &bytesWritten, NULL);


		numberOfMilkForDay = 0;
		numberOfBiscuitForDay = 0;
		numberOfCokeForDay = 0;
		numberOfChipsForDay = 0;

		char *nextPointer;
		int numberOfEachItem;
		numberOfEachItem = strtol(readBuf, &nextPointer, 10);



		int counter = 0;

		while (numberOfEachItem > 0)
		{
			int digit = numberOfEachItem % 10;   // Parse readBuff data to use
			numberOfEachItem /= 10;            //taking each element in data

			if (counter == 0) {

				numberOfCokeForDay = numberOfCokeForDay + digit;
				totalNumberOfCoke += numberOfCokeForDay;
			}
			else if (counter == 1) {
				numberOfChipsForDay = numberOfChipsForDay + digit;
				totalNumberOfchips += numberOfChipsForDay;
			}

			else if (counter == 2) {

				numberOfBiscuitForDay = numberOfBiscuitForDay + digit;
				totalNumberOfBiscuits += numberOfBiscuitForDay;
			}
			else if (counter == 3) {

				numberOfMilkForDay = numberOfMilkForDay + digit;
				totalNumberOfMilk += numberOfMilkForDay;
			}

			counter++;
		}
		int tempForMaxValue = 0;
		printf("-------------------------------DAY  : %d--------------------------- \n ", i + 1);
		printf(" total number of sold cokes for ( %d. ) day: %d\n", (i + 1), numberOfCokeForDay);
		printf("  total number of sold chips for in ( %d. )day: %d\n", (i + 1), numberOfChipsForDay);
		printf(" total number of sold biscuit for in ( %d. ) day: %d\n", (i + 1), numberOfBiscuitForDay);
		printf("total number of sold milk for in ( %d. ) day: %d\n", (i + 1), numberOfMilkForDay);
		if (numberOfCokeForDay > tempForMaxValue) {
			tempForMaxValue = numberOfCokeForDay;
		}
		if (numberOfMilkForDay > tempForMaxValue) {
			tempForMaxValue = numberOfMilkForDay;
		}
		if (numberOfBiscuitForDay > tempForMaxValue) {
			tempForMaxValue = numberOfBiscuitForDay;
		}
		if (numberOfChipsForDay > tempForMaxValue) {
			tempForMaxValue = numberOfChipsForDay;
		}
		if (tempForMaxValue == numberOfCokeForDay) {
			printf(" most saled item in ( %d. ) day  is: COKE  by number of  %d item \n", (i + 1), numberOfCokeForDay);
		}
		else if (tempForMaxValue == numberOfMilkForDay) {
			printf("Today's most saled item is: Milk  by number of %d item \n", numberOfMilkForDay);
		}
		else if (tempForMaxValue == numberOfBiscuitForDay) {
			printf("Today's most saled item is: BISCUIT  by number of %d item\n", numberOfBiscuitForDay);
		}
		else if (tempForMaxValue == numberOfChipsForDay) {
			printf("Today's most saled item is: Chips  %d item \n", numberOfChipsForDay);
		}
		printf("-------------------------------END OF DAY  : %d--------------------------- \n ", i + 1);
	}
	printf("The total number of sold coke in seven days  : %d\n", totalNumberOfCoke);
	printf("The total number of sold chips in seven days  : %d\n", totalNumberOfchips);
	printf("The total number of sold biscuit in seven days: %d\n", totalNumberOfBiscuits);
	printf("The total number of sold milk in seven days : %d\n", totalNumberOfMilk);
	int tempForTotal = 0;

	if (totalNumberOfCoke > tempForTotal) {
		tempForTotal = totalNumberOfCoke;
	}

	if (totalNumberOfMilk > tempForTotal) {
		tempForTotal = totalNumberOfMilk;
	}
	if (totalNumberOfBiscuits > tempForTotal) {
		tempForTotal = totalNumberOfBiscuits;
	}
	if (totalNumberOfchips > tempForTotal) {
		tempForTotal = totalNumberOfchips;
	}

	if (tempForTotal == totalNumberOfCoke) {
		printf("The most sold item in seven days is coke by %d item \n", totalNumberOfCoke);
	}
	else if (tempForTotal == totalNumberOfMilk) {
		printf("The most sold item in seven days is milk by %d item \n", totalNumberOfMilk);
	}
	else if (tempForTotal == totalNumberOfBiscuits) {
		printf("The most sold item in seven days is biscuit by %d item \n", totalNumberOfBiscuits);
	}
	else if (tempForTotal == totalNumberOfchips) {
		printf("The most sold item in seven days is chips by %d item \n", totalNumberOfchips);
	}
	printf("press any key for finish \n");
	system("pause");
	exit(0);

	return 1;
}
