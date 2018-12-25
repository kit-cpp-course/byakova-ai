#include "stdafx.h"
#include "EncryptionDecryption.h"

Enc c;

void main()
{
	int i, j, x;
	unsigned Z[7][10], DK[7][10], XX[5], TT[5], YY[5];
	short unsigned uskey[9];

	for (i = 1;i <= 8;i++) uskey[i] = i;
	c.key(uskey, Z);	/* generate encryption subkeys Z[i][r] */

	printf("\nencryption keys\t  Z1\t  Z2\t  Z3\t  Z4\t  Z5\t  Z6");
	for (j = 1;j <= 9;j++) {
		printf("\n %3d-th round", j);
		if (j == 9) for (i = 1;i <= 4;i++) printf("\t%6d", Z[i][j]);
		else for (i = 1;i <= 6;i++) printf("\t%6d", Z[i][j]);
	}

	c.de_key(Z, DK);	/* compute decryption subkeys DK[i][r] */

	printf("\n\ndecryption keys\t  DK1\t  DK2\t  DK3\t  DK4\t  DK5\t  DK6");

	for (j = 1;j <= 9;j++) {
		printf("\n %3d-th round", j);
		if (j == 9) for (i = 1;i <= 4;i++) printf("\t%6d", DK[i][j]);
		else for (i = 1;i <= 6;i++) printf("\t%6d", DK[i][j]);
	}

	for (x = 1;x <= 4;x++) XX[x] = 5;
	printf("\n\n plaintext  X\t%6u\t%6u\t%6u\t%6u\n",
		XX[1], XX[2], XX[3], XX[4]);

	c.cip(XX, YY, Z);	/* encipher XX to YY with key Z */

	printf("\n\n ciphertext Y\t%6u\t%6u\t%6u\t%6u\n",
		YY[1], YY[2], YY[3], YY[4]);

	c.cip(YY, TT, DK);	/* decipher YY to TT with key DK */

	printf("\n\n result     T\t%6u\t%6u\t%6u\t%6u\n",
		TT[1], TT[2], TT[3], TT[4]);

	getchar();
}