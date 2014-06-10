#include <stdio.h>
#include <stdlib.h>		//malloc()

#define FILENAME "llc_file"
#define BUFFER_SIZE 4160

#define MAC_FORMAT "%02X:%02X:%02X:%02X:%02X:%02X"

unsigned short getPacketLength(unsigned char *MAC_portion)
{
	unsigned short length;
	
	//sscanf()

	return length;
} 

void printMAC_portion(unsigned char * MAC_portion, int a, int b)
{
	int i = a;
	while(i <= b)
	{
		printf("%c", MAC_portion[i]);
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


long firstPacketLength(unsigned char * buffer)
{
	unsigned long length;

	unsigned long tmplong1, tmplong2;

	unsigned char *a = (unsigned char *) malloc(3);
	unsigned char *b = (unsigned char *) malloc(3);

	a[0] = buffer[36];
	a[1] = buffer[37];
	a[2] = 0x00;

	b[0] = buffer[39];
	b[1] = buffer[40];
	b[2] = 0x00;

	tmplong1 = strtol(a, NULL, 16);
	tmplong2 = strtol(b, NULL, 16);

	length = (tmplong1 << 16) + tmplong2;

	//free(a);
	//free(b);

	return length;
}

unsigned char * parse_dMAC(unsigned char *buffer)
{
	int i = 1;
	unsigned char *mac = (unsigned char *) malloc(12);
	mac[12] = 0x00;
	while(i < 13)
		if(i % 3 == 0)
			mac[i] = ':';
		else
			mac[i] = buffer[i];

	return mac;
}


int main()
{
	unsigned char buffer[BUFFER_SIZE];

	printf("\nAnalizando desde %s\n", FILENAME);

	file_into_buffer(buffer);

	printf("mac destino: \n");
	printMAC_portion(buffer, 0, 16);

	printf("mac origen: \n");
	printMAC_portion(buffer, 18, 35);

	printf("longitud: \n");	
	printMAC_portion(buffer, 36, 40);

	return 0;
}
