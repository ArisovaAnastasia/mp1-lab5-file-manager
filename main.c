#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Sort_selection(int N, int array[N], int new_array[N]){
    for (int i = 0; i < N; i++){
        new_array[i]= array[i];
    }
    int minPosition, tmp;
    for (int i = 0; i < N; i++)
    {
        minPosition = i;
        for (int j = i + 1; j < N; j++)
            if (new_array[minPosition] > new_array[j])
                minPosition = j;
        tmp = new_array[minPosition];
        new_array[minPosition] = new_array[i];
        new_array[i] = tmp;
    }
}

void merge(int *a, int l, int r)
{
    if (l == r) return;
    int mid = (l + r) / 2;
    merge(a, l, mid);
    merge(a, mid + 1, r);
    int i = l;
    int j = mid + 1;
    int *tmp = (int*)malloc(r * sizeof(int));
    for (int step = 0; step < r - l + 1; step++)
    {
        if ((j > r) || ((i <= mid) && (a[i] < a[j])))
        {
            tmp[step] = a[i];
            i++;
        }
        else
        {
            tmp[step] = a[j];
            j++;
        }
    }
    for (int step = 0; step < r - l + 1; step++)
        a[l + step] = tmp[step];
}

void mergeSort(int N, int array[N], int new_array[N]){
    for (int i = 0; i < N; i++){
        new_array[i]= array[i];
    }
    merge(new_array, 0, N-1);
}


struct File_Data{
    int size;
    char name[256];
};

int main(void) {
    bool exit = false;
    struct File_Data fileData[100];
    int filesize[100];
    char filename[100][256];
    //char path[256] = "/Users/vasilijeremin/Pictures/Прикольные фоточки";
    char path[256];
    printf("Введите директорию: ");
    gets(path);
    DIR *direct;
    direct = opendir (path);
    struct dirent *struct_dirent;
    int size_direct = -2;
    if (direct != NULL)
    {

        while (struct_dirent = readdir (direct)){
            if(size_direct >= 0) {

                strcpy(filename[size_direct], struct_dirent->d_name);
                struct stat st;
                char path_file[100];
                strcpy(path_file, path);
                if(path_file[strlen(path_file)-1]!= '/')
                    strcat(path_file, "/");
                strcat(path_file, struct_dirent->d_name);
                stat(path_file, &st);
                off_t size = st.st_size;
                filesize[size_direct] = size;

                //printf("%s", path_file);
                printf(" %s", struct_dirent->d_name);
                printf(" %i bytes\n", size);
            }
            ++size_direct;
        }
        while (!exit) {
            int select_sort;
            int sort_array[size_direct];
            printf("\nВыберите метод сортировки:\n"
                   "1. Сортировка выбором\n"
                   "2. Сортировка слиянием\n\n"
                   "3. Выйти\n");
            scanf("%i", &select_sort);
            switch (select_sort) {
                case 1:
                    printf("\n");
                    clock_t begin = clock();
                    Sort_selection(size_direct, filesize, sort_array);
                    clock_t end = clock();
                    int reverse = 1;
                    printf("Выберите метод сортировки:\n"
                           "1. По возрастанию\n"
                           "2. По убыванию\n");
                    scanf("%i", &reverse);
                    switch (reverse) {
                        case 1:
                            for (int i = 0; i < size_direct; ++i) {

                                for (int j = 0;j < size_direct; ++j) {
                                    if(sort_array[i] == filesize[j]){
                                        printf(" %s ", filename[j]);
                                        break;
                                    }
                                }
                                printf("%i bytes\n", sort_array[i]);
                            }
                            break;
                        case 2:
                            for (int i = size_direct-1; i >= 0; --i) {

                                for (int j = 0;j < size_direct; ++j) {
                                    if(sort_array[i] == filesize[j]){
                                        printf(" %s ", filename[j]);
                                        break;
                                    }
                                }
                                printf("%i bytes\n", sort_array[i]);
                            }
                    }

                    printf("%f seconds\n", (long double)(end - begin) / CLOCKS_PER_SEC);
                    break;
                case 2:
                    printf("\n");
                    clock_t begin1 = clock();
                    mergeSort(size_direct, filesize, sort_array);
                    clock_t end1 = clock();
                    int reverse1 = 1;
                    printf("Выберите метод сортировки:\n"
                           "1. По возрастанию\n"
                           "2. По убыванию\n");
                    scanf("%i", &reverse1);
                    switch (reverse1) {
                        case 1:
                            for (int i = 0; i < size_direct; ++i) {

                                for (int j = 0;j < size_direct; ++j) {
                                    if(sort_array[i] == filesize[j]){
                                        printf(" %s ", filename[j]);
                                        break;
                                    }
                                }
                                printf("%i bytes\n", sort_array[i]);
                            }
                            break;
                        case 2:
                            for (int i = size_direct-1; i >= 0; --i) {

                                for (int j = 0;j < size_direct; ++j) {
                                    if(sort_array[i] == filesize[j]){
                                        printf(" %s ", filename[j]);
                                        break;
                                    }
                                }
                                printf("%i bytes\n", sort_array[i]);
                            }
                    }

                    printf("%f seconds\n", (long double)(end1 - begin1) / CLOCKS_PER_SEC);
                    break;
                case 3:
                    exit = true;
                    break;
            }

        }

    }
    else
        puts ("Не удалось открыть каталог.");
}