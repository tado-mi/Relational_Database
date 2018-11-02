typedef struct CR *CR;

struct CR {
	
	int	id;	// 0 indicates that the given CR does not exist
			// its course and prepeq are NULL
	char*	course;
	char*	room;

	CR next;

};

CR new_CR (char* c, char* r){
    
	CR cr = (CR) malloc(sizeof(struct CR));
    
	(*cr).id = 1;
	(*cr).course = c;
	(*cr).room = r;
	(*cr).next = NULL;
    
	return cr;

}

// returns tuple from its description as a string
CR get_CR(char* tuple) {

	char str[300];
	strcpy(str, tuple);

	char *pch;

	pch = strtok (str, ",><");
	char *c = (char*) malloc(50 * sizeof(char));
	strcpy(c, pch);

	pch = strtok (NULL, ",><");
	char *r = (char*) malloc(50 * sizeof(char));
	strcpy(r, pch);

	return new_CR(c, r);

}

void print_CR(CR cr){

	printf("%s\t", (*cr).course);
	printf("%s\n", (*cr).room);

}

int hash_CR (char* course) {

        int c = 0;

	unsigned long hash = 5381;
        while (c = *course++) hash = ((hash << 5) + hash) + c;
	return hash % 1009;

}

// simple addition to the tail of the link list starting at (/including) head
void add_CR(CR head, CR to_add){
	
	if ((*head).next == NULL) (*head).next = to_add;
	else			  add_CR((*head).next, to_add);
    
}

struct CR CR_table[1009]; 

void initiate_CR(){

	for (int i = 0; i < 1009; i = i + 1) {

		CR_table[i].id		= 0;
		CR_table[i].course	= (char*) malloc (12 * sizeof(char*));
		CR_table[i].room 	= (char*) malloc (12 * sizeof(char*));

		CR_table[i].next	= NULL;

	}

}

void print_table_CR(){

	printf("\nCourse\t|Room\n");

	for (int i = 0; i < 1009; i = i + 1) {

		CR curr = &CR_table[i];
		if ((*curr).id == 0) continue;

		while (curr != NULL) {
			
			print_CR(curr);
			curr = (*curr).next;

		}

	}

}

void insert_CR(char* tuple){

	CR cr = get_CR(tuple);
	int index = hash_CR((*cr).course);

	CR curr = &CR_table[index];

	if ((*curr).id == 0) {

		CR_table[index] = *cr;

	} else {

		add_CR(curr, cr);

	}

}

// look up functions for individual attributes
node lookup_CR_C(char* c){

	node ans = new_node(hash_CR(c));
	return ans;
}

node lookup_CR_R(char* r){

	node ans = new_node(0);
	for (int i = 0; i < 1009; i =  i + 1) {

		CR temp = &CR_table[i];
		if ((*temp).id == 0) continue;

	        while(temp != NULL) { 

			if (is_equal((*temp).room, r)) {

				if (!contains(ans, i)) {

					add_node(ans, new_node(i));

				}

			}

			temp = (*temp).next;

		}

	}

	return (*ans).next;

}

// 'general' look up function
CR* lookup_CR(char* tuple){

	CR me = get_CR(tuple);
	node ans = fill();

	int found = 0;
    
	int c = ((*me).course[0] != '*');
	if (c) {

		node ans_c = lookup_CR_C((*me).course);
		ans = match_node(ans, ans_c);
		found = found || (ans_c != NULL);

	}

	int r = ((*me).room[0] != '*');
	if (r) {

		node ans_r = lookup_CR_R((*me).room);
		ans = match_node(ans, ans_r);
		found = found || (ans_r != NULL);

	}

	if (!found) {

		printf("no matches to %s found\n", tuple);

	}

	node temp = ans;

	CR* ans_CR = (CR*) malloc(1008 * sizeof(CR));
	int count = 0;

	while (temp != NULL) {

		CR curr = &CR_table[(*temp).data];
		temp = (*temp).next;

		while (curr != NULL) {

			int bc = !c || (is_equal((*me).course, (*curr).course));
			int br = !r || (is_equal((*me).room, (*curr).room));

			if (bc && br) {

				*(ans_CR + count) = curr;
				count = count + 1;

			}

			curr = (*curr).next;

		}

	}
        
	CR last = new_CR(NULL, NULL);
	(*last).id = 0;

	*(ans_CR + count) = last;

    	return ans_CR;
    
}
// delete functions

// check equality of two CR tuple instances
int equal_CR(CR cr_1, CR cr_2) {

	int c = is_equal((*cr_1).course, (*cr_2).course);
	if (!c) return 0;
	int p = is_equal((*cr_1).room, (*cr_2).room);
	if (!p) return 0;

	return 1;

}

// locates the 'ancestor' tuple me in the linked list it is in
CR locate_CR(CR me, CR head){

	CR temp   = head;
	CR parent = head;

	if (equal_CR(temp, me)) return NULL;

	while (!equal_CR(temp, me)) {

		parent = temp;
		temp = (*temp).next;

	}

	return parent;
    
}

// helper function
void deleteh_CR(CR me){
   
	int index = hash_CR((*me).course);
	CR head = &CR_table[index];

	if (equal_CR(head, me)) {

		if ((*head).next != NULL) {

			CR_table[index] = *((*head).next);

		} else {

			CR_table[index]    = *new_CR(NULL, NULL);
			CR_table[index].id = 0;

		}

	} else {


		CR x = locate_CR(me, head);
		if (x == NULL) {

		} else {

			(*x).next = (*me).next;
		}

	}

}

void delete_CR(char* tuple){

	CR* to_delete = lookup_CR(tuple);
	int count = 0;

	CR focus = *(to_delete + count);

	while ((*focus).id != 0) {

		deleteh_CR(focus);
		count = count + 1;
		focus = *(to_delete + count);

	}

}
