/*secretDeShamir.c*/
#include "secretDeShamir.h"


int constrPolynom(mpz_t* factors, int degree, const mpz_t secret)
{
	//we allocate an mpz_t array of size degree
	factors = malloc(sizeof(mpz_t) * degree);
	int i;
	char* seed;
	mpz_t seedMpz;
	gmp_randstate_t state;
	FILE* randomFic = NULL;
	
	gmp_randinit_default(state);
	mpz_init(seedMpz);
	randomFic = fopen("/dev/urandom", "r");

	//We put the secret in the first spot of the array (the secret being the constant of the resulting polynomial)
	mpz_init(factors[0]);
	mpz_set(factors[0], secret);

	//for each remaining elements of the array
	for(i = 1; i < degree; i++)
	{
		//we read random data from /dev/urandom
		fread(&seed, 1, sizeof(unsigned long int), randomFic);
		//we initialize our seed
		mpz_set_ui(seedMpz, (unsigned long int)seed);
		//we initialise our random state
		gmp_randseed(state, seedMpz);
		
		//we fill our array with the random value
		mpz_init(factors[i]);
		mpz_urandomb(factors[i], state, 32);
	}

	close(randomFic);
	mpz_clear(seedMpz);
	return(0);
}

int resPolynom(mpz_t* results, const mpz_t polynom, int nbPart)
{
	

	return(0);
}
