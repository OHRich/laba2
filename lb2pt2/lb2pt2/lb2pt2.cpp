// lb2pt2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

void shell(int* items, int count)
{

	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
	int i, j;
	int x, y;

	i = left; j = right;

	/* выбор компаранда */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int comp(const int* i, const int* j)
{
	return *i - *j;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	clock_t startTime, stopTime;
	double times;
	const int size = 1000000;
	int i = 0, m;
	int* a = (int*)malloc(size * sizeof(int));
	int* b = (int*)malloc(size * sizeof(int));
	int* c = (int*)malloc(size * sizeof(int));
	int* d = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++) {
		a[i] = rand() % 10;
	}

	for (i = 0; i < size; i++) {
		b[i] = i*2;
	}

	c[0] = 0;
	for (i = 1; i < size; i++) {
		c[i] = c[0] - i*2;
	}

	if (size % 2 == 0) {
		m = size / 2;
	}
	else {
		m = size / 2 + 1;
	}

	d[0] = 0;
	for (i = 1; i < m; i++) {
		d[i] = d[i-1] + 3;
	}
	for (i = m; i < size; i++) {
		d[i] = d[i-1] - 3;
	}

	ofstream fout("res.txt", ios_base::app);

	fout.width(20);
	fout << "Cортировка Шелла		";
	fout << size << "		";
	startTime = clock();
	shell(a, size);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";

	
	startTime = clock();
	shell(b, size);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";
	
	startTime = clock();
	shell(c, size);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec				";
	
	startTime = clock();
	shell(d, size);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		" << endl;
	
	fout.width(20);
	fout << "Быстрая сортировка		";
	fout << size << "		";
	startTime = clock();
	qs(a, 0, size - 1);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";
	
	startTime = clock();
	qs(b, 0, size - 1);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";
	
	startTime = clock();
	qs(c, 0, size - 1);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec				";
	
	startTime = clock();
	qs(d, 0, size - 1);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		" << endl;
	
	fout.width(20);
	fout << "Сортировка qsort		";
	fout << size << "		";
	startTime = clock();
	qsort(a, size, sizeof(int), (int(*) (const void*, const void*)) comp);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";
	
	startTime = clock();
	qsort(b, size, sizeof(int), (int(*) (const void*, const void*)) comp);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		";
	
	startTime = clock();
	qsort(c, size, sizeof(int), (int(*) (const void*, const void*)) comp);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec				";
	
	startTime = clock();
	qsort(d, size, sizeof(int), (int(*) (const void*, const void*)) comp);
	stopTime = clock();
	times = double(stopTime - startTime) / CLK_TCK;
	fout << times << " sec		" << endl << endl;

	fout.close();

	free(a);
	free(b);
	free(c);
	free(d);
}