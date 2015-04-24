#include <openssl/asn1.h>
#include <openssl/stack.h>
#include <openssl/safestack.h>

int main(int argc, char const *argv[])
{
	int len, i, ret;
	const char * name = "smit";
	unsigned char *p, *buf;
	ASN1_TYPE *at1 = ASN1_TYPE_new();
	ASN1_TYPE *at2 = ASN1_TYPE_new();
	ASN1_INTEGER *ai = ASN1_INTEGER_new();
	ASN1_INTEGER_set(ai, 100);
	ret= ASN1_TYPE_set1(at1, V_ASN1_INTEGER, ai);
	ASN1_OCTET_STRING *aos = ASN1_OCTET_STRING_new();
	ASN1_OCTET_STRING_set(aos, (const unsigned char *)name, strlen(name));
	ret = ASN1_TYPE_set1(at1, V_ASN1_INTEGER, ai);
	STACK_OF(ASN1_TYPE) *psk = sk_ASN1_TYPE_new_null();
	sk_ASN1_TYPE_push(psk, at1);
	len = i2d_ASN1_SET((struct stack_st_OPENSSL_BLOCK *) psk, NULL, (i2d_of_void*)i2d_ASN1_TYPE, V_ASN1_SET, V_ASN1_UNIVERSAL, IS_SET);
	p = buf =(unsigned char *)malloc(len);
	len = i2d_ASN1_SET((struct stack_st_OPENSSL_BLOCK*)psk, &buf, (i2d_of_void*)i2d_ASN1_TYPE, V_ASN1_SET, V_ASN1_UNIVERSAL, IS_SET);

	for (i = 0; i < len; ++i)
	{
		printf("%02x\t", p[i]);
		/* code */
	}
	printf("\n");
	
	return 0;
}