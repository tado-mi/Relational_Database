# showing off:

Code written by [Andrew Nyaisonga](https://github.com/AndrewNyaisonga) and [Lusine Keshishyan / tado-mi](https://github.com/tado-mi), implemented in November 2017.

Following is a brute, hard-coded implementation of a Relational Database in C, for a course taken at the University of Rochester. It is made public to demonstrate a code sample by the authors, and for learning. We trust it will not be used to violate academic honesty policies. We followed the relational database described in [FOCS](http://infolab.stanford.edu/~ullman/focs/ch08.pdf).<br/>

We implemented data structures of a **binary tree**, **linked list** (general) and a **hash table** (custom to each relation). As an independently implemented data structure, linked list stores an **int**, representing indeces. the data stored in a binary tree node is a linked list, corresponding to indeces of all the entries that belong in that node of the binary tree in the hash table.

each of the implemented relation acts as a linked list as well, having a pointer to an 'object' of the same data type and is used to address collisions.

# included files:

## supplement_func.c

implementation of 3 simple functions to be used in the relational database.<br/>

**fill():** returns a linked list filled filled with data of numbers 0 to 1009. 1009 is the hardcoded size of all the hash tables.

## operation.c

Hardcoded functions to answer queries of certain form.

## bin_tree.c

a simple [tree](https://en.wikipedia.org/wiki/Binary_tree) data structure.<br\>
sorting is addressed when implementing "insert" functions of the relations that use a secondary index (such as SNAP).

## linked_list.c

a simple [linked list](https://en.wikipedia.org/wiki/Linked_list) data structure.

# compiling

hit on the terminal

	make
	make run
	make clean

equivalent to:

	gcc main.c -o main.out
	./main.out
	rm main.out

# future aspirations

- [ ] create a generic data structure of a tuple, that supports primary and secondary indexing, select, project and join operations
- [ ] handle invalid queries
