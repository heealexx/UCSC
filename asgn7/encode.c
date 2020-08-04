#include "io.h"
#include "trie.h"
#include "code.h"
#include "word.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <getopt.h>

uint8_t bitlength (uint16_t next_code){

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

int compress(int infile, int outfile){

	TrieNode *root = trie_create();
	TrieNode *curr_node = root;
	TrieNode *prev_node = NULL;
	TrieNode *next_node = NULL;
	uint8_t curr_sym = 0;
	uint8_t prev_sym = 0;
	uint16_t next_code = START_CODE;

	while(read_sym(infile, &curr_sym)){
		next_node = trie_step(curr_node, curr_sym);
		if (next_node != NULL){
			prev_node = curr_node;
			curr_node = next_node;
		}else{
			buffer_pair(outfile, curr_node->code, curr_sym, bitlength(next_code));
			curr_node->children[curr_sym] = trie_node_create(next_code);
			curr_node = root;
			next_code = next_code + 1;
		}
		if (next_code == MAX_CODE){
			trie_reset(root);
			curr_node = root;
			next_code = START_CODE;
		}
		prev_sym = curr_sym;
	}
	if (curr_node != root){
		buffer_pair(outfile, prev_node->code, prev_sym, bitlength(next_code));
		next_code = (next_code + 1) % MAX_CODE;
	}
	buffer_pair(outfile, STOP_CODE, 0, bitlength(next_code));
	flush_pairs(outfile);

	trie_delete(root);	
	
	return 0;
}

int main(int argc, char **argv){

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
	}
	if (fd_in == -1){
		printf("error opening file\n");
		return -1;
	}

	if (outfile){
		fd_out = open(outfile_name, O_WRONLY | O_CREAT);
	}

	compress(fd_in, fd_out);
	
	close(fd_in);
	close(fd_out);
	
	return 0;
}
