#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/stack.h>
#include <openssl/safestack.h>
#include <openssl/asn1_mac.h>

typedef struct MY_SEQ
{
	ASN1_INTEGER *age;
	ASN1_OCTET_STRING *name;
	STACK_OF(ASN1_OCTET_STRING) *coursre;
}MY_SEQ;

ASN1_SEQUENCE(MY_SEQ) = 
{
	ASN1_SIMPLE(MY_SEQ, age, ASN1_INTEGER),
	ASN1_SIMPLE(MY_SEQ, name, ASN1_OCTET_STRING),
	ASN1_SET_OF(MY_SEQ, coursre, ASN1_OCTET_STRING)
}ASN1_SEQUENCE_END(MY_SEQ)
DECLARE_ASN1_FUNCTIONS(MY_SEQ)
IMPLEMENT_ASN1_FUNCTIONS(MY_SEQ)

int main(int argc, char const *argv[])
{
	int len, i, ret;
	const char *name1 = "smith", *name2 = "davi";
	unsigned char *p, *buf;
	MY_SEQ *myseq;
	myseq = MY_SEQ_new();
	ASN1_INTEGER_set(myseq->age, 32);
	ASN1_OCTET_STRING_set(myseq->name, (const char *) name1, strlen(name1));
	ASN1_OCTET_STRING *coursel = ASN1_OCTET_STRING_new();
	ASN1_OCTET_STRING_set(coursel, (const unsigned char *)"physics", strlen("physics"));
	SKM_sk_push(ASN1_OCTET_STRING, myseq->coursre, coursel);
	ASN1_OCTET_STRING *course2 = ASN1_OCTET_STRING_new();

	ASN1_OCTET_STRING_set(course2, (const unsigned char *)"chemics", strlen("chemics"));
	SKM_sk_push(ASN1_OCTET_STRING, myseq->coursre, course2);
	len = i2d_MY_SEQ(myseq, NULL);
	p = buf = (unsigned char *)malloc(len);
	len = i2d_MY_SEQ(myseq, &buf);
	for (i = 0; i < len; ++i)
		{
			printf("%02x\t", p[i]);
			/* code */
		}	
	printf("\n");

	return 0;
}