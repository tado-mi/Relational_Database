typedef struct bin_tree *bin_tree;
struct bin_tree {

	int value;	// for storing the secondary index
	node data;	// for storing the 'pointers' to the tuples sharing the same secondary index
	
	bin_tree right;
	bin_tree left;

};

bin_tree new_tree(int v, node list){

	bin_tree me = (bin_tree) malloc(sizeof(struct bin_tree));

	(*me).value	= v;
	(*me).data	= list;
	(*me).right	= NULL;
	(*me).left 	= NULL;

	return me;
}

// standard in order traversal
void print_tree(bin_tree root){

	if ((*root).left != NULL) print_tree((*root).left);

	printf("%d:", (*root).value);
	printf("\n\t");
	print_node((*root).data);

	if ((*root).right != NULL) print_tree((*root).right);
    }
