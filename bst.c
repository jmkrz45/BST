/*
    Project 4
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/
#include "bst.h"

/***************************/
/*** HELPER DECLARATIONS ***/
/***************************/
Pnode_t new_node( void *key, void *data )
{
  Pnode_t new = ( Pnode_t )malloc( sizeof( node_t ) );
  new->key = key;
  new->data = data;
  new->left = new->right = NULL;
  return new;
}
void free_node( Pnode_t node )
{
  if ( !node )
      return;
  free_node( node->left );
  free_node( node->right );
  free( node->key );
  free( node->data );
  free( node );
  return;
}
void insert_node( Pbst_t bst, Pnode_t cur, Pnode_t new, int depth )
{
  int compare = (*(bst->cmp_func))( new->key, cur->key );
  depth++; // Now atleast beyond 2nd layer
  if( compare == 0 ) // Same node found, free it
    free( new );
  if( compare >= 1 ) // Greater than, go right update stats
  {
    if( !cur->right )
    {
      bst->num_items++;
      if(depth > bst->height)
        bst->height = depth;
      cur->right = new;
    }
    else
      insert_node( bst, cur->right, new, depth );
  }
  if( compare <= -1 ) // Less than, go left update stats
  {
    if( !cur->left )
    {
      bst->num_items++;
      if(depth > bst->height)
        bst->height = depth;
      cur->left = new;
    }
    else
      insert_node( bst, cur->left, new, depth );
  }
}
void *find_node( Pbst_t bst, Pnode_t cur, void *key, int *depth)
{
  int compare = (*(bst->cmp_func))( key, cur->key );
  *depth = *depth + 1; // Increase depth/height counter to be dependently assigned later
  if( compare >= 1 ) // Greater than, go to the right
  {
    if( !cur->right )
      return NULL;
    else
      return( find_node( bst, cur->right, key, depth ) );
  }
  else if( compare <= -1 ) // Less than, go to the left
  {
    if( !cur->left )
      return NULL;
    else
      return( find_node( bst, cur->left, key, depth ) );
  }
  else
    return( cur->data );
}
void ascending_order( Pbst_t bst, Pnode_t cur )
{
  if (cur->left)
    ascending_order( bst, cur->left);
  bst->cur_walk[bst->cur_walk_index] = cur->data;
  bst->cur_walk_index++;
  if (cur->right)
    ascending_order( bst, cur->right);
}
/*****************************/
/*** REQUIRED DECLARATIONS ***/
/*****************************/
Pbst_t new_bst( int (*cmp_func)(void *, void *) )
{
  Pbst_t new = ( Pbst_t )malloc( sizeof( bst_t ) );
  new->root = NULL;
  new->cmp_func = cmp_fun;
  new->height = new->num_items = new->cur_walk_index = 0;
  return( new );
}
void free_bst( Pbst_t bst )
{
  if ( bst )
  {
    if( bst->root )
      free_node( bst->root );
    // free node_t *array once created
    free( bst );
  }
  return;
}
void insert_bst( Pbst_t bst, void *key, void *data )
{
  Pnode_t new = new_node(key, data);
  Pnode_t cur = bst->root;
  if( !cur ) //Need root if not yet establised
  {
    bst->root = new;
    bst->num_items = bst->height = 1;
    return;
  }
  int compare = (*(bst->cmp_func))( new->key, cur->key );
  int depth = 2; // Now beyond root, 2nd layer deep
  if( compare == 0 ) // Same data, do not insert
    free( new );
  if( compare >= 1 ) // Greater than, go right
  {
    if( !cur->right ) // Nothing there, insert
    {
      bst->num_items++;
      if(depth > bst->height)
        bst->height = depth;
      cur->right = new;
    }
    else
      insert_node( bst, cur->right, new, depth );
  }
  if( compare <= -1 ) // Less than, go left
  {
    if( !cur->left ) // Nothing there, insert
    {
      bst->num_items++;
      if(depth > bst->height)
        bst->height = depth;
      cur->left = new;
    }
    else
      insert_node( bst, cur->left, new, depth );
  }
}
void *find_bst( Pbst_t bst, void *key, int *depth )
{
  Pnode_t cur = bst->root;
  if( !cur ) // No root in the tree!?
    return NULL;
  int compare = (*(bst->cmp_func))( key, cur->key );
  *depth = 1;
  if( compare >= 1 ) // Greater than, go to the right
  {
    if( !cur->right ) // Not found
      return NULL;
    else
      return( find_node( bst, cur->right, key, depth ) );
  }
  if( compare <= -1 ) // Less than, go to the left
  {
    if( !cur->left ) // Not found
      return NULL;
    else
      return( find_node( bst, cur->left, key, depth ) );
  }
  if( compare == 0 )
    return( cur->data );
  else
    return NULL;
}
void stat_bst( Pbst_t bst, int *num_items, int *height )
{
  *num_items = bst->num_items;
  *height = bst->height;
}
void *start_bst_walk( Pbst_t bst )
{
  bst->cur_walk_index = 0;
  bst->cur_walk = (void * )malloc( ( bst->num_items )*sizeof( void ) );
  ascending_order( bst, bst->root );
  bst->cur_walk_index = 0;
  return( bst->cur_walk[bst->cur_walk_index] );
}
void *next_bst_walk( Pbst_t bst )
{
  bst->cur_walk_index++;
  if(bst->cur_walk_index <= bst->num_items)
    return(bst->cur_walk[bst->cur_walk_index]);
  else
    return NULL;
}
