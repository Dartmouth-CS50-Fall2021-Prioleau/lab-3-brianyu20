# Grader: Chahak Goyal

## Total points: 95/100

Overall git behavior: 4/5
* -1 for not having .gitignore files in directory or subdirectories

### set: 23/25

Makefile: 3/3
NOTE: Please use flags to make test and valgrind in the future.

Coding style: 2/2

Functionality: 11/12
```set_new```: 1/2
* -1 for not copying the key to node->key. You should copy it to node->key rather than assigning the duplicate of the same key to node->key because it defeats the purpose of copying the key to node->key.
```set_insert```: 2/2
NOTE: You could have used ```set_find``` to check if the key already existed rather than going over the whole set again by looping over it.
```set_find```: 2/2
```set_print```: 2/2
```set_iterate```: 2/2
```set_delete```: 2/2

* -1 for not having enough test cases for all the functions in ```settest.c```

No printfs: 1/1

No global variables: 1/1

Use of 'void*' to store items, 'char*' as keys: 1/1

Check 'NULL' key: 1/1

No change in API: 2/2

No memory leaks and errors: 2/2

### counters: 29/30

Makefile: 3/3 (see comment above)

Coding style: 2/2

Functionality: 12/12
```counters_new```: 2/2
```counters_add```: 2/2
```counters_get```: 2/2
```counters_print```: 2/2
```counters_iterate```: 2/2
```counters_delete```: 2/2

No printfs: 2/2

No global variables: 2/2

Use of integer keys: 2/2

Check if invalid key: 2/2

No change in API: 2/2

No memory leaks and errors: 2/2

-1 for not testing all functions in ```counterstest.c```

### hashtable: 39/40

Makefile: 3/3 (see comment above)

Coding style: 2/2

Functionality: 18/18
```hashtable_new```: 3/3
```hashtable_insert```: 3/3
```hashtable_find```: 3/3
```hashtable_print```: 3/3
```hashtable_iterate```: 3/3
```hashtable_delete```: 3/3

* -1 for not testing all functions in ```hashtabletest.c```

No printfs: 2/2

No global variables: 2/2

Use `void*` to store items, use `char*` as keys: 2/2

Check 'NULL' key: 2/2

No change in API: 2/2

No memory leaks and errors: 2/2