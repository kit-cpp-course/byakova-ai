#include "stdafx.h"
#include "EncryptionDecryption.h"
#include "Keys.h"
#include "Arg.h"
#include <iostream>
using namespace std;

Enc c; Display d;

int main(int argc, char **argv)
{
	FILE *input, *output;
	Arg a(argc, argv);
	if (a.error) {
		printf("Choose: <e|d> <key> <input file> <output file>\n", argv[0]);
		return 1;
	}
	input = fopen(a.input.c_str(), "r");
	output = fopen(a.output.c_str(), "w");

	int i, x;
	unsigned Z[7][10], DK[7][10], XX[5], TT[5], YY[5];
	short unsigned uskey[9];

	for (i = 1;i <= 8;i++) uskey[i] = i;
	c.key(uskey, Z);	/* generate encryption subkeys Z[i][r] */
	d.enKey();
	c.de_key(Z, DK);	/* compute decryption subkeys DK[i][r] */
	d.deKey();
	for (x = 1;x <= 4;x++) XX[x] = x;
	printf("\n\n plaintext  X\t%6u\t%6u\t%6u\t%6u\n",
		XX[1], XX[2], XX[3], XX[4]);

	switch (a.g)
	{
	case 1: c.cip(XX, YY, Z); break; /* encipher XX to YY with key Z */
	case 0:  c.cip(XX, YY, DK); break; /* decipher XX to YY with key DK */
	default:
		cout << "Error";
		break;
	}

	FILE * fp = fopen("file.txt", "w");
	fwrite(YY, 2, sizeof(YY), fp); 
	fclose(fp);
}