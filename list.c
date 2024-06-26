#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = (List *) malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if(list->current == NULL) return NULL;
  if(list->current->next == NULL) return NULL;
  list->current = list->current->next;
  return list->current->data ;
}

void * lastList(List * list) {
  if(list->tail  == NULL) return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if(list->current == NULL) return NULL;
  if(list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *actual = createNode(data);
  if(list->current == NULL)
  {
    list->head = actual;
    list->tail = actual;
    return;
  }
  actual->next = list->head;
  list->head->prev = actual;
  list->head = actual;
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *actual = createNode(data);
  
  if(list->current == list->head)
  {
    pushFront(list, data);
    /*actual->prev = list->current;
    actual->next = nextList(list);
    list->head->next = actual;*/
  }

  if(list->current == list->tail)
  {
    actual->prev = list->tail;
    list->tail->next = actual;
    list->tail = actual;
  }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *actual = list->current;
  void *dato = actual->data;
  
  if(list->current == list->head)
  {
    list->head = list->head->next;
    list->head->prev = NULL;
    list->current = list->head;
  }
  else if(list->current == list->tail)
  {
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    list->current = list->tail;
  }
  else
  {
    Node *anteriorCurrent = list->current->prev;
    Node *siguienteCurrent = list->current->next;
    anteriorCurrent = list->current->next;
    siguienteCurrent = list->current->prev;
    list->current = list->current->next;
  }
    
  free(actual);
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}