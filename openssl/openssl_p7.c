#include <openssl/pkcs7.h>
#include <openssl/objects.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	PKCS7 *p7, *innerp7;
	FILE *fp = NULL;
	PKCS7_SIGNER_INFO *p7i;
	EVP_PKEY *pkey;
	BIO *mybio;
	X509 *user;
	X509_ALGOR *md;
	int ret, len;
	unsigned char data[2048], *p, *buf;
	unsigned char *greet = "hello openssl";

	OpenSSL_add_all_algorithms();
	p7 = PKCS7_new();
	ret = PKCS7_set_type(p7, NID_pkcs7_data);
	p7->d.sign = PKCS7_SIGNED_new();
	innerp7 = PKCS7_new();
	ret = PKCS7_set_type(innerp7, NID_pkcs7_data);
	ASN1_STRING_set(innerp7->d.data, greet, strlen(greet));
	ret = PKCS7_set_content(p7, innerp7);

	fp = fopen("mycert4p12.cer", "rb");
	if(fp == NULL)
	{
		printf("fopen mycert\n");
		return 0;
	}	
	len = fread(data, 1, 1024, fp);
	fclose(fp);
	p = data;
	user = d2i_X509(NULL, (const unsigned char **)&p, len);   //ERROR
	ret = PKCS7_add_certificate(p7, user);
	fp = fopen("myprivkey.pem", "rb");
	if(fp == NULL)
	{
		printf("fopen mycert\n");
		return 0;
	}	
	len = fread(data, 1, 1024, fp);
	fclose(fp);
	p = data;
	pkey = d2i_PrivateKey(EVP_PKEY_RSA, NULL, (const unsigned char **)&p, len);

	ASN1_INTEGER_set(p7->d.sign->version, 2);
	p7i = PKCS7_add_signature(p7, user, pkey, EVP_md5());
	mybio = PKCS7_dataInit(p7, NULL);
	ret = PKCS7_dataFinal(p7, mybio);

	len = i2d_PKCS7(p7, NULL);
	 p = buf = malloc(len);
	 len = i2d_PKCS7(p7, &p);
	 fp = fopen("p7signed.cer", "wb");
	 fwrite(buf, len, 1, fp);
	 fclose(fp);

	 PKCS7_free(p7);
	return 0;
}