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

// helper function to free hashmap after use
void free_map(hashmap_t hashmap[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        node* current = hashmap[i];
        while(current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

bool check_word(const char* word, hashmap_t hashtable[]) {

    // edge case - if word is all digits, mark as true
    bool digits = true;
    for (int i = 0; i < strlen(word); i++) {
        if (!isdigit(word[i])) {
            digits = false;
        }
    }
    // 'word' must be all digits
    if (digits) return true;

    // start by computing hash
    int bucket = hash_function(word);
    hashmap_t cursor = hashtable[bucket];

    // traverse the list in the event of a hash collision and compare words
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

    //printf("%s \n", lower_case_word);

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

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]) {

    char* words[MAX_MISSPELLED];
    // get buffer size
    long size = 0;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    // reset file pointer
    fseek(fp, 0L, SEEK_SET);

    // add one to size to account for EOF character
    int num_misspelled = 0;
    char buffer[size + 1];
    char* token;

    while (fgets(buffer, (int)size + 1, fp)) {
        token = strtok(buffer, " ");
        while (token != NULL) {
            // handle case where last token character ends in terminating bit
            if(token[strlen(token) - 1] == '\n') {
                // chop off newline character
                token[strlen(token) - 1] = 0;
            }

            // clear punctuation
            if(ispunct(token[0])) token++;
            if(ispunct(token[strlen(token) - 1])) {
                token[strlen(token) - 1] = 0;
                // printf("new token: %s \n", token);
            }

            // check if word exists in dictionary
            if(check_word(token, hashtable) == false) {
                // printf("misspelled! %s index: %d \n", token, num_misspelled);
                words[num_misspelled] = token;
                num_misspelled++;
            }

            // move to next token
            token = strtok(NULL, " ");
            // printf("next token: %s \n", token);
        }
    }

    // copy words array to misspelled
    for(int i = 0; i < num_misspelled; i++) {
        // printf("array item: %s index: %d \n", words[i], i);
        misspelled[i] = words[i];
    }

    return num_misspelled;
}

