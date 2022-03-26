#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>

using namespace std;
#define PI 3.1415926

int changecalib(string labin, string labout, string type, double changeh, double changew, double changel, double changex, double changey, double changez, double changery)
{
	double lib[4][4];
	double result[15];
	double changematrix[4][4];
	double matrixresult[4][4];
	for (int i = 0; i < 4; i++)
		for(int j= 0; j< 4; j++)
	    {
			if (i == j)
				changematrix[i][j] = 1;
			else
				changematrix[i][j] = 0;
	    }
	ifstream in(labin);
	ofstream out(labout);
	string line;
	int space = 0;//Adjust space format
	while (getline(in, line))
	{
		space++;
		if (space != 1)
		{
			out << endl;
		}
		stringstream ss(line);
		double token;
		string calibtype;
		ss >> calibtype;
		out << calibtype;
		if (calibtype == "Tr_velo_to_cam:")
		{
			for(int k=0; k<3; k++)
				for (int j = 0; j < 4; j++)
				{
					ss >> token;
					lib[k][j] = token;
				}
			lib[3][0] = lib[3][1]=lib[3][2]=0;
			lib[3][3] = 1;
			if (type == "symmetry")
			{
				changematrix[1][1] = -1;
			}
			if (type == "translation")
			{
				changematrix[0][3] = -changex;
				changematrix[1][3] = -changey;
			}
			if (type == "scale")
			{
				changematrix[0][0] = (1.0 / changex);
				changematrix[1][1] = (1.0 / changey);
				changematrix[2][2] = (1.0 / changez);
			}
			if (type == "rotation")
			{
				changematrix[0][0] = cos(-changery);
				changematrix[0][1] = sin(-changery);
				changematrix[1][0] = -sin(-changery);
				changematrix[1][1] = cos(-changery);
			}
			for (int m = 0; m < 4; m++) {
				for (int s = 0; s < 4; s++) {
					matrixresult[m][s] = 0;
					for (int n = 0; n < 4; n++) {
						matrixresult[m][s] += lib[m][n] * changematrix[n][s];
					}
				}
			}
			int number = 0;
			for(int i=0; i<3; i++)
				for (int k = 0; k < 4; k++)
				{
					number++;
					result[number] = matrixresult[i][k];
				}
			for (int i = 1; i <= 12; i++)
			{
				out << " " << result[i];
			}
		}
		else
		{
			while (ss >> token)
			{
				out <<" "<< token;
			}
		}
	}
	in.close();
	out.close();
	return 0;
}