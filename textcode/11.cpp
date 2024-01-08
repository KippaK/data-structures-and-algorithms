/* Program extracts from Chapter 11 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 11.2:

class Trie {
public:  //  Add method prototypes here.

private:  //  data members
   Trie_node *root;
};


const int num_chars = 28;

struct Trie_node {
//    data members
   Record *data;
   Trie_node *branch[num_chars];
//    constructors
   Trie_node();
};


Error_code Trie::trie_search(const Key &target, Record &x) const
/*
Post: If the search is successful, a code of success is
      returned, and the output parameter x is set as a copy
      of the Trie's record that holds target.
      Otherwise, a code of not_present is returned.
Uses: Methods of class Key.
*/
{
   int position = 0;
   char next_char;
   Trie_node *location = root;
   while (location != NULL && (next_char = target.key_letter(position)) != ' ') {
         //  Terminate search for a NULL location or a blank in the target.
      location = location->branch[alphabetic_order(next_char)];
         //  Move down the appropriate branch of the trie.
      position++;
         //  Move to the next character of the target.
   }

   if (location != NULL && location->data != NULL) {
      x = *(location->data);
      return success;
   }
   else
      return not_present;
}


Error_code Trie::insert(const Record &new_entry)
/*
Post: If the Key of new_entry is already in the Trie,
      a code of duplicate_error is returned.
      Otherwise, a code of success is returned and
      the Record new_entry is inserted into the Trie.
Uses: Methods of classes Record and Trie_node.
*/
{
   Error_code result = success;
   if (root == NULL) root = new Trie_node;  //  Create a new empty Trie.
   int position = 0;                        //  indexes letters of new_entry
   char next_char;
   Trie_node *location = root;              //  moves through the Trie
   while (location != NULL &&
         (next_char = new_entry.key_letter(position)) != ' ') {
      int next_position = alphabetic_order(next_char);
      if (location->branch[next_position] == NULL)
         location->branch[next_position] = new Trie_node;
      location = location->branch[next_position];
      position++;
   }
   //  At this point, we have tested for all nonblank characters of new_entry.
   if (location->data != NULL) result = duplicate_error;
   else location->data = new Record(new_entry);
   return result;
}




// Section 11.3:

template <class Record, int order>
class B_tree {
public:  //  Add public methods.

private: //  data members
   B_node<Record, order> *root;
         //  Add private auxiliary functions here.
};


template <class Record, int order>
struct B_node {
//  data members:
   int count;
   Record data[order - 1];
   B_node<Record, order> *branch[order];
//  constructor:
   B_node();
};


template <class Record, int order>
Error_code B_tree<Record, order>::search_tree(Record &target)
/*
Post: If there is an entry in the B-tree whose key matches that in target,
      the parameter target is replaced by the corresponding Record from
      the B-tree and a code of success is returned.  Otherwise
      a code of not_present is returned.
Uses: recursive_search_tree
*/
{
   return recursive_search_tree(root, target);
}


template <class Record, int order>
Error_code B_tree<Record, order>::recursive_search_tree(
           B_node<Record, order> *current, Record &target)
/*
Pre:  current is either NULL or points to a subtree of the B_tree.
Post: If the Key of target is not in the subtree, a code of not_present
      is returned. Otherwise, a code of success is returned and
      target is set to the corresponding Record of the subtree.
Uses: recursive_search_tree recursively and search_node
*/
{
   Error_code result = not_present;
   int position;
   if (current != NULL) {
      result = search_node(current, target, position);
      if (result == not_present)
         result = recursive_search_tree(current->branch[position], target);
      else
         target = current->data[position];
   }
   return result;
}


template <class Record, int order>
Error_code B_tree<Record, order>::search_node(
   B_node<Record, order> *current, const Record &target, int &position)
/*
Pre:  current points to a node of a B_tree.
Post: If the Key of target is found in *current, then a code of
      success is returned, the parameter position is set to the index
      of target, and the corresponding Record is copied to
      target.  Otherwise, a code of not_present is returned, and
      position is set to the branch index on which to continue the search.
Uses: Methods of class Record.
*/
{
   position = 0;
   while (position < current->count && target > current->data[position])
      position++;         //  Perform a sequential search through the keys.
   if (position < current->count && target == current->data[position])
      return success;
   else
      return not_present;
}


