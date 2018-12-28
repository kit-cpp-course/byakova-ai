#include "Keys.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std; 

extern unsigned Z[7][10], DK[7][10], YY[5];

void Display::enKey()
{
	std::ofstream out;
	out.open("en_keys.txt");
	if (out.is_open())
	{
		out<<("\nencryption keys\t  Z1\t  Z2\t  Z3\t  Z4\t  Z5\t  Z6");
		for (int j = 1;j <= 9;j++) {
			out<<("\n %3d-th round", j);
			if (j == 9) for (int i = 1;i <= 4;i++) out<<("\t%6d", Z[i][j]);
			else for (int i = 1;i <= 6;i++) out<<("\t%6d", Z[i][j]);
		}
	}
}

void Display::deKey()
{
	std::ofstream out;
	out.open("de_keys.txt");
	if (out.is_open())
	{
		out<<("\n\ndecryption keys\t  DK1\t  DK2\t  DK3\t  DK4\t  DK5\t  DK6");
		for (int j = 1;j <= 9;j++) {
			out<<("\n %3d-th round", j);
			if (j == 9) for (int i = 1;i <= 4;i++) out<<("\t%6d", DK[i][j]);
			else for (int i = 1;i <= 6;i++) out<<("\t%6d", DK[i][j]);
		}
	}
}

