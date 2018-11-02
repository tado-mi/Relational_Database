typedef struct CSG *CSG;

struct CSG {

	char*	course;
	int	studentID;
	char*	grade;

	CSG next; 	// to implement linked list properties

};

CSG new_CSG(char* c, int s, char* g){
    
    CSG csg = (CSG) malloc(sizeof(struct CSG));
    
    (*csg).course	= c;
    (*csg).studentID	= s;
    (*csg).grade	= g;

    (*csg).next = NULL;
    
    return csg;

}

// returns tuple from its description as a string
CSG get_CSG(char* tuple) {

	char str[100]; 
	strcpy(str,tuple);

	char *pch;

	pch = strtok (str, ",><");
	char *c = (char*) malloc(5 * sizeof(char));
	strcpy(c, pch);

	pch = strtok (NULL, ",><");
	char *s = (char*) malloc(5 * sizeof(char));
	strcpy(s, pch);
	if (s[0] == '*') s = "0";

	pch = strtok (NULL, ",><");
	char *g = (char*) malloc(2 * sizeof(char));
	strcpy(g, pch);
	
	return new_CSG(c, atoi(s), g);
	   	
}

void print_CSG(CSG csg){
    
	printf("%s\t",		(*csg).course);
	printf("\t%d\t",	(*csg).studentID);
	printf("\t%s\n",	(*csg).grade);
    
}

int hash_CSG (char *c, int s){

        unsigned long hash = 5381;
        while (s = *c++) hash = ((hash << 5) + hash) + s; 
        return hash % 1009;
}

// simple addition to the tail of the link list starting(/including) head
void add_CSG(CSG head, CSG to_add){
    
	if ((*head).next == NULL) (*head).next = to_add;
     	
	else			  add_CSG((*head).next, to_add);
}

struct CSG CSG_table[1009]; 

void initiate_CSG() {

	for (int i = 0; i < 1009; i = i + 1) {

		CSG_table[i].studentID	= 0;
		CSG_table[i].course	= (char*) malloc(12 * sizeof(char*));
		CSG_table[i].grade	= (char*) malloc( 2 * sizeof(char*));

		CSG_table[i].next = NULL;

	}

}

void print_table_CSG(){

	printf("\nCourse\t\t|StudentID\t|Grade\n");

	for (int i = 0; i < 1009; i = i + 1){

		CSG curr = &CSG_table[i];
		if ((*curr).studentID == 0) continue;

		while (curr != NULL) {
			
			print_CSG(curr);
			curr = (*curr).next;

		}

	}

}

void insert_CSG(char* tuple){

	CSG csg = get_CSG(tuple);

	int ind = hash_CSG((*csg).course, (*csg).studentID);
	CSG current = &CSG_table[ind];

	if ((*current).studentID == 0){ // the cell is empty

	        CSG_table[ind] = *csg;

	} else {			// there is a collision

	        add_CSG(current, csg);

	}
}

// look up functions for individual attributes
node lookup_CSG_C (char* c){

	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

		CSG curr = &CSG_table[i];
		if ((*curr).studentID == 0) continue;

		while (curr != NULL) {

			if (is_equal((*curr).course, c)) {
				
				if (!contains(ans, i)) add_node(ans, new_node(i));

			}

			curr = (*curr).next;

		}

	}

	return (*ans).next; // skip the initial 0

}

node lookup_CSG_S (int s){

	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

		CSG curr = &CSG_table[i];
		if ((*curr).studentID == 0) continue;

		while (curr != NULL) {

			if ((*curr).studentID == s) {
				
				if (!contains(ans, i)) add_node(ans, new_node(i));

			}

			curr = (*curr).next;

		}

	}

	return (*ans).next; // skip the initial 0

}

node lookup_CSG_G (char* g){

	node ans = new_node(0);

	for (int i = 0; i < 1009; i = i + 1) {

		CSG curr = &CSG_table[i];
		if ((*curr).studentID == 0) continue;

		while (curr != NULL) {

			if (is_equal((*curr).grade, g)) {
				
				if (!contains(ans, i)) add_node(ans, new_node(i));

			}

			curr = (*curr).next;

		}

	}

	return (*ans).next; // skip the initial 0

}

// 'general' look up function
CSG* lookup_CSG(char* tuple){
    
	CSG  me = get_CSG(tuple);
   	node ans = fill();

	int found = 0;

	int c = ((*me).course[0] != '*');
	int s = ((*me).studentID != 0);

	if (c && s) {

		int index = hash_CSG((*me).course, (*me).studentID);
		node ans_cs = new_node(index);
		ans = match_node(ans, ans_cs);
		found = found || (ans_cs != NULL);

	} else if (c) {
		
		node ans_c = lookup_CSG_C((*me).course);
		ans = match_node(ans, ans_c);
		found = found || (ans_c != NULL);

	} else if (s) {

		node ans_s = lookup_CSG_S((*me).studentID);
		ans = match_node(ans, ans_s);
		found = found || (ans_s != NULL);

	}

	int g = ((*me).grade[0]  != '*');
	if (g) {

		node ans_g = lookup_CSG_G((*me).grade);
		ans = match_node(ans, ans_g);
		found = found || (ans_g !=  NULL);

	}

	if (!found) {

		printf("no matches to %s found\n", tuple);
		return NULL;

	}
 
    	node temp = ans;

	CSG* ans_CSG = (CSG*) malloc(1008 * sizeof(CSG));
	int count = 0;

    	while (temp != NULL) {

		CSG curr = &CSG_table[(*temp).data];
		temp = (*temp).next;

		while (curr != NULL) {

			int bc = !c || is_equal((*curr).course, (*me).course);
			int bs = !s || ((*curr).studentID == (*me).studentID);
			int bg = !g || is_equal((*curr).grade,  (*me).grade);

			if (bc && bs && bg) {

				*(ans_CSG + count) = curr;
				count = count + 1;

			}

			curr = (*curr).next;

		}
        
 	}

	CSG last = new_CSG(NULL, 0, NULL);
	
	*(ans_CSG + count) = last;
    
	return ans_CSG;
    
}

// delete functions

// locates the 'ancestor' of tuple me in the linked list it is in
CSG locate_CSG(CSG me, CSG head){

	CSG temp   = head;
	CSG parent = head;

	// assuming unique studentID as course-studentID is a key
	while ((*temp).studentID != (*me).studentID) {

		parent = temp;
		temp = (*temp).next;
	}
    
	return parent;

}

// helper function
void deleteh_CSG(CSG me){

	int ind = hash_CSG((*me).course, (*me).studentID);
	CSG head = &CSG_table[ind];

	if ((*head).studentID == (*me).studentID) {

		if ((*head).next != NULL) {

			CSG_table[ind] = *((*head).next);

		} else {

			CSG_table[ind] = *new_CSG(NULL, 0, NULL);

		}

	} else {


		CSG x = locate_CSG(me, head);
		if (x == NULL) {

			// something has gone wrong
			// this should never happen

		} else {

			(*x).next = (*me).next;

		}

	}
   
}

void delete_CSG(char* tuple){

	CSG* to_delete = lookup_CSG(tuple);
	int count = 0;

	CSG focus = *(to_delete + count);

	while ((*focus).studentID != 0) {

		deleteh_CSG(focus);
		count = count + 1;
		focus = *(to_delete + count);

	}
    
}
