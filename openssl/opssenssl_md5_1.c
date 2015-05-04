#include <openssl/md5.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	unsigned char * in = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	size_t len = strlen(in);
	char out[16];
	MD5(in, len, out);
	//MD2(in, len, out);
	for (i = 0; i < 16; ++i)
	{
		//printf("%02x\t", out[i] & 0xff);
		printf("%02x\t", out[i] );
	}
	printf("\n");
	return 0;
}