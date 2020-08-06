#include "Linked_List.h"

// create and delete the list
List* createList(){
    List* tempList = (List*)malloc(sizeof(List*));
    tempList->size = 0;
    tempList->head = NULL;

    if(NULL == tempList)
        return NULL;
    
    if(NULL == tempList->head)
        return NULL;

    return tempList;
}

void deleteList(List** currentList){
    while(NULL != currentList){
        Node* currentNode = (*currentList)->head;
        (*currentList)->head = (*currentList)->head->next;
        free(currentNode);
    }
    free(currentList);
}

// manipulate data from front
void push(List* currentList, InfoNode* info){
    Node* newHead = malloc(sizeof(Node));

    if(NULL == newHead)
        return NULL;

    newHead->info = info;
    newHead->next = currentList->head;
    currentList->head = newHead;
    currentList->size++;

    free(newHead);
}

// manipulate data from rear
void insertRear(List* currentList, InfoNode* info){
    Node* currentNode = malloc(sizeof(Node));
    currentNode->next = NULL;

    currentNode->info = info;
    currentList->tail->next = currentNode;
    currentList->tail = currentNode;
    currentList->size ++;

    free(currentNode); 
}


// manipulate at index
Node* getElementByKey(List* currentList, unsigned char *key){
    Node* currentElement = malloc(sizeof(Node));
    currentElement = currentList->head;
    while(currentElement->info->key != key){
        currentElement = currentElement->next;
    }
    return currentElement;
}