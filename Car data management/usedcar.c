#include "usedcar.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

araba* cardynamicarray = NULL;
unsigned int arraysize = 0;

araba* performancetestarray = NULL;
unsigned int perfsize = 0;

void readbrandfile(char* brandfilepath, char* brand) {
	clock_t begin = clock();
	if (cardynamicarray == NULL) {
		cardynamicarray = malloc(sizeof(araba));
		if (cardynamicarray == NULL) {
			printf("Dynamic array can't be started :(\n");
			return;
		}
		arraysize = 1;
	}
	else {
		arraysize++;
		cardynamicarray = realloc(cardynamicarray, sizeof(araba) * (arraysize));
		if (cardynamicarray == NULL) {
			printf("Dynamic array was lost in realloc :(\n");
			return;
		}
	}
	FILE* f = NULL, * f2 = NULL;
	f = fopen(brandfilepath, "r");
	if (f == NULL) {
		printf("There is no such file :(\n");
		return;
	}
	f2 = fopen("data.txt", "w");
	char ch;
	while ((ch = fgetc(f)) != EOF) {//virgullu yerleri bosluga, bosluluklu yerleri yok edip ayrý bir dosyaya kaydettim, duzgun sekilde okuyabilmek icin
		if (ch == ',') {
			ch = ' ';
			fputc(ch, f2);
		}
		else if (ch != ' ') {
			fputc(ch, f2);
		}
	}
	fclose(f);
	fclose(f2);
	f2 = fopen("data.txt", "r");
	fscanf(f2, "%*[^\n]");//okurken bastaki satiri atliyorum cunku orasi gereksiz
	while (1) {
		if (fscanf(f2, "%s %d %d %s %d %s %d %f %f", cardynamicarray[arraysize - 1].model, &cardynamicarray[arraysize - 1].year, &cardynamicarray[arraysize - 1].price,
			cardynamicarray[arraysize - 1].transmission, &cardynamicarray[arraysize - 1].mileage, cardynamicarray[arraysize - 1].fueltype, &cardynamicarray[arraysize - 1].tax,
			&cardynamicarray[arraysize - 1].milespergallon, &cardynamicarray[arraysize - 1].enginesize) == 9) {
			for (int i = 0; i < 10; i++) {
				cardynamicarray[arraysize - 1].brand[i] = brand[i];
				if (brand[i] == '\0' || (!(brand[i] >= 65 && brand[i] <= 90) && !(brand[i] >= 97 && brand[i] <= 122))) {
					cardynamicarray[arraysize - 1].brand[i] = '\0';
					break;
				}
			}
			arraysize++;
			cardynamicarray = realloc(cardynamicarray, sizeof(araba) * (arraysize));
			if (cardynamicarray == NULL) {
				printf("Dynamic array was lost in realloc :(\n");
				return;
			}
		}
		else {
			arraysize--;
			cardynamicarray = realloc(cardynamicarray, sizeof(araba) * (arraysize));
			if (cardynamicarray == NULL) {
				printf("Dynamic array was lost in realloc :(\n");
				return;
			}
			break;
		}
	}
	fclose(f2);
	remove("data.txt");//o dosyayla isim bitince sildim
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Data has been added from a file to dynamic array in %.2lf miliseconds, %d is total number of cars now :)\n", timespent, arraysize);
	return;
}

void writetofile(char* filepath) {
	clock_t begin = clock();
	FILE* f;
	f = fopen(filepath, "w");
	for (unsigned int i = 0; i < arraysize; i++) {
		fprintf(f, "index:%d brand:%s model:%s year:%d price:%d transmission:%s mileage:%d fueltype:%s tax:%d miles per gallon:%f enginesize:%f\n", i, cardynamicarray[i].brand, cardynamicarray[i].model, cardynamicarray[i].year, cardynamicarray[i].price, cardynamicarray[i].transmission, cardynamicarray[i].mileage, cardynamicarray[i].fueltype, cardynamicarray[i].tax, cardynamicarray[i].milespergallon, cardynamicarray[i].enginesize);
	}
	fclose(f);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been written to file(%s) in %.2lf miliseconds :)\n", filepath, timespent);
	return;
}

