#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>

using namespace std;
#define PI 3.1415926

int changelabel(string labin, string labout,string type, double changeh,double changew,double changel,double changex,double changey,double changez,double changery)
{
	double lab[20];
	ifstream in(labin);
	ofstream out(labout);
	string line;
	int space=0;//Adjust space format
	while (getline(in, line))
	{
		space++;
		if (space != 1)
		{
			out << endl;
		}
		stringstream ss(line);
		double token;
		string labeltype;
		ss >> labeltype;
		int number = 2;
		while (ss >> token)
		{
			lab[number] = token;
			number++;
		}
		out << labeltype;
		if (type == "symmetry"&& labeltype!="DontCare")
		{
			//lab[12] = -lab[12];
			lab[15] = fmod(PI- lab[15], 2 * PI);
		}
		if (type == "translation"&& labeltype != "DontCare")
		{
			//lab[12] = lab[12] + changex;
			//lab[13] = lab[13] + changey;
			//lab[14] = lab[14] + changez;
		}
		if (type == "scale"&& labeltype != "DontCare")
		{
			lab[9] = lab[9] * changeh;
			lab[10] = lab[10] * changew;
			lab[11] = lab[11] * changel;
			//lab[12] = lab[12] * changex;
			//lab[13] = lab[13] * changey;
			//lab[14] = lab[14] * changez;
		}
		if (type == "rotation"&& labeltype != "DontCare")
		{
			double xc = lab[12];
			double yc = lab[13];
			double zc = lab[14];
			lab[15] = fmod(lab[15] + changery, 2 * PI);
		}
		for (int i = 2; i <= 15; i++)
		{
			out <<" "<< lab[i];
		}
	}
	in.close();
	out.close();
	return 0;
}