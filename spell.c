//
// Created by Brandon on 9/26/2019.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// global variables
#define LENGTH 45
#define HASH_SIZE 2000
#define MAX_MISSPELLED 1000

// defining hashmap pointer
typedef node* hashmap_t;


bool check_word(const char* word, hashmap_t hashtable[]) {
//    Set int bucket to the output of hash_function(word).
//            Set hashmap_t cursor equal to hashmap[bucket].
//            While cursor is not NULL:
//    If word equals cursor->word:
//    return True.
//            Set curosr to cursor->next.
//            Set int bucket to the output of hash_function(word).
//            Set hashmap_t cursor equal to hashmap[bucket].
//            While cursor is  not NULL:
//    If lower_case(word) equals curosr->word:
//    return True.
//            Set curosr to cursor->next.
//    return False.
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
//    Initialize all values in hash table to NULL.
//            Open dict_file from path stored in dictionary.
//            If dict_file is NULL:
//    return false.
//            While word in dict_file is not EOF (end of file):
//    Set hashmap_t new_node to a new node.
//            Set new_node->next to NULL.
//            Set new_node->word equal to word.
//            Set int bucket to hash_function(word).
//    if hashtable[bucket] is NULL:
//    Set hashtable[bucket] to new_node.
//    else:
//    Set new_node->next to hashtable[bucket].
//            Set hashtable[bucket] to new_node.
//            Close dict_file.

    // set all values in hashtable to null
    for (int i = 0; i < HASH_SIZE; i++) {
        hashtable[i] = NULL;
    }

    // open the file
    FILE* dict_file = fopen(dictionary_file, "r");
    if(dict_file == NULL) return false;
    else return true;

}

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
//    Set int num_misspelled to 0.
//    While line in fp is not EOF (end of file):
//    Read the line.
//            Split the line on spaces.
//            For each word in line:
//    Remove punctuation from beginning and end of word.
//            If not check_word(word):
//    Append word to misspelled.
//            Increment num_misspelled.
//            Return num_misspelled.
}

