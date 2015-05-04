#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

#include <openssl/rsa.h>
int main(int argc, char const *argv[])
{
	int ret, inlen;
	unsigned int len;
	size_t outlen;
	unsigned long e  = RSA_3;
	char data[128];
	unsigned char out[500], dst[128];

	EVP_PKEY_CTX *ectx, *dctx;
	EVP_PKEY *pkey;
	RSA *rkey;
	//RSA *rsa;
	BIGNUM * bne;

//printf("hello\n");
	strcpy(data, "openssl hello world");
	inlen = strlen(data);
	bne = BN_new();
	ret = BN_set_word(bne, e);
	rkey = RSA_new();
	ret = RSA_generate_key_ex(rkey, 1024, bne, NULL);
//	printf("hello\n");
	if(ret <= 0)
		return 1;
	pkey = EVP_PKEY_new();
	ret = EVP_PKEY_assign_RSA(pkey, rkey);
	if(ret <= 0)
		return 1;
	ectx = EVP_PKEY_CTX_new(pkey, NULL);

	if(ectx == NULL)
		return 1;
	if(EVP_PKEY_encrypt_init(ectx) <= 0)
		return 1;
	printf("hello\n");
	ret = EVP_PKEY_decrypt(dctx, dst, &len, out, outlen);
printf("hello\n");
	if(ret > 0)
	{
		dst[len] = 0;
		printf("length of plain text = %d\n", len);
	}
	else
		printf("fail in private decrypt\n");

	printf("palin text = %s\n", dst);

	BN_free(bne);
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ectx);
	EVP_PKEY_CTX_free(dctx);


	return 0;
}