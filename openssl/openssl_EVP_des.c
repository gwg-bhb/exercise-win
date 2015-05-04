#include <openssl/evp.h>
#include <openssl/rand.h>

int main(int argc, char const *argv[])
{
	int ret;
	EVP_CIPHER_CTX ctx;
	const EVP_CIPHER *cipher;
	unsigned char key[24], in[117], out[120], dec[120], iv[8];
	int i, len, outlen;
	const char seeds[65] = "1234567899876543211234567899876543211234567899876543211234567890";
	RAND_seed(seeds, 64);
	ret = RAND_bytes(key, 24);
	for (int i = 0; i < 8; ++i)
	{
		iv[i] = i*3 + 28;
	}
	for (int i = 0; i < 117; ++i)
	{
		in[i] = i*2;
	}
	EVP_CIPHER_CTX_init(&ctx);
    
    cipher = EVP_des_ede3_cbc();

    //cipher = EVP_des_ede3_cfb();
    len = 0;
    ret = EVP_EncryptInit_ex(&ctx, cipher, NULL, key, iv);
    ret = EVP_EncryptUpdate(&ctx, out+len, &outlen, in, 60);
    printf("outlen = %d\n", outlen);

len += outlen;
EVP_EncryptUpdate(&ctx, out+len,&outlen, in+60, 57);
printf("outlen = %d\n", outlen);
len += outlen;
EVP_EncryptFinal_ex(&ctx, out+len, &outlen);
printf("outlen = %d\n", outlen);
len += outlen;

EVP_CIPHER_CTX_cleanup(&ctx);

EVP_CIPHER_CTX_init(&ctx);
ret = EVP_DecryptInit_ex(&ctx, cipher, NULL, key, iv);
len = 0;
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
len += outlen;
for (int i = 0; i < len; ++i)
{
	if (i % 8 == 0)
		printf("\n");
printf("%d\t", dec[i]);
}
printf("\n");
	return 0;
}