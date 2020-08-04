#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

Word *word_create(uint8_t *syms, uint32_t len){

	Word *word = (Word *)malloc(sizeof(Word));
	if (word){
		if (syms){
			word->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
			if (word->syms == NULL){
				printf("error calloc");
				return NULL;
			}
			for (uint32_t i = 0; i < len; i++){
				word->syms[i] = syms[i];
			}
		}else{
			word->syms = NULL;
		}
		word->len = len;
	}else{
		printf("error malloc");
		return NULL;
	}

	return word;
}

Word *word_append_sym(Word *w, uint8_t sym){

	if (w == NULL){
		Word *word = word_create(&sym, 1);
		return word;
	}
	Word *word = word_create(w->syms, w->len + 1);
	if (w->syms == NULL){
		word->syms = (uint8_t *)calloc(1, sizeof(uint8_t));
	}
	if (word){
		word->syms[w->len] = sym;
		return word;
	}
	
	return NULL;
}

void word_delete(Word *w){

	if (w){
		if (w->syms){
			free(w->syms);
		}
		free(w);
		w = NULL;
	}

}

WordTable *wt_create(void){

	WordTable *wt = (WordTable*)calloc(UINT16_MAX - 1, sizeof(Word));
	if (wt){
		wt[1] = word_create(0, 0);
		return wt;
	}
	return NULL;
}

void wt_reset(WordTable *wt){

	for (uint16_t i = 1; i < UINT16_MAX - 1; i++){
		if (wt[i]){
			word_delete(wt[i]);
			wt[i] = NULL;
		}
	}

}

void wt_delete(WordTable *wt){

	if(wt){
		wt_reset(wt);
		word_delete(wt[0]);
		free(wt);		
	}

}

//int main (void){

//	WordTable *wt = wt_create();	
//	Word *word1 = word_append_sym(wt[1], 's');
//	printf("%s\n", word1->syms);
//	printf("%s\n", wt[1]->syms);

//	return 0;
//}
