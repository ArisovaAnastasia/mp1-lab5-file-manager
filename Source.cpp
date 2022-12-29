#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <strsafe.h>
#include <time.h>
#include <windows.h>
#include <malloc.h>
#include <windows.h>
int cnt = 0;
void InsertSort(int n, WIN32_FIND_DATA mass[]) 
{
    WIN32_FIND_DATA element;
    int location;

    for (int i = 1; i < n; i++)
    {
        element = mass[i];
        location = i - 1;
        while (location >= 0 && mass[location].nFileSizeLow > element.nFileSizeLow)
        {
            mass[location + 1] = mass[location];
            location = location - 1;
        }
        mass[location + 1] = element;
    }
}
void MergeSort(int i, int j, WIN32_FIND_DATA a[], WIN32_FIND_DATA aux[]) 
{
    if (j <= i) {
        return;
    }
    int mid = (i + j) / 2;
    MergeSort(i, mid, a, aux);
    MergeSort(mid + 1, j, a, aux);
    int left = i;
    int right = mid + 1;
    int k;
    for (k = i; k <= j; k++) {
        if (left == mid + 1) {
            aux[k] = a[right];
            right++;
        }
        else if (right == j + 1) {
            aux[k] = a[left];
            left++;
        }
        else if (a[left].nFileSizeLow < a[right].nFileSizeLow) {
            aux[k] = a[left];
            left++;
        }
        else {
            aux[k] = a[right];
            right++;
        }
    }
    for (k = i; k <= j; k++) {
        a[k] = aux[k];
    }
}
int main()
{
    printf_s("Specify the path to the files:\n");
    TCHAR path[100];
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
        printf("Error in FindFirstFile\n");
        return -1;
    }
    WIN32_FIND_DATA filearr[200];
    WIN32_FIND_DATA arr[200];
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);

        }
        else
        {
            _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, ffd.nFileSizeLow);
            arr[cnt++] = ffd;
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    printf_s("Select sort mode\n");
    printf_s("Press 1 - InsertSort\n");
    printf_s("Press 2 - MergeSort\n");
    printf_s("Press 3 - Exit from the program \n");
    int choice, ch1, ch2;
    do {
        for (int i = 0; i < cnt; ++i)
        {
            filearr[i] = arr[i];
        }
        printf_s("Input sort mode\n");
        scanf_s("%i", &choice);
        double time_spent = 0.0;
        clock_t begin = clock();
        clock_t end = clock();
        //scanf_s("%*[^\n]");
        if (choice <= 0 || choice > 3)
            printf("Wrong sort mode selected\n");
        switch (choice) {
        case 1:
            WIN32_FIND_DATA aux[200];
            begin = clock();
            MergeSort(0, cnt - 1, filearr, aux);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf("Your sort took %.20llf seconds\n", time_spent);
            printf_s("Select output in ascending(1) / descending(2) order\n");
            do {
                scanf_s("%i", &ch1);
                if (ch1 <= 0 || ch1 > 2)
                    printf("Wrong output mode selected\n");
                printf("Printing the sorted array: \n");
                switch (ch1) {  
                case 1:
                    for (int i = 0; i < cnt; ++i)
                    {
                        _tprintf(TEXT("  %s   %ld bytes\n"), filearr[i].cFileName, filearr[i].nFileSizeLow);
                    }
                    break;
                case 2:
                    for (int i = 0; i < cnt; i++) {
                        aux[cnt - 1 - i] = filearr[i];
                    }
                    for (int i = 0; i < cnt; i++) {
                        filearr[i] = aux[i];
                    }
                    for (int i = 0; i < cnt; ++i)
                    {
                        _tprintf(TEXT("  %s   %ld bytes\n"), filearr[i].cFileName, filearr[i].nFileSizeLow);
                    }
                    break;
                }
                break;
            } while (true);
            printf("\n");
            printf("If you want to end the program press 3\n");
            break;
        case 2:
        {
            WIN32_FIND_DATA aux[200];
            begin = clock();
            InsertSort(cnt, filearr);
            end = clock();
            time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
            printf("Your sort took %.20llf seconds\n", time_spent);
            printf_s("Select output in ascending(1) / descending(2) order\n");
            do {
                scanf_s("%i", &ch2);
                if (ch2 <= 0 || ch2 > 2)
                    printf("Wrong output mode selected\n");
                printf("Printing the sorted array: \n");
                switch (ch2) {
                case 1:
                    for (int i = 0; i < cnt; ++i)
                    {
                        _tprintf(TEXT("  %s   %ld bytes\n"), filearr[i].cFileName, filearr[i].nFileSizeLow);
                    }
                    break;
                case 2:
                    for (int i = 0; i < cnt; i++) {
                        aux[cnt - 1 - i] = filearr[i];
                    }
                    for (int i = 0; i < cnt; i++) {
                        filearr[i] = aux[i];
                    }
                    for (int i = 0; i < cnt; ++i)
                    {
                        _tprintf(TEXT("  %s   %ld bytes\n"), filearr[i].cFileName, filearr[i].nFileSizeLow);
                    }
                    break;
                }
                break;
            } while (true);
            printf("\n");
            printf("If you want to end the program press 3\n");
            break;
        }
        case 3:
            printf("Exit completed");
            return 0;
            break;
        }
    } while (true);

    getchar();
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        printf("GetLastError\n");
        return -1;
    }
    FindClose(hFind);
}