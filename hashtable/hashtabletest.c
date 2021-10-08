 /* CS50
 * Brian Yu
 *Lab 3, testing file for the hashtable module
 *Usage: ./hashtabletest
 *Purpose: testing the module hashtable through testing normal and edge cases
 *10/8/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"
#include "file.h"

//local function prototypes
static void nameprint(FILE* fp, const char* key, void* item);
static void namedelete(void* item);
static void itemfunc(void* arg, const char* key, void* item);

int main(){

    //Initializing hashtable. The following inserts and deletes execute without memory leak.
    hashtable_t* hashtable1 = hashtable_new(10);

    //allocating memory for the items (allocating memory for item is not done in the module)
    int* first_item = malloc(sizeof(int*));
    int* second_item = malloc(sizeof(int*));
    int* third_item = malloc(sizeof(int*));

    //assigning values
    *first_item = 1;
    *second_item = 2;
    *third_item = 3;

    //assigning values
    const char* first_key = "first";
    const char* second_key = "second";
    const char* third_key = "third";

    //variable to use for the iteration function
    int hash_count = 0;

    //checking if the hashtable was made successfully
    if (hashtable1 == NULL) {
        fprintf(stderr, "bag_new failed for bag1\n");
    return 1;
    }
    else{
        printf("successfully created hashtable1\n");
    }

    //inserting three items into the hashtable
    hashtable_insert(hashtable1, first_key, first_item);
    hashtable_insert(hashtable1, second_key, second_item);
    hashtable_insert(hashtable1, third_key, third_item);

    printf("Should print a hashtable with first-1, second-2, and third-3 \n");
    hashtable_print(hashtable1, stdout, nameprint);


    hashtable_iterate(hashtable1, &hash_count, itemfunc);
    printf("The following number will be '3' if the iteration function is working correctly: %d\n", hash_count);


    hashtable_delete(hashtable1, namedelete);
}

//prtins a name
static void nameprint(FILE* fp, const char* key, void* item){
    int* name = item; 
  if (name == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "[%s,%d],", key, *name); 
  }
}

//deletes a name
static void namedelete(void* item){
    if (item != NULL) {
        free(item);   
    }
}

//updates the count when it encounters a new item
static void itemfunc(void* arg, const char* key, void* item){
    int* nitems = arg;

    if (nitems != NULL && item != NULL && key != NULL)
    (*nitems)++; 
}