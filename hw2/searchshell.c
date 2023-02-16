/*
 * Copyright ©2022 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Fall Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);

/*
Helper function to get a list of search results and
iterate through each result and print out the document 
and rank

Arguments:
  - DocTable* dt for finding documents
  - MemIndex* mi for getting search results
  - char** query for getting results from query
  - uint8_t query_len for length of query
Returns:
  - No returns
*/
static void ProcessQueries(DocTable* dt, MemIndex* mi, char** query, uint8_t query_len);

//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.
  
  // doc table and mem index
  DocTable* doc_table;
  MemIndex* mem_index;

  // declare input size, tokens, token save ptr
  int input_size = 1;
  char *tok;
  char *save_ptr;

  // allocate input
  char *input = (char*) malloc(sizeof(char) * input_size);

  printf("Indexing \'%s\'\n", argv[1]);

  // Crawl through input directory and ensure it isnt empty
  if (!CrawlFileTree(argv[1], &doc_table, &mem_index)) {
    Usage();
  }

  Verify333(doc_table != NULL);
  Verify333(mem_index != NULL);

  while (true) {
    char *tmp;
    int idx = 0;
    int input_char = -1;

    printf("enter query:\n");

    while (input_char) {
      input_char = tolower(getc(stdin));

      // Check for end
      if (input_char == EOF || input_char == '\n') {
        input_char = '\0';
      }
      // Check for realloc
      if (input_size <= idx) {
          input_size *= 2;
          tmp = (char*) realloc(input, sizeof(char) * input_size);

          if (input == NULL) {
            free(input);
            input = NULL;
            break;
          }
          input = tmp;
      }
      // Store input in char
      input[idx] = input_char;
      idx++;
    }

    // allocate for query char with tokens 
    char **query = (char**) malloc(input_size * sizeof(char *));
    Verify333(query != NULL);

    uint8_t query_len = 0;
    char *str = input;

    // loop to get tokens
    while (true) {
      tok = strtok_r(str, " ", &save_ptr);

      // break if token is null
      if (tok == NULL) {
        break;
      }
      // add to query
      query[query_len] = tok;
      query_len++;
      str = NULL;
    }

    ProcessQueries(doc_table, mem_index, query, query_len);
    free(query);
  }
  DocTable_Free(doc_table);
  MemIndex_Free(mem_index);

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

/*
Helper function to get a list of search results and
iterate through each result and print out the document 
and rank

Arguments:
  - DocTable* dt for finding documents
  - MemIndex* mi for getting search results
  - char** query for getting results from query
  - uint8_t query_len for length of query
Returns:
  - No returns
*/
static void ProcessQueries(DocTable* dt, MemIndex* mi, char** query, uint8_t query_len) {
  // list and iterator of search results and pointer for each result
  LinkedList *search_res;
  LLIterator *ll_it;
  SearchResult *res;

  // get search results
  search_res = MemIndex_Search(mi, query, query_len);
  
  if (search_res != NULL) {
    ll_it = LLIterator_Allocate(search_res);
    Verify333(ll_it != NULL);

    // loop search results and print out doc table name and rank
    while (LLIterator_IsValid(ll_it)) {
      LLIterator_Get(ll_it, (void **) &res);
      printf("  %s (%u)\n", DocTable_GetDocName(dt, res->doc_id), res->rank);
      LLIterator_Next(ll_it);
    }
    
    LLIterator_Free(ll_it);
  }
}