// lb2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

void arrayfilling(int** x, int size) {
	for (int i = 0; i < size; i++) {
		*(x + i) = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) 
		{
			*(*(x + i) + j) = rand() % 100 + 1;
		}
	}
}

void freedom(int** x, int size) {
	for (int i = 0; i < size; i++) {
		free(*(x + i)); //освобождаем память
	}
	free(x); //освобождаем память
}

int main()
{
	setlocale(LC_ALL, "rus");
    srand(time(NULL));
    clock_t startTime, stopTime;
    double times;
	const int size = 10000;

	int** a = (int**)malloc(size * sizeof(int*));
	int** b = (int**)malloc(size * sizeof(int*));
	int** c = (int**)malloc(size * sizeof(int*));

    int elem_c;

    startTime = clock(); //время до поиска

	arrayfilling(a, size);
	arrayfilling(b, size);
	
	for (int i = 0; i < size; i++) {
		*(c + i) = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++)
		{
			elem_c = 0;
			for (int r = 0; r < size; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
			}
			c[i][j] = elem_c;
		}
	}

    stopTime = clock();	//время после поиска
    times = double(stopTime - startTime) / CLK_TCK;
	ofstream fout("res.txt", ios_base::app);
	fout << "При размере " << size << " результат = " << times << " sec" << endl;
	fout.close();
    cout << times << " sec" << endl;
	freedom(a, size);
	freedom(b, size);
	freedom(c, size);
}