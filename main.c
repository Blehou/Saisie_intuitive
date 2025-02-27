
#include <stdio.h>
#include "predictiveText.h"
int main() {
    TrieNode *dictionary = create_node();
    TrieNode *prediction = create_node();

    load_words_into_trie(dictionary, "liste_francais.txt");
    load_words_into_trie(prediction, "mots_courants.txt");
    
    int choice;
    char prefix[MAX_WORD_LEN];
    char input_word[MAX_WORD_LEN];
    char custom_word[MAX_WORD_LEN];
    char original_word[MAX_WORD_LEN];
    char modified_word[MAX_WORD_LEN];

    /*vshfbgvioubvzb uavbubfvbhcvbpaubfvefhvfvb */

    do {
        choice = display_menu();

        switch (choice) {
            case 1:
                printf("Enter the prefix: ");
                scanf("%s", prefix);
                printf("Top 3 Predictions:\n");
                find_top_n_predictions(prediction, prefix, 3);
                break;
            case 2:
                printf("Enter the word: ");
                scanf("%s", input_word);
                process_input_word(dictionary, prediction, input_word);
                printf("Prediction dictionary updated.\n");
                break;
            case 3:
                printf("Enter the custom word: ");
                scanf("%s", custom_word);
                add_custom_word(prediction, custom_word);
                printf("Custom word added to the prediction dictionary.\n");
                break;
            case 4:
                printf("Enter the word to edit/delete: ");
                scanf("%s", original_word);
                printf("Enter the modified word or leave blank to delete: ");
                scanf("%s", modified_word);
                if (strlen(modified_word) > 0) {
                    edit_word(prediction, original_word, modified_word);
                    printf("Word updated in the prediction dictionary.\n");
                } else {
                    delete_word(prediction, original_word);
                    printf("Word deleted from the prediction dictionary.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice, try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character left by scanf
        getchar(); // Wait for the user to press Enter

    } while (choice != 0);

    return 0;
}
















