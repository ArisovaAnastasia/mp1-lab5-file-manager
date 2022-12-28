#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<tchar.h>
#include<strsafe.h>
#include<iostream>
int size = 0;

void InsertSort(WIN32_FIND_DATA arr[])
{
    int newElement, location;
    int n = size;
    for (int i = 1; i < n; i++)
    {
        newElement = arr[i].nFileSizeLow;
        location = i - 1;
        while (location >= 0 && arr[location].nFileSizeLow > newElement)
        {
            arr[location + 1] = arr[location];
            location = location - 1;
        }
        arr[location + 1].nFileSizeLow = newElement;
    }
}


void QuickSort(WIN32_FIND_DATA arr[], int left = 0, int right = size - 1) 
{
    int i = left;
    int j = right;
    WIN32_FIND_DATA temp;
    WIN32_FIND_DATA pivot = arr[left + int(rand() % (right - left))];
    while (i <= j) {
        while (arr[i].nFileSizeLow < pivot.nFileSizeLow)
            i++;
        while (arr[j].nFileSizeLow > pivot.nFileSizeLow)
            j--;
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (j > left)
        QuickSort(arr, left, j);
    if (i < right)
        QuickSort(arr, i, right);
}

int main() {
    TCHAR path[100];
    StringCbGets(path, 100);
    _tprintf(TEXT("\nTarget directory is %s\n\n"), path);
    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;
    printf_s("Please: Enter the path: ");
    StringCchCopy(szDir, MAX_PATH, path);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
    hFind = FindFirstFile(szDir, &ffd);
    if (INVALID_HANDLE_VALUE == hFind)
    {
        printf("Error in FindFirstFile\n");
        return -1;
    }
    WIN32_FIND_DATA arr[200];
    WIN32_FIND_DATA a[200];
    printf_s("Your files:\n");
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
        }
        else
        {
            _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, ffd.nFileSizeLow);
            a[size++] = ffd;
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    int flag=0;
    while (true)
    {
        clock_t begin;
        clock_t end;
        long double time_spent = 0.0;
        for (int i = 0; i < size; ++i)
        {
            arr[i] = a[i];
        }
        printf("Choose sort:\n1-InsertionSort\n2-QuickSort\n");
        do {
            printf("Input correct data:");
            scanf_s("%d", &flag);
        } while (flag > 2 || flag < 1);

        switch (flag)
        {
        case 1:
            begin = clock();
            InsertSort(arr);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf(" InsertSort took %.20llf seconds", time_spent);
            break;
        case 2:
            begin = clock();
            QuickSort(arr);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf("QuickSort took %.20llf seconds", time_spent);
            break;
        }
        for (int i = 0; i < size; ++i)
        {
            _tprintf(TEXT("  %s   %ld bytes\n"), arr[i].cFileName, arr[i].nFileSizeLow);
        }
        getchar();
        printf("Do you want to choose sort? 1-Yes 2-No");
        int kk;
        scanf_s("%d", &kk);
        if (kk == 2)
            return 0;
    }
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        printf("GetLastError\n");
        return -1;
    }
    FindClose(hFind);
}