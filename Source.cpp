#include <stdio.h>
#include <iomanip>
#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>
#include <time.h>

struct data {
	WCHAR name[100];
	int bytes;
};

void BubbleSort(data arr[], int n) {
	data buf;
	if (n == 1)
		return;
	for (int i = 0; i < n - 1; i++)
		if (arr[i].bytes > arr[i + 1].bytes) {
			buf = arr[i + 1];
			arr[i + 1] = arr[i];
			arr[i] = buf;
		}

	BubbleSort(arr, n - 1);
}

void Merge(data arr[], int l, int m, int r) {
	int i = l, j = m;
	data buf[6]{};
	for (int a = l; a < r; ++a) {
		if (i < m && j < r) {
			if (arr[i].bytes > arr[j].bytes)
				buf[a] = arr[j++];
			else
				buf[a] = arr[i++];

		}
		else {
			if (i >= m)
				buf[a] = arr[j++];
			else
				buf[a] = arr[i++];
		}
	}
	for (int i = l; i < r; ++i) {
		arr[i] = buf[i];
	}
}


void MergeSort(data arr[], int l, int r) {
	if (l + 1 >= r)
		return;
	int m = (r + l) / 2;
	MergeSort(arr, l, m);
	MergeSort(arr, m, r);
	Merge(arr, l, m, r);
}

void PrintStructArr(int a_size, data a[], int m) {
	if (m == 2) {
		for (int i = 0; i <= a_size; ++i) {
			wprintf_s(a[i].name);
			printf(" %i бит\n", a[i].bytes);
		}
	} else {
		for (int i = a_size; i >= 0; --i) {
			wprintf_s(a[i].name);
			printf(" %i бит\n", a[i].bytes);
		}
	}
	
	printf("\n");
}

int main() {
	setlocale(0, "");

	int ans_user = -1, flag_sort = -1, flag_met_sort = -1, k = -1;
	data files[1000];

	printf("Прототип файлового менеджера.\n"
		"Операции: \n"
		"	1. Выбрать сортировку;\n"
		"	2. Показать выбранную сортировку;\n"
		"	3. Ввод пути до директории, в которой необходимо отсортировать содержимое;\n"
		"	4. Завершить программу.\n");

	while (ans_user != 4) {
		printf("\nВведите команду: \n");
		scanf_s("%i", &ans_user);

		switch (ans_user){
		case 1:
			printf("\nДоступные сортировки: \n"
				"1. Сортировка пузырьком (простая сортировка);\n"
				"2. Сортировка слиянием (сложная сортировка).\n"
				"Выберите сортировку (введите цифру): \n");

			scanf_s("%i", &ans_user);
			while (!((ans_user == 1) or (ans_user == 2))) {
				printf("Повторите попытку.\n");
				scanf_s("%i", &ans_user);
			}
			flag_sort = ans_user;
			break;

		case 2:
			switch (flag_sort) {
			case -1:
				printf("Сортировка не выбрана.\n");
				break;
			case 1:
				printf("Сортировка пузырьком.\n");
				break;
			case 2:
				printf("Сортировка слиянием.\n");
				break;
			}
			break;

		case 3:
			if (flag_sort == -1) {
				printf("Для начала необходимо выбрать сортировку.\n");
			} else {
				printf("\nВведите путь: \n");
				getchar();

				TCHAR path[100]; 
				StringCbGets(path, 100);

				WIN32_FIND_DATA ffd;
				TCHAR szDir[MAX_PATH];

				HANDLE hFind = INVALID_HANDLE_VALUE;

				StringCchCopy(szDir, MAX_PATH, path);
				StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

				hFind = FindFirstFile(szDir, &ffd);

				if (INVALID_HANDLE_VALUE == hFind)
				{
					printf("Неправильный путь.\n");
					break;
				}

				while ((FindNextFile(hFind, &ffd) != 0) and (k <= 1000)) {
					if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						++k;
						StringCchCopy(files[k].name, MAX_PATH, ffd.cFileName);
						files[k].bytes = ffd.nFileSizeLow;
					}
				}

				printf("\nВведите метод сортировки (1 - по убыванию; 2 - по возрастанию)\n");
				scanf_s("%i", &ans_user);
				while (!((ans_user == 1) or (ans_user == 2))) {
					printf("Повторите попытку.\n");
					scanf_s("%i", &ans_user);
				}
				flag_met_sort = ans_user;

				if (flag_sort == 1) {
					clock_t begin = clock();
					BubbleSort(files, k+1);
					clock_t end = clock();
					if (flag_met_sort == 1) {
						printf("\n");
						PrintStructArr(k, files, 1);
					}
					else {
						printf("\n");
						PrintStructArr(k, files, 2);
					}
					printf("Время сортировки: %f сек.\n", (double)(end - begin) / CLOCKS_PER_SEC);
				} else {
					clock_t begin = clock();
					MergeSort(files, 0, k+1);
					clock_t end = clock();
					if (flag_met_sort == 1) {
						printf("\n");
						PrintStructArr(k, files, 1);
					}
					else {
						printf("\n");
						PrintStructArr(k, files, 2);
					}
					printf("Время сортировки: %f сек.\n", (double)(end - begin) / CLOCKS_PER_SEC);
				}

				FindClose(hFind);
				k = -1, flag_met_sort = -1;
				break;
			}
		}
	}

	return 0;
}