void quicksort(araba* darray, unsigned int size, unsigned int type) {
	if (size < 2) {
		return;
	}

	int lower, upper;
	araba pivot, temp;

	lower = 0;
	upper = size - 1;

	pivot = darray[rand() % (size)];

	while (lower <= upper) {
		if (type == 0) {
			while (darray[lower].year > pivot.year) {
				lower++;
			}
			while (darray[upper].year < pivot.year) {
				upper--;
			}
		}
		else if (type == 1) {
			while (darray[lower].price > pivot.price) {
				lower++;
			}
			while (darray[upper].price < pivot.price) {
				upper--;
			}
		}
		else if (type == 2) {
			while (darray[lower].mileage > pivot.mileage) {
				lower++;
			}
			while (darray[upper].mileage < pivot.mileage) {
				upper--;
			}
		}
		else if (type == 3) {
			while (darray[lower].tax > pivot.tax) {
				lower++;
			}
			while (darray[upper].tax < pivot.tax) {
				upper--;
			}
		}
		else if (type == 4) {
			while (darray[lower].milespergallon > pivot.milespergallon) {
				lower++;
			}
			while (darray[upper].milespergallon < pivot.milespergallon) {
				upper--;
			}
		}
		else if (type == 5) {
			while (darray[lower].enginesize > pivot.enginesize) {
				lower++;
			}
			while (darray[upper].enginesize < pivot.enginesize) {
				upper--;
			}
		}
		if (lower <= upper) {
			temp = darray[lower];
			darray[lower] = darray[upper];
			darray[upper] = temp;
			lower++;
			upper--;
		}
	}

	quicksort(darray, upper + 1, type);
	quicksort(&darray[lower], size - lower, type);
	return;
}

void quicksortbyyear() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 0);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by year in %.2lf miliseconds :)\n", timespent);
	return;
}

void quicksortbyprice() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 1);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by price in %.2lf miliseconds :)\n", timespent);
	return;
}

void quicksortbymileage() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 2);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by mileage in %.2lf miliseconds :)\n", timespent);
	return;
}

void quicksortbytax() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 3);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by tax in %.2lf miliseconds :)\n", timespent);
	return;
}

void quicksortbympg() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 4);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by miles per gallon in %.2lf miliseconds :)\n", timespent);
	return;
}