template <class Record, int order>
Error_code B_tree<Record, order>::insert(const Record &new_entry)
/*
Post: If the Key of new_entry is already in the B_tree,
      a code of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_entry
      is inserted into the B-tree in such a way that the properties of a B-tree
      are preserved.
Uses: Methods of struct B_node and the auxiliary function push_down.
*/
{
   Record median;
   B_node<Record, order> *right_branch, *new_root;
   Error_code result = push_down(root, new_entry, median, right_branch);

   if (result == overflow) {  //  The whole tree grows in height.
                              //  Make a brand new root for the whole B-tree.
      new_root = new B_node<Record, order>;
      new_root->count = 1;
      new_root->data[0] = median;
      new_root->branch[0] = root;
      new_root->branch[1] = right_branch;
      root = new_root;
      result = success;
   }
   return result;
}


template <class Record, int order>
Error_code B_tree<Record, order>::push_down(
                 B_node<Record, order> *current,
                 const Record &new_entry,
                 Record &median,
                 B_node<Record, order> *&right_branch)
/*
Pre:  current is either NULL or points to a node of a B_tree.
Post: If an entry with a Key matching that of new_entry is in the subtree
      to which current points, a code of duplicate_error is returned.
      Otherwise, new_entry is inserted into the subtree: If this causes the
      height of the subtree to grow, a code of overflow is returned, and the
      Record median is extracted to be reinserted higher in the B-tree,
      together with the subtree right_branch on its right.
      If the height does not grow, a code of success is returned.
Uses: Functions push_down (called recursively), search_node,
      split_node, and push_in.
*/
{
   Error_code result;
   int position;
   if (current == NULL) { //  Since we cannot insert in an empty tree, the recursion terminates.
      median = new_entry;
      right_branch = NULL;
      result = overflow;
   }
   else {   //   Search the current node.
      if (search_node(current, new_entry, position) == success)
         result = duplicate_error;
      else {
         Record extra_entry;
         B_node<Record, order> *extra_branch;
         result = push_down(current->branch[position], new_entry,
                            extra_entry, extra_branch);
         if (result == overflow) {  //  Record extra_entry now must be added to current
            if (current->count < order - 1) {
               result = success;
               push_in(current, extra_entry, extra_branch, position);
            }

            else split_node(current, extra_entry, extra_branch, position,
                            right_branch, median);
            //  Record median and its right_branch will go up to a higher node.
         }
      }
   }
   return result;
}


template <class Record, int order>
void B_tree<Record, order>::push_in(B_node<Record, order> *current,
   const Record &entry, B_node<Record, order> *right_branch, int position)
/*
Pre:  current points to a node of a B_tree.  The node *current is not full
      and entry belongs in *current at index position.
Post: entry has been inserted along with its right-hand branch
      right_branch into *current at index position.
*/
{
   for (int i = current->count; i > position; i--) {  //  Shift all later data to the right.
      current->data[i] = current->data[i - 1];
      current->branch[i + 1] = current->branch[i];
   }
   current->data[position] = entry;
   current->branch[position + 1] = right_branch;
   current->count++;
}


template <class Record, int order>
void B_tree<Record, order>::split_node(
   B_node<Record, order> *current,    //  node to be split
   const Record &extra_entry,          //  new entry to insert
   B_node<Record, order> *extra_branch,//  subtree on right of extra_entry
   int position,                  //  index in node where extra_entry goes
   B_node<Record, order> *&right_half, //  new node for right half of entries
   Record &median)                     //  median entry (in neither half)
