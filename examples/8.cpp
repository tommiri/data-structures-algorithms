/* Program extracts from Chapter 8 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 8.1:

template <class Record>
class Sortable_list:public List<Record> {
public:   //  Add prototypes for sorting methods here.
 private: //  Add prototypes for auxiliary functions here.
};




// Section 8.2:

template <class Record>
void Sortable_list<Record>::insertion_sort()
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the  entries are sorted into nondecreasing order.
Uses: Methods for the class Record; the contiguous List implementation of
      Chapter 6
*/
{
   int first_unsorted;    //  position of first unsorted entry
   int position;          //  searches sorted part of list
   Record current;        //  holds the entry temporarily removed from list

   for (first_unsorted = 1; first_unsorted < count; first_unsorted++)
      if (entry[first_unsorted] < entry[first_unsorted - 1]) {
         position = first_unsorted;
         current = entry[first_unsorted];         //  Pull unsorted entry out of the list.
         do {               //  Shift all entries until the proper position is found.
            entry[position] = entry[position - 1];
            position--;                           //  position is empty.
         } while (position > 0 && entry[position - 1] > current);
         entry[position] = current;
      }
}


template <class Record>
void Sortable_list<Record>::insertion_sort()
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the entries are sorted into nondecreasing order.
Uses: Methods for the class Record; the linked List implementation of Chapter 6.
*/
{
   Node <Record> *first_unsorted,  //  the first unsorted node to be inserted
                 *last_sorted,     //  tail of the sorted sublist
                 *current,         //  used to traverse the sorted sublist
                 *trailing;        //  one position behind current

   if (head != NULL) {          //  Otherwise, the empty list is already sorted.
      last_sorted = head;       //  The first node alone makes a sorted sublist.
      while (last_sorted->next != NULL) {
         first_unsorted = last_sorted->next;
         if (first_unsorted->entry < head->entry) {
            //  Insert *first_unsorted at the head of the sorted list:
            last_sorted->next = first_unsorted->next;
            first_unsorted->next = head;
            head = first_unsorted;
         }
         else {
            //  Search the sorted sublist to insert *first_unsorted:
            trailing = head;
            current = trailing->next;
            while (first_unsorted->entry > current->entry) {
               trailing = current;
               current = trailing->next;
            }

            //  *first_unsorted now belongs between *trailing and *current.

            if (first_unsorted == current)
               last_sorted = first_unsorted;  //  already in right position
            else {
               last_sorted->next = first_unsorted->next;
               first_unsorted->next = current;
               trailing->next = first_unsorted;
            }
         }
      }
   }
}



// Section 8.3:

template <class Record>
void Sortable_list<Record>::selection_sort()
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the entries are sorted into nondecreasing order.
Uses: max_key, swap.
*/
{
   for (int position = count - 1; position > 0; position--) {
      int max = max_key(0, position);
      swap(max, position);
   }
}


