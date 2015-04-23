#include <stdio.h>
#include <openssl/asn1.h>

int main()
{
	int ret, len, i;

	ASN1_BIT_STRING *a;
	a = ASN1_BIT_STRING_new();
	ASN1_BIT_STRING_set_bit(a, 11, 0);
	ret = ASN1_BIT_STRING_get_bit(a, 8);
	printf("%8th bit = %d\n", ret);
	ret = ASN1_BIT_STRING_get_bit(a, 11);

	printf("%11th bit = %d\n", ret);
	//i2d_ASN1_
	ASN1_BIT_STRING_free(a);
	return 0;
}