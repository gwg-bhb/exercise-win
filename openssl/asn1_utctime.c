#include <openssl/asn1.h>

int main(int argc, char const *argv[])
{
	int ret, len, i;
	time_t t;
	unsigned char *tmp, *buf, *p;
	const char *c= "141128103025Z";
	ASN1_UTCTIME *a = ASN1_UTCTIME_new(), *b;
	ret = ASN1_UTCTIME_set_string(a, c);
	len = i2d_ASN1_UTCTIME(a, NULL);
	p = buf = (unsigned char *)malloc(len);
	len = i2d_ASN1_UTCTIME(a, &buf);

	for (i = 0; i < len; ++i)
	{
		/* code */
		printf("%02x\t", p[i]);
	}
	printf("\n");

	b = d2i_ASN1_UTCTIME(NULL, (const unsigned char **)&p, len);
	tmp = ASN1_STRING_data(b);
	printf("time in b = %s\n", tmp);
	ASN1_UTCTIME_free(b);

	time(&t);
	b = ASN1_UTCTIME_set(a, t);
	tmp = ASN1_STRING_data(a);
	printf("time in a = %s\n", tmp);
	ASN1_UTCTIME_free(a);
	return 0;
}