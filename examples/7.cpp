/* Program extracts from Chapter 7 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */

// Section 7.1:

typedef int Key;
typedef int Record;

//  Definition of a Key class:
class Key
{
public:
   //  Add any constructors and methods for key data.
private:
   //  Add declaration of key data members here.
};

//  Declare overloaded comparison operators for keys.
bool operator==(const Key &x, const Key &y);
bool operator>(const Key &x, const Key &y);
bool operator<(const Key &x, const Key &y);
bool operator>=(const Key &x, const Key &y);
bool operator<=(const Key &x, const Key &y);
bool operator!=(const Key &x, const Key &y);

//  Definition of a Record class:
class Record
{
public:
   operator Key(); //  implicit conversion from Record to Key.
                   //  Add any constructors and methods for Record objects.
private:
   //  Add data components.
};

// Section 7.2:

Error_code sequential_search(const List<Record> &the_list,
                             const Key &target, int &position)
/*
Post: If an entry in the_list has key equal to target, then return
      success and the output parameter position locates such an entry
      within the list.
      Otherwise return not_present and position becomes invalid.
*/
{
   int s = the_list.size();
   for (position = 0; position < s; position++)
   {
      Record data;
      the_list.retrieve(position, data);
      if (data == target)
         return success;
   }
   return not_present;
}

class Key
{
   int key;

public:
   static int comparisons;
   Key(int x = 0);
   int the_key() const;
};

bool operator==(const Key &x, const Key &y);
bool operator>(const Key &x, const Key &y);
bool operator<(const Key &x, const Key &y);
bool operator>=(const Key &x, const Key &y);
bool operator<=(const Key &x, const Key &y);
bool operator!=(const Key &x, const Key &y);

bool operator==(const Key &x, const Key &y)
{
   Key::comparisons++;
   return x.the_key() == y.the_key();
}

int Key::comparisons = 0;

typedef Key Record;

void test_search(int searches, List<Record> &the_list)
/*

Pre:  None.
Post: The number of key comparisons and CPU time for a
      sequential searching function have been calculated.
Uses: Methods of the classes List, Random, and Timer,
      together with an output function print_out
*/
{
   int list_size = the_list.size();
   if (searches <= 0 || list_size < 0)
   {
      cout << " Exiting test: " << endl
           << " The number of searches must be positive." << endl
           << " The number of list entries must exceed 0." << endl;
      return;
   }
   int i, target, found_at;
   Key::comparisons = 0;
   Random number;
   Timer clock;

   for (i = 0; i < searches; i++)
   {
      target = 2 * number.random_integer(0, list_size - 1) + 1;
      if (sequential_search(the_list, target, found_at) == not_present)
         cout << "Error: Failed to find expected target " << target << endl;
   }
   print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

   Key::comparisons = 0;
   clock.reset();
   for (i = 0; i < searches; i++)
   {
      target = 2 * number.random_integer(0, list_size);
      if (sequential_search(the_list, target, found_at) == success)
         cout << "Error: Found unexpected target " << target
              << " at " << found_at << endl;
   }
   print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
}

// Section 7.3:

class Ordered_list : public List<Record>
{
public:
   Ordered_list();
   Error_code insert(const Record &data);
   Error_code insert(int position, const Record &data);
   Error_code replace(int position, const Record &data);
};

Error_code Ordered_list::insert(const Record &data)
/*
Post: If the Ordered_list is not full, the function succeeds:
      The Record data is inserted into the list, following the
      last entry of the list with a strictly lesser key (or in the
      first list position if no list element has a lesser key).
      Else: the function fails with the diagnostic Error_code overflow.
*/
{
   int s = size();
   int position;
   for (position = 0; position < s; position++)
   {
      Record list_data;
      retrieve(position, list_data);
      if (data >= list_data)
         break;
   }
   return List<Record>::insert(position, data);
}

