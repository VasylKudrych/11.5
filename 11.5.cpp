#include <iostream>
#include <string>
#include <stdio.h> 
#include <fstream>
using namespace std;

struct Warehouse
{
	int Year;
	int Month;
	int Day;
	int HowTime;
};
struct Producer
{
	string ProducerName;
	string Address;
};
struct Product
{
	Producer Producer;
	Warehouse Warehouse;
	string Name;
	int Price;
	int Size;

};
void showData(Product Obj[], int amount)
{

	cout << "№\t" << "Name\t" << "Price\t" << "Size\t" << "Producer name \t" << "Adress \t\t" << "Warehouse how time \t" << "DD \t" << "MM \t" << "YY \t" << "Third" << endl;
	cout << "==================================================================" << endl;
	for (int i = 0; i < amount; i++)
	{
		cout << i + 1 << '\t' << Obj[i].Name << '\t' << Obj[i].Price << '\t' << Obj[i].Size << '\t' << Obj[i].Producer.ProducerName << '\t' << Obj[i].Producer.Address << '\t' << Obj[i].Warehouse.HowTime << '\t' << Obj[i].Warehouse.Day << '\t' << Obj[i].Warehouse.Month << '\t' << Obj[i].Warehouse.Year << '\t'
			<< endl;
	}
}
void showDataSingle(Product Obj[], int i)
{

	cout << "№\t" << "Name\t" << "Price\t" << "Size\t" << "Producer name \t" << "Adress \t\t" << "Warehouse how time \t" << "DD \t" << "MM \t" << "YY \t" << "Third" << endl;
	cout << "==================================================================" << endl;
	cout << i + 1 << '\t' << Obj[i].Name << '\t' << Obj[i].Price << '\t' << Obj[i].Size << '\t' << Obj[i].Producer.ProducerName << '\t' << Obj[i].Producer.Address << '\t' << Obj[i].Warehouse.HowTime << '\t' << Obj[i].Warehouse.Day << '\t' << Obj[i].Warehouse.Month << '\t' << Obj[i].Warehouse.Year << '\t'
		<< endl;
}
int SearchProducer(Product Products[], int count, int sDate, string sName)
{
	int searchIndex = 0;
	for (int i = 0; i < count; i++)
	{
		if ((sDate == Products[i].Warehouse.HowTime) && (sName == Products[i].Name))
		{
			searchIndex = i;
		}
		else
		{
			searchIndex = -1;
		}
	}

	return searchIndex;

}
int SearchLongerArrival(Product Products[], int count)
{
	int searchIndex = 0;
	int max = Products[0].Warehouse.HowTime;
	for (int i = 0; i < count; ++i) {
		if (Products[i].Warehouse.HowTime > max) {
			max = Products[i].Warehouse.HowTime;
			searchIndex = i;
		}
	}
	return searchIndex;
}
int SearchBiggestSize(Product Products[], int count)
{
	int searchIndex = 0;
	int max = Products[0].Size;
	for (int i = 0; i < count; ++i) {
		if (Products[i].Size > max) {
			max = Products[i].Size;
			searchIndex = i;
		}
	}

	return searchIndex;
}
void Write(Product arr[], int count)
{
	ofstream file("file.dat", ios::binary | ios::in);
	for (int i = 0; i < count; i++)
	{
		file.write((char*)&arr[i], sizeof arr[i]);

	}
	file.close();
}

void Read()
{
	ifstream rf("file.dat", ios::out | ios::binary);
	if (!rf) {
		cout << "Cannot open file!" << endl;
	}
	const int count = 5;
	Product Products[count] = {};
	for (int i = 0; i < count; i++)
		rf.read((char*)&Products[i], sizeof(Product));
	rf.close();
	if (!rf.good()) {
		cout << "Error occurred at reading time!" << endl;
	}
	cout << "Read" << endl;
	showData(Products, count);

}

int main()
{
	const int count = 5;
	Product Products[count] = {};
	for (int i = 0; i < count; i++)
	{
		cout << "Input product Name :" << endl;
		cin >> Products[i].Name;
		cout << "Input product Size :" << endl;
		cin >> Products[i].Size;
		cout << "Input product Price :" << endl;
		cin >> Products[i].Price;
		cout << "Input Producer Name :" << endl;
		cin >> Products[i].Producer.ProducerName;
		cout << "Input Producer Address :" << endl;
		cin >> Products[i].Producer.Address;
		cout << "Input Warehouse expiration date of day :" << endl;
		cin >> Products[i].Warehouse.HowTime;
		cout << "Input Warehouse day of arrival :" << endl;
		cin >> Products[i].Warehouse.Day;
		cout << "Month of arrival :" << endl;
		cin >> Products[i].Warehouse.Month;
		cout << "Year of arrival :" << endl;
		cin >> Products[i].Warehouse.Year;
	}
	int sDate;
	string sName;
	int longArr;
	int biggSize;
	int searchIndex;
	int ch;
	do {
		cout << "Menu : " << endl;
		cout << "1 - Show data \t 2 - Search producer \t 3 - search longer arrival \t 4 - Search biggest size \t 5 - Read document and show him \t  6 - Write in document " << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "Show data" << endl;
			showData(Products, count);
			break;
		case 2:
			cout << "Search producer" << endl;
			cout << "Input date" << endl;
			cin >> sDate;
			cout << "Input name" << endl;
			cin >> sName;
			searchIndex = SearchProducer(Products, count, sDate, sName);
			if (searchIndex >= 0)
			{
				showDataSingle(Products, searchIndex);
			}
			else
				cout << "Not found" << endl;
			break;
		case 3:
			cout << "Search Longer Arrival" << endl;
			longArr = SearchLongerArrival(Products, count);
			showDataSingle(Products, longArr);
			break;
		case 4:
			cout << "Search Biggest Size" << endl;

			biggSize = SearchBiggestSize(Products, count);
			showDataSingle(Products, biggSize);
			break;
		case 5:
			cout << "Read successful" << endl;
			Read();
			break;
		case 6:
			cout << "Write successful" << endl;
			Write(Products, count);
			break;
		default:
			break;
		}
	} while (ch != 0);
	return 0;
}
