#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024


void
decode(uint16_t ins) 
{
	uint16_t nnn;

	uint8_t n;
	uint8_t x;
	uint8_t y;
	uint8_t kk;
	uint8_t first_nibble;

	nnn = ins & 0x0FFF;
	n = ins & 0x000F;
	x = (ins >> 8) & 0x0F;
	y = (ins & 0x00F0) >> 4;
	kk = ins & 0x00FF;
	first_nibble = (ins & 0xF000) >> 12;

	switch (first_nibble) {
		case 0x0:
			switch (kk) {
				case 0xE0:
					printf("CLS\n");
					break;
				case 0xEE:
					printf("RET\n");
					break;
				case 0x00:
					printf("NOP\n");
					break;
				default:
					printf("SPRITE DATA: 0x%04X\n", ins);
					break;
			}
			break;
		case 0x1:
			printf("JP 0x%04X\n",nnn);
			break;
		case 0x2:
			printf("CALL 0x%04X\n", nnn);
			break;
		case 0x3:
			printf("SE V[0x%02X],0x%02X\n", x, kk);
			break;
		case 0x4:
			printf("SNE V[0x%02X],0x%02X\n", x, kk);
			break;
		case 0x5:
			printf("SE V[0x%02X],V[0x%02X]\n", x, y);
			break;
		case 0x6:
			//printf("\nShoul I even be running here? 0x%04X\n", ins);
			printf("LD V[0x%02X],0x%02X\n", x, kk);
			break;
		case 0x7:
			printf("ADD V[0x%02X],0x%02X\n", x, kk);
			break;
		case 0x8:
			switch(n) {
				case 0x0:
					printf("LD V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x1:
					printf("OR V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x2:
					printf("AND V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x3:
					printf("XOR V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x4:
					printf("ADD V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x5:
					printf("SUB V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0x6:
					printf("SHR V[0x%02X]\n", x);
					break;
				case 0x7:
					printf("SUBN V[0x%02X],V[0x%02X]\n", x, y);
					break;
				case 0xE:
					printf("SHL V[0x%02X]\n", x);
					break;
			}
			break;
		case 0x9:
			printf("SNE V[0x%02X],V[0x%02X]\n", x, y);
			break;
		case 0xA:
			printf("LD I,0x%04X\n", nnn);
			break;
		case 0xB:
			printf("JP V[0],0x%04X\n", nnn);
			break;
		case 0xC:
			printf("RND V[0x%02X],0x%02X\n", x, kk);
			break;
		case 0xD:
			printf("DRW V[0x%02X],V[0x%02X],0x%02X\n", x, y, n);
			break;
		case 0xE:
			if (kk == 0x9E)
				printf("SKP V[0x%0X]\n", x);
			else if (kk == 0xA1)
				printf("SKNP V[0x%0X]\n", x);
			break;
		case 0xF:
			switch (kk) {
				case 0x0A:
					printf("LD V[0x%02X],K\n",x);
					break;
				case 0x15:
					printf("LD DT,V[0x%02X]\n",x);
					break;
				case 0x18:
					printf("LD ST,V[0x%02X]\n",x);
					break;
				case 0x1E:
					printf("ADD I,V[0x%02X]\n", x);
					break;
				case 0x29:
					printf("LD F,V[0x%02X]\n",x);
					break;
				case 0x33:
					printf("LD B,V[0x%02X]\n",x);
					break;
				case 0x55:
					printf("LD [I],V[0x%02X]\n",x);
					break;
				case 0x65:
					printf("LD V[0x%02X],I\n",x);
					break;
				default:
					printf("SPRITE DATA: 0x%04X\n", ins);
					break;
			}
			break;
		default:
			printf("SPRITE DATA: 0x%04X\n", ins);
			break;
	}
}

void 
disassemble(FILE *f)
{	
	uint16_t ins;
	uint16_t i;
	size_t bytes_read; 	


	printf("  ABS  |   Rel  |  OPC   | ASM\n");

	i = 0;
	while(1) {
		bytes_read = fread(&ins, 2, 1, f);
		ins = htons(ins);
		printf("0x%04X | 0x%04X | 0x%04X | ", i, 0x200 + i, ins);
		decode(ins);
		if (bytes_read == 0) {
			break;
		}
		i+=2;
	}
}

int
main(int argc, char *argv[])
{
	FILE *f;

	if (argc < 2) {
		fprintf(stderr, "Filename required");
		return -1;
	}

	f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("fopen");
		return -1;
	}

	disassemble(f);

	fclose(f);
	return 0;
}
