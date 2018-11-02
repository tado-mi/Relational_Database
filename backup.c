#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int length(char* s){
    int ans = 0;
    while(*s){
        ans++;
        s++;
    }
    return ans;
}

int isEqual(char* i, char* j){
    
    int max = length(i);
    if (max != length(j)){
        return 0;
    }
    
    for(int f = 0; f < max; f++){
        if(i[f] != j[f]){
            return 0;
        }
    }
    
    return 1;
    
}

// Linked List of ints
typedef struct LinkedNode *LinkedNode;
struct LinkedNode{
  int data;
  LinkedNode next;
};

LinkedNode newLinkedNode(int d){
    LinkedNode me = (LinkedNode) malloc(sizeof(struct LinkedNode));
    (*me).data = d;
    (*me).next = NULL;
    return me;
}

LinkedNode printLinkedNode(LinkedNode me){
    printf("{ ");
    while(me != NULL){
        printf("%d ", (*me).data);
        me = (*me).next;
    }
    printf("}\n\n");
}

void addLinkedNode(LinkedNode i, LinkedNode j){
    if((*i).next == NULL){
        (*i).next = j;    
    } else {
        addLinkedNode((*i).next, j);
    }
}

int containsLink(LinkedNode l, int i){
    while(l != NULL){
        if((*l).data == i){
            return 1;
        }
        l = (*l).next;
    }
    return 0;
}

int linkLength(LinkedNode l){
    int ans = 0;
    while(l != NULL){
        ans = ans + 1;
        l = (*l).next;
    }
    return ans;
}

LinkedNode matchLinkedNode(LinkedNode i, LinkedNode j){
    
    LinkedNode ans = newLinkedNode(0);
    
    int i_length = linkLength(i);
    int j_length = linkLength(j);
    
    if (i_length > j_length){
        for(int f = 0; f < j_length; f++){
            if(containsLink(i, (*j).data)){
                addLinkedNode(ans, newLinkedNode((*j).data));
            }
            
            j = (*j).next;
        }
    } else {
        for(int f = 0; f < i_length; f++){
            if(containsLink(j, (*i).data)){
                addLinkedNode(ans, newLinkedNode((*i).data));
            }
            i = (*i).next;
        }
    }
    
    return (*ans).next;
}

// Binary tree for secondary index
typedef struct BinTreeNode *BinTreeNode;
struct BinTreeNode{
    int value; // secondary index
    LinkedNode data; // pointers to tuples sharing same secondary index
    BinTreeNode right;
    BinTreeNode left;
};

BinTreeNode newBinTreeNode(int v, LinkedNode l){
    BinTreeNode me = (BinTreeNode) malloc(sizeof(struct BinTreeNode));
    (*me).value = v;
    (*me).data = l;
    (*me).right = NULL;
    (*me).left = NULL;
    return me;
}

void printBinTree(BinTreeNode root){
    if((*root).left != NULL){
        printBinTree((*root).left);
    }
    printf("%d:\n", (*root).value);
    printLinkedNode((*root).data);
    if((*root).right != NULL){
        printBinTree((*root).right);
    }
}

int hashfunction_CSG(char *Course, int id,int size_table){
        unsigned long hash = 5381;
       
        while (id = *Course++)
            hash = ((hash << 5) + hash) + id; 
            
    return hash%size_table;
}

//CSG table struct 
typedef struct CSG *CSG;
CSG newCSG(char* c, int s, char* g);
struct CSG{
    char* Course;
    int StudentId ;
    char* Grade;
    CSG next;
};
struct CSG CSG_table[1009]; 

void initiate_CSG(){
    for(int i=0;i<1009;i++){
        CSG_table[i].StudentId = 0;
        CSG_table[i].Course = (char*) malloc(12*sizeof(char*));
        CSG_table[i].Grade = (char*) malloc(2*sizeof(char*));
        CSG_table[i].next = NULL;
     }
}

void addLinkCSG(CSG first, CSG link){
    
    if((*first).next == NULL){
        (*first).next = link;
     
    } else {
        addLinkCSG((*first).next, link);
    }
    
}

CSG newCSG(char* c, int s, char* g){
    
    CSG csg = (CSG) malloc(sizeof(struct CSG));
    
    csg->Course = c;
    csg->StudentId = s;
    csg->Grade = g;
    csg->next = NULL;
    
    return csg;
}

void insertCSG(char* tuple){
    
    char * newCourse = (char*) malloc(5*sizeof(char));
    char *grade= (char*) malloc(2*sizeof(char));
    char Id[5];
    char str[100]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL, ",><");
    strcpy(Id,pch);
    pch = strtok (NULL, ",><");
    strcpy(grade,pch);
  
    
    
    int id = atoi(Id);
    
    CSG temp = newCSG(newCourse,id,grade);
           
    int index = hashfunction_CSG(newCourse,id,1009);
    
    CSG current = &CSG_table[index];
    if(current->StudentId == 0){
        CSG_table[index] = *temp;
    } else {
        addLinkCSG(&CSG_table[index], temp);
    }
}

void printCSG(CSG x){
    
    printf("%s\t", (*x).Course);
    printf("\t%d\t", (*x).StudentId);
    printf("\t%s\n", (*x).Grade);
    
    if ((*x).next != NULL){
        printCSG((*x).next);
    }
    
}

// creating the table
struct CSG CSG_table[1009];

void printTABLE_CSG(){
    
    printf("\nCourse \t|StudentID\t|Grade\n");
    for (int i = 0; i < 1009; i++){
        CSG current = &CSG_table[i];
        if(current->StudentId != 0){
            //printf("%d:", i);
            printCSG(&CSG_table[i]);
        }
     
    }
}

// lookup
LinkedNode fill(){
    LinkedNode ans = newLinkedNode(0);
    for (int i = 1; i < 1009; i++){
        addLinkedNode(ans, newLinkedNode(i));
    }
    return ans;
}

