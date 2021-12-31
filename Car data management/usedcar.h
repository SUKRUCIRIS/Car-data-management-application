#pragma once
typedef struct {
	char brand[10];
	char model[10];
	unsigned int year;
	unsigned int price;
	char transmission[10];
	unsigned int mileage;
	char fueltype[10];
	unsigned int tax;
	float milespergallon;
	float enginesize;
}araba;

void readbrandfile(char* brandfilepath, char* brand);//buldugum datasetler markalara gore ayrilmis oldugu icin bu sekilde bir fonksiyon yazdim

void writetofile(char* filepath);

void quicksort(araba* darray, unsigned int size, unsigned int type);//0 year, 1 price, 2 mileage, 3 tax, 4 mpg, 5 enginesize 

void quicksortbyyear();

void quicksortbyprice();

void quicksortbymileage();

void quicksortbytax();

void quicksortbympg();

void quicksortbyenginesize();

void sortandsavebyyear(char* filepath);

void sortandsavebyprice(char* filepath);

void sortandsavebymileage(char* filepath);

void sortandsavebytax(char* filepath);

void sortandsavebympg(char* filepath);

void sortandsavebyenginesize(char* filepath);

void addbyhand(araba x);

void deletebyhand(araba x);

void searchandsave(char* filepath, char* brand, char* model, char* transmission, char* fueltype, int yearmin, int yearmax, int pricemin, int pricemax, int mileagemin, int mileagemax, int taxmin, int taxmax, float mpgmin, float mpgmax, float enginemin, float enginemax);

void performancetest(char* brandfilepath, char* brand, int time);

int aynimi(char* m, char* n);