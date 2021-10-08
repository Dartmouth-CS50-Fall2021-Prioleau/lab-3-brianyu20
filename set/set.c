/* 
 * Brian Yu
 * part of lab 3; set
 * 10/5/21
 * set.c - set module
 * Insights into how to handle error cases were gained from bag.c
 * see set.h for more information.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

//local type
typedef struct setnode{
    char* key; 
    struct setnode* next; //pointer to the next node
    void* item; //storing any item 
} setnode_t;

//Global type
typedef struct set{
    struct setnode* head; //pointer to the first (head) node
} set_t;

//local function prototype
static setnode_t* setnode_new (void* item, const char* key);

//creates a new node in the set
static setnode_t* setnode_new (void* item, const char* key){
    
    //allocating memory
    setnode_t* node = malloc(sizeof(setnode_t));
    char* new_copy = malloc((strlen(key)+1)  * sizeof(char));
    //char* new_copy = malloc(sizeof(char*));
    //handling error cases
    if (node == NULL || new_copy == NULL){
        return NULL;
    }
    //if no error, initialize the new setnode
    else{
        strcpy(new_copy, key);
        node->key = new_copy;
        node->item = item;
        node->next = NULL;

        return node;
    }
} 

set_t* set_new(void){
    //allocating memory
    set_t* set = malloc(sizeof(set_t));

    //handling error case
    if (set == NULL){
        return NULL;
    }
    //if no error, initializing the set to null and returning the set
    else{
        set->head = NULL;
        return set;
    }
}

bool set_insert(set_t* set, const char* key, void* item){
    //handling false cases where parameter is null 
    if (set == NULL || key == NULL || item == NULL){
        return false;
    }

    //if the set is empty, create a new node and reset it as the set's head
    if (set->head == NULL){
        set->head = setnode_new(item, key);
        return true;
    }

    setnode_t* last_node; //make a variable to save the last node in the set
    // loop through the set
    for (setnode_t* node = set->head; node != NULL; node = node->next){
        //handling case where the key already exists
        if (node->key == key){
            return false;
        }
        //save the last node in the for loop
        last_node = node;
    }
    //if it hasn't exited the program by now, create a node. 
    setnode_t* new = setnode_new(item,key);
        //handling error cases
        if (new == NULL){
            return false;
        }
        //attach it to the last node and then return true
        
        last_node->next = new;
            return true;

}

void* set_find(set_t* set, const char* key){
    //handling two error cases first
    if (set == NULL || key == NULL){
        return NULL;
    }
    else{
        //loop through the set to find the key, and return the item pointer associated with it
        for (setnode_t* node = set->head; node != NULL; node = node->next){
            if (node->key == key){
                return node->item;
            }
        }
        return NULL;
    }
}

void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ){
    //only print if there is a valid file for writing
    if (fp != NULL){
        
        if (itemprint == NULL){
            fputs("{}\n", fp);
        }
        //handling case where pointer is null
        if (set->head == NULL){
            fputs("(null)\n", fp);
        }
        
        //parsing through the counter set to print to the file 
        else {
            fputs("{", fp);
            for(setnode_t* node = set->head; node != NULL; node = node->next){
                (*itemprint)(fp, node->key, node->item);
            }
            fputs("}\n",fp);
        }   
    }
}

void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)){
    //handling error cases
    if (set != NULL && itemfunc != NULL){
        // call itemfunc with arg, on each item
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->item); 
        }
    }
}

void set_delete(set_t* set, void (*itemdelete)(void* item)){
    //handling two error cases
    if(set != NULL && itemdelete != NULL){
        for (setnode_t* node = set->head; node!= NULL;){
            setnode_t* next = node->next;
            (*itemdelete)(node->item);
            free(node->key);
            free(node);
            node = next;
        }
        free(set);
    }
}