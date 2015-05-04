#include <openssl/pkcs7.h> 
#include <openssl/x509.h> 
#include <openssl/bio.h> 
int main(int argc, char* argv[]) 
{ 
PKCS7 *p7; 
FILE *fp = NULL; 
X509 *user; 
EVP_PKEY *pkey; 
BIO *mybio; 
int ret, len, i; 
unsigned char data[4096]/*因为SignandenvelopedData较大，所以缓冲区要大一些*/, *p; 

OpenSSL_add_all_algorithms(); //必须要显式进行调用 

//从文件加载P7 
fp = fopen("p7signandenv.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 4096, fp); 
fclose(fp); 
p = data; 
p7 = d2i_PKCS7(NULL, (const unsigned char**)&p, len); 

//加载用户证书 
fp = fopen("mycert4p12.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
user = d2i_X509(NULL, (const unsigned char**)&p, len); 

//读取私钥 
fp = fopen("myprivkey.pem", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
pkey = d2i_PrivateKey(EVP_PKEY_RSA, NULL, (const unsigned char**)&p, len); 

mybio = PKCS7_dataDecode(p7, pkey, NULL, user); 

if(mybio != NULL ) 
{ 
len = BIO_read(mybio, data, 32); 
data[len] = '\0'; 
printf("content in envelop = %s\n", data); 
} 
else 
{ 
printf("fail in decrypt envelop\n"); 
} 
BIO_free(mybio); 
PKCS7_free(p7); 
return 1; 
} 