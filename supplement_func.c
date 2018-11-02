int is_equal(char* str_1, char* str_2){

	int max  = strlen(str_1);
	if (max != strlen(str_2)) return 0;

	for (int i = 0; i < max; i = i + 1) {

		if (*(str_1 + i) != *(str_2 + i)) return 0;

	}

	return 1;

}

node fill(){

	node ans = new_node(0);

	for (int i = 1; i < 1009; i = i + 1){
	
	        add_node(ans, new_node(i));
	
	}

	return ans;
}

char* concat(const char* str_1, const char* str_2){

    char* str = malloc(strlen(str_1) + strlen(str_2) + 1);

    strcpy(str, str_1);
    strcat(str, str_2);

    return str;

}