LinkedNode lookup_CSG_C(char* c){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CSG temp = &CSG_table[i];
        while(temp != NULL){
            if((*temp).StudentId != 0 && isEqual((*temp).Course, c)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CSG_S(int s){

    LinkedNode ans = newLinkedNode(0);

    for(int i = 0; i < 1009; i++){
        CSG temp = &CSG_table[i];
        while(temp != NULL){
            if((*temp).StudentId == s){
                addLinkedNode(ans, newLinkedNode(i));
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CSG_G(char* g){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CSG temp = &CSG_table[i];
        
        while(temp!= NULL){
            if((*temp).StudentId != 0 && isEqual((*temp).Grade, g)){
                addLinkedNode(ans, newLinkedNode(i));
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CSG(char* tuple){
    
    printf("query: %s\n", tuple);
    
    char * newCourse = (char*) malloc(5*sizeof(char));
    char *grade= (char*) malloc(2*sizeof(char));
    char Id[5];
    char str[100]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL, ",><");
    strcpy(Id,pch);
    pch = strtok (NULL, ",><");
    strcpy(grade,pch);
    
    int id = 0;
    if (!(Id[0] == '*')) {
        id = atoi(Id);
    }
    
    CSG me = newCSG(newCourse,id,grade);

    int boolean_course = ((*me).Course[0] != '*');
    int boolean_id = ((*me).StudentId != 0);
    int boolean_grade = ((*me).Grade[0] != '*');
 
    
    LinkedNode ans = fill();

    if (boolean_course && boolean_id){
        ans = matchLinkedNode(ans, newLinkedNode(hashfunction_CSG((*me).Course, (*me).StudentId, 1009)));
    } else if(boolean_course){
        LinkedNode c = lookup_CSG_C((*me).Course);
        ans = matchLinkedNode(ans, c);
    } else if(boolean_id){
        LinkedNode s = lookup_CSG_S((*me).StudentId);
        ans = matchLinkedNode((*ans).next, s);
    }
    
    if (boolean_grade){
        LinkedNode g = lookup_CSG_G((*me).Grade);
        ans = matchLinkedNode(ans, g);
    }
    
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
    }

    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        CSG temp = &CSG_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).StudentId == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int bs = !boolean_id || ((*temp).StudentId == (*me).StudentId);
            int bg = !boolean_grade || isEqual((*temp).Grade, (*me).Grade);
            CSG temp_next = (*temp).next;
            if(bc && bs && bg){
                if((*temp).StudentId != 0){
                   printf("%s\t", (*temp).Course);
                   printf("\t%d\t", (*temp).StudentId);
                   printf("\t%s\n", (*temp).Grade);    
                }
            }
            
            temp = temp_next;
        }
        
    }
    
    return ans1;
    
}

CSG findCSG_prev(CSG me){
    
    int index = hashfunction_CSG((*me).Course, (*me).StudentId, 1009);
    
    CSG cell = &CSG_table[index];
    CSG parent = cell;
    
    // assuming unique StudentId as Course-StudentId is a key
    if ((*cell).StudentId == (*me).StudentId){
        printf("no parrent\n");
        return NULL;
    }
    
    while((*cell).StudentId != (*me).StudentId){
        parent = cell;
        cell = (*cell).next;
    }
    
    return parent;
}

void deleteCSG_helper(CSG me){
   
    int index = hashfunction_CSG((*me).Course, (*me).StudentId, 1009);
    CSG first = &CSG_table[index];
    
    // if the tuple is the first in LinkedList
    if ((*first).StudentId == (*me).StudentId){
        // reassign
        if ((*first).next != NULL) {
        CSG new_first = (*first).next;
        CSG_table[index] = *new_first;
        } else {
            CSG_table[index] = *newCSG(NULL, 0, NULL);
        }
        
    } else {
        CSG x = findCSG_prev(me);
        if (x == NULL){
            printf("tuple not found");
        } else {
            (*x).next = (*me).next;
        }
    }
    
}

int delete_CSG(char* tuple){
    
    printf("deleting: %s from CSG\n", tuple);
    
    char * newCourse = (char*) malloc(5*sizeof(char));
    char *grade= (char*) malloc(2*sizeof(char));
    char Id[5];
    char str[100]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL, ",><");
    strcpy(Id,pch);
    pch = strtok (NULL, ",><");
    strcpy(grade,pch);
    
    int id = 0;
    if (!(Id[0] == '*')) {
        id = atoi(Id);
    }
    
    CSG me = newCSG(newCourse,id,grade);

    int boolean_course = ((*me).Course[0] != '*');
    int boolean_id = ((*me).StudentId != 0);
    int boolean_grade = ((*me).Grade[0] != '*');
 
    
    LinkedNode ans = fill();

    if(boolean_course){
        LinkedNode c = lookup_CSG_C((*me).Course);
        ans = matchLinkedNode(ans, c);
    }
    
    if (boolean_id){
        LinkedNode s = lookup_CSG_S((*me).StudentId);
        ans = matchLinkedNode((*ans).next, s);
    }
    
    if (boolean_grade){
        LinkedNode g = lookup_CSG_G((*me).Grade);
        ans = matchLinkedNode(ans, g);
    }
    
    printf("resulting relation: \n");
    
    if (ans == NULL){
        printf("%s was not found\n", tuple);
        return 0;
    }

    while(ans != NULL){
        
        CSG temp = &CSG_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).StudentId == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int bs = !boolean_id || ((*temp).StudentId == (*me).StudentId);
            int bg = !boolean_grade || isEqual((*temp).Grade, (*me).Grade);
            CSG temp_next = (*temp).next;
            if(bc && bs && bg){
                if((*temp).StudentId != 0){
                   deleteCSG_helper(temp);
                }
            }
            
            temp = temp_next;
        }
        
    }
    
    printTABLE_CSG();
    
    return 1;
}

//SNAP 
typedef struct SNAP *SNAP;
void addBinTreeNode_SNAP(BinTreeNode root, SNAP snap);
struct SNAP{
    int StudentId;
    char* Name;
    char*Address;
    char* Phone;
    SNAP next;
};
// SNAP Bin Tree
// hash function: N -> secondary index

struct SNAP SNAP_table[1009];
struct BinTreeNode *SNAP_Tree;
int hashfunction_SNAP(SNAP snap){
    return (*snap).StudentId%1009;
}

void addLinkSNAP(SNAP first, SNAP link){
    
    if((*first).next == NULL){
     
        (*first).next = link;
     
    } else {
     
        addLinkSNAP((*first).next, link);
     
    }
    
}
SNAP newSNAP(int s, char* N, char* A,  char* P){
    SNAP snap = (SNAP) malloc(sizeof(struct SNAP));
    snap->Name = N;
    snap->StudentId = s;
    snap->Address = A;
    snap->Phone = P;
    snap->next = NULL;
   
    return snap;
}

void insertSNAP(char* tuple){
    
    char * newName = (char*) malloc(50*sizeof(char));
    char * newAdd = (char*) malloc(50*sizeof(char));
    char * newPhone = (char*) malloc(8*sizeof(char));
    char Id[5];
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(Id,pch);
    pch = strtok (NULL,",><");
    strcpy(newName,pch);
    pch = strtok (NULL, ",><");
    strcpy(newAdd,pch);
    pch = strtok (NULL, ",><");
    strcpy(newPhone,pch);
  
    //printf("%c\n",grade[1]);
    
    int id = atoi(Id);
    
    SNAP temp = newSNAP(id,newName,newAdd,newPhone);
           
    int index = id%1009;
    
    SNAP current = &SNAP_table[index];
    if(current->StudentId == 0){
        SNAP_table[index] = *temp;
    } else {
        addLinkSNAP(&SNAP_table[index], temp);
    }
    addBinTreeNode_SNAP(SNAP_Tree, temp);
}

void printSNAP(SNAP x){
    printf("%d\t", (*x).StudentId);
    printf("\t%s\t", (*x).Name);
    printf("\t%s\t", (*x).Address);
    printf("%s\n", (*x).Phone);
    
    if ((*x).next != NULL){
        printSNAP((*x).next);
    }
    
}

void printTABLE_SNAP(){
    printf("\nStudentID \t| \t Name \t| \t\tAddress \t| \tPhone\n");
    for (int i = 0; i < 1009; i++){
        SNAP current = &SNAP_table[i];
        if(current->StudentId != 0){
            //printf("%d:", i);
            printSNAP(&SNAP_table[i]);
        }
    }
}

void initiate_SNAP(){
    for(int i=0;i<1009;i++){
        SNAP_table[i].StudentId = 0;
        SNAP_table[i].Name = (char*) malloc(50*sizeof(char*));
        SNAP_table[i].Address = (char*) malloc(50*sizeof(char*));
        SNAP_table[i].Phone = (char*) malloc(8*sizeof(char*));
        SNAP_table[i].next = NULL;
     }
     
}

int hashfunction2_SNAP(char* string){
    unsigned long hash = 0;
        
    int c = 12345;
    while (c = *string++)
        hash = ((hash << 5) + hash) + c;
            
    return hash % 1009;
    
}

void addName_LinkedNode_SNAP(LinkedNode head, SNAP snap){
    if((*head).next == NULL){
        (*head).next = newLinkedNode(hashfunction_SNAP(snap));
    } else {
        addName_LinkedNode_SNAP((*head).next, snap);
    }
}

void addBinTreeNode_SNAP(BinTreeNode root, SNAP snap){
    int my_value = (*root).value;
    int new_value = hashfunction2_SNAP((*snap).Name);
    if(my_value < new_value){
        // move right
        BinTreeNode focus = (*root).right;
        if(focus == NULL){
            (*root).right = newBinTreeNode(new_value, newLinkedNode(hashfunction_SNAP(snap)));
        } else {
            addBinTreeNode_SNAP((*root).right, snap);
        }
    } else if (my_value > new_value){
        // move left
        BinTreeNode focus = (*root).left;
        if(focus == NULL){
            (*root).left = newBinTreeNode(new_value, newLinkedNode(hashfunction_SNAP(snap)));
        } else {
            addBinTreeNode_SNAP((*root).left, snap);
        }
    } else {
        // add to LinkedList
        addName_LinkedNode_SNAP((*root).data, snap);
    }
}

LinkedNode findBinTree(int v, BinTreeNode root){
    
    int my_value = (*root).value;
    
    if(my_value < v){
        // move right
        BinTreeNode focus = (*root).right;
        if(focus == NULL){
            printf("invalid query");
            return NULL;
        }
        findBinTree(v, focus);
    } else if (my_value > v){
        // move left
        BinTreeNode focus = (*root).left;
        if(focus == NULL){
            printf("invalid query");
            return NULL;
        }
        findBinTree(v, focus);
    } else {
        // add to LinkedList
        return (*root).data;
    }
}

LinkedNode lookup_SNAP_S(int s){

    LinkedNode ans = newLinkedNode(s % 1009);

    return ans;
}

LinkedNode lookup_SNAP_N(char* n){

    LinkedNode ans = findBinTree(hashfunction2_SNAP(n), SNAP_Tree);

    return ans;
}

LinkedNode lookup_SNAP_A(char* a){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        SNAP temp = &SNAP_table[i];
        while(temp != NULL){
            if((*temp).StudentId != 0 && isEqual((*temp).Address, a)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_SNAP_P(char* p){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        SNAP temp = &SNAP_table[i];
        while(temp != NULL){
            if((*temp).StudentId != 0 && isEqual((*temp).Phone, p)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_SNAP(char* tuple){
    
    printf("query: %s\n", tuple);
    
    char * newName = (char*) malloc(50*sizeof(char));
    char * newAdd = (char*) malloc(50*sizeof(char));
    char * newPhone = (char*) malloc(8*sizeof(char));
    char Id[5];
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(Id,pch);
    pch = strtok (NULL,",><");
    strcpy(newName,pch);
    pch = strtok (NULL, ",><");
    strcpy(newAdd,pch);
    pch = strtok (NULL, ",><");
    strcpy(newPhone,pch);
  
    //printf("%c\n",grade[1]);
    
    int id = atoi(Id);
    
    SNAP me = newSNAP(id,newName,newAdd,newPhone);
    
    int boolean_id = ((*me).StudentId != 0);
    int boolean_name = ((*me).Name[0] != '*');
    int boolean_add = ((*me).Address[0] != '*');
    int boolean_phone = ((*me).Phone[0] != '*');
 
    LinkedNode ans = fill();

    if (boolean_id){
        LinkedNode s = lookup_SNAP_S((*me).StudentId);
        ans = matchLinkedNode((*ans).next, s);
    }

    if(boolean_name){
        LinkedNode n = lookup_SNAP_N((*me).Name);
        ans = matchLinkedNode(ans, n);
    }
    
    if (boolean_add){
        LinkedNode a = lookup_SNAP_A((*me).Address);
        ans = matchLinkedNode(ans, a);
    }
    
     if (boolean_phone){
        LinkedNode p = lookup_SNAP_P((*me).Phone);
        ans = matchLinkedNode(ans, p);
    }
    
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
    }

    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        SNAP temp = &SNAP_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).StudentId == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bs = !boolean_id || ((*temp).StudentId == (*me).StudentId);
            int bn = !boolean_name || isEqual((*temp).Name, (*me).Name);
            int ba = !boolean_add || isEqual((*temp).Address, (*me).Address);
            int bp = !boolean_phone || isEqual((*temp).Phone, (*me).Phone);
            SNAP temp_next = (*temp).next;
            if(bn && bs && ba && bp){
                if((*temp).StudentId != 0){
                    printf("%d\t", (*temp).StudentId);
                    printf("\t%s\t", (*temp).Name);
                    printf("\t%s\t", (*temp).Address);
                    printf("%s\n", (*temp).Phone); 
                }
            }
            
            temp = temp_next;
        }
        
    }
    
    return ans1;
    
}

SNAP findSNAP_prev(SNAP me){
    
    int index = (*me).StudentId % 1009;
    
    SNAP cell = &SNAP_table[index];
    SNAP parent = cell;
    
    // assuming unique StudentId as Course-StudentId is a key
    if ((*cell).StudentId == (*me).StudentId){
        printf("no parrent\n");
        return NULL;
    }
    
    while((*cell).StudentId != (*me).StudentId){
        parent = cell;
        cell = (*cell).next;
    }
    
    return parent;
}

void deleteSNAP_helper(SNAP me){
   
    int index = (*me).StudentId % 1009;
    SNAP first = &SNAP_table[index];
    
    // if the tuple is the first in LinkedList
    if ((*first).StudentId == (*me).StudentId){
        // reassign
        if ((*first).next != NULL) {
        SNAP new_first = (*first).next;
        SNAP_table[index] = *new_first;
        } else {
            SNAP_table[index] = *newSNAP(0, NULL, NULL, NULL);
        }
        
    } else {
        SNAP x = findSNAP_prev(me);
        if (x == NULL){
            printf("tuple not found");
        } else {
            (*x).next = (*me).next;
        }
    }
    
}

int delete_SNAP(char* tuple){
    
    printf("deleting: %s from SNAP\n", tuple);
    
    char * newName = (char*) malloc(50*sizeof(char));
    char * newAdd = (char*) malloc(50*sizeof(char));
    char * newPhone = (char*) malloc(8*sizeof(char));
    char Id[5];
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(Id,pch);
    pch = strtok (NULL,",><");
    strcpy(newName,pch);
    pch = strtok (NULL, ",><");
    strcpy(newAdd,pch);
    pch = strtok (NULL, ",><");
    strcpy(newPhone,pch);
  
    //printf("%c\n",grade[1]);
    
    int id = atoi(Id);
    
    SNAP me = newSNAP(id,newName,newAdd,newPhone);
    
    int boolean_id = ((*me).StudentId != 0);
    int boolean_name = ((*me).Name[0] != '*');
    int boolean_add = ((*me).Address[0] != '*');
    int boolean_phone = ((*me).Phone[0] != '*');
 
    LinkedNode ans = fill();

    if (boolean_id){
        LinkedNode s = lookup_SNAP_S((*me).StudentId);
        ans = matchLinkedNode((*ans).next, s);
    }

    if(boolean_name){
        LinkedNode n = lookup_SNAP_N((*me).Name);
        ans = matchLinkedNode(ans, n);
    }
    
    if (boolean_add){
        LinkedNode a = lookup_SNAP_A((*me).Address);
        ans = matchLinkedNode(ans, a);
    }
    
     if (boolean_phone){
        LinkedNode p = lookup_SNAP_P((*me).Phone);
        ans = matchLinkedNode(ans, p);
    }
    
    printf("resulting table: \n");
    
    if (ans == NULL){
        printf("not found\n");
        return 0;
    }

    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        SNAP temp = &SNAP_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).StudentId == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bs = !boolean_id || ((*temp).StudentId == (*me).StudentId);
            int bn = !boolean_name || isEqual((*temp).Name, (*me).Name);
            int ba = !boolean_add || isEqual((*temp).Address, (*me).Address);
            int bp = !boolean_phone || isEqual((*temp).Phone, (*me).Phone);
            SNAP temp_next = (*temp).next;
            if(bn && bs && ba && bp){
                if((*temp).StudentId != 0){
                    deleteSNAP_helper(temp);
                }
            }
            
            temp = temp_next;
        }
    }
    
    printTABLE_SNAP();
    
    return 1;
    
}

char* match_Course(LinkedNode i, char* C){
    // i: linked list of indeces in SNAP hash table
    while (i != NULL){
        
        int index = (*i).data;
        
        
        SNAP snap = &SNAP_table[index];
        int id = (*snap).StudentId;
        
        // iterating through hash table to match CSG
        for (int f = 0; f < 1009; f++){
            
            CSG current = &CSG_table[f];
            // printCSG(current);
            if(current->StudentId != 0){ // if the cell is not empty
                while(current != NULL){
                    // printf("current StudentId: %d\n", current->StudentId);
                    if(current->StudentId == id && isEqual(current->Course,C)){
                        return current->Grade;
                    }
                    current = current->next;
                }
            }
        }
        
        i = (*i).next;
        
    }
    
    return "invalid request";
}

char* NC_G(char* N, char* C){
    // N: Name; C: Course
    int v = hashfunction2_SNAP(N);
    
    // linked list of index in SNAP hash table of SNAP with Name = N
    LinkedNode i = findBinTree(v, SNAP_Tree);
    
    if(i == NULL){
        return "invalid request";
    }
    
    char* answer = match_Course(i, C);
    
    printf("\n%s has received %s in course %s\n", N, answer, C);
    
    return answer;
}

//CP table struct 
int hashfunction_CP(char *Course,int size_table){
        unsigned long hash = 5381;
        int c = 0;
        while (c = *Course++)
            hash = ((hash << 5) + hash) + c; 
            
    return hash%size_table;
}

typedef struct CP *CP;
struct CP{
    int id;
    char*Course;
    char* Prerequisite;
    CP next;
};
struct CP CP_table[1009]; 

void initiate_CP(){
    for(int i=0;i<1009;i++){
        CP_table[i].id= 0;
        CP_table[i].Course = (char*) malloc(12*sizeof(char*));
        CP_table[i].Prerequisite = (char*) malloc(12*sizeof(char*));
        CP_table[i].next = NULL;
     }
}

void addLinkCP(CP first,CP link){
    
    if((*first).next == NULL){
     
        (*first).next = link;
     
    } else {
     
        addLinkCP((*first).next, link);
     
    }
    
}
CP newCP(char* C,char* P){
    
    CP cp = (CP) malloc(sizeof(struct CP));
    
    cp->id = 1;
    cp->Course = C;
    cp->Prerequisite = P;
    cp->next = NULL;
    
    return cp;
}
void insertCP(char* tuple){
    
    char * newCourse = (char*) malloc(50*sizeof(char));
    char * newPrerequisite = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newPrerequisite,pch);

    
    CP temp = newCP(newCourse,newPrerequisite);
           
    int index = hashfunction_CP(newCourse,1009);
    
    CP current = &CP_table[index];
    if(current->id == 0){
        CP_table[index] = *temp;
    } else {
        addLinkCP(&CP_table[index], temp);
    }
    
}

