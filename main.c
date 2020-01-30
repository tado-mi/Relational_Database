#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

// simple utility function for user/file input
void insert(char* tuple, char* relation) {

	if (is_equal(relation, "CSG"))  insert_CSG(tuple);
	if (is_equal(relation, "SNAP")) insert_SNAP(tuple);
	if (is_equal(relation, "CP"))   insert_CP(tuple);
	if (is_equal(relation, "CDH"))  insert_CDH(tuple);
	if (is_equal(relation, "CR"))   insert_CR(tuple);

}

void read(char* filename) {

	char* relation = (char*) malloc(strlen(filename) * sizeof(char));
	int i = 0;
	while (*(filename + i) != '.') {

		relation[i] = filename[i];
		i = i + 1;

	}
	relation[i] = '\0';

	FILE *file = fopen(filename, "r");

	if (file != NULL) {

		char line[200];
		while (fgets(line, sizeof line, file) != NULL) insert(line, relation);

	}

	fclose(file);

}

void print_database() {

	print_table_CSG();
	print_table_SNAP();
	print_table_CP();
	print_table_CDH();
	print_table_CR();

}

int main(){

	initiate_CSG();
	read("in/CSG.txt");

	initiate_SNAP();
	read("in/SNAP.txt");

	initiate_CP();
	read("in/CP.txt");

	initiate_CDH();
	read("in/CDH.txt");

	initiate_CR();
	read("in/CR.txt");

	printf("DATABASE:\n");
	print_database();
	printf("\n");

	printf("sample query 1:\n");
	nc_g("L. Van Pelt","CS101");

	printf("sample query 2:\n");
	ndh_r("C. Brown", "Tu", "10AM");

	return 0;

}
