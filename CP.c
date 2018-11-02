typedef struct CP *CP;

struct CP {
	
	int	id;	// 0 indicates that the given CP does not exist
			// its course and prepeq are NULL
	char*	course;
	char*	prereq;

	CP next;

};

CP new_CP (char* C, char* P){
    
	CP cp = (CP) malloc(sizeof(struct CP));
    
	(*cp).id = 1;
	(*cp).course = C;
	(*cp).prereq = P;
	(*cp).next = NULL;
    
	return cp;

}

// returns tuple from its description as a string
CP get_CP(char* tuple) {

	char str[300];
	strcpy(str, tuple);

	char *pch;

	pch = strtok (str, ",><");
	char *c = (char*) malloc(50 * sizeof(char));
	strcpy(c, pch);

	pch = strtok (NULL, ",><");
	char *p = (char*) malloc(50 * sizeof(char));
	strcpy(p, pch);

	return new_CP(c, p);

}

void print_CP(CP cp){

	printf("%s\t", (*cp).course);
	printf("%s\n", (*cp).prereq);

}

int hash_CP (char* course) {

        int c = 0;

	unsigned long hash = 5381;
        while (c = *course++) hash = ((hash << 5) + hash) + c;
	return hash % 1009;

}

// simple addition to the tail of the link list starting at (/including) head
void add_CP(CP head, CP to_add){
	
	if ((*head).next == NULL) (*head).next = to_add;
	else			  add_CP((*head).next, to_add);
    
}

struct CP CP_table[1009]; 

void initiate_CP(){

	for (int i = 0; i < 1009; i = i + 1) {

		CP_table[i].id		= 0;
		CP_table[i].course	= (char*) malloc (12 * sizeof(char*));
		CP_table[i].prereq 	= (char*) malloc (12 * sizeof(char*));

		CP_table[i].next	= NULL;

	}

}

void print_table_CP(){

	printf("\nCourse\t|Prerequisite\n");

	for (int i = 0; i < 1009; i = i + 1) {

		CP curr = &CP_table[i];
		if ((*curr).id == 0) continue;

		while (curr != NULL) {
			
			print_CP(curr);
			curr = (*curr).next;

		}

	}

}

void insert_CP(char* tuple){

	CP cp = get_CP(tuple);
	int index = hash_CP((*cp).course);

	CP curr = &CP_table[index];

	if ((*curr).id == 0) {

		CP_table[index] = *cp;

	} else {

		add_CP(curr, cp);

	}

}

// look up functions for individual attributes
node lookup_CP_C(char* c){

	node ans = new_node(hash_CP(c));
	return ans;
}

node lookup_CP_P(char* p){

	node ans = new_node(0);
	for (int i = 0; i < 1009; i =  i + 1) {

		CP temp = &CP_table[i];
		if ((*temp).id == 0) continue;

	        while(temp != NULL) { 

			if (is_equal((*temp).prereq, p)) {

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
CP* lookup_CP(char* tuple){

	CP me = get_CP(tuple);
	node ans = fill();

	int found = 0;
    
	int c = ((*me).course[0] != '*');
	if (c) {

		node ans_c = lookup_CP_C((*me).course);
		ans = match_node(ans, ans_c);
		found = found || (ans_c != NULL);

	}

	int p = ((*me).prereq[0] != '*');
	if (p) {

		node ans_p = lookup_CP_P((*me).prereq);
		ans = match_node(ans, ans_p);
		found = found || (ans_p != NULL);

	}

	if (!found) {

		printf("no matches to %s found\n", tuple);

	}

	node temp = ans;

	CP* ans_CP = (CP*) malloc(1008 * sizeof(CP));
	int count = 0;

	while (temp != NULL) {

		CP curr = &CP_table[(*temp).data];
		temp = (*temp).next;

		while (curr != NULL) {

			int bc = !c || (is_equal((*me).course, (*curr).course));
			int bp = !p || (is_equal((*me).prereq, (*curr).prereq));

			if (bc && bp) {

				*(ans_CP + count) = curr;
				count = count + 1;

			}

			curr = (*curr).next;

		}

	}
        
	CP last = new_CP(NULL, NULL);
	(*last).id = 0;

	*(ans_CP + count) = last;

    	return ans_CP;
    
}
// delete functions

// check equality of two CP tuple instances
int equal_CP(CP cp_1, CP cp_2) {

	int c = is_equal((*cp_1).course, (*cp_2).course);
	if (!c) return 0;
	int p = is_equal((*cp_1).prereq, (*cp_2).prereq);
	if (!p) return 0;

	return 1;

}

// locates the 'ancestor' tuple me in the linked list it is in
CP locate_CP(CP me, CP head){

	CP temp   = head;
	CP parent = head;

	if (equal_CP(temp, me)) return NULL;

	while (!equal_CP(temp, me)) {

		parent = temp;
		temp = (*temp).next;

	}

	return parent;
    
}

// helper function
void deleteh_CP(CP me){
   
	int index = hash_CP((*me).course);
	CP head = &CP_table[index];

	if (equal_CP(head, me)) {

		if ((*head).next != NULL) {

			CP_table[index] = *((*head).next);

		} else {

			CP_table[index]    = *new_CP(NULL, NULL);
			CP_table[index].id = 0;

		}

	} else {


		CP x = locate_CP(me, head);
		if (x == NULL) {

		} else {

			(*x).next = (*me).next;
		}

	}

}

void delete_CP(char* tuple){

	CP* to_delete = lookup_CP(tuple);
	int count = 0;

	CP focus = *(to_delete + count);

	while ((*focus).id != 0) {

		deleteh_CP(focus);
		count = count + 1;
		focus = *(to_delete + count);

	}

} 

