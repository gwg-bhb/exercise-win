#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	int ret, ek1[2], npukb, in1, out1, total = 0, total2 = 0;
	unsigned long e  = RSA_3;

	char *ek[2], iv[8], in[100], out[500], de[500];
	EVP_CIPHER_CTX  ctx, ctx2;
	EVP_CIPHER *type;
	EVP_PKEY *pubkey[2];
	RSA *rkey;
	BIGNUM *bne;

	bne = BN_new();
	ret = BN_set_word(bne, e);
	rkey = RSA_new();
	ret = RSA_generate_key_ex(rkey, 1024, bne, NULL);
	pubkey[0] = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pubkey[0], rkey);
	type = EVP_des_cbc();
	npukb = 1;

	EVP_CIPHER_CTX_init(&ctx);
	ek[0] = malloc(500);
	ret = EVP_SealInit(&ctx, type, ek, ek1, iv, pubkey, 1);
	if(ret != 1)
		goto err;
	else
		printf("succ in seal init\n");
	strcpy(in, "opwnssl hello world");
	in1 = strlen(in);
	ret = EVP_SealUpdate(&ctx, out, &out1, in, in1);
	if(ret != 1)
		goto err;
	else
		printf("succ in seal update\n");
	total += out1;
	ret = EVP_SealFinal(&ctx, out+out1, &out1);
	if(ret != 1)
		goto err;
	else
		printf("succ in seal final\n");
	total += out1;
	EVP_CIPHER_CTX_cleanup(&ctx);

	memset(de, 0, 500);
	EVP_CIPHER_CTX_init(&ctx2);
	ret = EVP_OpenInit(&ctx2, EVP_des_cbc(), ek[0], ek1[0], iv, pubkey[0]);
	if(ret != 1)
		goto err;
	else
		printf("succ in open inti\n");
	ret = EVP_OpenUpdate(&ctx2, de, &out1, out, total);
	if(ret != 1)
		goto err;
	else
		printf("succ in open updat\n");
	total2 += out1;
	ret = EVP_OpenFinal(&ctx2, de+out1, &out1);
	if(ret != 1)
		goto err;
	else
		printf("succ in open finish\n");
	total2 += out1;
	de[total2] = 0;
	printf("%s\n", de);
	EVP_CIPHER_CTX_cleanup(&ctx2);

	err:
	free(ek[0]);
	EVP_PKEY_free(pubkey[0]);
	BN_free(bne);

	return 0;
}