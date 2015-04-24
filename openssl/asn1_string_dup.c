#include <openssl/asn1.h>


int main(int argc, char const *argv[])
{
	int i, len, ret;
	char *c = "hello world";
	unsigned char *tmp, *buf, *p;
	ASN1_OCTET_STRING *str1, *str2, *str3;
	str1 = ASN1_OCTET_STRING_new();
	ret = ASN1_OCTET_STRING_set(str1, (const unsigned char *)c, strlen(c));
	tmp = ASN1_STRING_data(str1);
	printf("content in str1= %s\n", tmp);

	str2 = ASN1_OCTET_STRING_dup(str1);
	tmp = ASN1_STRING_data(str2);
	printf("content in str2 = %s\n",tmp );
	ret = ASN1_OCTET_STRING_cmp(str1, str2);
	if(!ret)
	{
		printf("content on str1 equals content in str2\n");
	}
	else
	{
		printf("content on str1 not equals content in str2\n");
	}

	len = i2d_ASN1_OCTET_STRING(str1, NULL);
	p = buf = (unsigned char *)malloc(len);

	len = i2d_ASN1_OCTET_STRING(str1, &buf);

	for (i = 0; i < len; ++i)
	{
		/* code */
		printf("%02x\t", p[i]);
	}
	printf("\n");

	str3 = d2i_ASN1_OCTET_STRING(NULL, (const unsigned char **)&p, len);
	tmp = ASN1_STRING_data(str3);
	printf("content in str3 = %s\n", tmp);

	ASN1_OCTET_STRING_free(str1);
	ASN1_OCTET_STRING_free(str2);
	return 0;
}