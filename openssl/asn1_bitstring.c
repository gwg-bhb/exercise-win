#include <openssl/asn1.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	long value;
	int ret, len, i;
	unsigned char *bitstr = "8";
	unsigned char buf2[16];
	unsigned char *buf = NULL, *p;
	ASN1_BIT_STRING *a, *q;
	a = ASN1_BIT_STRING_new();
	printf("len = %d\n", a->length);
	ASN1_BIT_STRING_set(a, bitstr, strlen(bitstr));

	len = i2d_ASN1_BIT_STRING(a, NULL);
	p = buf =malloc(sizeof(unsigned char) * len);
	len = i2d_ASN1_BIT_STRING(a, &buf);
	printf("after i2d der content len = %d\n", len);
	printf("len = %d\n", len);

	for (i = 0; i < len; ++i)
	{
		/* code */
		printf("%02x\n", p[i]);
	}
	printf("\n");

	q = d2i_ASN1_BIT_STRING(&a, &p, len);
	printf("after d2i length = %d\n", q->length);
	for (i = 0; i < q->length; ++i)
	{
		printf("%02x\t", q->data[i]);
	}
	printf("\n");
	ASN1_BIT_STRING_free(a);
	return 0;
}