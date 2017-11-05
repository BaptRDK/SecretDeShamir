#ifndef SECRETDESHAMIR
#define SECRETDESHAMIR
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include "RabinMiller/rabinMiller.h"

typedef struct polynom s_poly;

struct polynom
{
	mpz_t* factors;
	mpz_t mod;
	int degree;
};

/*Constructs a polynom with the secret as the constant and random number as the others factors*/
//OUT:
//	s_poly poly	: resulting polynom
//IN:
//	secret		: secret to share
int constrPolynom(s_poly* poly, const mpz_t secret);

/*Resolve the polynom for nbParts point betwen ]0; nbparts]*/
//OUT:
//	results		: resulting points
//IN:
//	poly		: polynom
//	nbpart		: number of parts to share
int resPolynom(mpz_t* results, const s_poly* poly, int nbPart);

/*Realises a Lagrange interpolation, returning the constant from the resulting polynom*/
//OUT:
//	secret		: constant of the polynom, the shared secret
//IN:
//	parts		: points from the polynom, parts of the secret
//	nbParts		: number of parts
int interLagrange(mpz_t secret, const mpz_t* parts, int nbPart);

/*generates a random prime number greater than lowerLim*/
//OUT:
//	prime		: resultaing prime number
//IN:
//	lowerLimit	: lower limit to the prime number
int genPrimeGt(mpz_t prime, const mpz_t lowerLim);
#endif
