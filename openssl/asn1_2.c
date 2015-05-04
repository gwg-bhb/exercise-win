#include <stdio.h>
#include <openssl/asn1.h>

int main(int argc, char const *argv[])
{
	/* code */
	long value;
	int ret, len, i;
	unsigned char *buf = NULL;
	unsigned char *p;
	ASN1_INTEGER *a = ASN1_INTEGER_new();
	ret = ASN1_INTEGER_set(a, 100);

	len = i2c_ASN1_INTEGER(a, NULL);
	p = buf = malloc(sizeof(unsigned char) * len);

	len = i2c_ASN1_INTEGER(a, &buf);
	for( i = 0; i < len; i++)
	{
		//printf("%0x\t", p[i]);
		printf("%0x\t", buf[i]);
	}
	printf("\n");

	a= c2i_ASN1_INTEGER(&a, &p, len);
	value = ASN1_INTEGER_get(a);
	printf("value = %0x\n", value);
	ASN1_INTEGER_free(a);
	return 0;
}