#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>


using namespace std;


void averageCalculation(ifstream& input, double& courseAvg);
void printResult(ofstream& output, string course, int groupNo, double average);


int main()
{

	string course1;
	string course2;
	int numberOfCourses = 0;

	double average1;
	double average2;
	double totalAvg1 = 0.0;
	double totalAvg2 = 0.0;

	ifstream group1;
	ifstream group2;
	ofstream outfile;


	group1.open("group1.txt");
	group2.open("group2.txt");

	if (!group1 || !group2)
	{
		cout << "Unable to open files." << endl;
		return 1;
	}


	outfile.open("student.out");

	outfile << fixed << showpoint;
	outfile << setprecision(2);



	outfile << "                                Bar Graph    " << endl;
	outfile << "   Course         Course " << "       0   10   20   30   40   50   60   70   80   90   100" << endl;
	outfile << "   ID             Average " << "      |....|....|....|....|....|....|....|....|....|....|" << endl;

	group1 >> course1;
	group2 >> course2;

	while (group1 && group2)
	{
		if (course1 != course2)
		{
			cout << " Error!" << endl;

			return 1;
		}
		else
		{
			averageCalculation(group1, average1);
			averageCalculation(group2, average2);

			printResult(outfile, course1, 1, average1);
			printResult(outfile, course2, 2, average2);

			totalAvg1 = totalAvg1 + average1;
			totalAvg2 = totalAvg2 + average2;

			outfile << endl;
			numberOfCourses++;
		}

		group1 >> course1;
		group2 >> course2;
	}

	if (group1 && !group2)
		cout << " Error; number of grades are not equal for two group." << endl;
	else
	{
		if (!group1 && group2)
			cout << "Error; number of grades are not equal for two group." << endl;
		else
		{
			outfile << "Group 1 -- **** " << endl;
			outfile << "Group 2 -- #### " << endl;
			outfile << "Avg for group 1: " << totalAvg1 / numberOfCourses << endl;
			outfile << "Avg for group 2: " << totalAvg2 / numberOfCourses << endl;
		}
	}
	group1.close();
	group2.close();
	outfile.close();

	return 0;
}

void averageCalculation(ifstream& input, double& courseAvg)

{
	double totalScore = 0.0;
	int numberOfStudent = 0;
	int grade;

	input >> grade;
	while (grade != -999)
	{
		totalScore = totalScore + grade;
		numberOfStudent++;
		input >> grade;
	}
	courseAvg = totalScore / numberOfStudent;
}


void printResult(ofstream& output, string course, int groupNo, double average)

{
	if (groupNo == 1)
		output << "   " << course << "            ";
	else
		output << "                  ";

	output << average;


	int numberOfSymbols = static_cast<int>(average) / 2;

	if (groupNo == 1)
	{
		output << "         ";
		for (int i = 1; i <= numberOfSymbols; i++)

			output << "*";
	}
	else
	{
		output << "         ";
		for (int i = 1; i <= numberOfSymbols; i++)

			output << "#";
	}
	output << endl;
}


