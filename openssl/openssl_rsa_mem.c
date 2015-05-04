#include <openssl/rsa.h>
#include <stdio.h>

const static int pad_type[5] = {1,2,3,4,5};
int main(int argc, char const *argv[])
{
	RSA *rsa;
	FILE *fp;
	int ret, len, padding, i ,flen;
	unsigned char from[128];
	unsigned char to[128];

	for (i = 0; i < 128; ++i)
	{
		from[i] = i;
		/* code */
	}
	if((fp = fopen("private.key", "r")) == NULL)
	{
		printf("FOPEN ERROR\n");
		return -1;
	}

	rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
	fclose(fp);
	for (i = 0; i < sizeof(pad_type)/sizeof(int); ++i)
	{
		flen = RSA_size(rsa);
		printf("flen = %d\n",flen );
		switch(pad_type[i])
		{
			case RSA_PKCS1_PADDING:
			case RSA_SSLV23_PADDING:
			flen -= 11;
			break;
			case RSA_PKCS1_OAEP_PADDING:
			flen -= 42;
			break;
			case RSA_X931_PADDING:
			flen -= 2;
			break;
			default:
			break;
		}
		 printf("feln = %d\n", flen);
			ret = RSA_public_encrypt(flen, from ,to, rsa, pad_type[i]);
			printf("IN RSA_public_encrypt ret = %d\n", ret);
			len = RSA_private_decrypt(128, to, from, rsa, pad_type[i]);
			printf("In RSA_private_decrype len = %d\n", len);
		/* code */
	}
   

	return 0;
}