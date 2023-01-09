#ifndef LINKED_LIST_POST
#define LINKED_LIST_POST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Publicacion {
    char texto[100];
} typedef Publicacion;

typedef Publicacion Type;

typedef struct Node_Type {
  Type data;
  struct Node_Type* next; // Point the next node.
} Node;

typedef struct LinkedList_Type {
  Node* first;
  Node* last;
} LinkedList;

LinkedList* linked_list_constructor();
void linked_list_destroyer(LinkedList* this);
bool linked_list_insert(LinkedList* this, Type value);
bool linked_list_is_empty(LinkedList* this);
void linked_list_peeker(LinkedList* this);

static Node* new_node(Type value) {
    Node* new = (Node*) malloc(sizeof(Node));
    if(new) {
        new->data = value;
        new->next = NULL;
    }

    return new;
}

static void delete_node(Node* node) {
    if (node) free(node); 
}

LinkedList* linked_list_constructor() {
  LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));
  if( this ) {
    this->first = NULL;
    this->last = NULL;
  }
  
  return this;
}

void linked_list_destroyer(LinkedList* this) {
  if( this ) {
    while( this->first ) {
      Node* tmp=this->first->next;
      delete_node(this->first);
      this->first=tmp;
    }
  }

  free(this);
}


bool linked_list_insert(LinkedList* this, Type value) {
  Node* node = new_node(value);
  if( !node ) return false;

  if ( linked_list_is_empty(this) ) {
    this->first = node;
    this->last = node;
  } else {
    this->last->next = node;
    this->last = node;
  }
  return false;
}

bool linked_list_is_empty(LinkedList* this) {
    if( this->first == NULL ) return true;
    return false;
}

void linked_list_peeker(LinkedList* this) {
    if( this == NULL || linked_list_is_empty(this) ) {
        printf("No hay publicaciones");
        return;
    } 
    Node* iterator = this->first;
    int it = 0;
    while( iterator != NULL ) {
        printf("publicacion # %d: %s\n", it + 1, iterator->data.texto);
        iterator = iterator->next;
        it++;
    }
}

#endif /*END LINKED_LIST_POST*/
