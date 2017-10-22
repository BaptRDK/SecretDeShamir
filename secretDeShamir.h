#ifndef SECRETDESHAMIR
#define SECRETDESHAMIR
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gmp.h>

int constrPolynom(mpz_t* factors, int degree, const mpz_t secret);

int resPolynom(mpz_t* results, const mpz_t* polynom, int degree, int nbPart);
#endif
