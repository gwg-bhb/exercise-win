#include <openssl/rsa.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	RSA *rsa;
	int modulelen = 1024;
	int ret;
	unsigned long e = RSA_3;
	BIGNUM *bn;

	bn = BN_new();
	ret = BN_set_word(bn, e);
	rsa = RSA_new();
	ret= RSA_generate_key_ex(rsa, modulelen, bn, NULL);
	if(1 != ret)
	{
		printf("ERROR in RSA_generate_key_ex\n");
		goto finally;
	}
	RSA_print_fp(stdout, rsa, 0);
	finally:
	RSA_free(rsa);

	return 0;
}