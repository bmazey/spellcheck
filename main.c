//
// Created by Brandon on 9/26/2019.
//

#include "spell.c"
#include "dictionary.h"

hashmap_t hashmap[HASH_SIZE];

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
    printf(exists ? "true" : "false");
}
