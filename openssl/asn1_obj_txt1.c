#inclide<openssl/asn1.h>

int main(int argc, char const *argv[])
{
	
	ASN1_OBJECT *obj = NULL;
	unsigned char txt[32];
	int len;
	const char *oid = "1.2.840.113549.2.5";
	int i, no_name= 1;

	obj = OBJ_txt2obj(oid, no_name);
	len = OBJ_obj2txt(txt, 32, obj, 1);
	printf("oid txt = %s\n", txt);
	i = OBJ_nid2obj(i);
	len = OBJ_obj2txt(txt, 32, obj,1);
	printf("oid text = %s\n", txt);
	ASN1_OBJECT_free(obj);
	return 0;
}