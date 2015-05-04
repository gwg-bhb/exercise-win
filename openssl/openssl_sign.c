#include <openssl/rsa.h>
#include <stdio.h>
#include <string.h>
#include <openssl/objects.h>
const static int pad_type[5] = {1,  3,5};
int main(int argc, char const *argv[])
{
	RSA *rsa;
	int modulelen = 1024;
	int ret, i;
	unsigned int len;
	unsigned long e  = RSA_3;

	BIGNUM *bn;
	unsigned char from[128];
	unsigned char to[128];

	bn = BN_new();
	ret = BN_set_word(bn, e);
	rsa  = RSA_new();
	ret = RSA_generate_key_ex(rsa, modulelen, bn, NULL);
	if(ret != 1)
	{
		printf("ERROR in RSA_generate_key_ex\n");
		goto finally;
	}

	for (i = 0; i < 100; ++i)
	{
		memset(&from[i], i, 1);

		/* code */
	}
	ret = RSA_sign(NID_sha1, from ,100, to, &len, rsa);
	printf("ret = %d, len = %d\n", ret, len);

	ret = RSA_verify(NID_sha1, to, 100, from, len, rsa);
	printf("ret = %d, len = %d\n",ret, len );
	finally:
	RSA_free(rsa);
	return 0;
}