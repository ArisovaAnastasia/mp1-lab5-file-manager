#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <string.h>
#include<time.h>

struct files{
    int size;
    char name[100];};
struct files database[7];

void bubbleSort(struct  files)
{
    for (int i = 0; i < 7 -1; i++)
    {
        for (int j = (7 - 1); j > i; j--)
        {
            if (database[j - 1].size > database[j].size)
            {
                int temp = database[j - 1].size;
                database[j - 1].size = database[j].size;
                database[j].size = temp;
                char temp1[100];
                strncpy(temp1,database[j-1].name,100);
                strncpy(database[j-1].name,database[j].name,100);
                strncpy(database[j].name,temp1,100);
            }
        }
    }
}


void QuickSort(int left, int right) {
    int i = left;
    int j = right;
    struct files pivot = database[left + (rand() % (right - left))];
    struct files temp;

    while (i <= j) {
        while (database[i].size < pivot.size)
            i++;
        while (database[j].size > pivot.size)
        j--;
        if (i <= j) {
            temp = database[i];
            database[i] = database[j];
            database[j] = temp;
            i++;
            j--;
        }
    }
    if (j > left)
        QuickSort(left, j);
    if (i < right)
        QuickSort(i, right);
}
//C:\LAB5


int main()
{
    int first =0;
    int last =7;

    printf("Please enter path");
    TCHAR path[100]; // = { "D:\RL" };
    StringCbGets(path, 100); // gets_s
    _tprintf(TEXT("\nTarget directory is %s\n\n"), path);

    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;
    StringCchCopy(szDir, MAX_PATH, path);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
    hFind = FindFirstFile(szDir, &ffd);
    int v=0;
    if (INVALID_HANDLE_VALUE == hFind)
    {
        printf("Error in FindFirstFile\n");
        return -1;
    }
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
            database[v].size=0;
            strncpy(database[v].name,ffd.cFileName,100);
            v++;
        }
        else
        {
            _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, ffd.nFileSizeLow);
            database[v].size=ffd.nFileSizeLow;
            strncpy(database[v].name,ffd.cFileName,100);
            v++;
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    printf("Let`s explore and sort your files :>\n");
    while(1)
    {
        printf("Please enter the mod:\n""Enter 1:Bubble sort\n""Enter 2: Quick sort\n""Enter 3: End session\n");
        int a=0;
        scanf("%i",&a);
        long double time_spent = 0.0;
        clock_t begin;
        clock_t end;
        switch(a)
        {
            case 1:
                begin = clock();
                printf("%.20f",begin);
                bubbleSort(database[0]);
                for (int i=0;i<7;++i)
                {
                    printf("%s - ",database[i].name);
                    printf("%i\n",database[i].size);
                }
                end = clock();
                printf("%.20f",end);
                time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time - %.20llf ", time_spent);
                getchar();
                a=0;
                break;

            case 2:
                begin = clock();
                QuickSort(0,6);
                for (int i=0;i<7;++i)
                {
                    printf("%s - ",database[i].name);
                    printf("%i\n",database[i].size);
                }
                end = clock();
                time_spent += (long double)(end - begin) / CLOCKS_PER_SEC;
                printf("Time - %.20llf ", time_spent);
                getchar();
                a=0;
                break;
            case 3:
                getchar();
                a=0;
                return -1;
            default:
                getchar();
                a=0;
                break;

        }
    }
}
