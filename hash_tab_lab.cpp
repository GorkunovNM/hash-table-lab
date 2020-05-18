#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include "slist.h"
#include "file_commander.h"

//=======================CONSTANTS=======================//
const int FUNCS_CNT = 5;
const size_t HASH_T_SIZE = 1000;
const size_t STANDART_OUT_LINE_LEN = 50;
//=======================================================//

//======================HASH  TABLE======================//
class hash_table {
public:
	hash_table(int sze) {
		size = sze;
		lists = (slist::slist **) calloc(sze, sizeof(slist::slist *));
		h_func = NULL;
	}

	void *search(char *word) {
		size_t hash = (*h_func)(word);
		slist::slist *searched_list = lists[hash];
		char *result = searched_list->search(word);
		if () return;
	}

	void insert(char *word) {
		;
	}

	void remove(char *word) {
		;
	}

	void set_h_func(size_t (*h_func_in)(char *word)) h_func = h_func_in;

	~hash_table() {
		for (size_t itt = 0; itt < size; ++itt) delete lists[itt];
		free(lists);
		size = 0;
		lists = NULL;
	}
private:
	int size;
	slist::slist **lists;
	size_t (*h_func)(char *word);
};
//=======================================================//

//================BIT OPERATIONS FOR STRS================//
void char_and(char *data_word, char *word) {
	size_t data_word_pos = 0;
	while (*(data_word + data_word_pos) != '\n') {
		word[data_word_pos] = word[data_word_pos] & data_word[data_word_pos];
		++data_word_pos;
	}
}

void char_or(char *data_word, char *word) {
	size_t data_word_pos = 0;
	while (*(data_word + data_word_pos) != '\n') {
		word[data_word_pos] = word[data_word_pos] | data_word[data_word_pos];
		++data_word_pos;
	}
}

void char_xor(char *data_word, char *word) {
	size_t data_word_pos = 0;
	while (*(data_word + data_word_pos) != '\n') {
		word[data_word_pos] = word[data_word_pos] ^ data_word[data_word_pos];
		++data_word_pos;
	}
}
//=======================================================//

//====================HASH  FUNCTIONS====================//
size_t hash_func_0(char *word) {
	return 1;
}

size_t hash_func_1(char *word) {
	size_t word_pos = 0;
	while (*(word + word_pos) != '\n') ++word_pos;
	return word_pos % HASH_T_SIZE;
}

size_t hash_func_2(char *word) {
	size_t ans = 0;
	size_t word_pos = 0;
	while (*(word + word_pos) != '\n') {
		ans = (ans + *(word + word_pos)) % HASH_T_SIZE;
		++word_pos;
	}
	return ans;
}

size_t hash_func_3(char *word) {
	size_t ans = 0;
	size_t word_len = 0;
	size_t word_pos = 0;
	while (*(word + word_pos) != '\n') {
		ans = (ans + *(word + word_pos));
		++word_len;
		++word_pos;
	}
	return (size_t) ans / word_len % HASH_T_SIZE;
}

size_t hash_func_4(char *word) {
	size_t ans = 0;
	size_t word_pos = 0;
	while (*(word + word_pos) != '\n') {
		ans = left_cycl_shft_m_to_l(ans) ^ *(word + word_pos);
		++word_pos;
	}
	return ans % HASH_T_SIZE;
}

size_t hash_func_SHA256(char *word) {
	unsigned int h[8] = {0x6A09E667, 
				0xBB67AE85, 
				0x3C6EF372, 
				0xA54FF53A, 
				0x510E527F, 
				0x9B05688C, 
				0x1F83D9AB, 
				0x5BE0CD19};
	unsigned int k[64] ={0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
   				0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
   				0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
   				0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
   				0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
   				0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
   				0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
   				0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};
   	size_t ans = 0;
   	size_t word_pos = 0;
	while (*(word + word_pos) != '\n') {
		++word_pos;
	}
	char ans_ch[word_pos + 1] = "";
	word[word_pos] = '\n';



	return 1;
}
//=======================================================//

size_t file_len(const char *file_name) {
	struct stat st;
	stat(file_name, &st);
	return st.st_size;
}

int main() {
	size_t (*funcs_ptrs[FUNCS_CNT])(char *word) = {hash_func_0, hash_func_1, hash_func_2, hash_func_3, hash_func_4}; 
	char file_in_name[20] = "words_out.txt";
	char file_out_name[20] = "data_0.csv";
	FILE *words_in = fopen(file_in_name, "r");

	size_t words_in_len = file_len(file_in_name);
	char *buf = (char *) calloc(words_in_len, sizeof(char));
	fread(buf, sizeof(char), words_in_len, words_in);

	hash_table *hash_t = new hash_table(HASH_T_SIZE);

	char *result = (char *) calloc(HASH_T_SIZE * STANDART_OUT_LINE_LEN, sizeof(char));
	FILE *result_file = NULL;
	for (int func_itt = 0; func_itt < FUNCS_CNT; ++func_itt) {
		hash_t->set_h_func(funcs_ptrs[func_itt]);
		;//hash_func here
		size_t out_size = 0;
		file_out_name[5] = '0' + func_itt;
		result_file = fopen(file_out_name, "w");
		fwrite(result, sizeof(char), out_size, result_file);
		fclose(result_file);
	}

	free(buf);
	buf = NULL;
	free(result);
	result = NULL;

	fclose(words_in);
	return 0;
}