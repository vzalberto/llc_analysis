#include <stdio.h>

#define FILENAME "llc_file"
#define BUFFER_SIZE 4160


unsigned short getPacketLength(unsigned char *MAC_portion)
{
	unsigned short length;
	length = (MAC_portion[12] << 16) + MAC_portion[13];
	return length;
} 

void getMAC_portion(unsigned char *MAC_portion)
{
	int i;
	FILE *fp;

	fp = fopen(FILENAME, "r");
	
	fread(MAC_portion, sizeof(unsigned char), 12, fp);	//Needs error validation

	close(fp);
}

void printMAC_portion(unsigned char * MAC_portion)
{
	int i = 0;
	while(i < 12)
	{
		printf("%02X ", MAC_portion[i]);
		i++;
	}
	printf("\n");
}

void file_into_buffer(unsigned char * buffer)
{
	FILE *fp;

	fp = fopen(FILENAME, "r");

	fread(buffer, sizeof(unsigned char), BUFFER_SIZE, fp);	//Needs error validation

	close(fp);
}

int main()
{
	unsigned char buffer[BUFFER_SIZE];

	printf("\nAnalizando desde %s\n", FILENAME);

	file_into_buffer(buffer);

	printMAC_portion(buffer);

	return 0;
}