void printCP(CP x){
    printf("%s\t", (*x).Course);
    printf("\t%s\n", (*x).Prerequisite);
    if ((*x).next != NULL){
        printCP((*x).next);
    }
    
}

void printTABLE_CP(){
    printf("\nCourse \t| \t Prerequisite\n");
    for (int i = 0; i < 1009; i++){
        CP current = &CP_table[i];
        if(current->id != 0){
            //printf("%d:", i);
            printCP(&CP_table[i]);
        }
    }
}

LinkedNode lookup_CP_C(char* c){

    LinkedNode ans = newLinkedNode(hashfunction_CP(c, 1009));
  
    return ans;
}

LinkedNode lookup_CP_P(char* p){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CP temp = &CP_table[i];
        while(temp != NULL){
            if((*temp).id != 0 && isEqual((*temp).Prerequisite, p)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CP(char* tuple){
    
    printf("query: %s\n", tuple);
    
    char * newCourse = (char*) malloc(50*sizeof(char));
    char * newPrerequisite = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newPrerequisite,pch);

    CP me = newCP(newCourse,newPrerequisite);
    
    int boolean_course = (!isEqual((*me).Course, "*"));
    int boolean_pre = (!isEqual((*me).Prerequisite, "*"));
    
    LinkedNode ans = fill();

    if (boolean_course){
        LinkedNode c = lookup_CP_C((*me).Course);
        ans = matchLinkedNode((*ans).next, c);
    }

    if(boolean_pre){
        LinkedNode p = lookup_CP_P((*me).Prerequisite);
        ans = matchLinkedNode(ans, p);
    }
   
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
     
    }
    
    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        CP temp = &CP_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).id == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int bp = !boolean_pre || isEqual((*temp).Prerequisite, (*me).Prerequisite);
            
            if(bc && bp){
                if((*temp).id != 0){
                    printf("\n%s\t", (*temp).Course);
                    printf("\t%s\t", (*temp).Prerequisite);
                }
            }
            
            temp = (*temp).next;
        }
        
    }
    
    return ans1;
    
}

