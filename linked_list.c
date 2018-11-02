typedef struct node *node;
struct node {

	int  data;
	node next;

};

node new_node(int d) {

	node me = (node) malloc(sizeof(struct node));

	(*me).data = d;
	(*me).next = NULL;

	return me;

}

node print_node(node me){

	node temp = me;

	printf("{ ");

	while (temp != NULL){

 		printf("%d ", (*temp).data);
		temp = (*temp).next;

	}

	printf("}");

}

void add_node(node head, node to_add){

	if((*head).next == NULL) (*head).next = to_add;    

	else			 add_node((*head).next, to_add);

}

int contains(node head, int data) {

	node temp = head;

	while (temp != NULL) {

		if ((*temp).data == data) return 1;
		temp = (*temp).next;

	}

	return 0;

}

int list_length(node head) {

	node temp = head;
	int  ans = 0;

	while (temp != NULL) {

		ans = ans + 1;
		temp = (*temp).next;

	}

	return ans;

}

// returns a list containing all the elements contained both in list_1 and list_2
node match_node(node list_1, node list_2){
    
	int len  = list_length(list_1);
	int len_ = list_length(list_2);

	if (len > len_) return match_node(list_2, list_1);

	node temp = list_1;
	node ans = new_node(0);

	// assume list_1 is shorter than list_2
	for (int i = 0; i < len; i = i + 1) {
		
		if (contains(list_2, (*temp).data)) {

			node n = new_node((*temp).data);
			add_node(ans, n);

		}

		temp = (*temp).next;

	}

	return (*ans).next; // ignore the initial 0
   
}
