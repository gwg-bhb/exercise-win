#include <stdio.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <openssl/bio.h>
int verify_callback(int ok, X509_STORE_CTX *ctx);
BIO *bio_err = NULL;

int main(int argc, char const *argv[])
{
	PKCS7 *p7;
	FILE *fp = NULL;
	PKCS7_SIGNER_INFO *si;
	STACK_OF(PKCS7_SIGNER_INFO) *sk;
	X509_STORE_CTX cert_ctx;
	X509_STORE *cert_store;
	BIO *mybio;
	int ret, len, i;
	unsigned char *errordesc;
	unsigned long errorno;

	unsigned char data[2028], *p, *buf;
	OpenSSL_add_all_algorithms();

	fp = fopen("p7signed.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 2048, fp);
	fclose(fp);
	p = data;
	p7 = d2i_PKCS7(NULL, (const unsigned char **)&p, len);

	mybio = PKCS7_dataInit(p7, NULL);
	sk = PKCS7_get_signer_info(p7);
	if(sk == NULL)
	{
		printf("no signer in p7\n");
		return 0;
	}

cert_store=X509_STORE_new(); 
X509_STORE_set_verify_cb_func(cert_store,verify_callback);//必须要有回调设置 
for(i = 0; i < sk_PKCS7_SIGNER_INFO_num(sk); i++) 
{ 
si = sk_PKCS7_SIGNER_INFO_value(sk, i); 
ret = PKCS7_dataVerify(cert_store, &cert_ctx, mybio, p7, si); 
if(ret == 1) 
printf("succ in pkcs7 signed data verify\n"); 
else 
printf("fail in pkcs7 signed data verify\n"); 
} 

X509_STORE_free(cert_store); 
PKCS7_free(p7); 
return 1; 
} 
int verify_callback(int ok, X509_STORE_CTX *ctx) 
{ 
char buf[256]; 
X509 *err_cert; 
int err,depth; 

err_cert=X509_STORE_CTX_get_current_cert(ctx); 
err = X509_STORE_CTX_get_error(ctx); 
depth = X509_STORE_CTX_get_error_depth(ctx); 

X509_NAME_oneline(X509_get_subject_name(err_cert),buf,256); 
BIO_printf(bio_err,"depth=%d %s\n",depth,buf); 
if (!ok) 
{ 
BIO_printf(bio_err,"verify error:num=%d:%s\n",err, 
X509_verify_cert_error_string(err)); 
if (depth < 6) 
{ 
ok=1; 
X509_STORE_CTX_set_error(ctx,X509_V_OK); 
} 
else 
{ 
ok=0; 
X509_STORE_CTX_set_error(ctx,X509_V_ERR_CERT_CHAIN_TOO_LONG); 
} 
} 
switch (ctx->error) 
{ 
case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT: 
X509_NAME_oneline(X509_get_issuer_name(ctx->current_cert),buf,256); 
BIO_printf(bio_err,"issuer= %s\n",buf); 
break; 
case X509_V_ERR_CERT_NOT_YET_VALID: 
case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD: 
BIO_printf(bio_err,"notBefore="); 
ASN1_UTCTIME_print(bio_err,X509_get_notBefore(ctx->current_cert)); 
BIO_printf(bio_err,"\n"); 
break; 
case X509_V_ERR_CERT_HAS_EXPIRED: 
case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD: 
BIO_printf(bio_err,"notAfter="); 
ASN1_UTCTIME_print(bio_err,X509_get_notAfter(ctx->current_cert)); 
BIO_printf(bio_err,"\n"); 
break; 
} 
BIO_printf(bio_err,"verify return:%d\n",ok); 
return(ok); 
} 