#include <stdio.h>
#include <openssl/evp.h>

int main(void)
{
	int i, len, total = 0, total2 = 0, ret;
	EVP_ENCODE_CTX ctx1, ctx2;
	unsigned char f[60];
	unsigned char t[80 + 1];
	for(i = 0; i < 60; i++)
	{
	  memset(&f[i], i, 1);	
	}
	EVP_EncodeInit(&ctx1);
	EVP_EncodeUpdate(&ctx1, t, &len, f, 60);
	total += len;
	printf("total = %d\n", total);
//	printf("%s\n", t);
	EVP_EncodeFinal(&ctx1, t + total, &len);
	total += len;
	printf("%total = %d\n", total);
	printf("%s\n", t);
	EVP_DecodeInit(&ctx2);
	ret = EVP_DecodeUpdate(&ctx2, f, &len, t, total);
	total2 += len;
	ret = EVP_DecodeFinal(&ctx2, f, &len);
	total2 += len;
	for(i = 0; i < total2; i++)
	{
		printf("%02x\t", f[i]);
	}
printf("\n");
	return 0;
}