/*
Pre:  current points to a node of a B_tree.
      The node *current is full, but if there were room, the record
      extra_entry with its right-hand pointer extra_branch would belong
      in *current at position position, 0 <= position < order.
Post: The node *current with extra_entry and pointer extra_branch at
      position position are divided into nodes *current and *right_half
      separated by a Record median.
Uses: Methods of struct B_node, function push_in.
*/
{
   right_half = new B_node<Record, order>;
   int mid = order/2;  //  The entries from mid on will go to right_half.
   if (position <= mid) {   //  First case:  extra_entry belongs in left half.
      for (int i = mid; i < order - 1; i++) {  //  Move entries to right_half.
         right_half->data[i - mid] = current->data[i];
         right_half->branch[i + 1 - mid] = current->branch[i + 1];
      }
      current->count = mid;
      right_half->count = order - 1 - mid;
      push_in(current, extra_entry, extra_branch, position);
   }
   else {  //  Second case:  extra_entry belongs in right half.
      mid++;      //  Temporarily leave the median in left half.
      for (int i = mid; i < order - 1; i++) {  //  Move entries to right_half.
         right_half->data[i - mid] = current->data[i];
         right_half->branch[i + 1 - mid] = current->branch[i + 1];
      }
      current->count = mid;
      right_half->count = order - 1 - mid;
      push_in(right_half, extra_entry, extra_branch, position - mid);
   }
      median = current->data[current->count - 1]; //  Remove median from left half.
      right_half->branch[0] = current->branch[current->count];
      current->count--;
}


template <class Record, int order>
Error_code B_tree<Record, order>::remove(const Record &target)
/*
Post: If a Record with Key matching that of target belongs to the
      B_tree, a code of success is returned and the corresponding node
      is removed from the B-tree.  Otherwise, a code of not_present
      is returned.
Uses: Function recursive_remove
*/
{
   Error_code result;
   result = recursive_remove(root, target);
   if (root != NULL && root->count == 0) {  //  root is now empty.
      B_node<Record, order> *old_root = root;
      root = root->branch[0];
      delete old_root;
   }
   return result;
}


template <class Record, int order>
Error_code B_tree<Record, order>::recursive_remove(
   B_node<Record, order> *current, const Record &target)
/*
Pre:  current is either NULL or
      points to the root node of a subtree of a B_tree.
Post: If a Record with Key matching that of target belongs to the subtree,
      a code of success is returned and the corresponding node is removed
      from the subtree so that the properties of a B-tree are maintained.
      Otherwise, a code of not_present is returned.
Uses: Functions search_node, copy_in_predecessor,
      recursive_remove (recursively), remove_data, and restore.
*/
{
   Error_code result;
   int position;
   if (current == NULL) result = not_present;
   else {
      if (search_node(current, target, position) == success) {  //  The target is in the current node.
         result = success;
         if (current->branch[position] != NULL) {     //  not at a leaf node
            copy_in_predecessor(current, position);

            recursive_remove(current->branch[position],
                             current->data[position]);
         }
         else remove_data(current, position);     //  Remove from a leaf node.
      }
      else result = recursive_remove(current->branch[position], target);
      if (current->branch[position] != NULL)
         if (current->branch[position]->count < (order - 1) / 2)
            restore(current, position);
   }
   return result;
}


template <class Record, int order>
void B_tree<Record, order>::remove_data(B_node<Record, order> *current,
                                        int position)
/*
Pre:  current points to a leaf node in a B-tree with an entry at position.
Post: This entry is removed from *current.
*/
{
   for (int i = position; i < current->count - 1; i++)
      current->data[i] = current->data[i + 1];
   current->count--;
}


template <class Record, int order>
void B_tree<Record, order>::copy_in_predecessor(
                    B_node<Record, order> *current, int position)
/*
Pre:  current points to a non-leaf node in a B-tree with an entry at position.
Post: This entry is replaced by its immediate predecessor under order of keys.
*/
{
   B_node<Record, order> *leaf = current->branch[position];  //   First go left from the current entry.
   while (leaf->branch[leaf->count] != NULL)
      leaf = leaf->branch[leaf->count]; //   Move as far rightward as possible.
   current->data[position] = leaf->data[leaf->count - 1];
}


template <class Record, int order>
void B_tree<Record, order>::restore(B_node<Record, order> *current,
                                    int position)
