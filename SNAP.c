typedef struct SNAP *SNAP;

struct SNAP {

	int 	studentID;
	char*	name;
	char*	address;
	char* 	phone;

	SNAP next;	// to implement linked list properties

};

SNAP new_SNAP(int s, char* n, char* a,  char* p) {
	
	SNAP snap = (SNAP) malloc(sizeof(struct SNAP));

	(*snap).studentID	= s;
	(*snap).name		= n;
	(*snap).address		= a;
	(*snap).phone		= p;

	(*snap).next = NULL;
   
	return snap;

}

// returns tuple from its description as a string
SNAP get_SNAP(char* tuple) {

	char str[300]; 
	strcpy(str,tuple);

	char *pch;

	pch = strtok (str,",><");
	char s[5];
	strcpy(s, pch);

	pch = strtok (NULL,",><");
	char *n = (char*) malloc(50 * sizeof(char));
	strcpy(n, pch);

	pch = strtok (NULL, ",><");
	char *a = (char*) malloc(50 * sizeof(char));
	strcpy(a, pch);

	pch = strtok (NULL, ",><");
	char *p = (char*) malloc( 8 * sizeof(char));
	strcpy(p, pch);
  
	int ID = 0;
	if(s[0] != '*') ID = atoi(s);
 
	return new_SNAP(ID, n, a, p);

}

void print_SNAP(SNAP snap){

	printf("%d\t",		(*snap).studentID);
	printf("\t%s\t",	(*snap).name);
	printf("\t%s\t",	(*snap).address);
	printf("%s\n",		(*snap).phone);
    
}

// primary index on student ID, since student ID is unique
int hash_SNAP(SNAP snap) {

	return (*snap).studentID % 1009;

}

// secondary index on student name, since lookup on name will be frequent
int hash2_SNAP(char* string){

	int c = 12345;
	
	unsigned long hash = 0;
	while (c = *string++) hash = ((hash << 5) + hash) + c;
	return hash % 1009;
    
}

// simple addition to the tail of the link list starting(/including) head
void add_SNAP(SNAP head, SNAP to_add){
    
	if((*head).next == NULL) (*head).next = to_add;
     
	else 			 add_SNAP((*head).next, to_add);
    
}

struct SNAP SNAP_table[1009];
// primary index storage DS
struct bin_tree *SNAP_tree;

void initiate_SNAP() {

	SNAP_tree = new_tree(0, NULL);
 
	for (int i = 0; i < 1009; i = i + 1) {

		SNAP_table[i].studentID = 0;
		SNAP_table[i].name	= (char*) malloc(50 * sizeof(char*));
		SNAP_table[i].address	= (char*) malloc(50 * sizeof(char*));
		SNAP_table[i].phone	= (char*) malloc( 8 * sizeof(char*));

		SNAP_table[i].next = NULL;
	
	}

}

void print_table_SNAP(){

	printf("\nStudentID\t|Name\t\t\t|Address\t|Phone\n");
	
	for (int i = 0; i < 1009; i = i + 1) {
	
	        SNAP curr = &SNAP_table[i];
        	if ((*curr).studentID == 0) continue;

		while (curr != NULL) {

			print_SNAP(curr);
			curr = (*curr).next;
		
		}

	}

}

void add_tree(bin_tree root, SNAP snap) {

	int v	   = (*root).value;
	int to_add = hash2_SNAP((*snap).name);
	int index  = hash_SNAP(snap);

	if (v < to_add) {

		// move right
		bin_tree focus = (*root).right;

		if (focus == NULL) (*root).right = new_tree(to_add, new_node(index));
		else add_tree((*root).right, snap);

	} else if (v > to_add) {

		// move left
		bin_tree focus = (*root).left;

		if (focus == NULL) (*root).left = new_tree(to_add, new_node(index));
		else add_tree((*root).left, snap);

	} else {

		// add to the linked list
		add_node((*root).data, new_node(index));
	}

}

void insert_SNAP(char* tuple){

	SNAP snap = get_SNAP(tuple);    
    	int index = hash_SNAP(snap);

	SNAP curr = &SNAP_table[index];

	if ((*curr).studentID == 0) {

		SNAP_table[index] = *snap;

	} else {

		add_SNAP(&SNAP_table[index], snap);

	}

	add_tree(SNAP_tree, snap);

}

node find(int v, bin_tree root){
    
    int my_value = (*root).value;
    
    if(my_value < v){
        // move right
        bin_tree focus = (*root).right;
        if(focus == NULL){
            printf("invalid query");
            return NULL;
        }
        find(v, focus);
    } else if (my_value > v){
        // move left
        bin_tree focus = (*root).left;
        if(focus == NULL){
            printf("invalid query");
            return NULL;
        }
        find(v, focus);
    } else {
        // add to LinkedList
        return (*root).data;
    }
}

