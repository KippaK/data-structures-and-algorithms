template <class C>
struct Node {
//  data members
   C entry;
   Node<C> *next;
   
//  constructors
   Node();
   Node(C, Node<C> *link_next = NULL);
};

template <class C>
Node<C>::Node()
{
   next = NULL;
}

template <class C>
Node<C>::Node (C data, Node<C> *link_next)
{
   entry = data;
   next = link_next;
}

template <class C>
class List {
public:
//  Specifications for the methods of the list ADT go here.
 
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(C &));
   Error_code retrieve(int position, C &x) const;
   Error_code replace(int position, const C &x);
   Error_code remove(int position, C &x);
   Error_code insert(int position, const C &x);
 
//  The following methods replace compiler-generated defaults.
   ~List();
   List(const List<C> &copy);
   void operator =(const List<C> &copy);
protected:
//  Data members for the linked list implementation now follow.
   int count;
   Node<C> *head;

//  The following auxiliary function is used to locate list positions
   Node<C> *set_position(int position) const;
};

template <class C>
List<C>::List()
/* 
 
Post: The List is initialized to be empty.
 
*/

{
   count = 0;
   head = NULL;
}
 
template <class C>
void List<C>::clear()
/* 
 
Post: The List is cleared.
 
*/

{
   Node<C> *p, *q;

   for (p = head; p; p = q) {
      q = p->next;
      delete p;
   }
   count = 0;
   head = NULL;
}
 
template <class C>
int List<C>::size() const
/* 
 
Post: The function returns the number of entries in the List.
 
*/

{
   return count;
}
 
template <class C>
bool List<C>::empty() const
/* 
 
Post: The function returns true or false according as the List is empty or not.
 
*/

{
   return count <= 0;
}
 
template <class C>
bool List<C>::full() const
/* 
 
Post: The function returns 1 or 0 according as the List is full or not.
 
*/

{
   return false;
}
 
template <class C>
void List<C>::traverse(void (*visit)(C &))
/* 
 
Post: The action specified by function (*visit) has been performed on every
entry of the List, beginning at position 0 and doing each in turn.
 
*/

{
   Node<C> *q;

   for (q = head; q; q = q->next)
      (*visit)(q->entry);
}
 
template <class C>
Error_code List<C>::insert(int position, const C &x)
/* 
 
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1, and
x is inserted at position of the List.

 
Else:
The function fails with a diagnostic error code.
 
*/
{
   if (position < 0 || position > count)
      return utility_range_error;
   Node<C> *new_node, *previous, *following;
   if (position > 0) {
      previous = set_position(position - 1);
      following = previous->next;
   }
   else following = head;
   new_node = new Node<C>(x, following);
   if (new_node == NULL)
      return overflow;
   if (position == 0)
      head = new_node;
   else
      previous->next = new_node;
   count++;
   return success;
}
 
template <class C>
Error_code List<C>::retrieve(int position, C &x) const
/* 
 
Post: If the List is not full and 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is copied to x.
Otherwise the function fails with an error code of range_error.
 
*/

{
   Node<C> *current;
   if (position < 0 || position >= count) return utility_range_error;
   current = set_position(position);
   x = current->entry;
   return success;
}
 
template <class C>
Error_code List<C>::replace(int position, const C &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is replaced by x,
all other entries remain unchanged.
Otherwise the function fails with an error code of utility_range_error.
 
*/

{
   Node<C> *current;
   if (position < 0 || position >= count) return utility_range_error;
   current = set_position(position);
   current->entry = x;
   return success;
}
 
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is removed
from the List, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x records a copy of
the entry formerly in position.
Otherwise the function fails with a diagnostic error code.
 
*/

template <class C>
Error_code List<C>::remove(int position, C &x)
{
   Node<C> *prior, *current;
   if (count == 0) return fail;
   if (position < 0 || position >= count) return utility_range_error;

   if (position > 0) {
      prior = set_position(position - 1);
      current = prior->next;
      prior->next = current->next;
   }

   else {
      current = head;
      head = head->next;
   }

   x = current->entry;
   delete current;
   count--;
   return success;
}
 
template <class C>
Node<C> *List<C>::set_position(int position) const
/*   
Pre:   position is a valid position in the List;
      0 <= position < count.
Post: Returns a pointer to the Node in position.
 */
{
   Node<C> *q = head;
   for (int i = 0; i < position; i++) q = q->next;
   return q;
}
 
template <class C>
List<C>::~List()
/* 
 
Post: The List is empty: all entries have been removed.
 
*/

{
   clear();
}
 
template <class C>
List<C>::List(const List<C> &copy)
/* 
 
Post: The List is initialized to copy the parameter copy.
 
*/

{
   count = copy.count;
   Node<C> *new_node, *old_node = copy.head;

   if (old_node == NULL) head = NULL;
   else {
      new_node = head = new Node<C>(old_node->entry);
      while (old_node->next != NULL) {
         old_node = old_node->next;
         new_node->next = new Node<C>(old_node->entry);
         new_node = new_node->next;
      }
   }
}
 
template <class C>
void List<C>::operator =(const List<C> &copy)
/* 
 
Post: The List is assigned to copy a parameter
 
*/

{
   List new_copy(copy);
   clear();
   count = new_copy.count;
   head = new_copy.head;
   new_copy.count = 0;
   new_copy.head = NULL;
}