CP findCP_prev(CP me, int index){
    
    CP cell = &CP_table[index];
    CP parent = cell;
    
    if((*cell).id == 0){
        printf("\nfind parent: no such tuple\n");
        return NULL;    }
    
    
    if (isEqual((*cell).Course,(*me).Course) && isEqual((*cell).Prerequisite, (*me).Prerequisite)){
        return NULL;
    }
    
    while(!isEqual((*cell).Course,(*me).Course) && !isEqual((*cell).Prerequisite, (*me).Prerequisite)){
        parent = cell;
        cell = (*cell).next;
    }
    
    return parent;
}

void deleteCP_helper(CP me){
   
    int index = hashfunction_CP((*me).Course, 1009);
    CP first = &CP_table[index];
    
    // if the tuple is the first in LinkedList
    if ((*first).Course == (*me).Course && (*first).Prerequisite == (*me).Prerequisite){
        // reassign
        if ((*first).next != NULL) {
        CP new_first = (*first).next;
        CP_table[index] = *new_first;
        } else {
            CP_table[index] = *newCP(NULL, NULL);
            (*(&CP_table[index])).id = 0;
        }
        
    } else {
        CP x = findCP_prev(me, index);
        if (x == NULL){
            printf("tuple not found");
        } else {
            (*x).next = (*me).next;
        }
    }
}

int delete_CP(char* tuple){
    
    printf("deleting: %s from CP\n", tuple);
    
    char * newCourse = (char*) malloc(50*sizeof(char));
    char * newPrerequisite = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newPrerequisite,pch);

    
    CP me = newCP(newCourse,newPrerequisite);
    
    int boolean_course = (!isEqual((*me).Course, "*"));
    int boolean_pre = (!isEqual((*me).Prerequisite, "*"));
    
    LinkedNode ans = fill();

    if (boolean_course){
        LinkedNode c = lookup_CP_C((*me).Course);
        ans = matchLinkedNode((*ans).next, c);
    }

    if(boolean_pre){
        LinkedNode p = lookup_CP_P((*me).Prerequisite);
        ans = matchLinkedNode(ans, p);
    }
   
    printf("resulting table: \n");

    while(ans != NULL){
        
        CP temp = &CP_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).id == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int bp = !boolean_pre || isEqual((*temp).Prerequisite, (*me).Prerequisite);
            
            if(bc && bp){
                if((*temp).id != 0){
                    deleteCP_helper(temp);
                }
            }
            
            temp = (*temp).next;
        }
        
    }
    
    printTABLE_CP();
    
    return 1;
    
}