// look up functions for individual attributes
node lookup_SNAP_S(int s){

	node ans = new_node(s % 1009);
	return ans;

}

node lookup_SNAP_N(char* n){

	node ans = find(hash2_SNAP(n), SNAP_tree);
    	return ans;

}

node lookup_SNAP_A(char* a){

	// brute force search
	node ans = new_node(0);

	for (int i = 0; i < 1009; i++){

		SNAP curr = &SNAP_table[i];
		while (curr != NULL) {

			if ((*curr).studentID == 0) continue;

			if (is_equal((*curr).address, a)) {

				if (!contains(ans, i)) add_node(ans, new_node(i));

			}

			curr = (*curr).next;

		}

	}

	return (*ans).next;

}

node lookup_SNAP_P(char* p){

	// brute force search
	node ans = new_node(0);

	for (int i = 0; i < 1009; i++){

		SNAP curr = &SNAP_table[i];
		while (curr != NULL) {

			if ((*curr).studentID == 0) continue;

			if (is_equal((*curr).phone, p)) {

				if (!contains(ans, i)) add_node(ans, new_node(i));

			}

			curr = (*curr).next;

		}

	}

	return (*ans).next;

}

// 'general' look up function
SNAP* lookup_SNAP(char* tuple){
    
	SNAP me = get_SNAP(tuple);
	node ans = fill();

	int found = 0;

	int s = ((*me).studentID  != 0);
	if (s) { // primary index lookup

		node ans_s = lookup_SNAP_S((*me).studentID);
		ans = match_node(ans, ans_s);
		found = found || (ans_s != NULL);

	}

	int n = ((*me).name[0]	  != '*');
	if (n) { // secondary index lookup

		node ans_n = lookup_SNAP_N((*me).name);
		ans = match_node(ans, ans_n);
		found = found || (ans_n != NULL);

	}

	int a = ((*me).address[0] != '*');
	if (a) {

		node ans_a = lookup_SNAP_A((*me).address);
		ans = match_node(ans, ans_a);
		found = found || (ans_a != NULL);

	}

	int p = ((*me).phone[0]   != '*');
	if (p) {

		node ans_p = lookup_SNAP_P((*me).phone);
		ans = match_node(ans, ans_p);
		found = found || (ans_p != NULL);

	}

	if (!found) {

		printf("no matches to %s found\n", tuple);
		return NULL;

	}

	node temp = ans;

	SNAP* ans_SNAP = (SNAP*) malloc(1008 * sizeof(SNAP));
	int count = 0;

	while (temp != NULL) {

		SNAP curr = &SNAP_table[(*temp).data];
		temp = (*temp).next;

		while (curr != NULL) {

			int bs = !s || ((*curr).studentID == (*me).studentID);
			int bn = !n || (is_equal((*curr).name, (*me).name));
			int ba = !a || (is_equal((*curr).address, (*me).address));
			int bp = !p || (is_equal((*curr).phone, (*me).phone));

			if (bs && bn && ba && bp) {

				*(ans_SNAP + count) = curr;
				count = count + 1;

			}

			curr = (*curr).next;

		}

	}

	SNAP last = new_SNAP(0, NULL, NULL, NULL);
	
	*(ans_SNAP + count) = last;

	return ans_SNAP;

}

// delete functions

// locates the 'ancestor' of tuple me in the linked list it is in
SNAP locate_SNAP(SNAP me, SNAP head){

	SNAP temp   = head;
	SNAP parent = head;
    
	// assuming unique studentID
	while ((*temp).studentID != (*me).studentID) {

		parent = temp;
		temp = (*temp).next;
	}

	return parent;

}

// helper function
void deleteh_SNAP(SNAP me){

	int index = hash_SNAP(me);
	SNAP head = &SNAP_table[index];

	if ((*head).studentID == (*me).studentID) {

		if ((*head).next != NULL) {

			SNAP_table[index] = *((*head).next);

		} else {

			SNAP_table[index] = *new_SNAP(0, NULL, NULL, NULL);

		}

	} else {


		SNAP x = locate_SNAP(me, head);
		if (x == NULL) {

			// something has gone wrong
			// this should never happen

		} else {

			(*x).next = (*me).next;

		}

	}
   
}

void delete_SNAP(char* tuple){

	SNAP* to_delete = lookup_SNAP(tuple);
	int count = 0;

	SNAP focus = *(to_delete + count);

	while ((*focus).studentID != 0) {

		deleteh_SNAP(focus);
		count = count + 1;
		focus = *(to_delete + count);

	}
   
}
