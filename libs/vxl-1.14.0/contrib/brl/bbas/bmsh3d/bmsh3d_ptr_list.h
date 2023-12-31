//:
// \file
// \brief 070510  A simple implementation of link list of NULL pointers.
// \author Ming-Ching Chang

#ifndef bmsh3d_ptr_list_h_
#define bmsh3d_ptr_list_h_

#include <vcl_set.h>
#include <vcl_cassert.h>

class bmsh3d_ptr_node
{
 protected:
  const void* ptr_;
  bmsh3d_ptr_node* next_;

 public:
  //====== Constructor/Destructor ======
  bmsh3d_ptr_node () {
    ptr_ = NULL;
    next_ = NULL;
  }
  bmsh3d_ptr_node (const void* ptr) {
    ptr_ = ptr;
    next_ = NULL;
  }

  //====== Data access functions ======
  const void* ptr() const {
    return ptr_;
  }
  void set_ptr (const void* ptr) {
    ptr_ = ptr;
  }

  bmsh3d_ptr_node* next() {
    return next_;
  }
  const bmsh3d_ptr_node* next() const {
    return next_;
  }
  void set_next (bmsh3d_ptr_node* next) {
    next_ = next;
  }
};

//: return size of the list.
inline unsigned int get_all_ptrs(const bmsh3d_ptr_node* head, vcl_set<const void*>& ptrs)
{
  unsigned int count = 0;
  bmsh3d_ptr_node const* curr = head;
  for (; curr != NULL; ++count, curr = curr->next()) {
    ptrs.insert(curr->ptr());
  }
#ifdef DEBUG
  assert(count == ptrs.size());
#endif
  return count;
}

//: return size of the list.
//  DEPRECATED!
inline unsigned int get_all_ptrs(const bmsh3d_ptr_node* head, vcl_set<void*>& ptrs)
{
  unsigned int count = 0;
  bmsh3d_ptr_node const* curr = head;
  for (; curr != NULL; ++count, curr = curr->next()) {
    ptrs.insert((void*)curr->ptr()); // casting away const!
    // TODO: FIX THIS BY USING THE OTHER get_all_ptrs() METHOD IN CALLER
  }
#ifdef DEBUG
  assert(count == ptrs.size());
#endif
  return count;
}

inline unsigned int count_all_ptrs (const bmsh3d_ptr_node* head)
{
  unsigned int count = 0;
  bmsh3d_ptr_node const* curr = head;
  for (; curr != NULL; ++count, curr = curr->next()) ;
  return count;
}

inline unsigned int clear_ptr_list (bmsh3d_ptr_node*& head)
{
  unsigned int count = 0;
  bmsh3d_ptr_node* curr = head;
  while (curr != NULL) {
    bmsh3d_ptr_node* tmp = curr;
    curr = curr->next();
    delete tmp;
    count++;
  }
  head = NULL;
  return count;
}

inline bool is_in_ptr_list (const bmsh3d_ptr_node* head, const void* input)
{
  bmsh3d_ptr_node const* curr = head;
  for (; curr != NULL; curr = curr->next()) {
    if (curr->ptr() == input)
      return true;
  }
  return false;
}

inline void add_to_ptr_list_head_ (bmsh3d_ptr_node*& head, bmsh3d_ptr_node* curr)
{
  assert (curr->next() == NULL);
  curr->set_next (head);
  head = curr;
}

inline void add_ptr_to_list (bmsh3d_ptr_node*& head, const void* input)
{
  assert (! is_in_ptr_list (head, input));
  assert (input != NULL);
  bmsh3d_ptr_node* curr = new bmsh3d_ptr_node (input);
  add_to_ptr_list_head_ (head, curr);
}

inline void add_ptr_check (bmsh3d_ptr_node*& head, const void* input)
{
  assert (! is_in_ptr_list (head, input));
  add_ptr_to_list (head, input);
}

inline bool check_add_ptr (bmsh3d_ptr_node*& head, const void* input)
{
  if (is_in_ptr_list (head, input))
    return false;
  add_ptr_to_list (head, input);
  return true;
}

inline bool del_ptr (bmsh3d_ptr_node*& head, const void* input)
{
  if (head == NULL)
    return false;
  if (head->ptr() == input) { //the head contains the input ptr.
    bmsh3d_ptr_node* tmp = head;
    head = head->next();
    delete tmp;
    return true;
  }

  bmsh3d_ptr_node* prev = head;
  bmsh3d_ptr_node* curr = prev->next();
  while (curr != NULL) {
    if (curr->ptr() == input) { //found, delete curr
      prev->set_next (curr->next());
      delete curr;
      return true;
    }
    prev = curr;
    curr = curr->next();
  }
  return false;
}

#endif

