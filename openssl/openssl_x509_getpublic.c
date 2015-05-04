#include <openssl/x509.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	X509 *x509 = NULL;
	FILE *fp;
	EVP_PKEY_CTX *ctx;
	EVP_PKEY *pkey;
	unsigned char data[2048], out[128], *p;
	unsigned char *plain = "openssl hello world";
	int ret, len, inlen, outlen;

	fp = fopen("test.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	x509 = d2i_X509(NULL, (unsigned char **)&p, len);

	pkey = X509_extract_key(x509);
	ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if(ctx == NULL)
		return 0;
	if(EVP_PKEY_encrypt_init(ctx) <= 0)
		return 0;
	inlen = strlen(plain);
	ret = EVP_PKEY_encrypt(ctx, out, &outlen, (const unsigned char *)plain, inlen);
	if(ret > 0)
		printf("length of encrypt text = %d\n", outlen);
	else 
		printf("fail in public enrcrypt\n");

	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);


	return 0;
}