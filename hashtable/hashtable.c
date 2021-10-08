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
#include "hashtable.h"
#include "hash.h"
#include "../set/set.h"

//defining the hashtable
typedef struct hashtable{
    int num_slots;
    set_t** table;

}hashtable_t;

hashtable_t* hashtable_new(const int num_slots){
    //handling error cases
    if (num_slots > 0){
        //allocate memory for the hashtable
        hashtable_t* new = malloc(sizeof(hashtable_t));
        if (new == NULL){
            return NULL;
        }
        else{
            new->num_slots = num_slots;
            //using calloc to initialize all the values to zero
            new->table = calloc(num_slots, sizeof(size_t));
            if (new->table != NULL){
                for (int i = 0; i < num_slots; i++){
                //the slots in the table will have a link to a set
                new->table[i] = set_new();
                }
                return new;
            }
            return NULL;
        }
    }return NULL;
}

bool hashtable_insert(hashtable_t* ht, const char* key, void* item){
    //handling error cases
    if (ht == NULL || key == NULL || item == NULL){
        return false;
    }
    //use the hash_jenkins to get the hash value, and use that to insert it into the appropriate set
    else{
         int hash = hash_jenkins(key, ht->num_slots);
         set_insert(ht->table[hash], key, item);
         return true;
    }
}

void* hashtable_find(hashtable_t* ht, const char* key){
    //handling error cases
    if (ht == NULL || key == NULL){
        return NULL;
    }
    else{
        //using the hashvalue to find it in the according set
        int hash = hash_jenkins(key, ht->num_slots);
        return set_find(ht->table[hash], key);
    }
}

void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)){
    //handling error cases
    if (fp != NULL){
        if (ht == NULL){
            fprintf(fp, "(null)");
        }
        if (itemprint == NULL){
            for (int i = 0; i < ht->num_slots; i++){
                fprintf(fp, "%d\n", i); //interpreted "one line per hash slot, with no items, if NULL itemprint." as such. 
            }
        }
        for (int i = 0; i < ht->num_slots; i++){
            set_print(ht->table[i], fp, itemprint);
        }
    }
}

void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)){
    //handling error cases
    if (ht != NULL && itemfunc != NULL && arg != NULL){
        // call itemfunc with arg, on each item
        for (int i = 0; i < ht->num_slots; i++) {
            set_iterate(ht->table[i], arg, itemfunc);
        }
    }
}

void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item)){
    if (ht != NULL){
        if (itemdelete != NULL){
            for (int i = 0; i < ht->num_slots; i++){
                set_delete(ht->table[i], itemdelete);
            }
            // need to free both the tables and the hashtable itself
            free(ht->table);
            free(ht);
        }
    }
}