/*
Pre:  current points to a non-leaf node in a B-tree; the node to which
      current->branch[position] points has one too few entries.
Post: An entry is taken from elsewhere to restore the minimum number of
      entries in the node to which current->branch[position] points.
Uses: move_left, move_right, combine.
*/
{
   if (position == current->count)   //  case:  rightmost branch
      if (current->branch[position - 1]->count > (order - 1) / 2)
         move_right(current, position - 1);
      else
         combine(current, position);
   else if (position == 0)       //  case: leftmost branch
      if (current->branch[1]->count > (order - 1) / 2)
         move_left(current, 1);
      else
         combine(current, 1);
   else                          //  remaining cases: intermediate branches
      if (current->branch[position - 1]->count > (order - 1) / 2)
         move_right(current, position - 1);
      else if (current->branch[position + 1]->count > (order - 1) / 2)
         move_left(current, position + 1);
      else
         combine(current, position);
}


template <class Record, int order>
void B_tree<Record, order>::move_left(B_node<Record, order> *current,
                                      int position)
/*
Pre:  current points to a node in a B-tree with more than the minimum
      number of entries in branch position and one too few entries in branch
      position - 1.
Post: The leftmost entry from branch position has moved into
      current, which has sent an entry into the branch position - 1.
*/
{
   B_node<Record, order> *left_branch = current->branch[position - 1],
                         *right_branch = current->branch[position];
   left_branch->data[left_branch->count] = current->data[position - 1];  //  Take entry from the parent.
   left_branch->branch[++left_branch->count] = right_branch->branch[0];
   current->data[position - 1] = right_branch->data[0];  //   Add the right-hand entry to the parent.
   right_branch->count--;
   for (int i = 0; i < right_branch->count; i++) {   //  Move right-hand entries to fill the hole.
      right_branch->data[i] = right_branch->data[i + 1];
      right_branch->branch[i] = right_branch->branch[i + 1];
   }
   right_branch->branch[right_branch->count] =
      right_branch->branch[right_branch->count + 1];
}


template <class Record, int order>
void B_tree<Record, order>::move_right(B_node<Record, order> *current,
                                       int position)
/*
Pre:  current points to a node in a B-tree with more than the minimum
      number of entries in branch position and one too few entries
      in branch position + 1.
Post: The rightmost entry from branch position has moved into
      current, which has sent an entry into the branch position + 1.
*/
{
   B_node<Record, order> *right_branch = current->branch[position + 1],
                         *left_branch = current->branch[position];
   right_branch->branch[right_branch->count + 1] =
      right_branch->branch[right_branch->count];
   for (int i = right_branch->count ; i > 0; i--) {  //  Make room for new entry.
      right_branch->data[i] = right_branch->data[i - 1];
      right_branch->branch[i] = right_branch->branch[i - 1];
   }
   right_branch->count++;
   right_branch->data[0] = current->data[position]; //  Take entry from parent.
   right_branch->branch[0] = left_branch->branch[left_branch->count--];
   current->data[position] = left_branch->data[left_branch->count];
}


template <class Record, int order>
void B_tree<Record, order>::combine(B_node<Record, order> *current,
                                    int position)
/*
Pre:  current points to a node in a B-tree with entries in the branches
      position and position - 1, with too few to move entries.
Post: The nodes at branches position - 1 and position have been combined
      into one node, which also includes the entry formerly in current at
      index  position - 1.
*/
{
   int i;
   B_node<Record, order> *left_branch = current->branch[position - 1],
                         *right_branch = current->branch[position];
   left_branch->data[left_branch->count] = current->data[position - 1];
   left_branch->branch[++left_branch->count] = right_branch->branch[0];
   for (i = 0; i < right_branch->count; i++) {
      left_branch->data[left_branch->count] = right_branch->data[i];
      left_branch->branch[++left_branch->count] =
                                        right_branch->branch[i + 1];
   }
   current->count--;
   for (i = position - 1; i < current->count; i++) {
      current->data[i] = current->data[i + 1];
      current->branch[i + 1] = current->branch[i + 2];
   }
   delete right_branch;
}




// Section 11.4:

enum Color {red, black};

template <class Record>
struct RB_node: public Binary_node<Record> {
   Color color;
   RB_node(const Record &new_entry) { color = red; data = new_entry;
                                      left = right = NULL; }
   RB_node()                { color = red; left = right = NULL; }
   void set_color(Color c)  { color = c; }
   Color get_color() const  { return color; }
};


