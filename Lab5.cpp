#include <stdio.h>
#include <string.h>
#include <strsafe.h>
#include <windows.h>
#include <tchar.h>
#include <time.h>

int size = 0;

void InsertionSort(WIN32_FIND_DATA arr[])  {
    int elem, location;
    int n = size;
    WIN32_FIND_DATA temp;
    for (int i = 1; i < n; i++)  {
        elem = arr[i].nFileSizeLow;
        location = i - 1;
        while (location >= 0 && arr[location].nFileSizeLow > elem)  {
            temp = arr[location + 1];
            arr[location + 1] = arr[location];
            arr[location] = temp;
            location = location - 1;
        }
        arr[location + 1].nFileSizeLow = elem;
    }
}

void QuickSort(WIN32_FIND_DATA arr[], int left = 0, int right = size - 1)   {
    int i = left;
    int j = right;
    WIN32_FIND_DATA temp;
    WIN32_FIND_DATA p = arr[left];
    while (i <= j) {
        while (arr[i].nFileSizeLow < p.nFileSizeLow)
            i++;
        while (arr[j].nFileSizeLow > p.nFileSizeLow)
            j--;
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (j > left) {
        QuickSort(arr, left, j);
    }
    if (i < right) {
        QuickSort(arr, i, right);
    }
}

int main() {
    int sorting = 1;
    int sort_type;
    WIN32_FIND_DATA sort[200];
    WIN32_FIND_DATA reserve[200];
    printf(" Input a path\n");
    TCHAR path[100];
    StringCbGets(path, 100);
    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;
    StringCchCopy(szDir, MAX_PATH, path);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
    hFind = FindFirstFile(szDir, &ffd);
    if (INVALID_HANDLE_VALUE == hFind)  {
        printf("Incorrect path\n");
        return -1;
    }
    printf_s(" Files:\n");
    while (FindNextFile(hFind, &ffd) != 0)  {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))  {
            _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, ffd.nFileSizeLow);
            reserve[size++] = ffd;
        }
    }
    while (sorting) {
        for (int i = 0; i < size; ++i)  {
            sort[i] = reserve[i];
        }
        printf("\n Select sort type:\n1 - Quick\n2 - Insertion\n");
        scanf_s("%i", &sort_type);
        double time = 0.0;
        if (sort_type == 2) {
            clock_t begin = clock();
            InsertionSort(sort);
            clock_t end = clock();
            time += (double)((end - begin) / CLOCKS_PER_SEC);
        }
        else {
            clock_t begin = clock();
            QuickSort(sort);
            clock_t end = clock();
            time += (double)((end - begin) / CLOCKS_PER_SEC);
        }
        for (int i = 0; i < size; ++i)  {
            _tprintf(TEXT("  %s   %ld bytes\n"), sort[i].cFileName, sort[i].nFileSizeLow);
        }
        printf(" time: %f", time);
        printf("\n Sort one more time?\n0 - no\n1 - yes\n");
        scanf_s("%i", &sorting);
    }
	return 0;
}