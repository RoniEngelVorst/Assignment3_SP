#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StrList.h"

typedef struct _node {
    char* _data;
    struct _node * _next;
} Node;

/*
 * StrList represents a StrList data structure.
 */
struct _StrList{
    struct _node* _head;
    size_t _size;
};
typedef struct _StrList StrList;

Node* Node_alloc(const char* data, Node* next) {
	Node* p = (Node*)malloc(sizeof(Node));
    if (p) {
        p->_data = (char*)malloc(strlen(data) + 1);
        if (p->_data) {
            strcpy(p->_data, data);
            p->_next = next;
            return p;
        } else {
            free(p);
            return NULL; // Handle memory allocation failure
        }
    }
    return NULL; // Handle memory allocation failure
}

void Node_free(Node* node) {
    free(node->_data);
	free(node);
}

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc(){
    StrList* p= (StrList*)malloc(sizeof(StrList));
	p->_head= NULL;
	p->_size= 0;
	return p;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList){
    if (StrList == NULL || StrList->_head == NULL) return;

    Node* p1 = StrList->_head;
    Node* p2;

    while(p1) {
        p2 = p1;
        p1 = p1->_next;
        Node_free(p2);
    }

    StrList->_head = NULL; // Set the head pointer to NULL to indicate an empty list
    StrList->_size = 0;
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data){
    if (StrList == NULL) {
        return; // Check for NULL StrList
    }

    Node* n = Node_alloc(data, NULL);
    if (n == NULL) {
        return; // Handle memory allocation failure
    }

    if (StrList->_head == NULL) {
        StrList->_head = n;
    } else {
        Node* temp = StrList->_head;
        while (temp->_next != NULL) {
            temp = temp->_next;
        }
        temp->_next = n;
    }
    StrList->_size++;
    
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList, const char* data,int index){
    if (index < 0 || index > StrList->_size) {
        return;
    }

    Node* n = Node_alloc((char*)data, NULL);
    if(n == NULL){
        return;
    }

    if(index == 0){
        n->_next = StrList->_head;
        StrList->_head = n;
        StrList->_size++;
        return;
    }
    else{
        Node* temp = StrList->_head;
        for(int i = 0; i < index-1; i++){
            temp = temp->_next;
        }
        n->_next = temp->_next;
        temp->_next = n;
        StrList->_size++;
    }
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList){
    return StrList->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    if(StrList == NULL){
        return;
    }
    if(StrList->_head == NULL){
        printf("\n");
        return;
    }
    Node* temp = StrList->_head;
    while(temp->_next != NULL){
        printf("%s ", temp->_data);
        temp = temp->_next;
    }
    printf("%s", temp->_data);
    printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index){
    if(index < 0 || index > Strlist->_size){
        return;
    }
    if(index == 0){
        printf("%s", Strlist->_head->_data);
        return;
    }
    Node* temp = Strlist->_head;
    for(int i = 0; i < index; i++){
        temp = temp->_next;
    }
    printf("%s", temp->_data);
    printf("\n");

}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist){
    int ans = 0;
    Node* temp = Strlist->_head;
    while(temp != NULL){
        int len = temp->_data ? strlen(temp->_data) : 0;
        ans = ans + len;
        temp = temp->_next;
    }
    return ans;

}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data){
    int ans = 0;
    Node* temp = StrList->_head;
    while(temp != NULL){
        if(strcmp(data, temp->_data) == 0){
            ans++;
        }
        temp = temp->_next;
    }
    return ans;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data){
    Node* temp = StrList->_head;
    Node* prev = NULL;

     while (temp != NULL) {
        if (strcmp(data, temp->_data) == 0) {
            Node* del = temp;
            if (prev != NULL) {
                prev->_next = temp->_next;
            } else {
                StrList->_head = temp->_next;
            }
            temp = temp->_next;
            free(del);
            // Decrement size of the list
            StrList->_size--;
        } else {
            prev = temp;
            temp = temp->_next;
        }
    }
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    if(StrList == NULL){
        return;
    }
    if(index < 0 || index >= StrList->_size){
        return;
    }
    if(index == 0){
        Node* del = StrList->_head;
        StrList->_head = del->_next;
        Node_free(del);
    }

    else{
        Node* temp = StrList->_head;
        for(int i = 0; i < index-1; i++){
            temp = temp->_next;
        }
        Node* del = temp->_next;
        temp->_next = del->_next;
        Node_free(del);
    }
    StrList->_size--;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1 == NULL && StrList2 == NULL){
        return 1;
    }
    if(StrList1->_size != StrList2->_size){
        return 0;
    }
    else{
        Node* temp1 = StrList1->_head;
        Node* temp2 = StrList2->_head;
        while(temp1 != NULL){
            if(strcmp(temp1->_data, temp2->_data) != 0){
                return 0;
            }
            temp1 = temp1->_next;
            temp2 = temp2->_next;
        }
        return 1;
    }
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList){
    if(StrList == NULL){
        return NULL;
    }
    struct _StrList* copy = StrList_alloc();
    if(copy == NULL){
        return NULL; // Handle allocation failure
    }
    copy->_size = 0;
    Node* temp = StrList->_head;
    while(temp != NULL){
        Node* n = Node_alloc(temp->_data, NULL);
        if(n == NULL){
            StrList_free(copy); // Free allocated memory if insertion fails
            return NULL; // Handle allocation failure
        }
        // Insert the node at the end of the copy list
        if(copy->_head == NULL){
            copy->_head = n;
        }
        else {
            Node* last = copy->_head;
            while(last->_next != NULL){
                last = last->_next;
            }
            last->_next = n;
        }
        copy->_size++;
        temp = temp->_next;
    }
    return copy;
}

/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList){
    if(StrList == NULL){
        return;
    }
    if(StrList->_head == NULL){
        return;
    }
    Node* current = StrList->_head;
    Node* prev = NULL;
    Node* next = NULL;

    while(current != NULL){
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }
    StrList->_head = prev;
}

//helper

int compareStrings(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort( StrList* StrList){
     if (StrList == NULL || StrList->_size < 2) {
        return;
    }

    char **arr = (char **)malloc(StrList->_size * sizeof(char *));
    if (arr == NULL) {
        // Handle memory allocation failure
        return;
    }

    Node *temp = StrList->_head;
    int i = 0;
    while (temp != NULL && i < StrList->_size) {
        arr[i] = strdup(temp->_data); // Allocate new memory for each string
        if (arr[i] == NULL) {
            // Handle memory allocation failure
            // Free allocated memory before returning
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return;
        }
        temp = temp->_next;
        i++;
    }

    qsort(arr, StrList->_size, sizeof(char *), compareStrings);
    temp = StrList->_head;
    i = 0;
    while (temp != NULL && i < StrList->_size) {
        free(temp->_data); // Free original memory
        temp->_data = arr[i]; // Assign sorted string
        temp = temp->_next;
        i++;
    }

    // Free the array
    free(arr);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList){
    Node* temp = StrList->_head;
    while(temp->_next != NULL){
        if(strcmp(temp->_data, temp->_next->_data) > 0){
            return 0;
        }
        temp = temp->_next;
    }
    return 1;
}
