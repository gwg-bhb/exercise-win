#include <openssl/pkcs7.h> 
#include <openssl/objects.h> 
#include <openssl/evp.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
PKCS7 *p7, *innerp7; 
FILE *fp = NULL; 
EVP_PKEY *pkey = NULL; 
PKCS7_SIGNER_INFO *p7i; 
PKCS7_RECIP_INFO *pri; 
BIO *mybio, *inbio; 
X509 *user; 
X509_ALGOR *md; 
int ret, len; 
unsigned char data[2048], *p, *buf; 
unsigned char* greet = "hello openssl"; 

unsigned long errorno; 
unsigned char* errordesc; 

OpenSSL_add_all_algorithms(); //必须要显式进行调用 

inbio = BIO_new(BIO_s_mem()); 
ret = BIO_write(inbio, greet, strlen(greet)); 

p7 = PKCS7_new(); 
ret = PKCS7_set_type(p7, NID_pkcs7_signedAndEnveloped); 


//加载用户证书 
fp = fopen("mycert4p12.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
user = d2i_X509(NULL, (const unsigned char**)&p, len); 
ret = PKCS7_add_certificate(p7, user); 
pri = PKCS7_add_recipient(p7, user); 

//读取私钥 
fp = fopen("myprivkey.pem", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
pkey = d2i_PrivateKey(EVP_PKEY_RSA, NULL, (const unsigned char**)&p, len); 

//第一个用户增加SignerInfo到列表中 
p7i = PKCS7_add_signature(p7, user, pkey, EVP_md5()); 

//加载用户证书 
fp = fopen("user2.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
user = d2i_X509(NULL, (const unsigned char**)&p, len); 
ret = PKCS7_add_certificate(p7, user); 
pri = PKCS7_add_recipient(p7, user); 

//读取私钥 
fp = fopen("user2_privatekey.pem", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
pkey = d2i_PrivateKey(EVP_PKEY_RSA, NULL, (const unsigned char**)&p, len); 

//第二个签名者增加到SignerInfo列表中 
p7i = PKCS7_add_signature(p7, user, pkey, EVP_md5()); 

ret = PKCS7_set_cipher(p7, EVP_des_ede3_cbc()); 

ret = PKCS7_final(p7, inbio, 0); //制作数字信封 

len = i2d_PKCS7(p7, NULL); 
p = buf = malloc(len); 
len = i2d_PKCS7(p7, &p); 
printf("in i2d len = %d\n", len); 

fp = fopen("p7signandenv.cer", "wb"); 
fwrite(buf, len, 1, fp); 
fclose(fp); 

PKCS7_free(p7); 
} 