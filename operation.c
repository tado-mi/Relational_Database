// hardcoded function to answer queries
// "what did _name_ get in _course_?"
void nc_g(char* name, char* c) {

	char* course = concat("<", concat(c, ","));

	// obtain student ID
	// create tuple <*,name,*,*>
	char* str = concat("<*,", concat(name, ",*,*>"));
	SNAP* snap_arr = lookup_SNAP(str);

	// extract student id
	int count = 0;
	SNAP snap = *(snap_arr + count);

	while ((*snap).studentID != 0) {

		char focusID[12];
		sprintf(focusID, "%d", (*snap).studentID);

		count = count + 1;
		snap  = *(snap_arr + count);

		char* temp = concat(course, concat(focusID, ",*>" ));

		CSG* csg_arr = lookup_CSG(temp);

		// print grades
		int j = 0;
		CSG csg = *(csg_arr + j);
		while ((*csg).studentID != 0) {

			printf("%s has received a %s in %s;\n", name, (*csg).grade, c);
			j = j + 1;
			csg = *(csg_arr + j);

		}

	}

}

// "where is _name_ on _day_ at _hour_?", assuming they are at a class
void ndh_r(char* name, char* day, char* hour){

	// obtain student ID
	// create tuple <*, name, *, *>
	char* str  = concat("<*,", concat(name, ",*,*>"));
	SNAP* snap_arr = lookup_SNAP(str);

	// obtain courses _name_ takes from their studentID
	CSG* csg_arr = (CSG*) malloc(1008 * sizeof(CSG));
	int csg_count = 0;

	int count = 0;
	SNAP focus = *(snap_arr + count);
	while ((*focus).studentID != 0) {

		char focusID[12];
		sprintf(focusID, "%d", (*focus).studentID);

		count = count + 1;
		focus = *(snap_arr + count);

		// create tuple <*, studentID, *>
		char* tuple = concat("<*,", concat(focusID, ",*>"));
		CSG*  arr   = lookup_CSG(tuple);

		int j = 0;
		CSG csg_focus = *(arr + j);

		while ((*csg_focus).studentID != 0) {

			*(csg_arr + csg_count) = csg_focus;
			csg_count = csg_count + 1;

			j = j + 1;
			csg_focus = *(arr + j);		

		}

	}

	// csg_count is the number of found csg tuples

	// obtain courses happening at day, hour
	char* temp = concat(concat(day, ","), concat(hour, ">"));
	char* str_ = concat("<*,", temp);
	CDH*  cdh_arr = lookup_CDH(str_);

	// look for correspondance
	count = 0;

	while (count < csg_count) {

		CSG focus_ = *(csg_arr + count);
		char* course_focus = (*focus_).course;

		int j = 0;
		CDH cdh = *(cdh_arr + j);
		while ((*cdh).id != 0) {

			if (is_equal(course_focus, (*cdh).course)) {

				// look up the room
				CR* cr_arr = lookup_CR(concat("<", concat(course_focus, ",*>")));
				int k = 0;
				CR cr = *(cr_arr + k);
				while ((*cr).id != 0) {

					printf("%s is in %s on %s at %s\n", name, (*cr).room, day, hour);
					k = k + 1;
					cr = *(cr_arr + k);

				}

			}

			j = j + 1;
			cdh = *(cdh_arr + j);

		}

		count = count + 1;

	}

}


