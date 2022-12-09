#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include<time.h>

int size = 0;



void selectionSort(WIN32_FIND_DATA arr[])
{
    int n = size;
    int i, j, min_idx;


    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].nFileSizeLow < arr[min_idx].nFileSizeLow)
                min_idx = j;

        
        if (min_idx != i) {
            WIN32_FIND_DATA temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

void QuickSort(WIN32_FIND_DATA arr[], int left=0, int right=size-1) {
    int i = left;
    int j = right;
    WIN32_FIND_DATA pivot = arr[left + int(rand() % (right - left))];
    WIN32_FIND_DATA temp;

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

    printf_s("There is your files:\n");
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

    int choose;
    

    while (true)
    {
        for (int i = 0; i < size; ++i)
        {
            arr[i] = a[i];
        }
        choose = 0;
        printf("Pleace,choose sort:\n1.Selection sort\n2.Quick sort\n");
        do {
            printf("Input correct data:");
            scanf_s("%d", &choose);
        } while (choose > 2 || choose < 1);
        long double time_spent = 0.0;
        clock_t begin;
        clock_t end;
        switch (choose)
        {
        case 1:
            begin = clock();
            selectionSort(arr);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf("Your sort took %.20llf seconds", time_spent);
            break;
        case 2:
            begin = clock();
            QuickSort(arr);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf("Your sort took %.20llf seconds", time_spent);
            break;
        }

        for (int i = 0; i < size; ++i)
        {
            _tprintf(TEXT("  %s   %ld bytes\n"), arr[i].cFileName, arr[i].nFileSizeLow);
        }


        getchar();
        printf("You wanna change sort Y/N?");
        char c; scanf_s("%c", &c);
        getchar();
        if (c == 'N')
            return 0;
    }
    

   //Замер времени
   // double time_spent = 0.0;
   // clock_t begin = clock();
   // clock_t end = clock();
   // time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   // printf("The elapsed time is %f seconds", time_spent);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        printf("GetLastError\n");
        return -1;
    }

    FindClose(hFind);
}
