#include <openssl/asn1.h>

int main(int argc, char const *argv[])
{
	/* code */
	long value;
	int ret, len, i;
	unsigned char * buf = NULL, *p;
	ASN1_BOOLEAN a = 0xff, q;

	len = i2d_ASN1_BOOLEAN(a, NULL);
	p = buf = malloc(sizeof(unsigned char)*len);
	len = i2d_ASN1_BOOLEAN(a, &buf);
	printf("len = %d\n", len);
	for ( i = 0; i < len; ++i)
	{
		printf("%02x\t", p[i]);
	}
	printf("\n");

	q = d2i_ASN1_BOOLEAN(&a, &p, len);

	printf("q = %d\n", q);

	return 0;
}