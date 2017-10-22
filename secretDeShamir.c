/*secretDeShamir.c*/
#include "secretDeShamir.h"


int constrPolynom(mpz_t* factors, int degree, const mpz_t secret)
{
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
	
	//clearing memory
	close(randomFic);
	mpz_clear(seedMpz);
	return(0);
}

int resPolynom(mpz_t* results, const mpz_t* polynom, int degree, int nbPart)
{
	int i;
	int j;

	mpz_t buffer;
	mpz_init(buffer);
	
	//for each part to create (ie n)	
	for(i=0; i<nbPart; i++)
	{
		
		mpz_init(results[i]);
		mpz_set_ui(results[i], 0);
		
		//we resolve the polynom of degree (degree-1)(ie k)
		for(j=0; j < degree; j++)
		{
			mpz_set_ui(buffer, 0);
			
			//we multiply the factor with x^j (x being just 1 to nbpart)
			mpz_mul_ui(buffer, polynom[j], (unsigned long int)(pow((double)(i+1), (double)j)));

			mpz_add(results[i], results[i], buffer);
		}

	}	
	
	//clearing memory
	mpz_clear(buffer);
	
	return(0);
}
