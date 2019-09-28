//
// Created by Brandon on 9/26/2019.
//

#include "spell.c"
#include "dictionary.h"

hashmap_t hashmap[HASH_SIZE];
char * misspelled[MAX_MISSPELLED];

// helper function to print loaded dictionary hashtable list values
void printList(struct node* n)
{
    while (n != NULL) {
        printf(" %s \n", n->word);
        n = n->next;
    }
}

int main() {
    // use below for WSL profile
    // bool loaded = load_dictionary("/home/bmazey/wordlist.txt", hashmap);

    // default Cygwin profile
    bool loaded = load_dictionary("C:\\Users\\Brandon\\CLionProjects\\spellcheck\\wordlist.txt", hashmap);
    printf(loaded ? "true" : "false");

    bool exists = check_word("12356", hashmap);
    printf(exists ? "true \n" : "false \n");

    // use below for WSL profile
    // FILE* test_file = fopen("/home/bmazey/test1.txt", "r");

    // default Cygwin profile
    FILE* test_file = fopen("C:\\Users\\Brandon\\CLionProjects\\spellcheck\\test1.txt", "r");

    int num_misspelled = check_words(test_file, hashmap, misspelled);
    printf("%d \n", num_misspelled);

    // close the file
    fclose(test_file);

    // free memory to clear Valgrind leak
    free_map(hashmap);

    // TODO - write tests
    // TODO - fix travis
    // TODO - fuzz
    // TODO - write report

    return 0;
}
