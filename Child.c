//Ýsmail Burak Kurhan
//220201055
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
typedef struct
{
	int threadNo;
	int* sum;
	int day;
	int startParagraph;
	int endParagraph;

}THREAD_PARAMETERS;

DWORD WINAPI threadWork(LPVOID parameters);
int main(int argc, char* argv[])
{
	HANDLE hStdin, hStdout;
	CHAR ReadingBuf[1024];

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	if (
		(hStdout == INVALID_HANDLE_VALUE) ||
		(hStdin == INVALID_HANDLE_VALUE)
		)
	{
		system("pause");
	}

	HANDLE* handles;
	THREAD_PARAMETERS* threadParamater;
	int* threadID;

	int threadCount = 0;
	int totalsum = 0;

	if (argc != 2)
	{
		system("pause");
	}
	threadCount = atoi(argv[1]);

	char message[100];
	int bytesToWrite;
	int bytesWritten = 0;
	bytesToWrite = strlen(message);
	bytesToWrite++;
	ReadFile(hStdin, ReadingBuf, 1024, &bytesToWrite, NULL);


	int dayNumberFromPipe = 0;
	int dayOfChild;
	sscanf(ReadingBuf, "%d", &dayNumberFromPipe);
	dayOfChild = dayNumberFromPipe;

	handles = malloc(sizeof(HANDLE)* threadCount);
	threadParamater = malloc(sizeof(THREAD_PARAMETERS)* threadCount);
	threadID = malloc(sizeof(int)* threadCount);

	int i = 0;
	for (i = 0; i < threadCount; i++)
	{
		if (dayOfChild == 1) {
			threadParamater[i].startParagraph = 2;
			threadParamater[i].endParagraph = 7;
		}

		else if (dayOfChild == 2) {
			threadParamater[i].startParagraph = 10;
			threadParamater[i].endParagraph = 13;

		}
		else if (dayOfChild == 3) {
			threadParamater[i].startParagraph = 16;
			threadParamater[i].endParagraph = 17;

		}
		else if (dayOfChild == 4) {
			threadParamater[i].startParagraph = 20;
			threadParamater[i].endParagraph = 25;

		}
		else if (dayOfChild == 5) {
			threadParamater[i].startParagraph = 28;
			threadParamater[i].endParagraph = 30;

		}
		else if (dayOfChild == 6) {
			threadParamater[i].startParagraph = 33;
			threadParamater[i].endParagraph = 36;

		}
		else if (dayOfChild == 7) {
			threadParamater[i].startParagraph = 39;
			threadParamater[i].endParagraph = 41;
		}
		threadParamater[i].threadNo = i;
		threadParamater[i].day = dayOfChild;
		threadParamater[i].sum = 0;
		handles[i] = CreateThread(NULL, 0, threadWork, &threadParamater[i], 0, &threadID[i]);

		if (handles[i] == INVALID_HANDLE_VALUE)
		{
			system("pause");
			exit(0);
		}
	}

	WaitForMultipleObjects(threadCount, handles, TRUE, INFINITE);

	for (i = 0; i < threadCount; i++)
	{
		CloseHandle(handles[i]);
	}
	char writerBuf[100];
	char buf2[100];
	char buf3[100];
	char buf4[100];
	char buf5[100];

	sprintf(writerBuf, "%d", dayOfChild);
	sprintf(buf2, "%d", (int)threadParamater[0].sum);
	sprintf(buf3, "%d", (int)threadParamater[1].sum);
	sprintf(buf5, "%d", (int)threadParamater[2].sum);
	sprintf(buf4, "%d", (int)threadParamater[3].sum);

	strcat(writerBuf, buf2);
	strcat(writerBuf, buf3);
	strcat(writerBuf, buf5);
	strcat(writerBuf, buf4);

	bytesToWrite = 0;
	bytesWritten = 0;
	bytesToWrite = strlen(ReadingBuf);
	bytesToWrite++;

	if (!WriteFile(hStdout, writerBuf, 1024, &bytesWritten, NULL)); {
	}

	free(handles);
	free(threadParamater);
	free(threadID);

	CloseHandle(hStdout);

	return 1;
}

DWORD WINAPI threadWork(LPVOID parameters)
{
	THREAD_PARAMETERS* param = (THREAD_PARAMETERS*)parameters;
#pragma warning(disable : 4996)

	int sum_milk = 0;
	int sum_coke = 0;
	int sum_biscuit = 0;
	int sum_chips = 0;

	char c[1000];
	FILE *fptr;


	if ((fptr = fopen("C:\\Users\\burak\\source\\repos\\HW_1\\market.txt", "r")) == NULL)
	{
		system("pause");
		exit(1);
	}

	int i = 0;
	int counter = 1;
	while (!feof(fptr)) {
		fgets(c, 1000, fptr);

		if (param->startParagraph == counter) {

			for (i = 0; i<param->endParagraph - param->startParagraph; i++) {
				char * pch;
				pch = strtok(c, "( ,)");
				while (pch != NULL)
				{
					if (param->threadNo == 0) {
						if (strcmp("MILK", pch) == 0) {
							sum_milk += 1;
						}
					}
					else if (param->threadNo == 1) {
						if (strcmp("BISCUIT", pch) == 0) {
							sum_biscuit += 1;
						}
					}
					else if (param->threadNo == 2) {
						if (strcmp("CHIPS", pch) == 0) {
							sum_chips += 1;
						}
					}
					else if (param->threadNo == 3) {
						if (strcmp("COKE", pch) == 0) {
							sum_coke += 1;
						}
					}
					pch = strtok(NULL, "( ,)");
				}
				fgets(c, 1000, fptr);
			}
			break;
		}
		counter += 1;
	}
	fclose(fptr);
	if (param->threadNo == 0) {
		param->sum = sum_milk;

	}
	else if (param->threadNo == 1) {
		param->sum = sum_biscuit;
	}
	else if (param->threadNo == 2) {
		param->sum = sum_chips;
	}
	else if (param->threadNo == 3) {
		param->sum = sum_coke;
	}
	return 1;
}


