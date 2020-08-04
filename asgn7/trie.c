#include "trie.h"
#include "code.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#define ALPHABET 256

TrieNode *trie_node_create(uint16_t code){
 
	TrieNode *trienode = (TrieNode *)malloc(sizeof(TrieNode));
	if (trienode){
		trienode->code = code;
		for (int i = 0; i < ALPHABET; i++){
			trienode->children[i] = NULL;
		}
		return trienode;
	}else{
		printf("error calloc");
		return NULL;
	}

	return NULL;
}

void trie_node_delete(TrieNode *n){

	if (n){
		free(n);
		n = NULL;
	}

}

TrieNode *trie_create(void){

	TrieNode *node = trie_node_create(EMPTY_CODE);
	return node;

}

void trie_reset(TrieNode *root){

	for (int i = 0; i < ALPHABET; i++){
		if (root->children[i] != NULL){
			trie_delete(root->children[i]);			
		}
	}

}

void trie_delete(TrieNode *n){

	for (int i = 0; i < ALPHABET; i++){
		if (n->children[i] != NULL){
			trie_delete(n->children[i]);
		}
	}
	trie_node_delete(n);

}

TrieNode *trie_step(TrieNode *n, uint8_t sym){
	
	if (n){
		if (n->children[sym] != NULL){
			return n->children[sym];
		}
	}
	return NULL;
}

//int main (void){

//	TrieNode *root = trie_create();
//	root->children['s'] = trie_node_create(2);
//	root->children['s']->children['h'] = trie_node_create(3);
//	root->children['s']->children['e'] = trie_node_create(5);
//	root->children['b'] = trie_node_create(4);
	
	



//}
