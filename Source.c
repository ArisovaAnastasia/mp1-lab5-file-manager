#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <memory.h>
#include <time.h>
#include <limits.h>
#include <omp.h>
int choice;
int selection;
struct filesInformation
{
    int size;
    char name[50];
};
struct filesInformation* information;

double tt1, tt2;
int c = 0, q = 0;

void programMenu();
void mainMenuChoiceInfo();
void programAbilities();
void sortingMethods();
void sortingPreference();
void sortingMethodChoice(int AmountOfFiles);
void elementsSwap(int* element1, int* element2);
void bubbleSort(int AmountOfFiles);
void printFunction1(int AmountOfFiles);
void printChoice(int AmountOfFiles);
void printFunction2(int AmountOfFiles);
void furtherOptions();
void insertionSort(int AmountOfFiles);
void selectionSort(int AmountOfFiles);
void shellSort(int AmountOfFiles);
void mergeSort(int l, int AmountOfFiles);
void merge(int l, int m, int AmountOfFiles);
void quickSort(int low, int AmountOfFiles);
int partition(int low, int AmountOfFiles);
void userControl();
void selectionControl();
void CountingSort();

void printChoice(int AmountOfFiles)
{
    q = scanf("%d", &choice);
    while (q != 1 || choice < 1 || choice > 2)
        userControl();
    q = 0;
    switch (choice)
    {
    case 1:
    {
        printFunction1(AmountOfFiles);
        break;
    }
    case 2:
    {
        printFunction2(AmountOfFiles);
        break;
    }
    }
}

void furtherOptions()
{
    printf("What do you want to do next ?\n");
    printf("1. Change folder's path\n");
    printf("2. Change sorting method\n");
    printf("3. Change how you want to sort files (by ascending or by descending)\n");
    printf("4. Exit\n");
}

void userControl()
{
    while ((c = getchar()) != '\n' && c != EOF);
    {
        printf("There is no such option, try again:\n");
        q = scanf("%d", &choice);
    }
}

void selectionControl()
{
    while ((c = getchar()) != '\n' && c != EOF);
    {
        printf("There is no such option, try again:\n");
        q = scanf("%d", &selection);
    }
}
void printFunction1(int AmountOfFiles)
{
    int i;
    printf("Listing of files:\n\n");
    printf("FILE    %29c SIZE\n", ' ', ' ');
    printf("----    %29c ----\n", ' ', ' ');
    for (i = 0; i < AmountOfFiles; i++)
        printf("%-36s  %d\n", information[i].name, information[i].size);
    printf("Time: %lf\n", tt2 - tt1);
}

void printFunction2(int AmountOfFiles)
{
    int i;
    printf("Listing of files:\n\n");
    printf("FILE   %29c SIZE\n", ' ', ' ');
    printf("----   %29c ----\n", ' ', ' ');
    for (i = AmountOfFiles - 1; i >= 0; i--)
        printf("%-36s %d\n", information[i].name, information[i].size);
    printf("Time: %lf\n", tt2 - tt1);
}

void sortingPreference()
{
    printf("Choose how you want to sort files:\n");
    printf("1. By ascending.\n");
    printf("2. By descending.\n");
}

void elementsSwap(int* element1, int* element2)
{
    int temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

void bubbleSort(int AmountOfFiles)
{
    int i;
    char* stringHelper;
    stringHelper = (char*)malloc(sizeof(char) * 256);
    if (AmountOfFiles == 1)
        return;
    for (i = 0; i < AmountOfFiles - 1; i++)
        if (information[i].size > information[i + 1].size)
        {
            elementsSwap(&information[i].size, &information[i + 1].size);
            strcpy(stringHelper, information[i + 1].name);
            strcpy(information[i + 1].name, information[i].name);
            strcpy(information[i].name, stringHelper);
        }
    bubbleSort(AmountOfFiles - 1);
    free(stringHelper);
}

void selectionSort(int AmountOfFiles)
{
    int i, j, minIndex;
    char* stringHelper;
    stringHelper = (char*)malloc(sizeof(char) * 256);
    for (i = 0; i < AmountOfFiles - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < AmountOfFiles; j++)
            if (information[j].size < information[minIndex].size)
                minIndex = j;
        elementsSwap(&information[minIndex].size, &information[i].size);
        strcpy(stringHelper, information[minIndex].name);
        strcpy(information[minIndex].name, information[i].name);
        strcpy(information[i].name, stringHelper);
    }
    free(stringHelper);
}

