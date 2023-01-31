#include <stdio.h>
#include <time.h>
#include <math.h>
#include "murmur.h"
#include "constants.h"
#include "hexa.h"
#include "prime.h"

unsigned int getSeedValue(char *key, int l, unsigned int seed)
{	
	int i;
	for(i=0;i<32;i++)
		seed=(unsigned int)murmur2(key,l,seed);	
	return seed;
}

void genHash(char *key, unsigned int seed, int bit_size, char *hash_value)
{
	
	int i=0,j=0,k=0,l=0,counter=0;
	int pos,bit;
	char *hash_bits=(char *)malloc(bit_size*sizeof(char)+1);
	for(l=0;key[l]!='\0';l++);
	seed=getSeedValue(key,l,seed);
	seed=tab[seed%2293];
	seed=getSeedValue(key,l,seed);
	seed=seed+bit_size;	
	
	for(i=0;i<bit_size;i++)
	{
		seed=murmur2(key,l,seed); // hash function calls for bit value.		
		pos=seed%31;
		bit=(seed & (1<<pos))>>pos;
		hash_bits[i]=bit;
		seed=murmur2(key,l,seed);  //hash function calls for seed value.	
	}	
	conIntoHex(hash_bits,bit_size,hash_value); 	
}

int main()
{
	char key[1024]="VORSHA";
	unsigned int seed=198899;
	int bit_size=512;
	char *hash_value=(char *)malloc((bit_size/4+2)*sizeof(char)+1);
	genHash(key,seed,bit_size,hash_value);
	printf("\nThe generated hash value is:\n%s\n",hash_value);
	printf("\nSuccefully completed...\n");
	return 0;
}


