#include <openssl/x509.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	X509 *x509 = NULL;
	FILE * fp;
	unsigned char data[2048], *p;
	int len, ret;

	fp = fopen("test.cer", "rb");
	if(fp == NULL)
		return 1;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	x509 = d2i_X509(NULL, (const unsigned char **) &p, len);
	ret = X509_print_fp(stdout, x509);
	return 0;
}