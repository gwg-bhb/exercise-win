#include <openssl/rsa.h>
#include <stdio.h>
#include <string.h>
const static int pad_type[5] = {1,2,3,4,5};
int main(int argc, char const *argv[])
{
	RSA *rsa;
	FILE *fp;
	int ret, len, padding, i ,flen;
	unsigned char from[128];
	unsigned char to[128], out[2048];
    unsigned char *private = "MIIEogIBAAKCAQEA1f8sG+scwOtBflbg4J2PlphHXncSXSzoR6WCM41BmIj1cqx6fZ8U8SvpzTn9P5WXyvzE/zapwodbRdNhXS0LBBv5x/wSKOk432yzY/511Ph4yJhpZf6oy3HHnVl++qMmkkQJMWRv77EF2bYtJznq53iqCYDH8/nieHrHuIWXxWGrb5/AmA6LMoEhtxKyz5wnCdiDNBTmrc/ER4VoLPL0B2Aw4531M/j0OpPgtzZQ8H9EvaM0QSz9Lx7Eg+5UdAGisUwdUp8uqvZft+SL8NWrEEWJw2EkOBdlBIeyR4WcL4xq1gLleyf6jS4/Uey45BJac+zPsLdwqxuRfXlzKhRFuQIDAQABAoIBADnuwLQ2LCyWA77+Khbk0NCGHRwXxCLxW1i6F8t4/D8dJMWMqASGIpc/uiXTAxpJlzRexb4JwF9nYXA/z2X4IblVEYPwW8IzkS/7L31sj929/oTfrfjsvimFffK9HcEglfqW7J4wgJU1KU5NIWAzL8LGSdIUyQzlo0fWhWcQ04udbJ8kNsovJizT4ykglf9cE/Znw0HkIrIZ6rgOcNfpCik4sZ2OCACs5qaVsDPQZxlVNKzIncIlkyr5uUp28u6sNhhhHSUBC1xVcrpxlJzB9RR/zuNf8km0NZ7JgPnWxACAbOMsrQPfg4vTcmutlL2QMbWGzoZ1F7Nr0MJIEMuDV1kCgYEA6q4nVBDoBBLx4Ctj9aqTNa0Iip36xj+IjCJmoY57jQLjnKr30Ek/tFpbNNCgqPCR9ZM1UWZGjEG6a1RXLPx1dekm4S1YcSWm3ZQ9w+6ix1l1oO1Mt/cT7S7zR/oc9OxkczZ99gErEQN0xs5ziTeusK1SbK19CvhpRZS4NBApTd8CgYEA6W/984UwZGDktHkD2pwLZ9FnKdK92+OxYFg9cGLRhnCxLNka4arZAMyt99zDnS6HRFgXy3Cu5jLXK7tRWu0oFYOA5SMFzevNhCkwEqF1Url7rn872Q3P6JGEJIh0xqulIjHOouEXGEwvS3MrJd++Qlo7ygvrfzrifKYq2f0WL2cCgYBq4OuqXpS8HkCn/jrlDE1E2cwVDUPDe/XdFGG3XCOqodE1bau04Vcw9SGqmQVCS2W9+NAEhVbF071p2hxlsYhxLcD2NmecCDDJoxTKIelibryikNAqzEz37TUA58i+RtasnfmZywhpFDDfxfBaYtCdSCJMumpDT8Tp2oRVubKF8wKBgCAki5M8g61Oqi8vephfZDKnYs0fd4UPlRzvCYawFKmuWrcSLeFk5Px3Mn0uqMC752RBvQUGPw7zcS1UXZ9niF1t/hGPAP2ZunK4OSZXlRAO+jjMzDDW9gnP/6IIKAwzFknfEdTbqZJu6xQ4h3hvloMMaa8odQTP1t/TAZOChcuBAoGAV067AD0jkyYND7WttaFid96SZcABnhfvlQDxkfNLY9MofjtaZC9AtEcTIx9yd3q2kJHaN5TyX3FAEQHuTSL19uCfMZzncV5HOkycTWYxzcMjo+utqpqTGzsRdpTbzQQRyZwL0E+NHd4CNn0W5zK49cJySWnMiVNMNLA37M1Nlto=";
    unsigned char * pubkey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA1f8sG+scwOtBflbg4J2PlphHXncSXSzoR6WCM41BmIj1cqx6fZ8U8SvpzTn9P5WXyvzE/zapwodbRdNhXS0LBBv5x/wSKOk432yzY/511Ph4yJhpZf6oy3HHnVl++qMmkkQJMWRv77EF2bYtJznq53iqCYDH8/nieHrHuIWXxWGrb5/AmA6LMoEhtxKyz5wnCdiDNBTmrc/ER4VoLPL0B2Aw4531M/j0OpPgtzZQ8H9EvaM0QSz9Lx7Eg+5UdAGisUwdUp8uqvZft+SL8NWrEEWJw2EkOBdlBIeyR4WcL4xq1gLleyf6jS4/Uey45BJac+zPsLdwqxuRfXlzKhRFuQIDAQAB";
int privkeylen = strlen(private);
int publkeylen = strlen(pubkey); 
	for (i = 0; i < 128; ++i)
	{
		from[i] = i;
		/* code */
	}
	len = EVP_DecodeBlock(out, private, privkeylen);
	const unsigned char * p = private + privkeylen - 1;
	while( *p == '=' )
		{
			p--;
			len++;
		}
		p = out;
		rsa = d2i_RSAPrivateKey(NULL, &p, len);
	
	for (i = 0; i < sizeof(pad_type)/sizeof(int); ++i)
	{
		flen = RSA_size(rsa);
		printf("flen = %d\n",flen );  //密钥长度,Byte
		switch(pad_type[i])
		{
			case RSA_PKCS1_PADDING:
			case RSA_SSLV23_PADDING:
			flen -= 11;
			break;
			case RSA_PKCS1_OAEP_PADDING:
			flen -= 42;
			break;
			case RSA_X931_PADDING:
			flen -= 2;
			break;
			default:
			break;
		}
		 printf("feln = %d\n", flen);
			ret = RSA_public_encrypt(flen, from ,to, rsa, pad_type[i]);
			printf("IN RSA_public_encrypt ret = %d\n", ret);
			len = RSA_private_decrypt(128, to, from, rsa, pad_type[i]);
			printf("In RSA_private_decrype len = %d\n", len);
		/* code */
	}

	return 0;
}