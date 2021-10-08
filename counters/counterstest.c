 /* CS50
 * Brian Yu
 *Lab 3, testing file for the counters module
 *Usage: ./counterstest
 *Purpose: testing the module counters through testing normal and edge cases
 *largely taken from the bag module
 *10/8/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "file.h"


static void itemfunc(void* arg, const int key, const int count);

int main(){


    counters_t* counters1 = NULL;           // one bag

    //variable to use later for the iterable function
    int counters_count = 0;

    //initializing first bag
    printf("Create first bag...\n");
    counters1 = counters_new();
    
    //checking if the counters was made successfully
    if (counters1 == NULL) {
        fprintf(stderr, "bag_new failed for bag1\n");
    return 1;
    }
    else{
        printf("successfully created counters1\n");
    }

    //adding items to the counters1
    counters_add(counters1, 1);
    counters_add(counters1, 2);
    printf("Should print a counters with one 1 and one 2\n");
    counters_print(counters1, stdout);
    

    //checking if the count of the key updates correctly
    counters_add(counters1, 1);
    counters_add(counters1, 3);
    printf("\nShould print two 1's, one 2, and one 3\n");
    counters_print(counters1, stdout);

    //checking the counters_set function
    counters_set(counters1, 5, 2);
    counters_set(counters1, 1, 5);
    counters_set(counters1, 5, -1); //checking that it doesn't take negative counts
    printf("\nShould print five 1's, two 5's, one 2, and one 3\n");
    counters_print(counters1,stdout);

    counters_iterate(counters1, &counters_count, itemfunc);
    printf("\nthere are %d items in this counters, which is correct\n", counters_count);

    //checking the counters_get fucntion
    int value_got;
    value_got = counters_get(counters1, 5);
    printf("\nShould print 2\n");
    printf("%d\n", value_got);  

    //deleting to make sure that there are no memory leaks
    counters_delete(counters1);
    

}

static void itemfunc(void* arg, const int key, const int count){
    int* nitems = arg;
    if (nitems != NULL){
        (*nitems)++;
    }
}