#include <openssl/x509.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	X509 *user = NULL, *secroot = NULL;
	FILE *fp;
	EVP_PKEY *pkey;
	const EVP_MD *type = NULL;
	unsigned char data[2048], *p;
	int ret, len;

	OpenSSL_add_all_digests();

	fp = fopen("second.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p =data;
	secroot = d2i_X509(NULL, (const unsigned char **)&p, len);

	pkey = X509_extract_key(secroot);

	fp = fopen("user.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	user = d2i_X509(NULL, (const unsigned char **)&p, len);

	ret = X509_verify(user, pkey);

	if(ret == 1)
		printf("succ in verify\n");
	else
		printf("fail in verify\n");
	//X509_free(root);
	X509_free(secroot);
	X509_free(user);
	EVP_PKEY_free(pkey);



	return 0;
}