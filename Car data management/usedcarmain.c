#include "usedcar.h"
#include <stdio.h>

int main() {
	int a;
	char m[1000];
	char n[10];
	araba y;
x:
	printf("\nPress 1 to add car data from a brand file to dynamic array.\n");
	printf("Press 2 to sort the cars by year and save in a file.\n");
	printf("Press 3 to sort the cars by price and save in a file.\n");
	printf("Press 4 to sort the cars by mileage and save in a file.\n");
	printf("Press 5 to sort the cars by tax and save in a file.\n");
	printf("Press 6 to sort the cars by miles per gallon and save in a file.\n");
	printf("Press 7 to sort the cars by engine size and save in a file.\n");
	printf("Press 8 to add car data by hand.\n");
	printf("Press 9 to delete car data by hand.\n");
	printf("Press 10 to search by parameters, write negative values for the numeric parameters you don't want to search.\n");
	printf(" Write 'null' for the string parameters you don't want to search.(case sensitive, max 10 characters)\n");
	printf(" Cars matching your search criteria will be saved in a file that you decided.(max 1000 characters filepath)\n");
	printf("Press 11 to test performance of the program. You will give brand file and brand to the program.\n");
	printf(" The program will read that data as much as time you want and sort it by price.\n");
	printf("Press something else to quit\n");
	scanf("%d", &a);
	if (a == 1) {
		printf("Write file path(max 1000 character)\n");
		scanf("%s", m);
		printf("Write brand name(max 10 character)\n");
		scanf("%s", n);
		readbrandfile(m, n);
		goto x;
	}
	else if (a == 2) {
		sortandsavebyyear("UsedCarDataSortedByYear.txt");
		goto x;
	}
	else if (a == 3) {
		sortandsavebyprice("UsedCarDataSortedByPrice.txt");
		goto x;
	}
	else if (a == 4) {
		sortandsavebymileage("UsedCarDataSortedByMileage.txt");
		goto x;
	}
	else if (a == 5) {
		sortandsavebytax("UsedCarDataSortedByTax.txt");
		goto x;
	}
	else if (a == 6) {
		sortandsavebympg("UsedCarDataSortedByMpg.txt");
		goto x;
	}
	else if (a == 7) {
		sortandsavebyenginesize("UsedCarDataSortedByEngineSize.txt");
		goto x;
	}
	else if (a == 8) {
		printf("Write brand name(max 10 character)\n");
		scanf("%s", y.brand);
		printf("Write model name(max 10 character)\n");
		scanf("%s", y.model);
		printf("Write year\n");
		scanf("%d", &(y.year));
		printf("Write price\n");
		scanf("%d", &(y.price));
		printf("Write transmission name(max 10 character)\n");
		scanf("%s", y.transmission);
		printf("Write mileage\n");
		scanf("%d", &(y.mileage));
		printf("Write fuel type name(max 10 character)\n");
		scanf("%s", y.fueltype);
		printf("Write tax\n");
		scanf("%d", &(y.tax));
		printf("Write miles per gallon\n");
		scanf("%f", &(y.milespergallon));
		printf("Write engine size\n");
		scanf("%f", &(y.enginesize));
		addbyhand(y);
		goto x;
	}
	else if (a == 9) {
		printf("Write brand name(max 10 character)\n");
		scanf("%s", y.brand);
		printf("Write model name(max 10 character)\n");
		scanf("%s", y.model);
		printf("Write year\n");
		scanf("%d", &(y.year));
		printf("Write price\n");
		scanf("%d", &(y.price));
		printf("Write transmission name(max 10 character)\n");
		scanf("%s", y.transmission);
		printf("Write mileage\n");
		scanf("%d", &(y.mileage));
		printf("Write fuel type name(max 10 character)\n");
		scanf("%s", y.fueltype);
		printf("Write tax\n");
		scanf("%d", &(y.tax));
		printf("Write miles per gallon\n");
		scanf("%f", &(y.milespergallon));
		printf("Write engine size\n");
		scanf("%f", &(y.enginesize));
		deletebyhand(y);
		goto x;
	}
	else if (a == 10) {
		char model[10];
		char transmission[10];
		char fueltype[10];
		int yearmin, yearmax, pricemin, pricemax, mileagemin, mileagemax, taxmin, taxmax;
		float mpgmin, mpgmax, enginemin, enginemax;
		printf("Write file path(max 1000 character)\n");
		scanf("%s", m);
		printf("Write brand name(max 10 character)\n");
		scanf("%s", n);
		printf("Write model name(max 10 character)\n");
		scanf("%s", model);
		printf("Write min year, max year(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%d %d", &yearmin, &yearmax);
		printf("Write min price, max price(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%d %d", &pricemin, &pricemax);
		printf("Write transmission name(max 10 character)\n");
		scanf("%s", transmission);
		printf("Write min mileage, max mileage(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%d %d", &mileagemin, &mileagemax);
		printf("Write fuel type name(max 10 character)\n");
		scanf("%s", fueltype);
		printf("Write min tax, max tax(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%d %d", &taxmin, &taxmax);
		printf("Write min miles per gallon, max miles per gallon(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%f %f", &mpgmin, &mpgmax);
		printf("Write min engine size, max engine size(Leave a space between them. If you want to search for a single value, write same value for both.)\n");
		scanf("%f %f", &enginemin, &enginemax);
		searchandsave(m, n, model, transmission, fueltype, yearmin, yearmax, pricemin, pricemax, mileagemin, mileagemax, taxmin, taxmax, mpgmin, mpgmax, enginemin, enginemax);
		goto x;
	}
	else if (a == 11) {
		printf("Write file path(max 1000 character)\n");
		scanf("%s", m);
		printf("Write brand name(max 10 character)\n");
		scanf("%s", n);
		printf("How many times do you want the data to be read?\n");
		scanf("%d", &a);
		performancetest(m, n, a);
		goto x;
	}
	else {
		return 0;
	}
}