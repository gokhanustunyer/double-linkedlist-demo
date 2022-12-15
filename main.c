#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct node node;
struct node
{
    int       data;    
    node     *next;
    node     *prev;
};

typedef struct {
    node   *first;
    node   * last;
    int     count;

} DoubleLinkedList;

bool deleteNode(DoubleLinkedList *lst);
bool deleteNodeFirst(DoubleLinkedList *lst);
bool deleteNodeByIndex(DoubleLinkedList *lst, int index);
bool insertNode(DoubleLinkedList *lst, int index, int value);
bool addNode(DoubleLinkedList *lst, int value);
bool addNodeFirst(DoubleLinkedList *lst, int value);
void printLinkedList(DoubleLinkedList *lst);
node* allocate();

int main(){
    DoubleLinkedList lst;
    lst.count = 0;
    lst.first = lst.last = NULL;

    for (int i=10;i<21;i++){
        addNode(&lst, i);
    }
    for (int j=9;j>-1;j--){
        addNodeFirst(&lst, j);
    }

    // for (int k=0;k<21;k++){
    //     deleteNode(&lst);
    // }
    printLinkedList(&lst);

    return 0;
}

bool addNode(DoubleLinkedList *lst, int value){
    node        *new_node;
    new_node = allocate();
    new_node -> data = value;
    new_node -> next = NULL;
    if (lst -> first == NULL){
        new_node -> prev = NULL;
        lst -> last = lst -> first = new_node;
    }
    else{
        new_node -> prev = lst -> last;
        lst -> last -> next = new_node;
        lst -> last = new_node;
    }
    lst -> count ++;
    return true;
}


bool addNodeFirst(DoubleLinkedList *lst, int value){
    node    * new_node;
    new_node = allocate();
    new_node -> data = value;
    new_node -> prev = NULL;
    if (lst -> first == NULL){
        new_node -> prev = NULL;
        lst -> last = lst -> first = new_node;
    }

    else{
        new_node -> next = lst -> first; 
        lst -> first -> prev = new_node;
        lst -> first = new_node;
    }
    lst -> count ++;
    return true;
}

bool insertNode(DoubleLinkedList *lst, int index, int value){
    node    * new_node, *itn;
    new_node =    allocate();
    new_node -> data = value;

    if (index >= lst -> count){
        printf("\nInvalid Index!\n");
        return 0;
    }

    itn = lst -> first;
    for (int i=0;i<index;i++){
            itn = itn -> next;
    }
    new_node -> prev = itn -> prev;
    itn -> prev -> next = new_node;
    new_node -> next = itn;
    itn -> prev = new_node;

    return 1;
}

bool deleteNodeFirst(DoubleLinkedList *lst){
    node    * delete;
    delete = lst -> first;
    if (delete == NULL){
        printf("\nList is Empty!\n");
        return 0;
    }

    lst -> first = lst -> first -> next;
    lst -> first -> prev = NULL;    
    free(delete);
    lst -> count --;
    return 1;
}


bool deleteNode(DoubleLinkedList *lst){
    node    * delete;
    delete = lst -> last;
    
    lst -> last = lst -> last -> prev;
    lst -> last -> next = NULL;
    free(delete);
    lst -> count --;
    return 1;
}

bool deleteNodeByIndex(DoubleLinkedList *lst, int index){
    node    * itn, * delete;

    if (index >= lst -> count){
        printf("\nInvalid Index!\n");
        return 0;
    }

    itn = lst -> first;
    for (int i=0;i<index;i++){
            itn = itn -> next;
    }
    delete = itn;
    itn -> prev -> next = itn -> next;

    free(delete);
    lst -> count --;
    return 1;
}


void printLinkedList(DoubleLinkedList *lst){
    node        *itn;
    itn = lst->first;

    while (itn != NULL){
        printf("%d ", itn->data);
        itn = itn->next;
    }
}


node* allocate(){
    return (node*)malloc(sizeof(node));
}

