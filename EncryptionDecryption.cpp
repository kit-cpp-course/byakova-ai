#include "EncryptionDecryption.h"

void Enc::cip(unsigned IN[5], unsigned OUT[5], unsigned Z[7][10]) 
{
	unsigned r, x1, x2, x3, x4, kk, t1, t2, a;
	x1 = IN[1]; x2 = IN[2]; x3 = IN[3]; x4 = IN[4];
	for (r = 1;r <= 8;r++) 			
	{
		/* the group operation on 64-bits block */
		x1 = mul(x1, Z[1][r]);		x4 = mul(x4, Z[4][r]);
		x2 = (x2 + Z[2][r]) & one;	x3 = (x3 + Z[3][r]) & one;
		
		kk = mul(Z[5][r], (x1^x3));
		t1 = mul(Z[6][r], (kk + (x2^x4)) & one);
		t2 = (kk + t1) & one;
		
		x1 = x1 ^ t1;		x4 = x4 ^ t2;
		a = x2 ^ t2;		x2 = x3 ^ t1;	x3 = a;

		printf("\n\t%1u-th rnd %6u\t%6u\t%6u\t%6u", r, x1, x2, x3, x4);
	}

	/* the output transformation */
	OUT[1] = mul(x1, Z[1][round + 1]);
	OUT[4] = mul(x4, Z[4][round + 1]);
	OUT[2] = (x3 + Z[2][round + 1]) & one;
	OUT[3] = (x2 + Z[3][round + 1]) & one;
}

unsigned Enc::mul(unsigned a, unsigned b)
{
	long int p;
	long unsigned q;
	if (a == 0) p = maxim - b;
	else
		if (b == 0) p = maxim - a;
		else {
			q = (unsigned long)a*(unsigned long)b;
			p = (q & one) - (q >> 16);
			if (p <= 0) p = p + maxim;
		}
	return (unsigned)(p&one);
}

unsigned Enc::inv(unsigned xin)
{
	long n1, n2, q, r, b1, b2, t;
	if (xin == 0) b2 = 0;
	else
	{
		n1 = maxim; n2 = xin; b2 = 1; b1 = 0;
		do {
			r = (n1 % n2); q = (n1 - r) / n2;
			if (r == 0) { if (b2 < 0) b2 = maxim + b2; }
			else { n1 = n2; n2 = r; t = b2; b2 = b1 - q * b2; b1 = t; }
		} while (r != 0);
	}
	return (unsigned)b2;
}

void Enc::key(short unsigned uskey[9], unsigned Z[7][10])
{
	short unsigned S[54];
	int i, j, r;
	for (i = 1;i < 9;i++) S[i - 1] = uskey[i];
	/* shifts */
	for (i = 8;i < 54;i++)
	{
		if ((i + 2) % 8 == 0)			
			S[i] = ((S[i - 7] << 9) ^ (S[i - 14] >> 7)) & one;
		else if ((i + 1) % 8 == 0)			
			S[i] = ((S[i - 15] << 9) ^ (S[i - 14] >> 7)) & one;
		else
			S[i] = ((S[i - 7] << 9) ^ (S[i - 6] >> 7)) & one;
	}

	/* get subkeys */

	for (r = 1;r <= round + 1;r++)
		for (j = 1;j < 7;j++)
			Z[j][r] = S[6 * (r - 1) + j - 1];
}

void Enc::de_key(unsigned Z[7][10], unsigned DK[7][10])
{
	int j;
	for (j = 1;j <= round + 1;j++)
	{
		DK[1][round - j + 2] = inv(Z[1][j]);
		DK[4][round - j + 2] = inv(Z[4][j]);

		if (j == 1 || j == round + 1) {
			DK[2][round - j + 2] = (fuyi - Z[2][j]) & one;
			DK[3][round - j + 2] = (fuyi - Z[3][j]) & one;
		}
		else {
			DK[2][round - j + 2] = (fuyi - Z[3][j]) & one;
			DK[3][round - j + 2] = (fuyi - Z[2][j]) & one;
		}
	}

	for (j = 1;j <= round + 1;j++)
	{
		DK[5][round + 1 - j] = Z[5][j];
		DK[6][round + 1 - j] = Z[6][j];
	}

}