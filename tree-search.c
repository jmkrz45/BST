/*
    Project 4
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/

#include "bst.h"
#define NUM_VALUES 10000
#define TRUE 1
#define FALSE 0

void create_data( Pbst_t bst )
{
  int i, *data, *key;
  for (i = 0; i < NUM_VALUES; i++)
  {
    data = ( int * )malloc( sizeof( int ) );
    key = ( int * )malloc( sizeof( int ) );
    *data = ( rand() % NUM_VALUES );
    *key = *data;
    insert_bst(bst, key, data);
  }
  int *num_items = ( int * )malloc( sizeof( int ) );
  int *height = ( int * )malloc( sizeof( int ) );
  stat_bst( bst, num_items, height );
  printf("Number of Nodes: %d\nHeight of BST: %d\n", *num_items, *height);
}

int main()
{
  int *depth = ( int * )malloc( sizeof( int ) );
  void *key = ( void * )malloc( sizeof (void ) );
  int value;

  Pbst_t bst = new_bst( cmp_fun );
  create_data(bst);
  while ( TRUE )
  {
    printf("Enter a number to find:  ");
    scanf("%d", &value );
    key = &value;
    if ( find_bst(bst, key, depth) )
      printf("Found the number %d after %d tries\n", *(int*)key, *depth);
    else
      printf("Could not find the number %d in the tree\n", *(int*)key);
  }
  free_bst( bst );
}

int cmp_fun( void *x, void *y )
{
  int cur_key = *(int*)x, searched_key = *(int*)y;
  if( cur_key < searched_key ) //Go right
    return -1;
  else if( cur_key > searched_key ) // Go left
    return 1;
  else
    return 0;
}
