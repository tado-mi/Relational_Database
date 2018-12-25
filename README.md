# showing off:

**author:** Andrew Nyaisonga, Lusine Keshishyan / tado-mi

**date:**   28 Nov 2017

**use:**    free. credit when due is encouraged and appreciated

# general

the included closely follows the relational database described in [FOCS](http://infolab.stanford.edu/~ullman/focs/ch08.pdf). it is a hard coded implementation (spesific to the given database) with a significant amount of copy-paste. <br\>

we implemented data structures of a **binary tree**, **linked list** (general) and a **hash table** (custom to each relation). As an independetly impleneted data structure, linked list stores an **int**, representing indeces. the data stored in a binary tree node is a linked list, corresponding to indeces of all the entries that belong in that node of the binary tree in the hash table.

each of the implemented relation acts as a linked list as well, having a pointer to an 'object' of the same data type and is used to address collisions.

# included files:

## supplement_func.c

implementation of 3 simple functions to be used in the relational database.<br/>

**fill():** returns a linked list filled filled with data of numbers 0 to 1009. 1009 is the hardcoded size of all the hash tables.

## operation.c

two hardcoded functions to answer queries of certain form.

## bin_tree.c

a simple [tree](https://en.wikipedia.org/wiki/Binary_tree) data structure.<br\>
sorting is addressed when implementing "insert" functions of the relations that use a secondary index.

## linked_list.c

a simple [linked list](https://en.wikipedia.org/wiki/Linked_list) data structure.

## relations

we will discuss **SNAP.c**, since all the relations are implemented with the same logic and following the same 'template', and SNAP is the most complicated one.

### SNAP.c

-- coming soon

# compiling

hit on the terminal

	make
	make run
	make clean

equivalent to:

	gcc main.c -o main
	./main
	rm main

# future aspirations

* create a generic data structure of a tuple, that supports primary and secondary indexing, select, project and join operations
* handle invalid queries
