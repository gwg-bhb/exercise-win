#include <openssl/sha.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	SHA_CTX ctx;
	char c;
	int ret, i, j, n = 2600, len;
	unsigned char in[2600], out[20] = {0}, *p = in;
    int  nu = 0;
	for (i = 0; i < 100; ++i)
	{
		c = i % 2?'a' : 'A';
		for (j = 0; j < 26; ++j)
		{
			in[i * 26 + j] = c++;
	//		printf("%c\t", in[i * 26 + j]);  //test
			nu++;
			/* code */
		}
//		printf("\n");
		/* code */
	}

	//printf("\n=====================\n nu = %d\n", nu);
	ret = SHA1_Init(&ctx);
	while(n > 0 && ret)
	{
		if(n > 256)
			len = 256;
		else
			len = n;

		ret = SHA1_Update( &ctx, p, len);
		 n -= 256;
		p += 256;
	
	}
	ret = SHA1_Final(out,  &ctx);

	for ( i = 0; i < 20; ++i)
		{
			printf("%02x\t", out[i] & 0xff);
			/* code */
		}
		printf("\n");
	return 0;
}