#include "predictiveText.h"
// Function to create a new Trie node
TrieNode *create_node() {
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    node->is_end_of_word = false;
    node->frequency = 0;
    for (int i = 0; i < EXTENDED_ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

int char_to_index(char c) {
    return (int) (unsigned char) c;
}

void find_top_n_predictions_helper(TrieNode *node, char *prefix, int n, int level, int *count) {
    if (*count >= n) return;

    if (node->is_end_of_word) {
        prefix[level] = '\0';
        printf("%s (%d)\n", prefix, node->frequency);
        (*count)++;
    }

    for (int i = 0; i < EXTENDED_ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            prefix[level] = (char) i;
            find_top_n_predictions_helper(node->children[i], prefix, n, level + 1, count);
        }
    }
}

void insert(TrieNode *root, const char *word) {
    TrieNode *curr = root;
    for (int level = 0; level < strlen(word); level++) {
        int index = char_to_index(word[level]);
        if (curr->children[index] == NULL) {
            curr->children[index] = create_node();
        }
        curr = curr->children[index];
    }
    curr->is_end_of_word = true;
    curr->frequency += 1;
}

void find_top_n_predictions(TrieNode *root, const char *prefix, int n) {
    TrieNode *curr = root;
    for (int level = 0; level < strlen(prefix); level++) {
        int index = char_to_index(prefix[level]);
        if (curr->children[index] == NULL) return;
        curr = curr->children[index];
    }

    char word_buffer[MAX_WORD_LEN];
    strcpy(word_buffer, prefix);
    int count = 0;
    int level = strlen(prefix);  // Initialize level with strlen(prefix)
    find_top_n_predictions_helper(curr, word_buffer, n, level, &count);
}


void load_words_into_trie(TrieNode *root, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: Could not open the file %s\n", file_path);
        return;
    }

    char word[MAX_WORD_LEN];
    while (fgets(word, MAX_WORD_LEN, file)) {
        // Remove newline character from the word
        word[strcspn(word, "\n")] = 0;
        insert(root, word);
    }

    fclose(file);
}

bool search(TrieNode *root, const char *word) {
    TrieNode *curr = root;
    for (int level = 0; level < strlen(word); level++) {
        int index = char_to_index(word[level]);
        if (curr->children[index] == NULL) return false;
        curr = curr->children[index];
    }
    return curr->is_end_of_word;
}

void process_input_word(TrieNode *dictionary, TrieNode *prediction, const char *word) {
    if (search(dictionary, word)) {
        insert(prediction, word);
    }
}

void add_custom_word(TrieNode *prediction, const char *word) {
    insert(prediction, word);
}

// Function to delete a word from the Trie
bool delete_word_helper(TrieNode *node, const char *word, int level) {
    if (node == NULL) return false;

    if (level == strlen(word)) {
        if (node->is_end_of_word) {
            node->is_end_of_word = false;
            return true;
        }
        return false;
    }

    int index = char_to_index(word[level]);
    if (delete_word_helper(node->children[index], word, level + 1)) {
        // Free memory if the node has no children
        bool has_children = false;
        for (int i = 0; i < EXTENDED_ALPHABET_SIZE; i++) {
            if (node->children[i] != NULL) {
                has_children = true;
                break;
            }
        }

        if (!has_children) {
            free(node->children[index]);
            node->children[index] = NULL;
        }
        return true;
    }
    return false;
}

void delete_word(TrieNode *root, const char *word) {
    delete_word_helper(root, word, 0);
}

// Function to edit a word in the Trie (delete the original and insert the modified word)
void edit_word(TrieNode *root, const char *original, const char *modified) {
    delete_word(root, original);
    insert(root, modified);
}

int display_menu() {
    int choice;
    printf("Word Prediction Menu:\n");
    printf("1. Show Top 3 Predictions\n");
    printf("2. Update Prediction Dictionary\n");
    printf("3. Add Custom Word\n");
    printf("4. Edit/Delete Word in Prediction Dictionary\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}