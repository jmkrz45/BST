/*
    Project 4
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/
#include "bst.h"

#define WORD_SIZE 40

void lower_case_word( char *w )
{
  int i = 0;

  while (w[i] != '\0') {
    w[i] = tolower(w[i]);
    i++;
  }
}

void dump_dictionary( Pbst_t bst )
{
  int *num_items = ( int * )malloc( sizeof( int ) );
  int *height = ( int * )malloc( sizeof( int ) );

  stat_bst( bst, num_items, height );
  printf("Number of unique words:  %d\nHeight:  %d\n", *num_items, *height);
  void *order = start_bst_walk( bst );
  while( order )
  {
    printf("%s:  %d\n", ((Pdata_t)order)->word, ((Pdata_t)order)->frequency);
    order = next_bst_walk( bst );
  }
}

int main(void)
{
  char c, word[WORD_SIZE];
  int char_index = 0;
  Pbst_t bst = new_bst( cmp_fun );
  void *data, *key, *cur;
  int *depth = ( int * )malloc( sizeof( int ) );

  printf("Parsing input ...\n");
  /* Read in characters until end is reached */
  while((c = getchar()) != EOF)
  {
    if((c == ' ') || (c == ',') || (c == '.') || (c == '!') || (c == '"') ||
        (c == ':') || (c == '\n'))
      {
      /* End of a word */
      if( char_index )
      {
        /* Word is not empty */
        word[char_index] = '\0';
        lower_case_word(word);
        key = ( void * )malloc( sizeof( void ) );
        strcpy((char*)key, word);
        cur = find_bst( bst, key, depth);
        if( !cur )
        {
          /* Malloc new data node */
          Pdata_t new = ( Pdata_t )malloc( sizeof( data_t ) );
          new->frequency = 1;
          new->word = ( char * )malloc( sizeof( char ) * strlen( word ) );
          strcpy( new->word, key);
          /* Have void* set to new node */
          data = new;
          insert_bst( bst, key, data );
        }
        else
        {
          ((Pdata_t)cur)->frequency++;
        }
        char_index = 0;
      }
    }
    else
    {
      /* Continue assembling word */
      word[char_index++] = c;
    }
  }
  dump_dictionary( bst );
  free_bst( bst );
}

int cmp_fun( void *x, void *y )
{
  char *cur_key = (char*)x, *searched_key = (char*)y;
  int z = strcmp( cur_key, searched_key );
  return z;
}
