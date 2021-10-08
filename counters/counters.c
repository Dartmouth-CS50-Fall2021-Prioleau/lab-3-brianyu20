/* 
 * Brian Yu
 * part of lab 3; counterset
 * 10/4/21
 * counters.c - counters module
 * see counters.h for more information.
 * Insights into how to handle error cases were gained from bag.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "mem.h"

// Local type
typedef struct counternode {
    int item; //pointer to this data
    struct counternode* next; //pointer to the next item
    int count; //pointer to the number of times this item has occured
} counternode_t;

//Global type
typedef struct counters {
    struct counternode* head;
} counters_t;

//local function prototype
static counternode_t* counternode_new(const int key);

counters_t* counters_new(void){
    counters_t* counters = mem_malloc(sizeof(counters_t));

    if (counters == NULL){
        return NULL;
    }
    else {
        //set the head to null here (initialized empty)
        counters->head = NULL;
        return counters;
    }

} 

int counters_add(counters_t* ctrs, const int key){
    if (ctrs == NULL || key < 0){
        return 0;
    }
    if (ctrs->head == NULL){
        ctrs->head = counternode_new(key);
        return ctrs->head->count;
    }
    else {
        //loop through the nodes
        counternode_t* last_node;
        for(counternode_t* node = ctrs->head; node != NULL; node = node->next){
            //if the key is already there, only increment the counter for the key.
            if (key == node->item){
                node->count++;
                return node->count; 
            }
            last_node = node;    
        }
        //if the key is not already there, create a new node and have the last item point to the new node
        counternode_t* new_node = counternode_new(key);
        last_node->next = new_node;
        return new_node->count; 
    }
}

// local function, not visible outside this file
static counternode_t*  counternode_new(const int key){
  counternode_t* node = mem_malloc(sizeof(counternode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } 
  else {
    node->item = key;
    node->next = NULL;
    node->count = 1;
    return node;
  }
}

int counters_get(counters_t* ctrs, const int key){
    //defensive coding
    if (ctrs == NULL || key < 0){
        return 0;
    }
    else {
        //loop through the counterset
        for(counternode_t* node = ctrs->head; node != NULL; node = node->next){
            //if the key exists in the counterset, return the count of that node
            if (node->item == key){
                return node->count;
            }
            
        }
        return 0;
    }
}

bool counters_set(counters_t* ctrs, const int key, const int count){
    //defensive coding
    if (ctrs == NULL || key < 0 || count < 0){
        return false;
    } //how to account for 'out of memory'?
    else{
        counternode_t* last_node; //creating variable to save the last node to add a potential new node to the end of the set
        //looping through
        for(counternode_t* node = ctrs->head; node != NULL; node = node->next){
            //if the key exists, update the count
            if (key == node->item){
                node->count = count;
                return true;
            }  
            last_node = node;
        } //exit for-loop
        counternode_t* new_node = counternode_new(key);// make a new counternode
        last_node->next = new_node;// use the variable created earlier on to add the new node to the end of the set
        new_node->count = count;// set the count as count
        return true; 
    }

}

void counters_print(counters_t* ctrs, FILE* fp){
    //only print if there is a valid file for writing
    if (fp != NULL){
        //handling case where pointer is null
        if (ctrs == NULL){
            fputs("(null)", fp);
        }
        //parsing through the counter set to print to the file 
        else {
            fputs("{", fp);
            for(counternode_t* node = ctrs->head; node != NULL; node = node->next){
                fprintf(fp, "[%d:%d],", node->item, node->count);
            }
            fputs("}",fp);
        }   
    }
}

void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count)){
    if (ctrs != NULL && itemfunc != NULL){
        // call itemfunc with arg, on each item
        for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->item, node->count); 
        }
    }
}

void counters_delete(counters_t* ctrs){
    if (ctrs != NULL){
        //need to save the next node within the for-loop to not lose the next pointer when the memory is freed.
        //For the above reason, the third clause in the for loop is not there to move the pointer within the for-loop
        for (counternode_t* node = ctrs->head; node != NULL;){
            counternode_t* next = node->next;
            mem_free(node);
            node = next;
        }
        mem_free(ctrs);
    }
}