void insertionSort(int AmountOfFiles)
{
    int i = 0;
    int last = information[AmountOfFiles - 1].size;
    int j = AmountOfFiles - 2;
    char* stringHelper;
    stringHelper = (char*)malloc(sizeof(char) * 256);
    if (AmountOfFiles <= 1)
        return;
    insertionSort(AmountOfFiles - 1);
    while (j >= 0 && information[j].size > last)
    {
        information[j + 1].size = information[j].size;
        strcpy(stringHelper, information[j + 1].name);
        strcpy(information[j + 1].name, information[j].name);
        strcpy(information[j].name, stringHelper);
        j--;
    }
    information[j + 1].size = last;
    free(stringHelper);
}

void shellSort(int AmountOfFiles)
{
    int i, j, step;
    int tmp;
    char* stringHelper;
    stringHelper = (char*)malloc(sizeof(char) * 256);
    for (step = AmountOfFiles / 2; step > 0; step /= 2)
        for (i = step; i < AmountOfFiles; i++)
        {
            tmp = information[i].size;
            for (j = i; j >= step; j -= step)
            {
                if (tmp < information[j - step].size)
                {
                    information[j].size = information[j - step].size;
                    strcpy(stringHelper, information[j - step].name);
                    strcpy(information[j - step].name, information[j].name);
                    strcpy(information[j].name, stringHelper);
                }
                else
                    break;
            }
            information[j].size = tmp;
        }
    free(stringHelper);
}

void merge(int l, int m, int AmountOfFiles)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = AmountOfFiles - m;
    int* L, * R;
    L = (int*)malloc(sizeof(int) * n1);
    R = (int*)malloc(sizeof(int) * n2);
    for (i = 0; i < n1; i++)
        L[i] = information[l + i].size;
    for (j = 0; j < n2; j++)
        R[j] = information[m + 1 + j].size;
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            information[k].size = L[i];
            i++;
        }
        else
        {
            information[k].size = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        information[k].size = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        information[k].size = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int l, int AmountOfFiles)
{
    if (l < AmountOfFiles) {
        int m = l + (AmountOfFiles - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, AmountOfFiles);
        merge(l, m, AmountOfFiles);
    }
}

int partition(int low, int AmountOfFiles)
{
    int pivot = information[AmountOfFiles].size;
    int i = (low - 1);
    for (int j = low; j <= AmountOfFiles - 1; j++)
    {
        if (information[j].size < pivot)
        {
            i++;
            elementsSwap(&information[i].size, &information[j].size);
        }
    }
    elementsSwap(&information[i + 1].size, &information[AmountOfFiles].size);
    return (i + 1);
}

void quickSort(int low, int AmountOfFiles)
{
    if (low < AmountOfFiles)
    {
        int pi = partition(low, AmountOfFiles);
        quickSort(low, pi - 1);
        quickSort(pi + 1, AmountOfFiles);
    }
}


void countingSort(int AmountOfFiles)
{
    int output[10];
    int* count;
    int max = information[0].size;
    int i;
    for (i = 1; i < AmountOfFiles; i++)
    {
        if (information[i].size > max)
            max = information[i].size;
    }
    count = (int*)malloc(sizeof(int) * (max + 1));
    for (i = 0; i <= max; i++)
    {
        count[i] = 0;
    }
    for (i = 0; i < AmountOfFiles; i++)
    {
        count[information[i].size]++;
    }
    for (i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }
    for (i = AmountOfFiles - 1; i >= 0; i--)
    {
        output[count[information[i].size] - 1] = information[i].size;
        count[information[i].size]--;
    }
    for (i = 0; i < AmountOfFiles; i++)
    {
        information[i].size = output[i];
    }
}