template <class Entry>
struct Binary_node {
   Entry data;
   Binary_node<Entry> *left;
   Binary_node<Entry> *right;
   virtual Color get_color() const { return red; }
   virtual void set_color(Color c) { }
   Binary_node()                   { left = right = NULL; }
   Binary_node(const Entry &x)     { data = x; left = right = NULL; }
};


template <class Record>
class RB_tree: public Search_tree<Record> {
public:
   Error_code insert(const Record & new_entry);
private:  //  Add prototypes for auxiliary functions here.
};


enum RB_code {okay, red_node, left_red, right_red, duplicate};
/*  These outcomes from a call to the recursive insertion function describe
the following results:

okay:      The color of the current root (of the subtree) has not changed;
           the tree now satisfies the conditions for a red-black tree.

red_node:  The current root has changed from black to red; modification
           may or may not be needed to restore the red-black properties.

right_red: The current root and its right child are now both red;
           a color flip or rotation is needed.

left_red:  The current root and its left child are now both red;
           a color flip or rotation is needed.

duplicate: The entry being inserted duplicates another entry; this is
           an error.
*/


template <class Record>
Error_code RB_tree<Record>::insert(const Record &new_entry)
/*
Post: If the key of new_entry is already in the RB_tree, a code of duplicate_error
      is returned.  Otherwise, a code of success is returned and the Record new_entry is
      inserted into the tree in such a way that the properties of an RB-tree
      have been preserved.
Uses: Methods of struct RB_node and recursive function rb_insert.
*/
{
   RB_code status = rb_insert(root, new_entry);
   switch (status) {   //  Convert private RB_code to public Error_code.
      case red_node:             //  Always split the root node to keep it black.
         root->set_color(black); /*  Doing so prevents two red nodes at the top
                  of the  tree and a resulting attempt to rotate
                  using a parent node that does not exist. */
      case okay:
         return success;
      case duplicate:
         return duplicate_error;
      case right_red:
      case left_red:
         cout << "WARNING: Program error detected in RB_tree::insert" << endl;
         return internal_error;
   }
}


template <class Record>
RB_code RB_tree<Record>::rb_insert(Binary_node<Record> *&current,
                                   const Record &new_entry)
/*
Pre:  current is either NULL or points to the
      first node of a subtree of an RB_tree
Post: If the key of new_entry is already in the subtree, a code of duplicate
      is returned.  Otherwise, the Record new_entry is inserted into the subtree
      pointed to by current.  The properties of a red-black tree have been
      restored, except possibly at the root current and one of its children,
      whose status is given by the output RB_code.
Uses: Methods of class RB_node, rb_insert recursively, modify_left,
      and modify_right.
*/
{
   RB_code status,
           child_status;
   if (current == NULL) {
      current = new RB_node<Record>(new_entry);
      status = red_node;
   }
   else if (new_entry == current->data)
      return duplicate;
   else if (new_entry < current->data) {
      child_status = rb_insert(current->left, new_entry);
      status = modify_left(current, child_status);
   }
   else {
      child_status = rb_insert(current->right, new_entry);
      status = modify_right(current, child_status);
   }
   return status;
}


template <class Record>
RB_code RB_tree<Record>::modify_left(Binary_node<Record> *&current,
                                     RB_code &child_status)
/*
Pre:  An insertion has been made in the left subtree of *current that
      has returned the value of child_status  for this subtree.
Post: Any color change or rotation needed for the tree rooted at current
      has been made, and a status code is returned.
Uses: Methods of struct RB_node, with rotate_right,
      double_rotate_right, and flip_color.
*/
{
   RB_code status = okay;
   Binary_node<Record> *aunt = current->right;
   Color aunt_color = black;
   if (aunt != NULL) aunt_color = aunt->get_color();
   switch (child_status) {
   case okay:
      break;         //  No action needed, as tree is already OK.
   case red_node:
      if (current->get_color() == red)
         status = left_red;
      else
         status = okay;        //  current is black, left is red, so OK.
      break;
   case left_red:
      if (aunt_color == black) status = rotate_right(current);
      else                     status = flip_color(current);
      break;
   case right_red:
      if (aunt_color == black) status = double_rotate_right(current);
      else                     status = flip_color(current);
      break;
   }
   return status;
}

/*************************************************************************/