template <class Record>
int Sortable_list<Record>::max_key(int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list and low <= high.
Post: The position of the entry between low and high with the largest
      key is returned.
Uses: The class Record, the contiguous List implementation of Chapter 6.
*/
{
   int largest, current;
   largest = low;
   for (current = low + 1; current <= high; current++)
      if (entry[largest] < entry[current])
         largest = current;
   return largest;
}


template <class Record>
void Sortable_list<Record>::swap(int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list.
Post: The entry at position low is swapped with the entry at position high.
Uses: The contiguous List implementation of Chapter 6.
*/
{
   Record temp;
   temp = entry[low];
   entry[low] = entry[high];
   entry[high] = temp;
}



// Section 8.4:

template <class Record>
void Sortable_list<Record>::shell_sort()
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the entries are sorted into nondecreasing order.
Uses: sort_interval
*/
{
   int increment,    //  spacing of entries in sublist
       start;        //  starting point of sublist
   increment = count;

   do {
      increment = increment / 3 + 1;
      for (start = 0; start < increment; start++)
         sort_interval(start, increment);  //  modified insertion sort
   } while (increment > 1);
}



// Section 8.6:

void Sortable_list::sort()
{
   if the list has length greater than 1 {
      partition the list into lowlist, highlist;
      lowlist.sort();
      highlist.sort();
      combine(lowlist, highlist);
   }
}



// Section 8.7:

template <class Record>
void Sortable_list<Record>::merge_sort()
/*
Post: The entries of the sortable list have been rearranged so that
      their keys are sorted into nondecreasing order.
Uses: The linked List implementation of Chapter 6 and recursive_merge_sort.
*/
{
   recursive_merge_sort(head);
}


template <class Record>
void Sortable_list<Record>::recursive_merge_sort(Node<Record> *&sub_list)
/*
Post: The nodes referenced by sub_list have been rearranged so that their
      keys are sorted into nondecreasing order.  The pointer parameter
      sub_list is reset to point at the node containing the smallest key.
Uses: The linked List implementation of Chapter 6;
      the functions divide_from, merge, and recursive_merge_sort.
*/
{
   if (sub_list != NULL && sub_list->next != NULL) {
      Node<Record> *second_half = divide_from(sub_list);
      recursive_merge_sort(sub_list);
      recursive_merge_sort(second_half);
      sub_list = merge(sub_list, second_half);
   }
}


template <class Record>
Node<Record> *Sortable_list<Record>::divide_from(Node<Record> *sub_list)
/*
Post: The list of nodes referenced by sub_list has been reduced
      to its first half, and a pointer to the first node in the second half
      of the sublist is returned.  If the sublist has an odd number of
      entries, then its first half will be one entry larger than its second.
Uses: The linked List implementation of Chapter 6.
*/
{
   Node<Record> *position, //  traverses the entire list
                *midpoint, //  moves at half speed of position to midpoint
                *second_half;

   if ((midpoint = sub_list) == NULL) return NULL;  //  List is empty.
   position = midpoint->next;
   while (position != NULL) { //  Move position twice for midpoint's one move.
      position = position->next;
      if (position != NULL) {
         midpoint = midpoint->next;
         position = position->next;
      }
   }
   second_half = midpoint->next;
   midpoint->next = NULL;
   return second_half;
}


template <class Record>
Node<Record> *Sortable_list<Record>::merge(Node<Record> *first,
                                           Node<Record> *second)
/*
Pre:  first and second point to ordered lists of nodes.
Post: A pointer to an ordered list of nodes is returned.
      The ordered list contains all entries that were referenced by
      first and second.  The original lists of nodes referenced
      by first and second are no longer available.
Uses: Methods for Record class; the linked List implementation of Chapter 6.
*/
{
   Node<Record> *last_sorted; //  points to the last node of sorted list
   Node<Record> combined;     //  dummy first node, points to merged list

   last_sorted = &combined;
   while (first != NULL && second != NULL) { //  Attach node with smaller key
      if (first->entry <= second->entry) {
         last_sorted->next = first;
         last_sorted = first;
         first = first->next;   //  Advance to the next unmerged node.
      }
      else {
         last_sorted->next = second;
         last_sorted = second;
         second = second->next;
      }
   }

//  After one list ends, attach the remainder of the other.
   if (first == NULL)
      last_sorted->next = second;
   else
      last_sorted->next = first;
   return combined.next;
}



// Section 8.8:

template <class Record>
void Sortable_list<Record>::quick_sort()
/*
Post: The entries of the Sortable_list have been rearranged so
      that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6, recursive_quick_sort.
*/
{
   recursive_quick_sort(0, count - 1);
}


template <class Record>
void Sortable_list<Record>::recursive_quick_sort(int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list.
Post: The entries of the Sortable_list have been
      rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6,
      recursive_quick_sort, and partition.
*/
{
   int pivot_position;
   if (low < high) {   //   Otherwise, no sorting is needed.
      pivot_position = partition(low, high);
      recursive_quick_sort(low, pivot_position - 1);
      recursive_quick_sort(pivot_position + 1, high);
   }
}


template <class Record>
int Sortable_list<Record>::partition(int low, int high)
/*
Pre:  low and high are valid positions of the Sortable_list, with low <= high.
Post: The center (or left center) entry in the range between indices
      low and high of the Sortable_list
      has been chosen as a pivot.  All entries of the Sortable_list
      between indices low and high, inclusive, have been
      rearranged so that those with keys less than the pivot come
      before the pivot and the remaining entries come
      after the pivot.  The final position of the pivot is returned.
Uses: swap(int i, int j) (interchanges entries in positions
      i and j of a Sortable_list), the contiguous List implementation
      of Chapter 6, and methods for the class Record.
*/
{
   Record pivot;
   int i,            //  used to scan through the list
       last_small;   //  position of the last key less than pivot
   swap(low, (low + high) / 2);
   pivot = entry[low];   //  First entry is now pivot.
   last_small = low;
   for (i = low + 1; i <= high; i++)
/*
At the beginning of each iteration of this loop, we have the following
conditions:
        If low < j <= last_small then entry[j].key < pivot.
        If last_small < j < i then entry[j].key >= pivot.
*/
      if (entry[i] < pivot) {
         last_small = last_small + 1;
         swap(last_small, i);  //  Move large entry to right and small to left.
      }
   swap(low, last_small);      //  Put the pivot into its proper position.
   return last_small;
}



// Section 8.9:

template <class Record>
void Sortable_list<Record>::heap_sort()
/*
Post: The entries of the Sortable_list have been rearranged so
      that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6,build_heap,
      and insert_heap.
*/
{
   Record current;    //  temporary storage for moving entries
   int last_unsorted; //  Entries beyond last_unsorted have been sorted.
   build_heap();      //  First phase:  Turn the list into a heap.
   for (last_unsorted = count - 1; last_unsorted > 0; last_unsorted--) {
      current = entry[last_unsorted];   //  Extract the last entry from the list.
      entry[last_unsorted] = entry[0];     //  Move top of heap to the end
      insert_heap(current, 0, last_unsorted - 1);  //  Restore the heap
   }
}


template <class Record>
void Sortable_list<Record>::insert_heap(const Record &current, int low, int high)
/*
Pre:  The entries of the Sortable_list between indices low + 1 and high,
      inclusive, form a heap. The entry in position low will be discarded.
Post: The entry current has been inserted into the Sortable_list
      and the entries rearranged
      so that the entries between indices low and high, inclusive,
      form a heap.
Uses: The class Record, and the contiguous List implementation of Chapter 6.
*/
{
   int large;           //  position of child of entry[low] with the larger key

   large = 2 * low + 1; //  large is now the left child of low.
   while (large <= high) {
      if (large < high && entry[large] < entry[large + 1])
         large++;       //  large is now the child of low with the largest key.
      if (current >= entry[large])
         break;         //  current belongs in position low.

      else {            //  Promote entry[large] and move down the tree.
         entry[low] = entry[large];
         low = large;
         large = 2 * low + 1;
      }
   }
   entry[low] = current;
}


template <class Record>
void Sortable_list<Record>::build_heap()
/*
Post: The entries of the Sortable_list have been rearranged
      so that it becomes a heap.
Uses: The contiguous List implementation of Chapter 6, and insert_heap.
*/
{
   int low;   //  All entries beyond the position low form a heap.
   for (low = count / 2 - 1; low >= 0; low--) {
      Record current = entry[low];
      insert_heap(current, low, count - 1);
   }
}

/*************************************************************************/