// CDH

struct BinTreeNode *CDH_Tree;
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int hashfunction_CDH(char *Course,char *Day,int size_table){
        unsigned long hash = 5381;
        int c = 0;
        char *both = concat(Course,Day);
        while (c = *both++)
            hash = ((hash << 5) + hash) + c; 
            
    return hash%size_table;
}

typedef struct CDH *CDH;
struct CDH{
    int id;
    char* Course;
    char* Day;
    char* Hour;
    CDH next;
};
struct CDH CDH_table[1009]; 

void initiate_CDH(){
    CDH_Tree = newBinTreeNode(0, NULL);
    for(int i=0;i<1009;i++){
        CDH_table[i].id= 0;
        CDH_table[i].Course = (char*) malloc(12*sizeof(char*));
        CDH_table[i].Day = (char*) malloc(12*sizeof(char*));
        CDH_table[i].Hour = (char*) malloc(12*sizeof(char*));
        CDH_table[i].next = NULL;
     }
}

void addLinkCDH(CDH first,CDH link){
    
    if((*first).next == NULL){
     
        (*first).next = link;
     
    } else {
     
        addLinkCDH((*first).next, link);
     
    }
    
}

CDH newCDH(char* C,char* D,char *H){
    
    CDH cdh = (CDH) malloc(sizeof(struct CDH));
    
    cdh->id = 1;
    cdh->Course = C;
    cdh->Day = D;
    cdh->Hour = H;
    cdh->next = NULL;
    
    return cdh;
}

void addBinTreeNode_CDH(BinTreeNode root, CDH cdh);
void insertCDH(char* tuple){
    
    char * newCourse = (char*) malloc(12*sizeof(char));
    char * newDay = (char*) malloc(12*sizeof(char));
    char * newHour = (char*) malloc(12*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newDay,pch);
     pch = strtok (NULL,",><");
    strcpy(newHour,pch);

    
    CDH temp = newCDH(newCourse,newDay,newHour);
           
    int index = hashfunction_CDH(newCourse,newDay,1009);
    
    addBinTreeNode_CDH(CDH_Tree, temp);
    
    CDH current = &CDH_table[index];
    if(current->id == 0){
        CDH_table[index] = *temp;
    } else {
        addLinkCDH(&CDH_table[index], temp);
    }
    
}

void printCDH(CDH x){
    printf("%s\t", (*x).Course);
    printf("\t%s\t", (*x).Day);
    printf("\t%s\n", (*x).Hour);
    if ((*x).next != NULL){
        printCDH((*x).next);
    }
    
}

void printTABLE_CDH(){
    printf("\nCourse \t|\t\tDay\t|\tHour\n");
    for (int i = 0; i < 1009; i++){
        CDH current = &CDH_table[i];
        if(current->id != 0){
            //printf("%d:", i);
            printCDH(&CDH_table[i]);
        }
    }
}

