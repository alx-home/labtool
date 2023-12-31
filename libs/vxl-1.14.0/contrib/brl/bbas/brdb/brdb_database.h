#ifndef brdb_database_h_
#define brdb_database_h_

//:
// \file
// \brief A database
// \author Yong Zhao
// \date Tue Mar 23, 2007
//
// \verbatim
//  Modifications
// \endverbatim



#include <vcl_vector.h>
#include <vcl_map.h>
#include <vcl_set.h>
#include <vcl_string.h>
#include <vbl/vbl_ref_count.h>
#include <brdb/brdb_relation_sptr.h>
#include <brdb/brdb_tuple_sptr.h>
#include <brdb/brdb_selection_sptr.h>
#include <brdb/brdb_query.h>
#include <brdb/brdb_database_sptr.h>
#include <vsl/vsl_binary_io.h>


class brdb_database : public vbl_ref_count
{
public:
  //: Constructor - create an empty database;
  brdb_database();

  //: Constructor - create a database populated with relations
  brdb_database(vcl_vector<brdb_relation_sptr> relations, vcl_vector<vcl_string> relation_names);

  //: get the number of relations 
  int size() const;

  //: clear the database
  void clear();

  //: check whether a relation exists
  bool exists(const vcl_string& relation_name) const;

  //: check whether a relation exists with the given attribute
  bool exists(const vcl_string& relation_name, const vcl_string& attribute_name) const;

  //: check whether the database is empty;
  bool empty() const {return relations_.empty();}

  //: add a tuple into a relation
  bool add_tuple(const vcl_string& relation_name, const brdb_tuple_sptr& new_tuple);

  //: remove one relation
  bool remove_relation(const vcl_string& relation_name);

  //: clear one relation
  bool clear_relation(const vcl_string& relation_name);

  //: add a new relation to the database
  bool add_relation(const vcl_string& relation_name, const brdb_relation_sptr& new_relation);

  //: get a relation by name
  brdb_relation_sptr get_relation(const vcl_string& name) const;

  //: print the whole database
  void print() const;

  //: get all the relation names
  vcl_set<vcl_string> get_all_relation_names() const;

  //: SQL join of two relations in the database, returning the result
  brdb_relation_sptr join(const vcl_string& r1, const vcl_string& r2) const;

  //: SQL join of two relations in the database, adding the result to the database
  bool join(const vcl_string& r1, const vcl_string& r2, const vcl_string& result );

  //: submit a query, get a selection which contains the result of query.
  brdb_selection_sptr select(const vcl_string& relation_name, brdb_query_aptr q) const;

  //: merge another database into this one
  bool merge(const brdb_database_sptr& other);

  //: binary IO write
  void b_write(vsl_b_ostream os);

  //: binary IO read
  void b_read(vsl_b_istream is);

private:
  vcl_map<vcl_string, brdb_relation_sptr> relations_;
};




#endif  // brdb_database_h_
