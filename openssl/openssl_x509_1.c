#include <openssl/x509.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	X509 *x509 = NULL;
	FILE *fp;
	ASN1_TIME *tm;
	unsigned char data[2048], name[64], *p;
	X509_NAME *issurerName, *subjectName;
	X509_NAME_ENTRY *nameEntry;
	int len, ret, i, j, count;
	ASN1_OBJECT *obj;

	fp = fopen("test.cer", "rb");
	if(fp == NULL)
		return 1;
	len = fread(data, 1, 1024, fp);
	fclose(fp);

	p = data;
	x509 = d2i_X509(NULL, (const unsigned char **)&p, len);
	
	ret = X509_get_version(x509);
	printf("version = %d\n", ret);

	ret = ASN1_INTEGER_get(X509_get_serialNumber(x509));
	printf("sn = %d\n", ret);

	X509_ALGOR_get0(&obj, &ret, (void **)&p, x509->sig_alg);
	len = OBJ_obj2txt(name, 64, obj, 0);
	printf("signature algor = %s\n", name);

	issurerName = X509_get_issuer_name(x509);
	count = X509_NAME_entry_count(issurerName);
	printf("count of issure name = %d\n", count);
	//printf("count of issure name = %d\n", );
	for (i = 0; i < count; ++i)
	{
		nameEntry = X509_NAME_get_entry(issurerName, i);
		printf("%s\n", ASN1_STRING_data(X509_NAME_ENTRY_get_data(nameEntry)));
	}
	printf("begin data = %s\n", ASN1_STRING_data(X509_get_notBefore(x509)));
	printf("end data = %s\n",ASN1_STRING_data(X509_get_notAfter(x509)));

	subjectName = X509_get_subject_name(x509);
	count = X509_NAME_entry_count(subjectName);
	printf("count of subject name  = %d\n", count);
	for (i = 0; i < count; ++i)
	{
		nameEntry = X509_NAME_get_entry(subjectName, i);
		printf("%s\n", ASN1_STRING_data(X509_NAME_ENTRY_get_data(nameEntry)));
	}
	return 0;
}