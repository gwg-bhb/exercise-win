#include <openssl/asn1.h>
#include <stdio.h>

int  main(int argc, char *argv[])
{
	long value;
	int ret;
	ASN1_INTEGER *a = ASN1_INTEGER_new();
	value = ASN1_INTEGER_get(a);
	printf("value = %d\n", value);

	ret = ASN1_INTEGER_set(a, 100);
	printf("ret = %d\n", ret);
	value = ASN1_INTEGER_get(a);
	printf("value = %d\n", value);

	ret = ASN1_INTEGER_set(a, -100);
	printf("ret = %d\n", ret);
	value = ASN1_INTEGER_get(a);
	printf("value = %d\n", value);
	ASN1_INTEGER_free(a);
	return 0;
}