Error_code Ordered_list::insert(int position, const Record &data)
/*
Post: If the Ordered_list is not full, 0 <= position <= n,
      where n is the number of entries in the list,
      and the Record data can be inserted at position in the list,
      without disturbing the list order, then the function succeeds:
      Any entry formerly in position and all later entries have their
      position numbers increased by 1 and data is inserted at position
      of the List.
      Else: the function fails with a diagnostic Error_code.
*/
{
   Record list_data;
   if (position > 0)
   {
      retrieve(position - 1, list_data);
      if (data < list_data)
         return fail;
   }
   if (position < size())
   {
      retrieve(position, list_data);
      if (data > list_data)
         return fail;
   }
   return List<Record>::insert(position, data);
}

Error_code recursive_binary_1(const Ordered_list &the_list, const Key &target,
                              int bottom, int top, int &position)
/*
Pre:  The indices bottom to top define the
      range in the list to search for the target.
Post: If a Record in the range of locations
      from bottom to top in the_list has key equal
      to target, then position locates
      one such entry and a code of success is returned.
      Otherwise, the Error_code of not_present is returned
      and position becomes undefined.
Uses: recursive_binary_1 and methods of the classes List and Record.
*/
{
   Record data;
   if (bottom < top)
   { // List has more than one entry.
      int mid = (bottom + top) / 2;
      the_list.retrieve(mid, data);
      if (data < target) // Reduce to top half of list.
         return recursive_binary_1(the_list, target, mid + 1, top, position);
      else // Reduce to bottom half of list.
         return recursive_binary_1(the_list, target, bottom, mid, position);
   }
   else if (top < bottom)
      return not_present; // List is empty.
   else
   { // List has exactly one entry.
      position = bottom;
      the_list.retrieve(bottom, data);
      if (data == target)
         return success;
      else
         return not_present;
   }
}

Error_code run_recursive_binary_1(const Ordered_list &the_list,
                                  const Key &target, int &position)
{
   return recursive_binary_1(the_list, target, 0, the_list.size() - 1, position);
}

Error_code binary_search_1(const Ordered_list &the_list,
                           const Key &target, int &position)
/*
Post: If a Record in the_list  has Key equal to target, then position locates
      one such entry and a code of success is returned.
      Otherwise, not_present is returned and position is undefined.
Uses: Methods for classes List and Record.
*/
{
   Record data;
   int bottom = 0, top = the_list.size() - 1;

   while (bottom < top)
   {
      int mid = (bottom + top) / 2;
      the_list.retrieve(mid, data);
      if (data < target)
         bottom = mid + 1;
      else
         top = mid;
   }
   if (top < bottom)
      return not_present;
   else
   {
      position = bottom;
      the_list.retrieve(bottom, data);
      if (data == target)
         return success;
      else
         return not_present;
   }
}

Error_code recursive_binary_2(const Ordered_list &the_list, const Key &target,
                              int bottom, int top, int &position)
/*
Pre:  The indices bottom to top define the
      range in the list to search for the target.
Post: If a Record in the range from bottom to top in the_list
      has key equal to target, then position locates
      one such entry, and a code of success is returned.
      Otherwise, not_present is returned, and position is undefined.
Uses: recursive_binary_2, together with methods from the classes
      Ordered_list and Record.
*/
{
   Record data;
   if (bottom <= top)
   {
      int mid = (bottom + top) / 2;
      the_list.retrieve(mid, data);
      if (data == target)
      {
         position = mid;
         return success;
      }

      else if (data < target)
         return recursive_binary_2(the_list, target, mid + 1, top, position);
      else
         return recursive_binary_2(the_list, target, bottom, mid - 1, position);
   }
   else
      return not_present;
}

Error_code run_recursive_binary_2(const Ordered_list &the_list,
                                  const Key &target, int &position)
{
   return recursive_binary_2(the_list, target, 0, the_list.size() - 1, position);
}

Error_code binary_search_2(const Ordered_list &the_list,
                           const Key &target, int &position)
/*
Post: If a Record in the_list has key equal to target, then position locates
      one such entry and a code of success is returned.
      Otherwise, not_present is returned and position is undefined.
Uses: Methods for classes Ordered_list and Record.
*/
{
   Record data;
   int bottom = 0, top = the_list.size() - 1;
   while (bottom <= top)
   {
      position = (bottom + top) / 2;
      the_list.retrieve(position, data);
      if (data == target)
         return success;
      if (data < target)
         bottom = position + 1;
      else
         top = position - 1;
   }
   return not_present;
}

/*************************************************************************/
