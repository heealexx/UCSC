#include "code.h"
#include "word.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define size 32000

static uint8_t buff[size];
static uint16_t index = 0;
static uint8_t buff1[size];
static uint16_t index1 = 0;

//void read_header(int infile, FileHeader *header){}

bool read_sym(int infile, uint8_t *sym){

	//static uint8_t binary[size];
	static uint8_t chars[size];
	
	static uint16_t index = 0;
	static uint16_t end = 0;

	if(index == 0){
		end = read(infile, chars, size / 8);
	}
	if(end == 0){
		return false;
	}
	//printf("%u", end);

	if (index < end){
		*sym = chars[index];
		//printf("%c", *sym);
		index += 1;
		return true;
	}else{
		index = 0;
	}

	return true;	
}

void buffer_pair (int outfile, uint16_t code, uint8_t sym, uint8_t bitlen){

	//static uint8_t buff[size];
	uint16_t mask = 0x0001;
	uint8_t mask8 = 0x01;
	//static uint16_t index = 0;
	//printf("code:%u sym:%c bitlen:%u\n", code, sym, bitlen);
	//printf("index:%u\n", index);
	for (uint8_t i = 0; i < bitlen; i++){
		if (code & mask){
			buff[index] = 1;
			//printf("1");
		}else{
			buff[index] = 0;
			//printf("0");
		}
		index += 1;
		mask = mask << 1;
		if (index == size - 1){
                        //for (int j = 0; j < size; j++){
                        //        printf("%u", buff[j]);
                        //}
			write (outfile, buff, size / 8);
			index = 0;
			//printf("write\n");
		}
	}
	mask = mask >> bitlen;	

	for (uint8_t i = 0; i < 8; i++){
		if (sym & mask8){
			buff[index] = 1;
			//printf("1");
		}else{
			buff[index] = 0;
			//printf("0");
		}
		index += 1;
		mask8 = mask8 << 1;
		if (index == size - 1){
			//printf("index%u\n", index);
			//for (int j = 0; j < size; j++){
			//	printf("%u", buff[j]);
			//}
			write (outfile, buff, size / 8);
			index = 0;
			//printf("write\n");
		}
	}
	//printf("\n");	
}

void flush_pairs(int outfile){

	//for (int i = 0; i < index; i++){
	//	printf("%u", buff[index]);
	//}
	//printf("\n");
	//printf("%d\n", outfile);
	//printf("index:%u\n", index);
	write (outfile, buff, (index / 8) + 1);	

}

bool read_pair (int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen){

	static uint8_t buff[size];
	static uint16_t index = 0;
	static uint16_t end = 0;

	//printf("index:%u\n", index);
	if (index == 0){
		end = read(infile, buff, size / 8) * 8;
		//printf("end:%u\n", end);
	}
	//printf("end:%u\n", end);

	*code = 0;
	uint8_t sum = 1;
	//printf("bitlen:%u\n", bitlen);
	for (uint8_t i = 0; i < bitlen; i++){
		//printf("%u", buff[index]);
		//printf("index:%u buff:%u\n", index, buff[index]);
		if (buff[index] && (index < end)){
			*code += sum;
			//printf("here:%u index:%u\n", buff[index], index);
		}
		//printf("here\n");
		sum *= 2;
		index += 1;
		if (index == end){
			index = 0;
			end = read(infile, buff, size / 8);
			//printf("read\n");
		}
	}

	//for (int i = 0; i < size; i++){
	//	printf("%u", buff[i]);
	//}
	//return false;	
	//printf("code:%u\n", *code);
	if (*code == STOP_CODE){
		//printf("ended\n");
		return false;
	}
	//printf("code:%u\n", *code);

	sum = 1;
	*sym = 0;
	for (uint8_t i = 0; i < 8; i++){
		//printf("%u", buff[index]);
		if (buff[index] && (index < end)){
			*sym += sum;
		}
		sum *= 2;
		index += 1;
		if (index == end){
			index = 0;
			end = read(infile, buff, size / 8);
		}
	}
	//printf("code:%u sym:%c\n", *code, *sym);
	//printf("\n");

	return true;
}

void buffer_word(int outfile, Word *w){

	//static uint8_t buff[size];
	//static uint16_t index = 0;

	//printf("index:%u\n", index);
	if (index1 < size){
		for (uint32_t i = 0; i < w->len; i++){
			if (index1 < size){
				buff1[index1] = w->syms[i];
				//printf("%c", buff1[index]);
				index1 += 1;
			}else{
				write(outfile, buff1, size / 8);
				index1 = 0;
			}
		}
	}else{
		write(outfile, buff1, size / 8);
		index1 = 0;
	}

}

void flush_words(int outfile){

	if (index1 > 0){
		write(outfile, buff1, (index1 / 8) + 1);
	}
	
}

//int main (void){

//	int fd = open("testio.txt", O_WRONLY | O_CREAT);

//	buffer_pair(fd, START_CODE, 's', 2);
//	buffer_pair(fd, 3, 'h', 2);
//	buffer_pair(fd, 4, 'e', 3);

//	fd = open("testio.txt", O_RDONLY);
//	uint16_t code = 0;
//	uint8_t sym = 0;
//	read_pair(fd, &code, &sym, 2);
//	printf("code:%u sym:%c\n", code, sym);
//	read_pair(fd, &code, &sym, 2);
//	printf("code:%u sym:%c\n", code, sym);

//	close(fd);
//	return 0;

//}