void quicksortbyenginesize() {
	clock_t begin = clock();
	if (arraysize > 0) {
		quicksort(cardynamicarray, arraysize, 5);
	}
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Dynamic array has been sorted by engine size in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebyyear(char* filepath) {
	clock_t begin = clock();
	quicksortbyyear();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebyprice(char* filepath) {
	clock_t begin = clock();
	quicksortbyprice();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebymileage(char* filepath) {
	clock_t begin = clock();
	quicksortbymileage();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebytax(char* filepath) {
	clock_t begin = clock();
	quicksortbytax();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebympg(char* filepath) {
	clock_t begin = clock();
	quicksortbympg();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void sortandsavebyenginesize(char* filepath) {
	clock_t begin = clock();
	quicksortbyenginesize();
	writetofile(filepath);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Sorting and saving are finished in %.2lf miliseconds :)\n", timespent);
	return;
}

void addbyhand(araba x) {
	clock_t begin = clock();
	arraysize++;
	cardynamicarray = realloc(cardynamicarray, sizeof(araba) * (arraysize));
	if (cardynamicarray == NULL) {
		printf("Dynamic array was lost in realloc :(\n");
		return;
	}
	cardynamicarray[arraysize - 1] = x;
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Data has been added by hand to dynamic array in %.2lf miliseconds, %d is total number of cars now :)\n", timespent, arraysize);
	return;
}

void deletebyhand(araba x) {
	clock_t begin = clock();
	int a = 0;
	unsigned int i;
	for (i = 0; i < arraysize; i++) {
		a = 0;
		for (int k = 0; k < 10; k++) {
			if (cardynamicarray[i].brand[k] != x.brand[k]) {
				a = 1;
				continue;
			}
			if (cardynamicarray[i].brand[k] == '\0' && x.brand[k] == '\0') {
				break;
			}
		}
		for (int k = 0; k < 10; k++) {
			if (cardynamicarray[i].model[k] != x.model[k]) {
				a = 1;
				continue;
			}
			if (cardynamicarray[i].model[k] == '\0' && x.model[k] == '\0') {
				break;
			}
		}
		if (cardynamicarray[i].year != x.year) {
			a = 1;
			continue;
		}
		if (cardynamicarray[i].price != x.price) {
			a = 1;
			continue;
		}
		for (int k = 0; k < 10; k++) {
			if (cardynamicarray[i].transmission[k] != x.transmission[k]) {
				a = 1;
				continue;
			}
			if (cardynamicarray[i].transmission[k] == '\0' && x.transmission[k] == '\0') {
				break;
			}
		}
		if (cardynamicarray[i].mileage != x.mileage) {
			a = 1;
			continue;
		}
		for (int k = 0; k < 10; k++) {
			if (cardynamicarray[i].fueltype[k] != x.fueltype[k]) {
				a = 1;
				continue;
			}
			if (cardynamicarray[i].fueltype[k] == '\0' && x.fueltype[k] == '\0') {
				break;
			}
		}
		if (cardynamicarray[i].tax != x.tax) {
			a = 1;
			continue;
		}
		if (cardynamicarray[i].milespergallon != x.milespergallon) {
			a = 1;
			continue;
		}
		if (cardynamicarray[i].enginesize != x.enginesize) {
			a = 1;
			continue;
		}
		if (a == 0) {
			break;
		}
	}
	if (a == 1) {
		double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
		printf("No such element was found in the dynamic array in %.2lf miliseconds :(\n", timespent);
		return;
	}
	else if (a == 0) {
		araba y = cardynamicarray[i];
		cardynamicarray[i] = cardynamicarray[arraysize - 1];
		cardynamicarray[arraysize - 1] = y;
		arraysize--;
		cardynamicarray = realloc(cardynamicarray, sizeof(araba) * arraysize);
		if (cardynamicarray == NULL) {
			printf("Dynamic array was lost in realloc :(\n");
			return;
		}
		double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
		printf("The element was found and deleted from the dynamic array in %.2lf miliseconds :)\n", timespent);
		return;
	}
}

void searchandsave(char* filepath, char* brand, char* model, char* transmission, char* fueltype, int yearmin, int yearmax, int pricemin, int pricemax, int mileagemin, int mileagemax,
	int taxmin, int taxmax, float mpgmin, float mpgmax, float enginemin, float enginemax) {
	clock_t begin = clock();
	FILE* f;
	f = fopen(filepath, "w");
	int x = 0;
	for (int i = 0; i < arraysize; i++) {
		x = 0;
		if (!aynimi(brand, "null")) {
			for (int k = 0; k < 10; k++) {
				if (cardynamicarray[i].brand[k] != brand[k]) {
					x = 1;
					break;
				}
				if (cardynamicarray[i].brand[k] == '\0' && brand[k] == '\0') {
					break;
				}
			}
		}
		if (x == 1) {
			continue;
		}
		if (!aynimi(model, "null")) {
			for (int k = 0; k < 10; k++) {
				if (cardynamicarray[i].model[k] != model[k]) {
					x = 1;
					break;
				}
				if (cardynamicarray[i].model[k] == '\0' && model[k] == '\0') {
					break;
				}
			}
		}
		if (x == 1) {
			continue;
		}
		if (!aynimi(transmission, "null")) {
			for (int k = 0; k < 10; k++) {
				if (cardynamicarray[i].transmission[k] != transmission[k]) {
					x = 1;
					break;
				}
				if (cardynamicarray[i].transmission[k] == '\0' && transmission[k] == '\0') {
					break;
				}
			}
		}
		if (x == 1) {
			continue;
		}
		if (!aynimi(fueltype, "null")) {
			for (int k = 0; k < 10; k++) {
				if (cardynamicarray[i].fueltype[k] != fueltype[k]) {
					x = 1;
					break;
				}
				if (fueltype[k] == '\0') {
					break;
				}
			}
		}
		if (x == 1) {
			continue;
		}
		if ((yearmin >= 0 && yearmax >= 0) && !(cardynamicarray[i].year >= yearmin && cardynamicarray[i].year <= yearmax)) {
			continue;
		}
		if ((pricemin >= 0 && pricemax >= 0) && !(cardynamicarray[i].price >= pricemin && cardynamicarray[i].price <= pricemax)) {
			continue;
		}
		if ((mileagemin >= 0 && mileagemax >= 0) && !(cardynamicarray[i].mileage >= mileagemin && cardynamicarray[i].mileage <= mileagemax)) {
			continue;
		}
		if ((taxmin >= 0 && taxmax >= 0) && !(cardynamicarray[i].tax >= taxmin && cardynamicarray[i].tax <= taxmax)) {
			continue;
		}
		if ((mpgmin >= 0 && mpgmax >= 0) && !(cardynamicarray[i].milespergallon >= mpgmin && cardynamicarray[i].milespergallon <= mpgmax)) {
			continue;
		}
		if ((enginemin >= 0 && enginemax >= 0) && !(cardynamicarray[i].enginesize >= enginemin && cardynamicarray[i].enginesize <= enginemax)) {
			continue;
		}
		fprintf(f, "index:%d brand:%s model:%s year:%d price:%d transmission:%s mileage:%d fueltype:%s tax:%d miles per gallon:%f enginesize:%f\n", i, cardynamicarray[i].brand,
			cardynamicarray[i].model, cardynamicarray[i].year, cardynamicarray[i].price, cardynamicarray[i].transmission, cardynamicarray[i].mileage, cardynamicarray[i].fueltype,
			cardynamicarray[i].tax, cardynamicarray[i].milespergallon, cardynamicarray[i].enginesize);
	}
	fclose(f);
	double timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("The search has been completed and written to file(%s) in %.2lf miliseconds :)\n", filepath, timespent);
	return;
}

void performancetest(char* brandfilepath, char* brand, int time) {
	clock_t begin = clock();
	if (performancetestarray == NULL) {
		performancetestarray = malloc(sizeof(araba));
		if (performancetestarray == NULL) {
			printf("Dynamic array can't be started :(\n");
			return;
		}
		perfsize = 1;
	}
	else {
		perfsize++;
		performancetestarray = realloc(performancetestarray, sizeof(araba) * (perfsize));
		if (performancetestarray == NULL) {
			printf("Dynamic array was lost in realloc :(\n");
			return;
		}
	}
	FILE* f = NULL, * f2 = NULL;
	f = fopen(brandfilepath, "r");
	if (f == NULL) {
		printf("There is no such file :(\n");
		return;
	}
	f2 = fopen("data.txt", "w");
	char ch;
	while ((ch = fgetc(f)) != EOF) {//virgullu yerleri bosluga, bosluluklu yerleri yok edip ayrý bir dosyaya kaydettim, duzgun sekilde okuyabilmek icin
		if (ch == ',') {
			ch = ' ';
			fputc(ch, f2);
		}
		else if (ch != ' ') {
			fputc(ch, f2);
		}
	}
	fclose(f);
	fclose(f2);
	f2 = fopen("data.txt", "r");
	clock_t begin3;
	double timespent;
	for (int mar = 0; mar < time; mar++) {
		begin3 = clock();
		if (mar != 0) {
			perfsize++;
			performancetestarray = realloc(performancetestarray, sizeof(araba) * (perfsize));
			if (performancetestarray == NULL) {
				printf("Dynamic array was lost in realloc :(\n");
				return;
			}
		}
		rewind(f2);
		fscanf(f2, "%*[^\n]");//okurken bastaki satiri atliyorum cunku orasi gereksiz
		while (1) {
			if (fscanf(f2, "%s %d %d %s %d %s %d %f %f", performancetestarray[perfsize - 1].model, &performancetestarray[perfsize - 1].year, &performancetestarray[perfsize - 1].price, performancetestarray[perfsize - 1].transmission, &performancetestarray[perfsize - 1].mileage, performancetestarray[perfsize - 1].fueltype, &performancetestarray[perfsize - 1].tax, &performancetestarray[perfsize - 1].milespergallon, &performancetestarray[perfsize - 1].enginesize) == 9) {
				for (int i = 0; i < 10; i++) {
					performancetestarray[perfsize - 1].brand[i] = brand[i];
					if (brand[i] == '\0' || (!(brand[i] >= 65 && brand[i] <= 90) && !(brand[i] >= 97 && brand[i] <= 122))) {
						performancetestarray[perfsize - 1].brand[i] = '\0';
						break;
					}
				}
				perfsize++;
				performancetestarray = realloc(performancetestarray, sizeof(araba) * (perfsize));
				if (performancetestarray == NULL) {
					printf("Dynamic array was lost in realloc :(\n");
					return;
				}
			}
			else {
				perfsize--;
				performancetestarray = realloc(performancetestarray, sizeof(araba) * (perfsize));
				if (performancetestarray == NULL) {
					printf("Dynamic array was lost in realloc :(\n");
					return;
				}
				break;
			}
		}
		timespent = (double)(clock() - begin3) / (CLOCKS_PER_SEC / 1000);
		printf("%d. data addition step is done in %.2lf miliseconds, %d is total number of cars now :)\n", mar + 1, timespent, perfsize);
	}
	fclose(f2);
	remove("data.txt");//o dosyayla isim bitince sildim
	clock_t begin2 = clock();
	quicksort(performancetestarray, perfsize, 1);
	timespent = (double)(clock() - begin2) / (CLOCKS_PER_SEC / 1000);
	printf("%d added car datas are sorted by price in %.2lf miliseconds :)\n", perfsize, timespent);
	timespent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
	printf("The whole performance test is done in %.2lf miliseconds :)\n", timespent);
	perfsize = 0;
	free(performancetestarray);
	performancetestarray = NULL;
	return;
}

int aynimi(char* m, char* n) {
	for (int i = 0; i < 10; i++) {
		if (m[i] == '\0' || n[i] == '\0') {
			return 1;
		}
		if (m[i] != n[i]) {
			return 0;
		}
	}
	return 1;
}
