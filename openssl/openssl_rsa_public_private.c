#include <openssl/rsa.h>
#include <stdio.h>

const static int pad_type[5] = {1,  3,5};
int main(int argc, char const *argv[])
{
	RSA *rsa;
	int modulelen = 1024;
	int ret, len, i, j, flen;
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
	for (i = 0; i < sizeof(pad_type)/sizeof(int); ++i)
	{
		flen = RSA_size(rsa);
		printf("flen = %d\n", flen);
		switch(pad_type[i])
		{
			case RSA_PKCS1_PADDING:
		//	case RSA_SSLV23_PADDING:
			flen -= 11;
			break;
		//	case RSA_PKCS1_OAEP_PADDING:
		//	flen -= 42;
		//	break;
			case RSA_X931_PADDING:
			flen -= 2;
			break;
			default:
			break;
		}
		printf("feln = %d\n", flen);
		for (j = 0; j < flen; ++j)
			from[j] = j;
			ret = RSA_private_encrypt(flen, from ,to, rsa, pad_type[i]);
			printf("IN RSA_public_encrypt ret = %d\n", ret);
			len = RSA_public_decrypt(128, to, from, rsa, pad_type[i]);
			printf("In RSA_private_decrype len = %d\n", len);
			/* code */
		
		/* code */
	}
	finally:
	RSA_free(rsa);
	return 0;
}