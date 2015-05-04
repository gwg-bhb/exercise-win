#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	int ret, inlen, outlen = 0;
	unsigned char e = RSA_3;
	char data[100], out[500];
	EVP_MD_CTX md_ctx, md_ctx2;
	EVP_PKEY *pkey;
	RSA *rkey;
	BIGNUM *bne;

	strcpy(data, "openssl hello world");
	inlen = strlen(data);
	bne= BN_new();
	ret = BN_set_word(bne, e);
	rkey = RSA_new();
	ret = RSA_generate_key_ex(rkey, 1024, bne, NULL);
	if(ret != 1)
		return -1;
	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pkey, rkey);

	EVP_MD_CTX_init(&md_ctx);
	ret = EVP_SignInit_ex(&md_ctx, EVP_md5(), NULL);
	if(ret != 1)
		return -1;
	ret = EVP_SignUpdate(&md_ctx, data, inlen);
	if(ret != 1)
		return -1;
	ret = EVP_SignFinal(&md_ctx, out, &outlen, pkey);
	if(ret == 1)
		printf("succ in sign\n");
	else
		printf("fail in sign\n");
	EVP_MD_CTX_cleanup(&md_ctx);

	EVP_MD_CTX_init(&md_ctx2);
	ret = EVP_VerifyInit_ex(&md_ctx2, EVP_md5(), NULL);
	if(ret != 1)
		return -1;
	ret = EVP_VerifyUpdate(&md_ctx2, data, inlen);
	if(ret != 1)
		return -1;
	ret = EVP_VerifyFinal(&md_ctx2, out, outlen, pkey);
	if(ret == 1)
		printf("succ in verify\n");
	else
		printf("fail in verify\n");

	RSA_free(rkey);
	BN_free(bne);
	EVP_MD_CTX_cleanup(&md_ctx2);

	return 0;

}