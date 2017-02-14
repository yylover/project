#include <stdio.h>
#include <netinet/in.h>


//字节序判断
/**
 *大端字节序：整数的高位字节存储在内存的高地址处。小端字节序是指低位地址在内存的低地址处。
#include <netinet/in.h>
unsigned long int htonl(unsigned long int hostlong);
unsigned long int ntohl(unsigned long int netlong);
unsigned short int htons(unsigned short int hostshort);
unsigned short int ntohs(unsigned short int netshort);

 */
void byteorder() {
	union Data{
		short value;
		char union_bytes[sizeof(short)];
	} data;

	data.value = 0x0102;

	if (data.union_bytes[0] == 1 && data.union_bytes[1] == 2) {
		printf("big endian\n");
	} else if (data.union_bytes[0] == 2 && data.union_bytes[1] == 1) {
		printf ("little endian\n");
	} else {
		printf("unknown\n");
	}
}


int main() {
	printf(" %lu \n", sizeof(short));
	byteorder();
	short value = 0x0102;
	printf("%x\n", value);
	printf("%x\n", htons(value));
	printf("%x\n", ntohs(htons(value)));

	int valint = 0x01020304;
	printf("%x\n", htonl(valint));
	printf("%x\n", ntohl(htonl(valint)));

	return 0;
}
