//
// Created by Brandon on 9/26/2019.
//

#include "spell.c"
#include "dictionary.h"

hashmap_t hashmap[HASH_SIZE];
char * mispelled[MAX_MISSPELLED];

// helper function to print loaded dictionary hashtable list values
void printList(struct node* n)
{
    while (n != NULL) {
        printf(" %s \n", n->word);
        n = n->next;
    }
}

int main() {
    bool loaded = load_dictionary("C:\\Users\\Brandon\\CLionProjects\\spellcheck\\wordlist.txt", hashmap);
    //printf(loaded ? "true" : "false");

    //for(int i = 0; i < HASH_SIZE; i++) {
        //printList(hashmap[i]);
    //}

    bool exists = check_word("chAperon", hashmap);
    printf(exists ? "true \n" : "false \n");

    FILE* test_file = fopen("C:\\Users\\Brandon\\CLionProjects\\spellcheck\\test1.txt", "r");

    int num_misspelled = check_words(test_file, hashmap, mispelled);
    printf("%d \n", num_misspelled);
}
