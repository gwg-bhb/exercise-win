#include <openssl/x509.h>
#include <stdio.h>


int main(void)
{
	X509_STORE_CTX *ctx;
	X509_STORE *xs;
	X509 *user = NULL, *secroot = NULL, *root = NULL;
	FILE *fp;
	unsigned char data[2048], *p;
	int ret, len;
	long errorcode;
	const char * tmp;

	OpenSSL_add_all_digests(); //现实调用
	ctx = X509_STORE_CTX_new();
	xs = X509_STORE_new();

	fp = fopen("root.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	root = d2i_X509(NULL, (const unsigned char **)&p, len);
	printf("root = %x\n", root);

	fp =fopen("second.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	secroot = d2i_X509(NULL, (const unsigned char **)&p, len);

	fp = fopen("user.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	user = d2i_X509(NULL, (const unsigned char **)&p, len);
	printf("user cert = %x\n", user);

	ret = X509_STORE_add_cert(xs, root);
	ret = X509_STORE_add_cert(xs, secroot);

	ret = X509_STORE_CTX_init(ctx, xs, user, NULL);

	ret = X509_verify_cert(ctx);
	printf("ret = %d\n", ret);
	if(ret == 1)
		printf("succ in cert verify\n");
	else
		printf("fail in cert verify\n");
	X509_free(root);
	X509_free(secroot);
	X509_free(user);
	X509_STORE_free(xs);
	X509_STORE_CTX_cleanup(ctx);
	X509_STORE_CTX_free(ctx);

	return 0;
}