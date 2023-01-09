#ifndef LINKED_LIST_FRIEND
#define LINKED_LIST_FRIEND

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Amigo {
    char nombre_usuario[50];
} typedef Amigo;

typedef struct Node_friend_Type {
  Amigo data;
  struct Node_friend_Type* next; // Point the next node.
} Node_friend;

typedef struct LinkedList_Friend_Type {
  Node_friend* first;
  Node_friend* last;
} LinkedList_Friend;

LinkedList_Friend* linked_list_constructor_friend();
void linked_list_destroyer_friend(LinkedList_Friend* this);
bool linked_list_insert_friend(LinkedList_Friend* this, Amigo value);
bool linked_list_is_empty_friend(LinkedList_Friend* this);
void linked_list_peeker_friend(LinkedList_Friend* this);

static Node_friend* new_node_friend(Amigo value) {
    Node_friend* new = (Node_friend*) malloc(sizeof(Node_friend));
    if(new) {
        new->data = value;
        new->next = NULL;
    }

    return new;
}

static void delete_node_friend(Node_friend* node) {
    if (node) free(node); 
}

LinkedList_Friend* linked_list_constructor_friend() {
  LinkedList_Friend* this = (LinkedList_Friend*) malloc(sizeof(LinkedList_Friend));
  if( this ) {
    this->first = NULL;
    this->last = NULL;
  }
  
  return this;
}

void linked_list_destroyer_friend(LinkedList_Friend* this) {
  if( this ) {
    while( this->first ) {
      Node_friend* tmp=this->first->next;
      delete_node_friend(this->first);
      this->first=tmp;
    }
  }

  free(this);
}


bool linked_list_insert_friend(LinkedList_Friend* this, Amigo value) {
  Node_friend* node = new_node_friend(value);
  if( !node ) return false;

  if ( linked_list_is_empty_friend(this) ) {
    this->first = node;
    this->last = node;
  } else {
    this->last->next = node;
    this->last = node;
  }
  return false;
}

bool linked_list_is_empty_friend(LinkedList_Friend* this) {
    if( this->first == NULL ) return true;
    return false;
}

void linked_list_peeker_friend(LinkedList_Friend* this) {
    if( this == NULL || linked_list_is_empty_friend(this) ) {
        printf("No hay amigos");
        return;
    } 
    Node_friend* iterator = this->first;
    int it = 0;
    while( iterator != NULL ) {
        printf("amigo # %d: %s\n", it + 1, iterator->data.nombre_usuario);
        iterator = iterator->next;
        it++;
    }
}

#endif /*END LINKED_LIST_FRIEND*/
