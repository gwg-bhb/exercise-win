#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	int ret = 0, i;
	unsigned char buf[32];
	unsigned char seeds[64] = "1234567899876543211234567899876543211234567899876543211234567890";
	while(!(ret = RAND_status()))
	{
		printf("err code = %d\n", ret);
		RAND_seed(seeds, 64);
	}
	memset(buf, 0, 32);
	ret = RAND_bytes(buf, 32);
	for (i = 0; i < 32; ++i)
	{
		if( 0 == i % 8)
		printf("\n");
		printf("%02x\t", buf[i]);
		/* code */
	}
	printf("\n");
	return 0;
}