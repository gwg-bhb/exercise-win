#include <openssl/evp.h>
#include <openssl/rand.h>

int main(int argc, char const *argv[])
{
	int ret;
	EVP_CIPHER_CTX ctx;
	const EVP_CIPHER *cipher;
	unsigned char key[8], in[117], out[120], dec[120];
	int i, len, outlen;
   //用随技数做密钥
	const char seeds[65] = "1234567899876543211234567899876543211234567899876543211234567890";
	RAND_seed(seeds, 64);
	ret = RAND_bytes(key, 8);
	for (i = 0; i < 117; ++i)
	{
		in[i] = i * 2;

	}
	EVP_CIPHER_CTX_init(&ctx);
	cipher = EVP_des_ecb();

	len = 0;
	ret = EVP_EncryptInit_ex(&ctx, cipher, NULL, key, NULL);
	ret = EVP_EncryptUpdate(&ctx, out+len, &outlen, in, 60);
	printf("outlen = %d\n", outlen);

	len += outlen;
	EVP_CIPHER_CTX_cleanup(&ctx);
	EVP_CIPHER_CTX_init(&ctx);
	ret = EVP_DecryptInit_ex(&ctx, cipher, NULL, key, NULL);
	len = 0;
	/*
	for(int j = 0; j <= 3; j++)
	{
		EVP_DecryptUpdate(&ctx, dec+len, &outlen, out+30*j , 60);
	printf("outlen = %d\n", outlen);
	len += outlen;
	}
	*/
	
	EVP_DecryptUpdate(&ctx, dec+len, &outlen, out, 60);
	printf("outlen = %d\n", outlen);
	len += outlen;
	EVP_DecryptUpdate(&ctx, dec+len, &outlen, out+60, 30);
	printf("outlen = %d\n", outlen);
	len += outlen;
	EVP_DecryptUpdate(&ctx, dec+len, &outlen, out+90, 30);
	printf("outlen = %d\n", outlen);
	len += outlen;

	ret = EVP_DecryptFinal_ex(&ctx, dec+len, &outlen);
	EVP_CIPHER_CTX_cleanup(&ctx);
	printf("outlen = %d\n", outlen);
	len += outlen;
	for (i = 0; i < len; ++i)
	{
		if(i % 8 == 0)
			printf("\n");
		printf("%d\t", dec[i]);
		/* code */
	}
	printf("\n");
	return 0;
}