void sortingMethodChoice(int AmountOfFiles)
{
    q = scanf("%d", &choice);
    while (q != 1 || choice > 7 || choice < 1)
        userControl();
    q = 0;
    switch (choice)
    {
      case 1:
      {
        tt1 = omp_get_wtime();
        bubbleSort(AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
      case 2:
      {
        tt1 = omp_get_wtime();
        insertionSort(AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
      case 3:
      {
        tt1 = omp_get_wtime();
        selectionSort(AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
      case 4:
      {
        tt1 = omp_get_wtime();
        mergeSort(0, AmountOfFiles - 1);
        tt2 = omp_get_wtime();
        break;
      }
      case 5:
      {
        tt1 = omp_get_wtime();
        quickSort(0, AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
      case 6:
      {
        tt1 = omp_get_wtime();
        shellSort(AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
      case 7:
      {
        tt1 = omp_get_wtime();
        countingSort(AmountOfFiles);
        tt2 = omp_get_wtime();
        break;
      }
    }
}

void sortingMethods()
{
    printf("Choose sorting method:\n");
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Merge Sort\n");
    printf("5. QuickSort\n");
    printf("6. ShellSort\n");
    printf("7. CountingSort\n");
}

void mainMenuChoiceInfo()
{
    printf("1. What this program can do.\n");
    printf("2. Sort files.\n");
    printf("3. Exit.\n\n");
}

void programAbilities()
{
    printf("This program is supposed to sort files by ascending or by descending using different sorting methods.\n");
    printf("All you have to do is choose sorting method, choose how you want to sort them (by ascending or by descending) and then enter path to the your PC'sfolder.\n\n");
    programMenu();
}

void programMenu()
{
    mainMenuChoiceInfo();
    q = scanf("%d", &choice);
    while (q != 1 || choice < 1 || choice > 3)
        userControl();
    q = 0;
    switch (choice)
    {
    case 1:
    {
        programAbilities();
        break;
    }
    case 2:
    {
        printf("\n");
        break;
    }
    case 3:
    {
        break;
    }
    }
}

void stringEditor(char* string, char* stringcopy, int stringcopylen)
{
    int i = 0, k = 0;
    char* slashes = "\\";
    for (i = 0; i < stringcopylen; i++)
        stringcopy[i] = 0;
    char* stringPointer;
    stringPointer = strtok(string, slashes);
    while (stringPointer != NULL)
    {
        strcat(stringcopy, stringPointer);
        strcat(stringcopy, "\\");
        stringPointer = strtok(NULL, slashes);
    }
    strcat(stringcopy, "*.*");
}

void main()
{
    int i = 0;
    int stringcopylen = 256;
    int AmountOfFiles = 0;
    int counter = 0;
    char* string;
    char* stringcopy;
    struct _finddata_t file;
    intptr_t hFile;
    string = (char*)malloc(sizeof(char*) * 256);
    stringcopy = (char*)malloc(sizeof(char*) * 256);
    printf("Greetings. This program will help you sort your files. Choose one of the following options below.\n\n");
    programMenu();
    if (choice == 3)
        return;
    while (selection != 4)
    {
        i = 0;
        AmountOfFiles = 0;
        selection = 0;
        printf("Enter path to a folder\n");
        getchar();
        gets(string);
        stringEditor(string, stringcopy, stringcopylen);
        printf("\n");
        while (((hFile = _findfirst(stringcopy, &file)) == -1L))
        {
            printf("No files in current directory! Try to enter path again:\n");
            gets(string);
            stringEditor(string, stringcopy, stringcopylen);
            hFile = _findfirst(stringcopy, &file);
        }
        do
        {
            AmountOfFiles++;
        } while (_findnext(hFile, &file) == 0);
        _findclose(hFile);
        while (selection != 1 && selection != 4)
        {
            i = 0;
            information = (struct filesInformation*)malloc(sizeof(struct filesInformation) * AmountOfFiles);
            hFile = _findfirst(stringcopy, &file);
            do
            {
                information[i].size = file.size;
                strcpy(information[i].name, file.name);
                i++;
            } while (_findnext(hFile, &file) == 0);
            _findclose(hFile);
            selection = 0;
            sortingMethods();
            sortingMethodChoice(AmountOfFiles);
            while (selection != 1 && selection != 2 && selection != 4)
            {
                sortingPreference();
                printChoice(AmountOfFiles);
                printf("\n");
                furtherOptions();
                q = scanf("%d", &selection);
                while (q != 1 || selection < 1 || selection > 4)
                    selectionControl();
                q = 0;
            }
            free(information);
        }
    }
    free(string);
    free(stringcopy);
}