LinkedNode lookup_CDH_C(char* c){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CDH temp = &CDH_table[i];
        while(temp != NULL){
            if((*temp).id != 0 && isEqual((*temp).Course, c)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CDH_D(char* d){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CDH temp = &CDH_table[i];
        while(temp != NULL){
            if((*temp).id != 0 && isEqual((*temp).Day, d)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CDH_H(char* h){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CDH temp = &CDH_table[i];
        while(temp != NULL){
            if((*temp).id != 0 && isEqual((*temp).Hour, h)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

CDH findCDH_prev(CDH me, int index){
    
    CDH cell = &CDH_table[index];
    CDH parent = cell;
    
    if((*cell).id == 0){
        printf("\nfind parent: no such tuple\n");
        return NULL;
    }
    
    
    if (isEqual((*cell).Course,(*me).Course) && isEqual((*cell).Day, (*me).Day) && isEqual((*cell).Hour, (*me).Hour)){
        return NULL;
    }
    
    while(!isEqual((*cell).Course,(*me).Course) && !isEqual((*cell).Day, (*me).Day) && isEqual((*cell).Hour, (*me).Hour)){
        parent = cell;
        cell = (*cell).next;
    }
    
    return parent;
}

void deleteCDH_helper(CDH me){
   
    int index = hashfunction_CDH((*me).Course, (*me).Day, 1009);
    CDH first = &CDH_table[index];
    
    // if the tuple is the first in LinkedList
    if ((*first).Course == (*me).Course && (*first).Day == (*me).Day && (*first).Hour == (*me).Hour){
        // reassign
        if ((*first).next != NULL) {
        CDH new_first = (*first).next;
        CDH_table[index] = *new_first;
        } else {
            CDH_table[index] = *newCDH(NULL, NULL, NULL);
            (*(&CDH_table[index])).id = 0;
        }
        
    } else {
        CDH x = findCDH_prev(me, index);
        if (x == NULL){
            printf("tuple not found");
        } else {
            (*x).next = (*me).next;
        }
    }
}

LinkedNode lookup_del_CDH(char* tuple, int lookup_only){
    
    if(lookup_only){
        printf("query");
    } else {
        printf("deleting");
    }
    printf(": %s\n", tuple);
    
    char * newCourse = (char*) malloc(12*sizeof(char));
    char * newDay = (char*) malloc(12*sizeof(char));
    char * newHour = (char*) malloc(12*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newDay,pch);
     pch = strtok (NULL,",><");
    strcpy(newHour,pch);

    CDH me = newCDH(newCourse,newDay,newHour);
    
    int boolean_course = (!isEqual((*me).Course, "*"));
    int boolean_day = (!isEqual((*me).Day, "*"));
    int boolean_hour = (!isEqual((*me).Hour, "*"));
    
    LinkedNode ans = fill();
    
    if (boolean_course && boolean_day){
        ans = matchLinkedNode(ans, newLinkedNode(hashfunction_CDH((*me).Course, (*me).Day, 1009)));
    } else if (boolean_course){
        LinkedNode c = lookup_CDH_C((*me).Course);
        ans = matchLinkedNode(ans, c);
    } else if (boolean_day){
        LinkedNode d = lookup_CDH_D((*me).Day);
        ans = matchLinkedNode(ans, d);
    }
    
    if(boolean_hour){
        LinkedNode h = lookup_CDH_H((*me).Hour);
        ans = matchLinkedNode(ans, h);
    }
   
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
        
    }
    
    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        CDH temp = &CDH_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).id == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int bd = !boolean_day || isEqual((*temp).Day, (*me).Day);
            int bh = !boolean_hour || isEqual((*temp).Hour, (*me).Hour);
            
            if(bc && bd && bh){
                if((*temp).id != 0){
                    if(lookup_only){
                        printf("\n%s\t", (*temp).Course);
                        printf("\t%s\t", (*temp).Day);
                        printf("\t%s\t", (*temp).Hour);
                    } else {
                        deleteCDH_helper(temp);
                    }
                }
            }
            
            temp = (*temp).next;
        }
        
    }
    
    if(!lookup_only){
        printTABLE_CDH();
    }
    
    return ans1;
    
}

LinkedNode lookup_CDH(char* tuple){
    return lookup_del_CDH(tuple, 1);
}

void delete_CDH(char* tuple){
    lookup_del_CDH(tuple, 0);
}

//CR table struct 
int hashfunction_CR(char *Course,int size_table){
        unsigned long hash = 5381;
        int c = 0;
      
        while (c = *Course++)
            hash = ((hash << 5) + hash) + c; 
            
    return hash%size_table;
}

typedef struct CR *CR;
struct CR{
    int id;
    char*Course;
    char* Room;
    CR next;
};
struct CR CR_table[1009]; 

void initiate_CR(){
    for(int i=0;i<1009;i++){
        CR_table[i].id= 0;
        CR_table[i].Course = (char*) malloc(12*sizeof(char*));
        CR_table[i].Room = (char*) malloc(50*sizeof(char*));
        CR_table[i].next = NULL;
     }
}

void addLinkCR(CR first,CR link){
    
    if((*first).next == NULL){
     
        (*first).next = link;
     
    } else {
     
        addLinkCR((*first).next, link);
     
    }
    
}
CR newCR(char* C,char* R){
    
    CR cr = (CR) malloc(sizeof(struct CR));
    
    cr->id = 1;
    cr->Course = C;
    cr->Room= R;
    cr->next = NULL;
    
    return cr;
}
void insertCR(char* tuple){
    
    char * newCourse = (char*) malloc(12*sizeof(char));
    char * newRoom = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newRoom,pch);
    
    CR temp = newCR(newCourse,newRoom);
           
    int index = hashfunction_CR(newCourse,1009);
    
    CR current = &CR_table[index];
    if(current->id == 0){
        CR_table[index] = *temp;
    } else {
        addLinkCR(&CR_table[index], temp);
    }
    
}

int hashfunction2_CDH(char* Day, char* Hour){
    
    unsigned long hash = 5381;
    int c = 0;
    char* both = concat(Day, Hour);
    while( c  = *both++){
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash % 1009;
}

void addName_LinkedNode_CDH(LinkedNode head, CDH cdh){
    if((*head).next == NULL){
        (*head).next = newLinkedNode(hashfunction_CDH((*cdh).Course, (*cdh).Day, 1009));
    } else {
        addName_LinkedNode_CDH((*head).next, cdh);
    }
}

void addBinTreeNode_CDH(BinTreeNode root, CDH cdh){
    int my_value = (*root).value;
    int new_value  = hashfunction2_CDH((*cdh).Day, (*cdh).Hour);
    
    if(my_value < new_value){
//      move right
        BinTreeNode focus  = (*root).right;
        if(focus == NULL){
            (*root).right = newBinTreeNode(new_value, newLinkedNode(hashfunction_CDH((*cdh).Course, (*cdh).Day, 1009)));
        } else {
            addBinTreeNode_CDH((*root).right, cdh);
        }   
    } else if (my_value > new_value){
//      move left
        BinTreeNode focus  = (*root).left;
        if(focus == NULL){
            (*root).left = newBinTreeNode(new_value, newLinkedNode(hashfunction_CDH((*cdh).Course, (*cdh).Day, 1009)));
        } else {
            addBinTreeNode_CDH((*root).left, cdh);
        }
    } else {
//      add to the LinkedList
        addName_LinkedNode_CDH((*root).data, cdh);
    }
}

void printCR(CR x){
    printf("%s\t", (*x).Course);
    printf("\t%s\t\n", (*x).Room);
    if ((*x).next != NULL){
        printCR((*x).next);
    }
    
}

void printTABLE_CR(){
    printf("\nCourse \t|\t\tRoom\n");
    for (int i = 0; i < 1009; i++){
        CR current = &CR_table[i];
        if(current->id != 0){
            //printf("%d:", i);
            printCR(&CR_table[i]);
        }
    }
}

LinkedNode lookup_CR_C(char* c){

    LinkedNode ans = newLinkedNode(hashfunction_CR(c, 1009));
    
    return ans;
}

LinkedNode lookup_CR_R(char* r){

    LinkedNode ans = newLinkedNode(0);
    for(int i = 0; i < 1009; i++){
        CR temp = &CR_table[i];
        while(temp != NULL){
            if((*temp).id != 0 && isEqual((*temp).Room, r)){
                if(!containsLink(ans, i)){
                    addLinkedNode(ans, newLinkedNode(i));    
                }
            }   
            temp = (*temp).next;
        }
    }

    return (*ans).next;
}

LinkedNode lookup_CR(char* tuple){
    
    printf("query: %s\n", tuple);
    
    char * newCourse = (char*) malloc(50*sizeof(char));
    char * newRoom = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newRoom,pch);

    CR me = newCR(newCourse,newRoom);
    
    int boolean_course = (!isEqual((*me).Course, "*"));
    int boolean_room = (!isEqual((*me).Room, "*"));
    
    LinkedNode ans = fill();

    if (boolean_course){
        LinkedNode c = lookup_CR_C((*me).Course);
        ans = matchLinkedNode((*ans).next, c);
    }

    if(boolean_room){
        LinkedNode r = lookup_CR_R((*me).Room);
        ans = matchLinkedNode(ans, r);
    }
   
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
        
    }
    
    LinkedNode ans1 = ans;

    while(ans != NULL){
        
        CR temp = &CR_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).id == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int br = !boolean_room || isEqual((*temp).Room, (*me).Room);
            
            if(bc && br){
                if((*temp).id != 0){
                    printf("\n%s\t", (*temp).Course);
                    printf("\t%s\t", (*temp).Room);
                }
            }
            
            temp = (*temp).next;
        }
        
    }
    
    return ans1;
    
}

CR findCR_prev(CR me, int index){
    
    CR cell = &CR_table[index];
    CR parent = cell;
    
    if((*cell).id == 0){
        printf("\nfind parent: no such tuple\n");
        return NULL;    }
    
    
    if (isEqual((*cell).Course,(*me).Course) && isEqual((*cell).Room, (*me).Room)){
        return NULL;
    }
    
    while(!isEqual((*cell).Course,(*me).Course) && !isEqual((*cell).Room, (*me).Room)){
        parent = cell;
        cell = (*cell).next;
    }
    
    return parent;
}

void deleteCR_helper(CR me){
   
    int index = hashfunction_CR((*me).Course, 1009);
    CR first = &CR_table[index];
    
    // if the tuple is the first in LinkedList
    if ((*first).Course == (*me).Course && (*first).Room == (*me).Room){
        // reassign
        if ((*first).next != NULL) {
        CR new_first = (*first).next;
        CR_table[index] = *new_first;
        } else {
            CR_table[index] = *newCR(NULL, NULL);
            (*(&CR_table[index])).id = 0;
        }
        
    } else {
        CR x = findCR_prev(me, index);
        if (x == NULL){
            printf("tuple not found");
        } else {
            (*x).next = (*me).next;
        }
    }
}

int delete_CR(char* tuple){
    
    printf("deleting: %s from CR\n", tuple);
    
    char * newCourse = (char*) malloc(50*sizeof(char));
    char * newRoom = (char*) malloc(50*sizeof(char));
    char str[300]; 
    strcpy(str,tuple);
    char * pch;
    pch = strtok (str,",><");
    strcpy(newCourse,pch);
    pch = strtok (NULL,",><");
    strcpy(newRoom,pch);

    CR me = newCR(newCourse,newRoom);
    
    int boolean_course = (!isEqual((*me).Course, "*"));
    int boolean_room = (!isEqual((*me).Room, "*"));
    
    LinkedNode ans = fill();

    if (boolean_course){
        LinkedNode c = lookup_CR_C((*me).Course);
        ans = matchLinkedNode((*ans).next, c);
    }

    if(boolean_room){
        LinkedNode r = lookup_CR_R((*me).Room);
        ans = matchLinkedNode(ans, r);
    }
   
    printf("result: \n");
    
    if (ans == NULL){
        printf("not found\n");
        return 0;
    }

    while(ans != NULL){
        
        CR temp = &CR_table[(*ans).data];
        ans = (*ans).next;
        
        if((*temp).id == 0){
            continue;
        }
        
        while(temp != NULL){
            
            int bc = !boolean_course || isEqual((*temp).Course, (*me).Course);
            int br = !boolean_room || isEqual((*temp).Room, (*me).Room);
            
            if(bc && br){
                if((*temp).id != 0){
                    deleteCR_helper(temp);
                }
            }
            
            temp = (*temp).next;
        }
        
    }
    
    printTABLE_CR();
    
    return 1;
}

void NDH_R(char* N, char* Day, char* Hour){
    
    int m = hashfunction2_SNAP(N);
//  linked list of index in SNAP_table with Name matching N
    LinkedNode i = findBinTree(m, SNAP_Tree);

    SNAP temp = &SNAP_table[(*i).data];
//  linked list of StudentIds with Name matching N
    LinkedNode Id = newLinkedNode((*temp).StudentId);
    

    int v = hashfunction2_CDH(Day, Hour);
//  linked list of index in CDH_table with Day mathching D and Hour mathching H
    LinkedNode j  = findBinTree(v, CDH_Tree);

    while(j != NULL) {

        CDH current = &CDH_table[(*j).data];
        char* current_course = (*current).Course;
        
        int CSG_index = hashfunction_CSG(current_course, (*Id).data, 1009);
        CSG csg = &CSG_table[CSG_index];

        if ((*csg).StudentId != 0){ //Student does take the course
            CR cr = &CR_table[hashfunction_CR(current_course, 1009)];
            char* room = (*cr).Room;
            printf("\n%s is in %s at %s on %s\n", N, room, Hour, Day);
        }       

        Id = (*Id).next;
        if (Id == NULL){
            break;
        }
        
        j = (*j).next;
    }
}

void writeCSG(){
   FILE *crFile;
    crFile = fopen("CSG.txt", "w+");
        for (int i = 0; i < 1009; i++){
        CSG current = &CSG_table[i];
        if(current->StudentId != 0){
                 CSG x = &CSG_table[i];
            while (x!= NULL){
    fprintf(crFile, "<");
                fprintf(crFile, (*x).Course);
                fprintf(crFile, ",");
                fprintf(crFile,"%d", (*x).StudentId);
                fprintf(crFile, ",");
                fprintf(crFile, (*x).Grade);
                fprintf(crFile, ">\n");
                x = (*x).next;
                }
        }

        }
}
void writeSNAP(){
        FILE *crFile;
    crFile = fopen("SNAP.txt", "w+");
        for (int i = 0; i < 1009; i++){
        SNAP current = &SNAP_table[i];
        if(current->StudentId != 0){
            SNAP x = &SNAP_table[i];
            while (x!= NULL){
                fprintf(crFile, "<");
                fprintf(crFile,"%d", (*x).StudentId);
                fprintf(crFile, ",");
                fprintf(crFile, (*x).Name);
                fprintf(crFile, ",");
                fprintf(crFile, (*x).Address);
                fprintf(crFile, ",");
                fprintf(crFile, (*x).Phone);
                fprintf(crFile, ">\n");
                x = (*x).next;
                }
  }
        }
        fclose(crFile);
}
void writeCP(){
    FILE *crFile;
    crFile = fopen("CP.txt", "w+");
        for (int i = 0; i < 1009; i++){
        CP current = &CP_table[i];
        if(current->id != 0){
            CP x = &CP_table[i];
        while (x!= NULL){
                fprintf(crFile, "<");
            fprintf(crFile, (*x).Course);
            fprintf(crFile, ",");
                    fprintf(crFile, (*x).Prerequisite);
                fprintf(crFile, ">\n");
                x = (*x).next;
                }
        }
        }
   fclose(crFile);
}
void writeCDH(){
    FILE *crFile;
    crFile = fopen("CDH.txt", "w+");
        for (int i = 0; i < 1009; i++){
        CDH current = &CDH_table[i];
        if(current->id != 0){
           CDH x = &CDH_table[i];
               while (x!= NULL){
                fprintf(crFile, "<");
            fprintf(crFile, (*x).Course);
            fprintf(crFile, ",");
                    fprintf(crFile, (*x).Day);
                    fprintf(crFile, ",");
                fprintf(crFile, (*x).Hour);
                fprintf(crFile, ">\n");
                        x = (*x).next;
                }
        }
 }
        fclose(crFile);
}
void writeCR(){
    FILE *crFile;
    crFile = fopen("CR.txt", "w+");
        for (int i = 0; i < 1009; i++){
        CR current = &CR_table[i];
        if(current->id != 0){
                CR x = &CR_table[i];
               while (x!= NULL){
                fprintf(crFile, "<");
                fprintf(crFile, (*x).Course);
                fprintf(crFile, ",");
            fprintf(crFile, (*x).Room);
            fprintf(crFile, ">\n");

                x = (*x).next;
                }
        }
        }
        fclose(crFile);
}
void supportedTables(){
    printf("Course-StudentId-Grade as CSG\n");
    printf("StudentId-Name-Address-Phone as SNAP\n");
    printf("Course-Prerequisite as CP\n");
    printf("Course-Day-Hour as CDH\n");
    printf("Course-Room as CR\n");
}
void write_tofile(char * Relation)    {
    if(Relation == "CSG")
        writeCSG();
    else if(Relation == "SNAP")
        writeSNAP();
    else if(Relation == "CP")
        writeCP();
    else if(Relation == "CDH")
        writeCDH();
    else if(Relation == "CR")
        writeCR();

    else {
        printf("No such relation, Please check support tables below\n");
  supportedTables();
    }
}

void insert(char * tuple, char* Relation){
    if(Relation == "CSG")
        insertCSG(tuple);
    else if(Relation == "SNAP")
        insertSNAP(tuple);
    else if(Relation == "CP")
        insertCP(tuple);
    else if(Relation == "CDH")
        insertCDH(tuple);
    else if(Relation == "CR")
        insertCR(tuple);
    else {
        printf("No such relation, Please check support tables below\n");
        supportedTables();
    }

}
char * readRelation(char * fileName){
    if(fileName == "CSG.txt") return "CSG";
   if(fileName == "SNAP.txt")  return "SNAP";
   if(fileName == "CP.txt") return "CP";
   if(fileName == "CDH.txt") return "CDH";
   if(fileName == "CR.txt") return "CR";
}
void read(char * fileName){
   FILE *file = fopen (fileName, "r" );
   char *Relation = readRelation(fileName);

   if ( file != NULL ){
      char line [ 200 ];
      while ( fgets ( line, sizeof line, file ) != NULL ){
         insert (line, Relation );
      }
      fclose ( file );
   }
   else{
      printf("No such file, Please check support tables below and add .txt to ge\
t the file eg CSG.txt\n");
      supportedTables();
    supportedTables();
   }

}

LinkedNode select_(char* schema, char c, char* value){
    // example: select_("CSG", 'C', "CS101") or select_("SNAP", 'N', "C. Brown")
    printf("\nselect_ in %s by %s\n", schema, value);
    char* tuple = "<";
    if(schema == "CSG"){
        if(c == 'C'){
            tuple = concat(tuple, value);
            tuple = concat(tuple, ",*,*>");
        } else if (c == 'S'){
            tuple = concat(tuple, "*,");
            tuple = concat(tuple, value);
            tuple = concat(tuple, ",*>");
        } else if (c == 'G'){
            tuple = concat(tuple, "*,*,");
            tuple = concat(tuple, value);
            tuple = concat(tuple,">");
        } else {
            printf("error in select_\n");
            return NULL;
        }
        return lookup_CSG(tuple);
    } else if (schema == "SNAP"){
        if (c == 'S'){
            tuple = concat(concat(tuple, value), ",*,*,*>");
        } else if (c == 'N'){
            tuple = concat(tuple, concat("*", concat(value, ",*,*>")));
        } else if (c == 'A'){
            tuple = concat(tuple, concat("*,*,",concat(value, ",*>")));
        } else if (c == 'P'){
            tuple = concat(tuple, concat("*,*,*", concat(value, ">")));
        } else {
            printf("error in select_\n");
            return NULL;
        }
        return lookup_SNAP(tuple);
    } else if (schema == "CDH"){
        if(c == 'C'){
            tuple = concat(tuple, concat(value, ",*,*>"));
        } else if (c == 'D'){
            tuple = concat(tuple, concat("*,", concat(value, ",*>")));
        } else if (c == 'H'){
            tuple = concat(tuple, concat("*,*,", concat(value, ">")));
        } else {
            printf("error in select_\n");
            return NULL;
        } 
        return lookup_CDH(tuple);
    } else if (schema == "CR"){
        if (c == 'C'){
            tuple = concat(tuple, concat(value, ",*>"));
        } else if (c == 'R'){
            tuple = concat(tuple, concat("*,", concat(value, ">")));
        } else {
            printf("error in select_\n");
            return NULL;
        }
        return lookup_CR(tuple);
    } else if (schema == "CP"){
        if (c == 'C'){
            tuple = concat(tuple, concat(value, ",*>"));
        } else if (c == 'P'){
            tuple = concat(tuple, concat("*,", concat(value, ">")));
        } else {
            printf("error in select_\n");
            return NULL;
        }
        return lookup_CP(tuple);
    } else {
        printf("how about sumbitting a valid request for select_?\n");
        return NULL;
    }
}

struct CRDH{
    char* Course;
    char* Room;
    char* Day;
    char* Hour;
    int id;
};

typedef struct CRDH *CRDH;
struct CRDH CRDH_table[500];

CRDH newCRDH(char* c, char* r, char* d, char* h){
    CRDH me = (CRDH) malloc(sizeof(CRDH));
    (*me).Course = c;
    (*me).Room = r;
    (*me).Day = d;
    (*me).Hour = h;
    (*me).id = 1;
    return me;
}

void printTABLE_CRDH(){
    int c = 0;
    while(1){
        
        CRDH temp = &CRDH_table[c];
        c = c + 1;
        
        if(!(*temp).id) break;
        
        printf("\n%s\t%s\t%s\t%s", (*temp).Course, (*temp).Room, (*temp).Day, (*temp).Hour);
        
    }
}

void joinCR_DH(LinkedNode cr, LinkedNode cdh){
    
    // printLinkedNode(cr);
    // printLinkedNode(cdh);
    
    
    int c = 0;
    
    while(cr != NULL){
        
        CR current_cr = &CR_table[(*cr).data];
        if((*current_cr).id == 0) {continue;}
        
        printf("trying to match %s\n", (*current_cr).Course);
        // printCR(current_cr);
        
        while((*current_cr).id != 0){
            
            while(cdh != NULL){
               
                CDH current_cdh = &CDH_table[(*cdh).data];
                
                if((*current_cdh).id == 0) {continue;}
                printf("with: %s\n", (*current_cdh).Course);

                while((*current_cdh).id != 0){
                    
                    if((*current_cr).Course == (*current_cdh).Course){
                        CRDH temp = newCRDH((*current_cr).Course, (*current_cr).Room, (*current_cdh).Day, (*current_cdh).Hour);
                        CRDH_table[c] = *temp;
                        c = c + 1;
                        printf("\n\nmatched!\n\n");
                    }
                    
                    current_cdh = (*current_cdh).next;    
                   
                    
                }
                cdh = (*cdh).next;
            }
            
                current_cr = (*current_cr).next;
            
             
        }
     (cr) = (*cr).next;
    }
}

int main(){
    
    // printf("CSG table\n");
    initiate_CSG();
    insertCSG("<CS101,12345,A>");
    insertCSG("<CS101,67890,B>");
    insertCSG("<EE200,12345,C>");
    insertCSG("<CS200,12345,C>");
    insertCSG("<PH200,12345,C>");
    insertCSG("<EE200,22222,B+>");
    insertCSG("<CS101,33333,A−>");
    insertCSG("<PH100,67890,C+>");
    printTABLE_CSG();
    
    printf("\n\n");
    lookup_CSG("<EE200,*,*>");
    printf("\n\n");
    delete_CSG("<EE200,*,*>");
    printf("\n\n");
    
    SNAP_Tree = newBinTreeNode(0, NULL);
    // printf("SNAP table\n");
    initiate_SNAP();
    insertSNAP("<12345,C. Brown,12 Apple St.,555-1234>");
    insertSNAP("<67890,L. Van Pelt,34 Pear Ave.,555-5678>");
    insertSNAP("<22222,P. Patty,56 Grape Blvd.,555-9999>");
    insertSNAP("<22212,P. Patty,6 NoOneCares,666-6666>");
    printTABLE_SNAP();
    
    printf("\n\n");
    lookup_SNAP("<*,P. Patty,*,*>");
    printf("\n\n");
    delete_SNAP("<*,C. Brown,*,*>");
    printf("\n\n");
    
    // printf("CP table\n");
    initiate_CP();
    insertCP("<CS101,CS100>");
    insertCP("<EE200,EE005>");
    insertCP("<EE200,CS100>");
    insertCP("<CS120,CS101>");
    insertCP("<CS121,CS120>");
    insertCP("<CS205,CS101>");
    insertCP("<CS206,CS121>");
    insertCP("<CS206,CS205>");
    printTABLE_CP();

    printf("\n\n");
    lookup_CP("<*,CS100>");
    printf("\n\n");
    delete_CP("<*,CS100>");
    printf("\n\n");

    // printf("CDH table\n");
    initiate_CDH();
    insertCDH("<CS101,M,9AM>");
    insertCDH("<CS101,W,9AM>");
    insertCDH("<CS101,F,9AM>");
    insertCDH("<EE200,Tu,10AM>");
    insertCDH("<EE200,W,1PM>");
    insertCDH("<EE200,Th,10AM>");
    printTABLE_CDH();
    
    printf("\n\n");
    lookup_CDH("<EE200,*,*>");
    printf("\n\n");
    delete_CDH("<*,W,*>");
    printf("\n\n");
    
    // printf("CR table\n");
    initiate_CR();
    insertCR("<CS101,Turing Aud.");
    insertCR("<EE200,25 Ohm Hall>");
    insertCR("<PH100,Newton Lab.>");
    printTABLE_CR();
    
    printf("\n\n");
    lookup_CR("<*,*>");
    printf("\n\n");
    delete_CR("<*,Newton Lab.>");
    printf("\n\n");
    
    printf("\n\n PART 2 \n\n");
    
    NC_G("L. Van Pelt","CS101");
    NDH_R("P. Patty", "F", "9AM");
    
    printf("\n\n PART 3 \n\n");
    
    // select_("CSG",'C',"PH100");
    // select_("SNAP",'S',"67890");
    // select_("CDH", 'D', "Tu");
    // select_("CR", 'C', "CS101");
    // select_("CP", 'P', "CS205");
    
  
    printf("\n\n\n\n\n\n JOIN \n\n\n");
    
    joinCR_DH(select_("CR", 'C', "*"), select_("CDH", 'D', "*"));
    printTABLE_CRDH();
    
    return 0;
}
