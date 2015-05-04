#include <openssl/x509.h>

int main(int argc, char const *argv[])
{
	X509 *x509 = NULL;
	FILE *fp;
	ASN1_TIME *tm;
	unsigned char data[2048], *p;
	ASN1_OBJECT *obj;
	unsigned char *authKeyID = "2.5.29.35";
	unsigned char *basicCon = "2.5.29.19";
	unsigned char * keyUsage = "2.5.29.15";
	unsigned char *extKeyUsage = "2.5.29.37";
	X509_EXTENSION *ext;
	ASN1_STRING *str;
	int pos, len, i;

	fp = fopen("test.cer", "rb");
	if(fp == NULL)
		return 0;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	x509 = d2i_X509(NULL, (const unsigned char **)&p, len);

	obj = OBJ_txt2obj(authKeyID, 0);
	pos = X509_get_ext_by_OBJ(x509, obj, -1);
	ext = X509_get_ext(x509, pos);
	str = X509_EXTENSION_get_data(ext);
	len = ASN1_STRING_length(str);
	printf("oid = %s\n", authKeyID);
	for (i = 0; i < len; ++i)
		printf("%x\t", ASN1_STRING_data(str)[i]);
		printf("\n");
	obj = OBJ_txt2obj(basicCon, 0);
	pos = X509_get_ext_by_OBJ(x509, obj, -1);
	ext = X509_get_ext(x509, pos);
	str = X509_EXTENSION_get_data(ext);
	len = ASN1_STRING_length(str);
	printf("oid = %s\n", keyUsage);
	printf("content blow\n");

	for ( i = 0; i < len; ++i)
	{
		printf("%x\t", ASN1_STRING_data(str)[i]);
	}
	printf("\n");

	obj = OBJ_txt2obj(extKeyUsage, 0);
	pos = X509_get_ext_by_OBJ(x509, obj, -1);
	ext = X509_get_ext(x509, pos);
	str = X509_EXTENSION_get_data(ext);
	len = ASN1_STRING_length(str);
	printf("oid = %s\n", extKeyUsage);
	printf("content blow\n");
	int j;
	for (j = 0; j < len; ++j)
	{
		printf("%x\t", ASN1_STRING_data(str)[j]);
	}
	printf("\n");


	return 0;
}