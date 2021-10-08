 /* CS50
 * Brian Yu
 *Lab 3, testing file for the set module
 *Usage: ./settest
 *Purpose: testing the module set through testing normal and edge cases
 *Largely taken from the bag module
 *10/8/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "file.h"

static void nameprint(FILE* fp, const char* key, void* item);
static void namedelete(void* item);
static void itemfunc(void* arg, const char* key, void* item);

int main(){
  
  //allocating memory and initializing the items and keys to go in the set
  const char* string_pointer1 = NULL;
  const char* string_pointer2 = NULL;
  const char* string_pointer3 = NULL;
  int* item_pointer1 = malloc(sizeof(int*));
  int* item_pointer2 = malloc(sizeof(int*));
  int* item_pointer3 = malloc(sizeof(int*));

  int set_count = 0;

  set_t* set1 = NULL;

  set1 = set_new();

  //checking to make sure that set is made
  if (set1 == NULL) {
        fprintf(stderr, "set_new failed for set1\n");
    return 1;
    }
    else{
        printf("successfully created set1\n");
    }


  //assigning values
  string_pointer1 = "programming";
  string_pointer2 = "math";
  string_pointer3 = "philosophy";
  *item_pointer1 = 256;  
  *item_pointer2 = 101;
  *item_pointer3 = 2;
  
  printf("Nothing is added yet, should print null\n");
  set_print(set1,stdout,nameprint); //checking to print null


  //inserting the key items into the set
  set_insert(set1, string_pointer1, item_pointer1);
  set_insert(set1, string_pointer2, item_pointer2);
  set_insert(set1, string_pointer3, item_pointer3);

  printf("Should print 256, 101, 2 inside the set\n"); 
  set_print(set1,stdout,nameprint);

  set_iterate(set1, &set_count, itemfunc);
  printf("Printing the number of items in thes set, it should be 3 and it is:%d", set_count);
  

  set_delete(set1, namedelete);
    
}
/* count the non-null items in the bag.
 * note here we don't care what kind of item is in bag.
 */
static void itemfunc(void* arg, const char* key, void* item)
{
  int* nitems = arg;

  //the iterable function that calls item func already loops through the set, so no need to loop again here
  if (nitems != NULL && item != NULL && key != NULL)
    (*nitems)++; 
}

// print a name, in quotes.
void nameprint(FILE* fp, const char* key, void* item)
{
  int* name = item; 
  if (name == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "[%d],", *name); 
  }
}

// delete a name 
void namedelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}