#include<stdio.h>
#include<windows.h>
#include<time.h>
#include <tchar.h> 
#include <strsafe.h>




void Merge(int l, int m, int r);
void MergeSort(int l, int r);
void InsertionSort(int size);
int FindData();
void swap(int i, int j);

struct files_info {
	TCHAR name[64];
	int size;
};
struct files_info data[100];


int main(){
	int file_count, sort_method;
	double time_spent = 0.0;
	do {
		file_count = FindData();
		if (file_count == -1)
			printf("Enter directory path again\n");
	} while (file_count == -1);
	printf("OK, which sort method do you choose?\n Enter 1 to choose Merge sort\n Enter 2 to choose Insertion sort\n");
	do {
		scanf_s("%i", &sort_method);
		if (sort_method != 1 && sort_method != 2)
			printf("Please, enter 1 or 2");
	} while (sort_method != 1 && sort_method != 2);

	clock_t begin = clock();

	if (sort_method == 1)
		MergeSort(0, file_count);
	else
		InsertionSort(file_count);
	
	clock_t end = clock();
	
	for (int i = 0; i < file_count; ++i)
			_tprintf(TEXT("%s %i\n"), data[i].name, data[i].size);

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time is %f seconds", time_spent);
}



int FindData() {
	TCHAR path[100];
	_tprintf(TEXT("Please, enter your directory path: "));
	StringCbGets(path, 100);
	_tprintf(TEXT("\nTarget directory is %s\n\n"), path);


	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	

	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;


	StringCchCopy(szDir, MAX_PATH, path); 
	StringCchCat(szDir, MAX_PATH, TEXT("\\*")); 

	hFind = FindFirstFile(szDir, &ffd);


	if (INVALID_HANDLE_VALUE == hFind)
	{
		printf("Error\n");
		return -1;
	}


	int i = 0;
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			StringCchCopy(data[i].name, 64, ffd.cFileName);
			data[i].size = ffd.nFileSizeLow;
			++i;
		}
	} while (FindNextFile(hFind, &ffd) != 0);


	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		printf("ERROR_NO_MORE_FILES\n");
		return - 1;
	}

	FindClose(hFind);

	return i;
}	


void Merge(int l, int m, int r) {
	int i = l, j = m;
	int bufnum[100];
	TCHAR bufname[100][64];
	for (int a = l; a < r; ++a) {
		if (i < m && j < r) {
			if (data[i].size > data[j].size) {
				bufnum[a] = data[j].size;
				StringCchCopy(bufname[a], 64, data[j].name);
				++j;
			}
			else {
				bufnum[a] = data[i].size;
				StringCchCopy(bufname[a], 64, data[i].name);
				++i;
			}
		}
		else {
			if (i >= m) {
				bufnum[a] = data[j].size;
				StringCchCopy(bufname[a], 64, data[j].name);
				++j;
			}
			else {
				bufnum[a] = data[i].size;
				StringCchCopy(bufname[a], 64, data[i].name);
				++i;
			}
		}
	}
	for (int i = l; i < r; ++i) {
		data[i].size = bufnum[i];
		StringCchCopy(data[i].name, 64, bufname[i]);
	}
}


void MergeSort(int l, int r) {
	if (l + 1 >= r)
		return;
	int m = (r + l) / 2;
	MergeSort(l, m);
	MergeSort(m, r);
	Merge(l, m, r);
}


void InsertionSort(int size) {
	int c;
	for (int i = 1; i < size; ++i)
		for (int j = i; j > 0; --j) {
			if (data[j].size < data[j - 1].size) {
				c = data[j].size;
				data[j].size = data[j - 1].size;
				data[j - 1].size = c;
				
				swap(j, j-1);
			}
		}
}

void swap(int i, int j) {
	TCHAR buf[64];
	StringCchCopy(buf, 64, data[i].name);
	StringCchCopy(data[i].name, 64, data[j].name);
	StringCchCopy(data[j].name, 64, buf);
}