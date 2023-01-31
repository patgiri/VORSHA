#include <stdio.h>
#include <math.h>
#include "murmur.h"
#include "constants.h"
#include "hexa.h"
#include "prime.h"


//Computing secret seed value from publicly visible seed value.
unsigned int getSeedValue(char *key, int l, unsigned int seed)
{	
	int i;
	for(i=0;i<32;i++)
		seed=(unsigned int)murmur2(key,l,seed);	
	return seed;
}

int getDim(unsigned int seed)
{
	unsigned int t=seed%prime[100];//9791; //9781
	unsigned int dim;
	dim=sqrt(t);//+cbrt(bit_size);
	dim=(dim<16)?(dim+16):dim;
	return dim;
}

/*
key: It is a secret key
seed: The first seed value is a public constant, and the consequent seed values become secret key.
bit_size: It is also a public constant
hash_value: Array to be output in hexadecimal format.

*/

void genHash(char *key, unsigned int seed, int bit_size, char *hash_value)
{
	int s,t,r,c,w,X,Y,Z;
	int i=0,j=0,k=0,l=0,p=0,counter=0;
	int pos,bit;
	char *hash_bits=(char *)malloc(bit_size*sizeof(char)+1);

	for(l=0;key[l]!='\0';l++);
	
	seed=(unsigned int)getSeedValue(key,l,seed);
	seed=tab[seed%2293];
	seed=getSeedValue(key,l,seed);
	r=getDim(seed);
	while(1)
	{
		seed=(unsigned int)getSeedValue(key,l,seed);
		c=getDim(seed)+5;
		if(r!=c)
			break;
	}	
	
	while(1)
	{
		seed=(unsigned int)getSeedValue(key,l,seed);
		w=getDim(seed)+7;
		if((w!=r)&&(w!=c))
			break;
	}	

	X=prime[r];  //X!=Y!=Z
	Y=prime[c+5];
	Z=prime[w+7];
	printf("Vector dimensions are X:%d  Y:%d  Z:%d\n",X,Y,Z);

	unsigned char ***vector=(unsigned char ***)malloc(X*sizeof(unsigned char **));
	unsigned int hv; 					//Hash value
	if(vector==NULL)
	{
		printf("Unable to allocate!\n");
		return;
	}
	for(i=0;i<X;i++)
	{
		vector[i]=(unsigned char **)malloc(Y*sizeof(unsigned char *));
		if(vector==NULL)
		{
			printf("Unable to allocate!\n");
			return;
		}
		for(j=0;j<Y;j++)
		{
			vector[i][j]=(unsigned char *)malloc(Z*sizeof(unsigned char));
			if(vector==NULL)
			{
				printf("Unable to allocate!\n");
				return;
			}
		}
	}
	seed=seed+bit_size;
	//Filling the vector with 0s and 1s.
	for(i=0;i<X;i++)
	{
		for(j=0;j<Y;j++)
		{
			for(k=0;k<Z;k++)
			{
				seed=(unsigned int)getSeedValue(key,l,seed); //hash function calls for seed value.
				hv=(unsigned int)murmur2(key,l,seed); // hash function calls for a single bit value.
				pos=hv%31;
				bit=(hv&(1<<pos))>>pos;
				vector[i][j][k]=bit;
				seed=hv;  
			}
		}
	}
	
	for(p=0;p<bit_size;p++)
	{
		seed=(unsigned int)getSeedValue(key,l,seed);
		hv=(unsigned int)murmur2(key,l,seed);
		i=hv%X;
		seed=hv;
		seed=(unsigned int)getSeedValue(key,l,seed);
		hv=(unsigned int)murmur2(key,l,seed);
		j=hv%Y;
		seed=hv;
		seed=(unsigned int)getSeedValue(key,l,seed);
		hv=(unsigned int)murmur2(key,l,seed);
		k=hv%Z;
		seed=hv;
		
		hash_bits[p]=vector[i][j][k];
	}	
	conIntoHex(hash_bits,bit_size,hash_value);
}

int main()
{
	char key[1024]="7mPis5soans@91uex.c";
	unsigned int seed=198899;
	int bit_size=256;
	char *hash_value=(char *)malloc((bit_size/4+2)*sizeof(char)+1);
	genHash(key,seed,bit_size,hash_value);
	printf("\nThe generated hash value is:\n%s\n",hash_value);
	printf("\nSuccefully completed...\n");
	return 0;
}


