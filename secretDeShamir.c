/*secretDeShamir.c*/
#include "secretDeShamir.h"


int constrPolynom(s_poly* poly, const mpz_t secret)
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
	mpz_init(poly->factors[0]);
	mpz_set(poly->factors[0], secret);


	genPrimeGt(poly->mod, secret);


	//for each remaining elements of the array
	for(i = 1; i < poly->degree; i++)
	{
		//we read random data from /dev/urandom
		fread(&seed, 1, sizeof(unsigned long int), randomFic);
		//we initialize our seed
		mpz_set_ui(seedMpz, (unsigned long int)seed);
		//we initialise our random state
		gmp_randseed(state, seedMpz);
		
		//we fill our array with the random value
		mpz_init(poly->factors[i]);
		mpz_urandomb(poly->factors[i], state, 128);

	}
		
	//clearing memory
	close(randomFic);
	mpz_clear(seedMpz);
	return(0);
}

int resPolynom(mpz_t* results, const s_poly* poly, int nbAllPart)
{
	int i;
	int j;

	mpz_t buffer;
	mpz_init(buffer);


	//for each part to create (ie n)	
	for(i=0; i<nbAllPart; i++)
	{
		
		mpz_init(results[i]);
		mpz_set_ui(results[i], 0);
		
		//we resolve the polynom of degree (degree-1)(ie k)
		for(j=0; j < poly->degree; j++)
		{
			mpz_set_ui(buffer, 0);
			
			//we multiply the factor with x^j (x being just 1 to nbpart)
			mpz_mul_ui(buffer, poly->factors[j], (unsigned long int)(pow((double)(i+1), (double)j)));

			mpz_add(results[i], results[i], buffer);

		}

		mpz_mod(results[i], results[i], poly->mod);
	}	
	
	//clearing memory
	mpz_clear(buffer);
	
	return(0);
}

int interLagrange(mpz_t secret, const mpz_t* parts, int nbParts)
{
	//iterators
	int i, j;
	//buffers
	signed long int buff2;
	mpz_t buff1;

	mpz_init(buff1);

	mpz_set_ui(buff1, (unsigned long int)0);
	
	//calculates the reduced lagrange's polynom (to only get the constant part, i.e. the secret)
	for(i=0; i < nbParts; i++)
	{
		mpz_set_ui(buff1, 1);
		for(j=0; j<nbParts; j++)
		{
			if(i != j)
			{
				buff2 = (j+1) / (j-i);

				mpz_mul_si(buff1, buff1, buff2);
			}
		}
		mpz_mul(buff1, buff1, parts[i]);

		mpz_add(secret, secret, buff1);
	}


	mpz_clear(buff1);
	return(0);
}

int genPrimeGt(mpz_t prime, const mpz_t lowerLim)
{
	
	FILE* randFic = NULL;
	char* seed = NULL;
	mpz_t seedMpz;
	gmp_randstate_t state;

	gmp_randinit_default(state);
	mpz_init(seedMpz);
	mpz_init(prime);
	
	//open the /dev/urandom file
	randFic = fopen("/dev/urandom", "r");

	do
	{
		//reads 32bits from /dev/urandom
		fread(&seed, 1, sizeof(unsigned long int), randFic);
		
		mpz_set_ui(seedMpz, (unsigned long int)seed);

		gmp_randseed(state, seedMpz);

		mpz_urandomb(prime, state, 128);

		//add the lowerlimit to be sure to be above
		mpz_add(prime, prime, lowerLim);		
	//loop while the rabinMiller test fails
	}while(isPrime(prime) == 0);
	
	close(randFic);
	mpz_clear(seedMpz);

	return(0);
}
