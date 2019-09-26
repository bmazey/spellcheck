//
// Created by Brandon on 9/26/2019.
//

#include "spell.c"
#include "dictionary.h"

hashmap_t hashmap[HASH_SIZE];

int main() {
    bool loaded = load_dictionary("C:\\Users\\Brandon\\CLionProjects\\spellcheck\\wordlist.txt", hashmap);
    printf(loaded ? "true" : "false");
}
