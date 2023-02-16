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

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {
  
/*
 * Helper function that takes two DocIDElementHeader lists and compares them
 * to create a combined list with updated position numbers if the same 
 * doc id is found in both lists
 * 
 * Arguments:
 * - const list<DocIDElementHeader> &list_1 for first list to compare
 * - const list<DocIDElementHeader> &list_2 for second list to compare
 * 
 * Return:
 * - a list<DocIDElementHeader> that holds the combined lists with updated
 *   positions numbers for each doc id
*/
static list<DocIDElementHeader> Combine_Lists (const list<DocIDElementHeader> &list_1,
                                               const list<DocIDElementHeader> &list_2);

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;
  
  // iterate through index files
  for (int i = 0; i < array_len_; i++) {
    // declare readers for index files
    IndexTableReader* itr = itr_array_[i];
    DocTableReader* dtr = dtr_array_[i];

    // initialize element list
    list<DocIDElementHeader> el_list;

    // iterate through queries
    for (size_t j = 0; j < query.size(); j++) {
      
      DocIDTableReader* didtr_curr = itr->LookupWord(query[j]); // look up query

      // if query not found clear element list break
      if (didtr_curr == NULL) {
        el_list.clear();
        delete(didtr_curr);
        break;
      }

      // if first query, add doc id list to element list
      if (j == 0) {
        el_list = didtr_curr->GetDocIDList();
        continue;
      }

      // if not first query add to curr element list
      list<DocIDElementHeader> el_list_curr = didtr_curr->GetDocIDList();

      // combine overall element list and curr element list to update num positions
      el_list = Combine_Lists(el_list, el_list_curr);
      
      delete(didtr_curr); // delete curr DocIDTableReader
    }

    if (el_list.size() == 0) {
      continue; // if no elements in list go to next index file
    } else {
      for (DocIDElementHeader el: el_list) { // iterate through elements
        QueryProcessor::QueryResult query_res;
        DocID_t doc_id = el.doc_id;

        // get doc name from id and rank from num positions
        Verify333(dtr->LookupDocID(doc_id, &query_res.document_name));
        query_res.rank = el.num_positions;

        final_result.push_back(query_res); // push result to final list
      }
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

/*
 * Helper function that takes two DocIDElementHeader lists and compares them
 * to create a combined list with updated position numbers if the same 
 * doc id is found in both lists
 * 
 * Arguments:
 * - const list<DocIDElementHeader> &list_1 for first list to compare
 * - const list<DocIDElementHeader> &list_2 for second list to compare
 * 
 * Return:
 * - a list<DocIDElementHeader> that holds the combined lists with updated
 *   positions numbers for each doc id
*/
static list<DocIDElementHeader> Combine_Lists (const list<DocIDElementHeader> &list_1,
                                               const list<DocIDElementHeader> &list_2) {
  list<DocIDElementHeader> combined; // combined lists

  // iterate through first list
  for (DocIDElementHeader el_1: list_1) {
    // get doc id and position numbers
    DocID_t doc_id = el_1.doc_id;
    int num_positions = el_1.num_positions;

    bool id_found = false; // to check if doc ids match

    // iterate through second list
    for (DocIDElementHeader el_2: list_2) {
      if (el_2.doc_id == doc_id) { // if doc ids match
        id_found = true;
        num_positions += el_2.num_positions; // update positions
        break;
      }
    }

    if (id_found) {
      // push new DocIDElementHeader to combined list
      combined.push_back(DocIDElementHeader(doc_id, num_positions));
    }
  }
  return combined; // return combined list
}

}  // namespace hw3
