#include <openssl/evp.h>
#include <stdio.h>
int main(void)
{
	char f[3] = {
	0x08, 0x13, 0x31
	};

	char t[4];
	int ret, len, i;
	len = EVP_EncodeBlock(t, f, 3);
	for(i = 0; i < len; i++)
	{
		printf("%c\t", t[i]);
	}
	printf("\n");
	len = EVP_EncodeBlock(t, f, 2);
	for(i = 0; i < len; i++)
	{
		printf("%c\t", t[i]);
	}
printf("\n");
	len = EVP_EncodeBlock(t, f, 1);
	for(i = 0; i < len; i++)
	{
		printf("%c\t", t[i]);
	}
	printf("\n");

	return 0;
}