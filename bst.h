/*
    Project 4
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_ {
  int frequency;
  char *word;
} data_t, *Pdata_t;

typedef struct node_ {
  void *key, *data;
  struct node_ *left, *right;
} node_t, *Pnode_t;

typedef struct bst_ {
  Pnode_t root;
  int (*cmp_func)( void *, void * );
  int height, num_items, cur_walk_index;
  Pnode_t *cur_walk;
} bst_t, *Pbst_t;


/*************************/
/*** HELPER PROTOTYPES ***/
/*************************/
int cmp_fun( void *x, void *y );
Pnode_t new_node( void *key, void *data );
void free_node( Pnode_t node );
void insert_node( Pbst_t bst, Pnode_t cur, Pnode_t new, int depth );
void *find_node( Pbst_t bst, Pnode_t cur, void *key, int *depth);
void ascending_order( Pbst_t bst, Pnode_t cur );
/***************************/
/*** REQUIRED PROTOTYPES ***/
/***************************/
Pbst_t new_bst( int (*cmp_func)( void *, void * ) );
void free_bst( Pbst_t bst );
void insert_bst( Pbst_t bst, void *key, void *data );
void *find_bst( Pbst_t bst, void *key, int *depth );
void stat_bst( Pbst_t bst, int *num_items, int *height );
void *start_bst_walk( Pbst_t bst );
void *next_bst_walk( Pbst_t bst );
