#include<stdio.h>
#include <iomanip>
#include <string.h>
#include <windows.h>
#include <tchar.h> 
#include <time.h>
#include <strsafe.h>
struct data {
	WCHAR name[100];
	int bytes;};

void bubblesort(data files[], int y) {
	data buf;
	if (y == 1) {
		return;
	}
	for (int i = 0; i < y - 1; i++)
		if (files[i].bytes > files[i + 1].bytes) {
			buf = files[i + 1];
			files[i + 1] = files[i];
			files[i] = buf;
		}

	bubblesort(files, y - 1);
}
void quicksort(int l, data arr[], int r) {
	int i = l;
	int j = r;
	data temp;
	data pivot = arr[l + int(rand() % (r - l))];
	while (i <= j) {
		while (arr[i].bytes < pivot.bytes)
			i++;
		while (arr[j].bytes > pivot.bytes)
			j--;
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (j > l)
		quicksort(l, arr, j);
	if (i < r)
		quicksort(i, arr, r);
	}
	 
void printt(int y,data arr[],int u) {
	if (u == 1) {
		for (int i = y; i >= 0; --i) {
			wprintf_s(arr[i].name);
			printf(" %i bit\n", arr[i].bytes);
		}
	}
	else {
		for (int i = 0; i <= y; ++i) {
			wprintf_s(arr[i].name);
			printf(" %i bit\n", arr[i].bytes);
		}
	}
	}


int main() {
	char num; data files[1000];int war;int sort = 0;int y = 0;int h = 0;
	do{
	printf("1-select sorting\n");printf("2-specify the path to the directory\n");
	printf("select an action\n");
		scanf_s("%c", &num);
		switch (num) {
		case'1':
			printf("Choose a sorting method\n");
			printf("1-bubble sorting, 2-quick sorting\n");
			scanf_s("%i", &sort);
			while (!((sort == 1) || (sort == 2))) {
				printf("try again\n");
				scanf_s("%i", &sort);
			}
			break;
		case '2':
			printf("specify the path\n");
			getchar();
			TCHAR path[100];
			StringCbGets(path, 100);
			WIN32_FIND_DATA ffd;
			TCHAR szDir[MAX_PATH];
			HANDLE hFind = INVALID_HANDLE_VALUE;
			DWORD dwError = 0;
			StringCchCopy(szDir, MAX_PATH, path);
			StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
			hFind = FindFirstFile(szDir, &ffd);
			if (INVALID_HANDLE_VALUE == hFind)
			{
				printf("you have indicated the path incorrectly\n");
				break;
			}

			do {
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					StringCchCopy(files[y].name, MAX_PATH, ffd.cFileName);
					files[y].bytes = ffd.nFileSizeLow;
					y++;
				}
			} while ((FindNextFile(hFind, &ffd) != 0) && (y < sizeof(files)));

			printf("select a sorting option\n");
			printf("1- descending . 2-ascending\n");
			scanf_s("%i", &war);
			if (sort == 1) {
				clock_t b = clock();
				bubblesort(files, y);
				clock_t end = clock();
				printf("time: %f s.\n", (double)(end - b) / CLOCKS_PER_SEC);
				if (war == 1) { printt(y, files, 1); }
				else { printt(y, files, 2); }

			}
			else if (sort == 2) {
				clock_t b = clock();
				quicksort(0, files, y + 1);
				clock_t end = clock();
				printf("time: %f s.\n", (double)(end - b) / CLOCKS_PER_SEC);
				if (war == 1) { printt(y, files, 1); }
				else { printt(y, files, 2); }
			}
			h++;
			break;
		}
	} while (h == 0);
}