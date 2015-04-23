#include <stdio.h>
#include <openssl/asn1.h>

int main(int argc, char const *argv[])
{
	ASN1_OBJECT *obj;
	const unsigned char oid[] = {"1.2.840.113549.2.5"};
	int i, len;
	unsigned char *buf;
	len = a2d_ASN1_OBJECT(NULL, 0, oid, -1);
	printf("len = %d\n", len);
	
	buf  = (unsigned char *)malloc(sizeof(unsigned char )*len);
	len = a2d_ASN1_OBJECT(buf, len, oid, -1);
	for ( i = 0; i < len; ++i)
	{
		printf("%02x\t", buf[i]);
	}
	printf("\n");
	return 0;
}