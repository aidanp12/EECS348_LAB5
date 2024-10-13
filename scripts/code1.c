/* Author: Aidan P
 * Lab: Lab5
 * Purpose: Read sale data from a file then perform operations according to requirements
 * Created: 10/11/24
 * Last Edited: 10/13/24
 */

#include <stdio.h>

#define NUM_MONTHS 12

// Initialize functions
float MaxValue(float numArray[]);
float MinValue(float numArray[]);
void sixMonthAverage(float salesData[]);
void printMonth(float monthlySale, float salesData[]);
float averageValue(float numArray[]);
void sort(float salesData[], float rawSalesData[]);
//Set up array of months for future ease of printing
const char *MONTHS[] = {"January", "Februray", "March", "April", "May", "June", "July", "August", "September", "OCtober", "November", "December"};

int main()
{
	FILE *file;
	float saleData;
	int count = 0;
	float monthData[NUM_MONTHS];

	file = fopen("sales_data.txt","r");
	if (file == NULL)
	{
		printf("Error opening file.\n");
		return 1;
	}

	printf("\nMonthly Sales Report\n\n");
	while(fscanf(file, "%f", &saleData) == 1)
	{
		printf("%s: %f\n", MONTHS[count], saleData);
		monthData[count++] = saleData;
	}
	fclose(file);
	// Find values for sales summary
	float maxMonth = MaxValue(monthData);
	float minMonth = MinValue(monthData);

	// Print summary data
	printf("\nSales Summary\n\n");
	printf("Max: %f (", maxMonth);
	printMonth(maxMonth, monthData);
	printf(")\nMin: %f (", minMonth);
	printMonth(minMonth, monthData);
	printf(")\nAverage: %f\n",averageValue(monthData));

	// Print six month moving average
	printf("\nSix Month Moving Average Report\n\n");
	sixMonthAverage(monthData);

	// Sort the sales data
	float sortedSales[NUM_MONTHS];
	for (int i = 0; i < NUM_MONTHS; i++) {sortedSales[i] = monthData[i];}
	printf("\nSales Report (Highest to Lowest)\n\n");
	sort(sortedSales, monthData);
}

float MinValue(float numArray[])
{	
	// Simple algorithm to find the min number out of the data set
	float minNumber = numArray[0];
	for (int i = 0; i < NUM_MONTHS; i++)
	{
		if (numArray[i] < minNumber)
		{
			minNumber = numArray[i];
		}
	}

	return minNumber;
}

float MaxValue(float numArray[])
{
	// Much alike the min value function, but inverse
	float maxNumber = numArray[0];
	for (int i = 0; i < NUM_MONTHS; i++)
	{
		if (numArray[i] > maxNumber)
		{
			maxNumber = numArray[i];
		}
	}
	return maxNumber;
}

float averageValue(float numArray[])
{
	// Add all of the sales data together take average
	float arraySum;
	for (int i = 0; i < NUM_MONTHS; i++)
	{
		arraySum += numArray[i];
	}
	return (arraySum/NUM_MONTHS);
}

void printMonth(float monthlySale, float salesData[])
{
	// Find the associated month to given input value out of original sales data array
	for (int i = 0; i < NUM_MONTHS; i++)
	{
		if (monthlySale == salesData[i])
		{
			printf("%s", MONTHS[i]);
		}
	}
}	

void sixMonthAverage(float salesData[])
{
	float monthSums;
	// Find the average for each 6-month period available in a year
	for (int i = 0; i + 6 < NUM_MONTHS; i++)
	{
		for (int j = i; j < i + 6; j++)
		{
			monthSums += salesData[j];
		}
		printf("%s-%s: %f\n", MONTHS[i], MONTHS[i+6], monthSums/6);
		monthSums = 0;
	}
}


void sort(float salesData[], float rawSalesData[])
{
	// A simple bubble sort algorithm to sort a copy of the month sale data
	int preSorted = 1;
	for (int position = 0; position < NUM_MONTHS - 1; position++)
	{
		for (int current = 0; current < NUM_MONTHS - position - 1; current++)
		{
			int nextValue = current + 1;
			float tempData;
			if (salesData[current] > salesData[nextValue])
			{
				tempData = salesData[nextValue];
				salesData[nextValue] = salesData[current];
				salesData[current] = tempData;
				preSorted = 0;
			}
		}
		// Checks if the number was already in place
		if (preSorted != 0)
		{
			break;
		}
	}
	// Print out sorted sales data
	for (int i = 0; i < NUM_MONTHS; i++)
	{
		// Print high - low by subtracting i from the length of the data array
		printMonth(salesData[NUM_MONTHS - i - 1], rawSalesData);
		printf(": %f\n", salesData[NUM_MONTHS - i - 1]);
	}
}
