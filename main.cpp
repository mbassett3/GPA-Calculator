#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void input(int & classCount, vector<string> & classNames, vector<int> & classLevels,vector<double> & classCredits, vector<double> & classGrades);
double calculate(int classCount, vector<double>& classCredits, vector<double> & classGrades, vector<int> & classLevels, vector<double> & gpas);
void findLevels(vector<string> & levels, int classCount, vector<int> & classLevels);
void output(int classCount, double average, vector<string> & classNames, vector<double>& classCredits, vector<double> & classGrades, vector<string> & levels);

struct gradeScale {
	int numericalGrade;
	double regularGpa;
	double honorsGpa;
	double apGpa;
};

vector<gradeScale> scale = {
//  num, reg, honors, ap
	{97, 4.40, 4.65, 4.90},
	{93, 4.00, 4.25, 4.50},
	{90, 3.60, 3.85, 4.10},
	{87, 3.40, 3.65, 3.90},
	{83, 3.00, 3.25, 3.50},
	{80, 2.60, 2.85, 3.10},
	{77, 2.40, 2.65, 2.90},
	{73, 2.00, 2.25, 2.50},
	{70, 1.60, 1.85, 2.10},
	{67, 1.40, 1.65, 1.90},
	{63, 1.00, 1.25, 1.50},
	{60, 0.60, 0.85, 1.10},
};

int main()
{
	vector <int> classLevels;
	vector <double> classCredits, classGrades, gpas;
	vector <string> classNames, levels;
	int classCount = 0;
	double average;

	input(classCount, classNames, classLevels, classCredits, classGrades);
	average = calculate(classCount, classCredits, classGrades, classLevels, gpas);
	findLevels(levels, classCount, classLevels);
	output(classCount, average, classNames, classCredits, classGrades, levels);
}


void input(int & classCount, vector<string>& classNames, vector<int>& classLevels, vector<double>& classCredits, vector<double>& classGrades) {
	// Basic outputs
	cout << setw(10);
	cout << "How many classses: ";
	cin >> classCount;
	cout << endl << "---------------------" << endl << endl;
	cout << "Class levels-" << endl;
	cout << "Regular - 1, Honors - 2, AP - 3" << endl;

	// Prompts
	for (int x = 0; x < classCount; x++) {
		// Class Names
		string className;
		cout << "Name of class #" << x + 1 << ": ";
		cin >> className;
		classNames.push_back(className);

		// Class Levels
		int classLevel;
		cout << "Class level: ";
		cin >> classLevel;
		// Error Trap
		if (classLevel != 1 && classLevel != 2 && classLevel != 3) {
			do {
				cout << "ERROR - Class Level must be between 1 - 3. Try again- ";
				cin >> classLevel;
			} while (classLevel != 1 && classLevel != 2 && classLevel != 3);
		}
		classLevels.push_back(classLevel);

		// Class credits
		double classCredit;
		cout << "Class credits: ";
		cin >> classCredit;
		classCredits.push_back(classCredit);

		// Class Grades
		double classGrade;
		cout << "Grade in " << classNames[x] << ": ";
		cin >> classGrade;
		// Error Trap
		if (classGrade < 0 || classGrade > 100) {
			do {
				cout << "ERROR - Class grade must be between 0 - 100. Try again- ";
				cin >> classGrade;
			} while (classGrade < 0 || classGrade > 100);
		}
		classGrades.push_back(classGrade);
		cout << endl;
	}
}

double calculate(int classCount, vector<double>& classCredits, vector<double>& classGrades, vector<int>& classLevels, vector<double>& gpas) {
	double average = 0;

	for (int x = 0; x < classCount; x++) {
		int index = 0;
		double diff = abs(scale[0].numericalGrade - classGrades[x]);
		for (int i = 1; i < scale.size(); i++) {
			double newDiff = abs(scale[i].numericalGrade - classGrades[x]);
			if (newDiff < diff) {
				index = i;
				diff = newDiff;
			}
		}
		switch (classLevels[x]) {
		case 1:
			gpas.push_back(scale[index].regularGpa);
			break;
		case 2:
			gpas.push_back(scale[index].honorsGpa);
			break;
		case 3:
			gpas.push_back(scale[index].apGpa);
			break;
		}
	}

	double totalCredits = 0;
	for (int x = 0; x < classCount; x++) {
		average += (gpas[x] * (classCredits[x] / 5));
		totalCredits += classCredits[x];
	}
	average /= (totalCredits / 5);
	return average;
}

void findLevels(vector<string>& levels, int classCount, vector<int>& classLevels) {
	for (int x = 0; x < classCount; x++) {
		switch (classLevels[x]) {
		case 1:
			levels.push_back("Regular");
			break;
		case 2:
			levels.push_back("Honors");
			break;
		case 3:
			levels.push_back("AP");
			break;
		}
	}
}

void output(int classCount, double average, vector<string>& classNames, vector<double>& classCredits, vector<double>& classGrades, vector<string>& levels) {
	cout << endl << "------------------TRANSCRIPT------------------" << endl << endl;
	cout << setw(15) << "Class name" << setw(15) << "Class Level" << setw(15) << "Class Credits" << setw(15) << "Class Grade" << endl;
	cout << endl;
	cout << fixed << showpoint << setprecision(2);
	for (int x = 0; x < classCount; x++) {
		cout << x + 1 << "." << setw(13) << classNames[x] << setw(13) << levels[x] << setw(13) << classCredits[x] << setw(13) << classGrades[x] << endl;
	}
	cout << fixed << showpoint << setprecision(2) << setw(25);
	cout << endl << "GPA: " << average << endl << endl;
}