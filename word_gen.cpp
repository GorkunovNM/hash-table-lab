#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <cstdlib>
#include "file_commander.h"

//=======================CONSTANTS=======================//
const int FACTOR = 2;
const int FILE_IN_NAME_SIZE = 20;
const int FILE_OUT_NAME_SIZE = 20;
//=======================================================//

//====================PARSE FUNCTIONS====================//
size_t dict_this(char *text, char *dict, size_t text_len);
//=======================================================//

int main() {
	char file_in_name[FILE_IN_NAME_SIZE]  = "text_in.txt";
	char file_out_name[FILE_OUT_NAME_SIZE] = "words_out.txt";

	FILE *text_in   = fopen(file_in_name,  "r");
	FILE *words_out = fopen(file_out_name, "w");
	if (!text_in) {
		printf("Input file not found!\n");
		return 1;
	}
		
	size_t text_in_len = file_len(file_in_name);
	char *buf = (char *) calloc(text_in_len, sizeof(char));
	fread(buf, sizeof(char), text_in_len, text_in);

	char *result = (char *) calloc(text_in_len * FACTOR, sizeof(char));
	size_t out_size = dict_this(buf, result, text_in_len);
	fwrite(result, sizeof(char), out_size, words_out);

	free(buf);
	buf = NULL;
	free(result);
	result = NULL;

	fclose(text_in);
	fclose(words_out);
	
	return 0;
}

size_t dict_this(char *text, char *dict, size_t text_len) {
	size_t j = 0;
	int is_word = 1;
	for (size_t i = 0; i < text_len && text[i] != EOF; ++i) {
		if (isalpha(text[i])) {
			dict[j] = text[i];
			is_word = 1;
			++j;
		}
		else if (text[i] != '\0') {
			if (is_word == 1) {
				dict[j] = '\0';
				is_word = 0;
				++j;
				dict[j] = '\n';
				++j;
			}
		}
	}
	return j;
}