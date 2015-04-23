#include <openssl/asn1.h>

int main(int argc, char const *argv[])
{
	ASN1_OBJECT *obj;
	const unsigned char *oid= "1.2.840.113549.2.5";
	unsigned char *buf, *p;
	unsigned char txt[32];
	int i, no_name = 1, len;
	obj= OBJ_txt2obj(oid, no_name);
	len = i2d_ASN1_OBJECT(obj, NULL);
	p = buf = malloc(len);
	len = i2d_ASN1_OBJECT(obj, &buf);
	for (i = 0; i < len; ++i)
	{
		printf("%02x\t", p[i]);
	}
	len = OBJ_obj2txt(txt, 32, obj, 0);
	printf("oid text =%s\n", txt);
	len = OBJ_obj2txt(txt, 32, obj, 1);
	printf("oid text = %s\n", txt);
	return 0;
}