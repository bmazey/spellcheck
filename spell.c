//
// Created by Brandon on 9/26/2019.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "dictionary.c"

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

    printf("%s \n", word);

    int bucket = hash_function(word);
    hashmap_t cursor = hashtable[bucket];
    while(cursor != NULL) {
        if(strcmp(word, cursor->word) == 0) return true;
        cursor = cursor->next;
    }

    // make lower case
    char lower_case_word[strlen(word)];
    for(int i = 0; i < strlen(word); i++) {
        lower_case_word[i] = tolower(word[i]);
    }

    // add null character at end of string apparently ...
    lower_case_word[strlen(word)] = '\0';

    printf("%s \n", lower_case_word);

    // recalculate hash
    bucket = hash_function(lower_case_word);
    cursor = hashtable[bucket];

    // check against new word
    while(cursor != NULL) {
        if(strcmp(lower_case_word, cursor->word) == 0) return true;
        cursor = cursor->next;
    }

    // no possible match!
    return false;
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

    // iterate and add words to hashtable ... stop at EOF
    char word[LENGTH];
    while (fscanf(dict_file, "%s", word) > 0) {
        hashmap_t new_node = malloc(sizeof(node));
        new_node->next = NULL;
        strcpy(new_node->word, word);
        int bucket = hash_function(new_node->word);

        if(hashtable[bucket] == NULL) {
            hashtable[bucket] = new_node;
        }
        else {
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
    }
    // close file
    fclose(dict_file);

    // assuming everything works, return true
    return true;
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

    int num_misspelled = 0;
    char buffer[LENGTH];
    char * token;
    char * word;
    while (fgets(buffer, LENGTH, fp)) {
        token = strtok(buffer, " ");

        while (token != NULL) {
            printf("%s\n", token);
            //word = clear_punctuation(token);
            //if(!check_word(word, hashtable)) {
                //strcpy(*misspelled, word);
                //num_misspelled++;
            //}
            //printf("%s\n", word);
            token = strtok(NULL, " ");
        }
    }

    return num_misspelled;
}

