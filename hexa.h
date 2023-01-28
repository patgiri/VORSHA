
void conIntoHex(char *hash_bits, int n, char *hash_value)
{
    int i=0,j=0,count=0,k=3;
    int m=0;
    char hex[]="0123456789abcdef";
    int r=n%4;
    int p,t;
    r=n%4;
    p=r-1;
    t=n-r;
    for(i=0;i<t;i++)
    {
        m+=(1<<k)*hash_bits[i];    
        k--;
        count++;        
        if(count==4)
        {
            hash_value[j++]=hex[m];
            m=0;
            count=0;
            k=3;
        }
    }
    m=0;
    if(t!=n)
    {
	for(;i<n;i++)
	{
		m+=(1<<p)*hash_bits[i];    
        	p--;
	}
	hash_value[j++]=hex[m];
	printf("\nBit size is not multiple of 4!\nThe last hexadecimal code, %c, is not 4 bits!\nIt is %d bits!\n",hex[m],r);
    }
    hash_value[j]='\0';
}
