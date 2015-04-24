#include <openssl/asn1t.h>

typedef struct MY_SEQ
{
	/* data */
	ASN1_INTEGER *age;
	ASN1_OCTET_STRING *name;
}MY_SEQ;
ASN1_SEQUENCE(MY_SEQ) = 
{
	ASN1_SIMPLE(MY_SEQ, age, ASN1_INTEGER),
	ASN1_SIMPLE(MY_SEQ, name, ASN1_OCTET_STRING)
}ASN1_SEQUENCE_END(MY_SEQ)
DECLARE_ASN1_FUNCTIONS(MY_SEQ)
IMPLEMENT_ASN1_FUNCTIONS(MY_SEQ)

int main(int argc, char const *argv[])
{
	int len, i;
	char buf[100];
	unsigned char *p = buf;
    const unsigned char * smith= "smith";
    MY_SEQ * myseq = MY_SEQ_new();
    ASN1_INTEGER_set(myseq->age, 30);
    ASN1_OCTET_STRING_set(myseq->name, smith, strlen(smith));

    len = i2d_MY_SEQ(myseq, &p);  //更改了p指针的位置
    printf("len = %d\n", len);
    p = buf;
    for (i = 0; i < len; ++i)
     {
     	//printf("%02x\t", buf[i]);
     	printf("%02x\t", *(p+i));
     } 
     printf("\n");
	return 0;
}