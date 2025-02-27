#ifndef PREDICTIVETEXT_H
#define PREDICTIVETEXT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 100

#define ASCII_SIZE 128
#define EXTENDED_ALPHABET_SIZE 256

typedef struct TrieNode {
    struct TrieNode *children[EXTENDED_ALPHABET_SIZE];
    int is_end_of_word;
    int frequency;
} TrieNode;

TrieNode *create_node();
int char_to_index(char c);
void insert(TrieNode *root, const char *word);
void find_top_n_predictions_helper(TrieNode *node, char *prefix, int n, int level, int *count);
void find_top_n_predictions(TrieNode *root, const char *prefix, int n);
void load_words_into_trie(TrieNode *root, const char *file_path);
bool search(TrieNode *root, const char *word);
void process_input_word(TrieNode *dictionary, TrieNode *prediction, const char *word);
void add_custom_word(TrieNode *prediction, const char *word);
bool delete_word_helper(TrieNode *node, const char *word, int level);
void delete_word(TrieNode *root, const char *word);
void edit_word(TrieNode *root, const char *original, const char *modified);
int display_menu();

#endif