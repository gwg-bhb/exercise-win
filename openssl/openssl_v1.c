#include <openssl/pkcs7.h> 
#include <openssl/objects.h> 
#include <openssl/evp.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
PKCS7 *p7, *innerp7; 
FILE *fp = NULL; 
BIO *mybio; 
X509 *user; 
STACK_OF(X509) *xs; 
int ret, len; 
unsigned char data[2048], *p, *buf; 
unsigned char* greet = "hello openssl"; 

OpenSSL_add_all_algorithms(); //必须要显式进行调用 

xs = sk_X509_new_null(); 
//加载用户证书 
fp = fopen("mycert4p12.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
user = d2i_X509(NULL, (const unsigned char**)&p, len); 
sk_X509_push(xs, user); 

fp = fopen("user.cer", "rb"); 
if(fp == NULL) return 0; 
len = fread(data, 1, 1024, fp); 
fclose(fp); 
p = data; 
user = d2i_X509(NULL, (const unsigned char**)&p, len); 
sk_X509_push(xs, user); 

mybio = BIO_new(BIO_s_mem()); 
ret = BIO_write(mybio, greet, strlen(greet)); 

p7 = PKCS7_encrypt(xs, mybio, EVP_des_ede3_cbc(), 0); 

len = i2d_PKCS7(p7, NULL); 
p = buf = malloc(len); 
len = i2d_PKCS7(p7, &p); 
fp = fopen("p7env.cer", "wb"); 
fwrite(buf, len, 1, fp); 
fclose(fp); 
sk_X509_free(xs); 
BIO_free(mybio); 
PKCS7_free(p7); 
} 