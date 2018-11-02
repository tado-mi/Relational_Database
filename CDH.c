typedef struct CDH *CDH;

struct CDH {
	
	int   id;
	char* course;
	char* day;
	char* hour;

	CDH next;

};

CDH new_CDH(char* c, char* d, char *h) {

	CDH cdh = (CDH) malloc(sizeof(struct CDH));

	(*cdh).id	= 1;

	(*cdh).course	= c;
	(*cdh).day	= d;
	(*cdh).hour	= h;

	(*cdh).next = NULL;
	
	return cdh;

}

// returns a tuple from its description as a string
CDH get_CDH(char* tuple) {

	char str[300];
	strcpy(str, tuple);

	char *pch;

	pch = strtok (str, ",><");
	char *c = (char*) malloc(12 * sizeof(char));
	strcpy(c, pch);

	pch = strtok (NULL, ",><");
	char *d = (char*) malloc(12 * sizeof(char));
	strcpy(d, pch);

	pch = strtok(NULL, ",><");
	char *h = (char*) malloc(12 * sizeof(char));
	strcpy(h, pch);

	return new_CDH(c, d, h);

}

void print_CDH(CDH cdh){
	
	printf("%s\t",	(*cdh).course);
	printf("%s\t",	(*cdh).day);
	printf("%s\n",	(*cdh).hour);
    
}

// primary index on both course and day
int hash_CDH(CDH cdh) {

        char *both = concat((*cdh).course, (*cdh).day);

        int c = 0;
	unsigned long hash = 5381;
        while (c = *both++) hash = ((hash << 5) + hash) + c; 
            
	return hash % 1009;
}

// secondary index on both day and hour
int hash2_CDH(CDH cdh) {

	char *both = concat((*cdh).day, (*cdh).hour);

	int c = 0;
	unsigned long hash = 5381;
        while (c = *both++) hash = ((hash << 5) + hash) + c; 

	return hash % 1009;

}

// simple addition to the tail of the linked starting at head
void add_CDH(CDH head, CDH to_add) {

	if ((*head).next == NULL) (*head).next = to_add;

	else			  add_CDH((*head).next, to_add);

}

struct CDH CDH_table[1009]; 
// primary index storage DS
struct bin_tree *CDH_tree;

void initiate_CDH(){
 
	CDH_tree = new_tree(0, NULL);
	for (int i = 0; i < 1009; i = i + 1){

		CDH_table[i].id		= 0;
		CDH_table[i].course	= (char*) malloc(12 * sizeof(char*));
	        CDH_table[i].day	= (char*) malloc(12 * sizeof(char*));
        	CDH_table[i].hour	= (char*) malloc(12 * sizeof(char*));
	        CDH_table[i].next	= NULL;
	}

}

void print_table_CDH(){

	printf("\nCourse\t|Day\t|Hour\n");

	for (int i = 0; i < 1009; i = i + 1) {

		CDH curr = &CDH_table[i];
		if ((*curr).id == 0) continue;

		while (curr != NULL) {

			print_CDH(curr);
			curr = (*curr).next;			

		}

	}

}

void add_tree_CDH(bin_tree root, CDH cdh){

	int v		= (*root).value;
	int to_add	= hash2_CDH(cdh);
	int index	= hash_CDH(cdh);

	if (v < to_add) {

		// move right
		bin_tree focus = (*root).right;

		if (focus == NULL) (*root).right = new_tree(to_add, new_node(index));
		else add_tree_CDH((*root).right, cdh);

	} else if (v > to_add) {
		
		// move left
		bin_tree focus = (*root).left;
		
		if (focus == NULL) (*root).left = new_tree(to_add, new_node(index));
		else add_tree_CDH((*root).left, cdh);

	} else {

		// add to the linked list
		add_node((*root).data, new_node(index));

	}

}

void insert_CDH(char* tuple){

	CDH cdh = get_CDH(tuple);
	int ind = hash_CDH(cdh);

	add_tree_CDH(CDH_tree, cdh);    
   
	CDH temp = &CDH_table[ind];

	if ((*temp).id == 0) {

		CDH_table[ind] = *cdh;

	} else {

		add_CDH(temp, cdh);

	}
   
}

node find_CDH(int v, bin_tree root) {

	return find(v, root);
	// note:
	// although implemented for SNAP, find is a simple binary search

}

// look up functions for individual attributes
node lookup_CDH_C(char* c){

	// brute force search
	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

	        CDH temp = &CDH_table[i];
		if ((*temp).id == 0) continue;

		while (temp != NULL) {

			if (is_equal((*temp).course, c)) {
				
				add_node(ans, new_node(i));

			}

			temp = (*temp).next;

		}

	}

	return (*ans).next;

}

