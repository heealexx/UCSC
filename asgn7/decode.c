#include "code.h"
#include "io.h"
#include "word.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>

int decompress(int infile, int outfile);

uint8_t bitlength(uint16_t next_code){
	
	if (next_code == 0){
		return 1;
	}
	uint16_t mask = 0x8000;
	uint8_t bitlen = 0;
	for (int i = 16; i > 0; i--){
		if ((next_code & mask) == 0){
			mask = mask >> 1;
		}else{
			bitlen = i;
			break;
		}
	}
	return bitlen;
}

int main (int argc, char **argv){

	int c = 0;
	bool infile = false;
	bool outfile = false;
	bool stats = false;	
	char *infile_name;
	char *outfile_name;
	int fd_in = 0;
	int fd_out = 1;
	
	while ((c = getopt(argc, argv, "vi:o:")) != -1){
		switch (c){
		case 'v':
			stats = true;
			break;
		case 'i':
			infile = true;
			infile_name = optarg;
			break;
		case 'o':
			outfile = true;
			outfile_name = optarg;
			break;
		default:
			infile = false;
			outfile = false;
			stats = false;
			break;
		}
	}

	if (infile){
		fd_in = open(infile_name, O_RDONLY);
	}else{
		fd_in = 0;		
	}
	if (fd_in == -1){
		printf("error opening file");
		return -1;
	}

	if (outfile){
		fd_out = open(outfile_name, O_WRONLY | O_CREAT);
	}else{
		fd_out = 1;
	}

	decompress(fd_in, fd_out);
	
	close(fd_in);
	close(fd_out);

	return 0;
}

int decompress(int infile, int outfile){

	WordTable *wt = wt_create();
	uint8_t curr_sym = 0;
	uint16_t curr_code = 0;
	uint16_t next_code = START_CODE;
	while (read_pair(infile, &curr_code, &curr_sym, bitlength(next_code))){
		wt[next_code] = word_append_sym(wt[curr_code], curr_sym);
		buffer_word(outfile, wt[next_code]);
		next_code = next_code + 1;
		if (next_code == MAX_CODE){
			wt_reset(wt);
			next_code = START_CODE;
		}
	}
	flush_words(outfile);

	wt_delete(wt);

	return 0;
}
