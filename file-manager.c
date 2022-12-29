#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

struct nameSize {
    long long size;
    char name[512];
};

void bubble_sort(struct nameSize array[], int size) {
    for (int i = 0; i < size-1; ++i) {
        for (int j = size-1; j > i; --j) {
            if (array[j-1].size > array[j].size) {
                struct nameSize temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
    }
}

void merge(struct nameSize array[], int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    struct nameSize left[n1], right[n2];

    for (i = 0; i < n1; i++)
        left[i] = array[start + i];
    for (j = 0; j < n2; j++)
        right[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (left[i].size <= right[j].size) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(struct nameSize array[], int start, int end) {
    if (start < end) {
        int m = start + (end - start) / 2;

        merge_sort(array, start, m);
        merge_sort(array, m + 1, end);

        merge(array, start, m, end);
    }
}

int main() {
    char *path = (char*) malloc(sizeof (char));
    gets(path);
    if (path[strlen(path)-1]!='/')
        strcat(path,"/");

    DIR *folder = opendir(path);
    if(folder == NULL)
    {
        perror("Unable to read entity");
        return(1);
    }

    struct dirent *entity;
    struct stat stats;
    struct nameSize *files = malloc(sizeof(struct nameSize));

    int count = 0;

    while ((entity = readdir(folder)) != NULL) {
        if (entity->d_type == DT_REG) {
            char *filePath = (char *) malloc(sizeof(char));
            strcat(filePath, path);
            strcat(filePath, entity->d_name);
            stat(filePath, &stats);

            files[count].size = stats.st_size;
            strcpy(files[count].name, filePath);

            free(filePath);
            count++;
        }
    }

    int mode;
    printf("Choose sorting method: 1)Bubble Sort; 2)Merge Sort; \n0) Exit \n >>>");
    scanf("%d", &mode);

    clock_t start, end;
    double cpu_time_used;

    switch(mode) {
        case 0:
            return 0;
            break;
        case 1:
            start = clock();
            bubble_sort(files, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            break;
        case 2:
            start = clock();
            merge_sort(files, 0, count-1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            break;
        default:
            printf("Choose correct mode, please\n");
            break;
    }

    for (int i = 0; i<count; i++)
        printf("Size: %-8lld Name:%s\n", files[i].size, files[i].name);
    printf("Completed in %f seconds\n", cpu_time_used);

    closedir(folder);
    return 0;
}