node lookup_CDH_D(char* d){

	// brute force search
	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

	        CDH temp = &CDH_table[i];
		if ((*temp).id == 0) continue;

		while (temp != NULL) {

			if (is_equal((*temp).day, d)) {
				
				add_node(ans, new_node(i));

			}

			temp = (*temp).next;

		}

	}

	return (*ans).next;

}

node lookup_CDH_H(char* h){

	// brute force search
	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

	        CDH temp = &CDH_table[i];
		if ((*temp).id == 0) continue;

		while (temp != NULL) {

			if (is_equal((*temp).hour, h)) {
				
				add_node(ans, new_node(i));

			}
			
			temp = (*temp).next;

		}

	}

	return (*ans).next;

}

// 'general' look up function
CDH* lookup_CDH(char* tuple) {

	CDH cdh = get_CDH(tuple);
	node ans = fill();

	int found = 0;

	int c = ((*cdh).course[0] != '*');
	int d = ((*cdh).day[0]	  != '*');
	int h = ((*cdh).hour[0]	  != '*');

	if (c && d) { // primary index look up

		node ans_cd = new_node(hash_CDH(cdh));
		ans = match_node(ans, ans_cd);
		found = found || (ans_cd != NULL);

	} else if (d && h) { // secondary index look up

		node ans_dh = find(hash2_CDH(cdh), CDH_tree);
		// note: although find was written for SNAP, it is a simple binary search
		//	 that can be applied to any binary tree
		ans = match_node(ans, ans_dh);
		found = found || (ans_dh != NULL);


	} else {

		if (c) {

		node ans_c = lookup_CDH_C((*cdh).course);
		ans = match_node(ans, ans_c);
		found = found || (ans_c != NULL);

		}
		
		if (d) {

		node ans_d = lookup_CDH_D((*cdh).day);
		ans = match_node(ans, ans_d);
		found = found || (ans_d != NULL);

		}

		if (h) {

		node ans_h = lookup_CDH_H((*cdh).hour);
		ans = match_node(ans, ans_h);
		found = found || (ans_h != NULL);

		}

	}

	if (!found) {

		printf("no matches to %s found\n", tuple);
		return NULL;

	}

	node temp = ans;

	CDH* ans_CDH = (CDH*) malloc(1008 * sizeof(CDH));
	int count = 0;

	while (temp != NULL) {

		CDH curr = &CDH_table[(*temp).data];
		temp = (*temp).next;

		while (curr != NULL) {

			int bc = !c || is_equal((*curr).course, (*cdh).course);
			int bd = !d || is_equal((*curr).day, (*cdh).day);
			int bh = !h || is_equal((*curr).hour, (*cdh).hour);

			if (bc && bd && bh) {

				*(ans_CDH + count) = curr;
				count = count + 1;

			}

			curr = (*curr).next;

		}

	}

	CDH last = new_CDH(NULL, NULL, NULL);
	(*last).id = 0;

	*(ans_CDH + count) = last;
	return ans_CDH;

}

// delete functions

// locates the 'ancestor of tuple me in the linked list it is in
int equal_CDH(CDH cdh_1, CDH cdh_2) {

	int c = is_equal((*cdh_1).course, (*cdh_2).course);
	if (!c) return 0;

	int d = is_equal((*cdh_1).day, (*cdh_2).day);
	if (!d) return 0;

	int h = is_equal((*cdh_1).hour, (*cdh_2).hour);
	if (!h) return 0;

	return 1;

}

CDH locate_CDH(CDH me, CDH head){
    
	CDH temp	= head;
	CDH parent	= head;

	while (!equal_CDH(me, temp)) {

		parent = temp;
		temp = (*temp).next;

	}

	return parent;

}

void deleteh_CDH(CDH me){
   
	int index = hash_CDH(me);
	CDH head = &CDH_table[index];

	if (equal_CDH(head, me)) {

		if ((*head).next != NULL) {

			CDH_table[index] = *((*head).next);

		} else {

			CDH_table[index] = *new_CDH(NULL, NULL, NULL);
			CDH_table[index].id = 0;
    
		}

	} else {

		CDH x = locate_CDH(me, head);
		if (x == NULL) {

		} else {

			(*x).next = (*me).next;

		}

	}

}

void delete_CDH(char* tuple) {

	CDH* to_delete = lookup_CDH(tuple);
	int count = 0;

	CDH focus = *(to_delete + count);

	while ((*focus).id != 0) {

		deleteh_CDH(focus);
		count = count + 1;
		focus = *(to_delete + count);

	}

}
