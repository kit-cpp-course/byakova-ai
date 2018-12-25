#pragma once
#include "stdafx.h"

class Enc
{
public:

	/* encrypt algorithm */
	void cip(unsigned IN[5], unsigned OUT[5], unsigned Z[7][10]);

	/* multiplication using the Low-High algorithm */
	unsigned mul(unsigned a, unsigned b);

	/* compute inverse of xin by Euclidean gcd alg. */
	unsigned inv(unsigned xin);

	/* generate encryption subkeys Z's */
	void key(short unsigned uskey[9], unsigned Z[7][10]);

	/* compute decryption subkeys DK's */
	void de_key(unsigned Z[7][10], unsigned DK[7][10]);

};