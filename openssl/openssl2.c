#include <stdio.h>
#include <openssl/evp.h>

int main(void)
{
	int i, len, total = 0;
	EVP_ENCODE_CTX ctx;
	unsigned char f[60];
	unsigned char t[81];
	for(i = 0; i< 60; i++)
	{
		memset(&f[i], i, 1);
	}
	EVP_EncodeInit(&ctx);
	EVP_EncodeUpdate(&ctx, t, &len, f, 60);
	total += len;
	printf("total = %d\n", total);
	EVP_EncodeFinal(&ctx, t + total, &len);
	total += len;
	printf("total = %d\n", total);
	printf("%s\n", t);
	
	return 0;
} 
