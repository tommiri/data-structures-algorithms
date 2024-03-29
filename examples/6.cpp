/* Program extracts from Chapter 6 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */

// Section 6.2:

template <class List_entry>
class List
{
   //  Add in member information for the class.
};

template <class List_entry>
class List
{
public:
   //  methods of the List ADT
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);

protected:
   //  data members for a contiguous list implementation
   int count;
   List_entry entry[max_list];
};

template <class List_entry>
int List<List_entry>::size() const
/*
Post: The function returns the number of entries in the List.
*/
{
   return count;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: The function fails with a diagnostic error code.
*/
{
   if (full())
      return overflow;

   if (position < 0 || position > count)
      return range_error;

   for (int i = count - 1; i >= position; i--)
      entry[i + 1] = entry[i];

   entry[position] = x;
   count++;
   return success;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/*
Post: The action specified by function (*visit) has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
   for (int i = 0; i < count; i++)
      (*visit)(entry[i]);
}

template <class Node_entry>
struct Node
{
   //  data members
   Node_entry entry;
   Node<Node_entry> *next;
   //  constructors
   Node();
   Node(Node_entry, Node<Node_entry> *link = NULL);
};

template <class List_entry>
class List
{
public:
   //  Specifications for the methods of the list ADT go here.
   //  The following methods replace compiler-generated defaults.
   ~List();
   List(const List<List_entry> &copy);
   void operator=(const List<List_entry> &copy);

protected:
   //  Data members for the linked list implementation now follow.
   int count;
   Node<List_entry> *head;

   //  The following auxiliary function is used to locate list positions
   Node<List_entry> *set_position(int position) const;
};

template <class List_entry>
Node<List_entry> *List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List; 0 <= position < count.
Post: Returns a pointer to the Node in position.
*/
{
   Node<List_entry> *q = head;
   for (int i = 0; i < position; i++)
      q = q->next;
   return q;
}

new_node->next = following;
previous->next = new_node;

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their position
      numbers increased by 1, and x is inserted at position of the List.
      Else: The function fails with a diagnostic error code.
*/
{
   if (position < 0 || position > count)
      return range_error;
   Node<List_entry> *new_node, *previous, *following;
   if (position > 0)
   {
      previous = set_position(position - 1);
      following = previous->next;
   }
   else
      following = head;
   new_node = new Node<List_entry>(x, following);
   if (new_node == NULL)
      return overflow;
   if (position == 0)
      head = new_node;
   else
      previous->next = new_node;
   count++;
   return success;
}

template <class List_entry>
class List
{
public:
   //  Add specifications for the methods of the list ADT.
   //  Add methods to replace the compiler-generated defaults.

protected:
   //  Data members for the linked-list implementation with
   //  current position follow:
   int count;
   mutable int current_position;
   Node<List_entry> *head;
   mutable Node<List_entry> *current;

   //  Auxiliary function to locate list positions follows:
   void set_position(int position) const;
};

template <class List_entry>
void List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current Node pointer references the Node at position.
*/
{
   if (position < current_position)
   { //  must start over at head of list
      current_position = 0;
      current = head;
   }
   for (; current_position != position; current_position++)
      current = current->next;
}

template <class Node_entry>
struct Node
{
   //  data members
   Node_entry entry;
   Node<Node_entry> *next;
   Node<Node_entry> *back;
   //  constructors
   Node();
   Node(Node_entry, Node<Node_entry> *link_back = NULL,
        Node<Node_entry> *link_next = NULL);
};

template <class List_entry>
class List
{
public:
   //  Add specifications for methods of the list ADT.
   //  Add methods to replace compiler generated defaults.
protected:
   //  Data members for the doubly-linked list implementation follow:
   int count;
   mutable int current_position;
   mutable Node<List_entry> *current;

   //  The auxiliary function to locate list positions follows:
   void set_position(int position) const;
};

template <class List_entry>
void List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current Node pointer references the Node at position.
*/
{
   if (current_position <= position)
      for (; current_position != position; current_position++)
         current = current->next;
   else
      for (; current_position != position; current_position--)
         current = current->back;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: the function fails with a diagnostic error code.
*/
{
   Node<List_entry> *new_node, *following, *preceding;
   if (position < 0 || position > count)
      return range_error;
   if (position == 0)
   {
      if (count == 0)
         following = NULL;
      else
      {
         set_position(0);
         following = current;
      }
      preceding = NULL;
   }
   else
   {
      set_position(position - 1);
      preceding = current;
      following = preceding->next;
   }
   new_node = new Node<List_entry>(x, preceding, following);

   if (new_node == NULL)
      return overflow;
   if (preceding != NULL)
      preceding->next = new_node;
   if (following != NULL)
      following->back = new_node;
   current = new_node;
   current_position = position;
   count++;
   return success;
}

// Section 6.3:

class String
{
public: //  methods of the string ADT
   String();
   ~String();
   String(const String &copy); //  copy constructor
   String(const char *copy);   //  conversion from C-string
   String(List<char> &copy);   //  conversion from List

   void operator=(const String &copy);
   const char *c_str() const; //  conversion to C-style string

protected:
   char *entries;
   int length;
};

bool operator==(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator!=(const String &first, const String &second);

String::String(const char *in_string)
/*
Pre:  The pointer in_string references a C-string.
Post: The String is initialized by the C-string in_string.
*/
{
   length = strlen(in_string);
   entries = new char[length + 1];
   strcpy(entries, in_string);
}

String::String(List<char> &in_list)
/*
Post: The String is initialized by the character List in_list.
*/
{
   length = in_list.size();
   entries = new char[length + 1];
   for (int i = 0; i < length; i++)
      in_list.retrieve(i, entries[i]);
   entries[length] = '\0';
}

const char *String::c_str() const
/*
Post: A pointer to a legal C-string object matching the String is returned.
*/
{
   return (const char *)entries;
}

String s = "abc";
const char *new_string = s.c_str();
s = "def";
cout << new_string;

String s = "Some very long string";
cout << s.c_str(); //  creates garbage from a temporary C-string object

bool operator==(const String &first, const String &second)
/*
Post: Return true if the String first agrees with String second.
      Else: Return false.
*/
{
   return strcmp(first.c_str(), second.c_str()) == 0;
}

String s = "some_string";
cout << s.c_str() << endl;
cout << strlen(s.c_str()) << endl;

void strcat(String &add_to, const String &add_on)
/*
Post: The function concatenates String add_on onto the end of String add_to.
*/
{
   const char *cfirst = add_to.c_str();
   const char *csecond = add_on.c_str();
   char *copy = new char[strlen(cfirst) + strlen(csecond) + 1];
   strcpy(copy, cfirst);
   strcat(copy, csecond);
   add_to = copy;
   delete[] copy;
}

String read_in(istream &input)
/*
Post: Return a String read (as characters terminated
      by a newline or an end-of-file character) from an istream parameter.
*/
{
   List<char> temp;
   int size = 0;
   char c;
   while ((c = input.peek()) != EOF && (c = input.get()) != '\n')
      temp.insert(size++, c);
   String answer(temp);
   return answer;
}

void write(String &s)
/*
Post: The String parameter s is written to cout.
*/
{
   cout << s.c_str() << endl;
}

// Section 6.4:

int main(int argc, char *argv[]) // count, values of command-line arguments
/*
Pre:  Names of input and output files are given as command-line arguments.
Post: Reads an input file that contains lines (character strings),
      performs simple editing operations on the lines, and
      writes the edited version to the output file.
Uses: methods of class Editor
*/
{
   if (argc != 3)
   {
      cout << "Usage:\n\t edit  inputfile  outputfile" << endl;
      exit(1);
   }
   ifstream file_in(argv[1]); //  Declare and open the input stream.
   if (file_in == 0)
   {
      cout << "Can't open input file " << argv[1] << endl;
      exit(1);
   }
   ofstream file_out(argv[2]); //  Declare and open the output stream.
   if (file_out == 0)
   {
      cout << "Can't open output file " << argv[2] << endl;
      exit(1);
   }
   Editor buffer(&file_in, &file_out);
   while (buffer.get_command())
      buffer.run_command();
}

class Editor : public List<String>
{
public:
   Editor(ifstream *file_in, ofstream *file_out);
   bool get_command();
   void run_command();

private:
   ifstream *infile;
   ofstream *outfile;
   char user_command;

   //  auxiliary functions
   Error_code next_line();
   Error_code previous_line();
   Error_code goto_line();
   Error_code insert_line();
   Error_code substitute_line();
   Error_code change_line();
   void read_file();
   void write_file();
   void find_string();
};

Editor::Editor(ifstream *file_in, ofstream *file_out)
/*
Post: Initialize the Editor members infile and outfile with the parameters.
*/
{
   infile = file_in;
   outfile = file_out;
}

bool Editor::get_command()
/*
Post: Sets member user_command; returns true unless the user's command is q.
Uses: C library function tolower.
*/
{
   if (current != NULL)
      cout << current_position << " : "
           << current->entry.c_str() << "\n??" << flush;
   else
      cout << "File is empty. \n??" << flush;

   cin >> user_command; //  ignores white space and gets command
   user_command = tolower(user_command);
   while (cin.get() != '\n')
      ; //  ignore user's enter key
   if (user_command == 'q')
      return false;
   else
      return true;
}

void Editor::run_command()
/*
Post: The command in user_command has been performed.
Uses: methods and auxiliary functions of the class Editor,
      the class String, and the String processing functions.
*/
{
   String temp_string;
   switch (user_command)
   {
   case 'b':
      if (empty())
         cout << " Warning: empty buffer " << endl;
      else
         while (previous_line() == success)
            ;
      break;

   case 'c':
      if (empty())
         cout << " Warning: Empty file" << endl;
      else if (change_line() != success)
         cout << " Error: Substitution failed " << endl;
      break;

   case 'd':
      if (remove(current_position, temp_string) != success)
         cout << " Error: Deletion failed " << endl;
      break;

   case 'e':
      if (empty())
         cout << " Warning: empty buffer " << endl;
      else
         while (next_line() == success)
            ;
      break;

   case 'f':
      if (empty())
         cout << " Warning: Empty file" << endl;
      else
         find_string();
      break;

   case 'g':
      if (goto_line() != success)
         cout << " Warning: No such line" << endl;
      break;

   case '?':
   case 'h':
      cout << "Valid commands are: b(egin) c(hange) d(el) e(nd)" << endl
           << "f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior) " << endl
           << "q(uit) r(ead) s(ubstitute) v(iew) w(rite) " << endl;

   case 'i':
      if (insert_line() != success)
         cout << " Error: Insertion failed " << endl;
      break;

   case 'l':
      cout << "There are " << size() << " lines in the file." << endl;
      if (!empty())
         cout << "Current line length is "
              << strlen((current->entry).c_str()) << endl;
      break;

   case 'n':
      if (next_line() != success)
         cout << " Warning: at end of buffer" << endl;
      break;

   case 'p':
      if (previous_line() != success)
         cout << " Warning: at start of buffer" << endl;
      break;

   case 'r':
      read_file();
      break;

   case 's':
      if (substitute_line() != success)
         cout << " Error: Substitution failed " << endl;
      break;

   case 'v':
      traverse(write);
      break;

   case 'w':
      if (empty())
         cout << " Warning: Empty file" << endl;
      else
         write_file();
      break;

   default:
      cout << "Press h or ? for help or enter a valid command: ";
   }
}

void Editor::read_file()
/*
Pre:  Either the Editor is empty or the user authorizes the command.
Post: The contents of *infile are read to the Editor.
      Any prior contents of the Editor are overwritten.
Uses: String and Editor methods and functions.
*/
{
   bool proceed = true;
   if (!empty())
   {
      cout << "Buffer is not empty; the read will destroy it." << endl;
      cout << " OK to proceed? " << endl;
      if (proceed = user_says_yes())
         clear();
   }

   int line_number = 0, terminal_char;
   while (proceed)
   {
      String in_string = read_in(*infile, terminal_char);
      if (terminal_char == EOF)
      {
         proceed = false;
         if (strlen(in_string.c_str()) > 0)
            insert(line_number, in_string);
      }
      else
         insert(line_number++, in_string);
   }
}

Error_code Editor::insert_line()
/*
Post: A string entered by the user is inserted as a user-selected line number.
Uses: String and Editor methods and functions.
*/
{
   int line_number;
   cout << " Insert what line number? " << flush;
   cin >> line_number;
   while (cin.get() != '\n')
      ;
   cout << " What is the new line to insert? " << flush;
   String to_insert = read_in(cin);
   return insert(line_number, to_insert);
}

void Editor::find_string()
/*
Pre:  The Editor is not empty.
Post: The current line is advanced until either it contains a copy
      of a user-selected string or it reaches the end of the Editor.
      If the selected string is found, the corresponding line is
      printed with the string highlighted.
Uses: String and Editor methods and functions.
*/
{
   int index;
   cout << "Enter string to search for:" << endl;
   String search_string = read_in(cin);
   while ((index = strstr(current->entry, search_string)) == -1)
      if (next_line() != success)
         break;
   if (index == -1)
      cout << "String was not found.";
   else
   {
      cout << (current->entry).c_str() << endl;
      for (int i = 0; i < index; i++)
         cout << " ";
      for (int j = 0; j < strlen(search_string.c_str()); j++)
         cout << "^";
   }
   cout << endl;
}

Error_code Editor::change_line()
/*
Pre:  The Editor is not empty.
Post: If a user-specified string appears in the
      current line, it is replaced by a new user-selected string.
      Else: an Error_code is returned.
Uses: String and Editor methods and functions.
*/
{
   Error_code result = success;
   cout << " What text segment do you want to replace? " << flush;
   String old_text = read_in(cin);
   cout << " What new text segment do you want to add in? " << flush;
   String new_text = read_in(cin);

   int index = strstr(current->entry, old_text);
   if (index == -1)
      result = fail;
   else
   {
      String new_line;
      strncpy(new_line, current->entry, index);
      strcat(new_line, new_text);
      const char *old_line = (current->entry).c_str();
      strcat(new_line, (String)(old_line + index + strlen(old_text.c_str())));
      current->entry = new_line;
   }
   return result;
}

// Section 6.5:

typedef int index;
const int max_list = 7; //  small value for testing purposes

template <class List_entry>
class Node
{
public:
   List_entry entry;
   index next;
};

template <class List_entry>
class List
{
public:
   //  Methods of the list ADT
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);

protected:
   //  Data members
   Node<List_entry> workspace[max_list];
   index available, last_used, head;
   int count;

   //  Auxiliary member functions
   index new_node();
   void delete_node(index n);
   int current_position(index n) const;
   index set_position(int position) const;
};

template <class List_entry>
index List<List_entry>::new_node()
/*
Post: The index of the first available Node in workspace is returned;
      the data members available, last_used, and workspace are updated
      as necessary.  If the work-space is already full, -1 is returned.
*/
{
   index new_index;

   if (available != -1)
   {
      new_index = available;
      available = workspace[available].next;
   }
   else if (last_used < max_list - 1)
   {
      new_index = ++last_used;
   }
   else
      return -1;
   workspace[new_index].next = -1;
   return new_index;
}

template <class List_entry>
void List<List_entry>::delete_node(index old_index)
/*
Pre:  The List has a Node stored at index old_index.
Post: The List index old_index is pushed onto the linked stack
      of available space; available, last_used, and workspace are
      updated as necessary.
*/
{
   index previous;
   if (old_index == head)
      head = workspace[old_index].next;
   else
   {
      previous = set_position(current_position(old_index) - 1);
      workspace[previous].next = workspace[old_index].next;
   }
   workspace[old_index].next = available;
   available = old_index;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/*
Post: The action specified by function *visit has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
   for (index n = head; n != -1; n = workspace[n].next)
      (*visit)(workspace[n].entry);
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: the function fails with a diagnostic error code.
*/
{
   index new_index, previous, following;

   if (position < 0 || position > count)
      return range_error;

   if (position > 0)
   {
      previous = set_position(position - 1);
      following = workspace[previous].next;
   }
   else
      following = head;
   if ((new_index = new_node()) == -1)
      return overflow;
   workspace[new_index].entry = x;
   workspace[new_index].next = following;
   if (position == 0)
      head = new_index;
   else
      workspace[previous].next = new_index;
   count++;
   return success;
}

// Section 6.6:

void permute(int k, int n)
/*
Pre:  1 through k - 1 are already in the permutation list;
Post: inserts the integers from k through n into the permutation list
*/
{
   for //  each of the k possible positions in the list
   {
      //  Insert k into the given position.
      if (k == n)
         process_permutation;
      else
         permute(k + 1, n);
      //  Remove k from the given position.
   }
}

void permute(int new_entry, int degree, List<int> &permutation)
/*
Pre:  permutation contains a permutation with entries in positions 1
      through new_entry - 1.
Post: All permutations with degree entries, built from the given
      permutation, have been constructed and processed.
Uses: permute recursively, process_permutation, and List functions.
*/
{
   for (int current = 0; current < permutation.size() + 1; current++)
   {
      permutation.insert(current, new_entry);
      if (new_entry == degree)
         process_permutation(permutation);
      else
         permute(new_entry + 1, degree, permutation);
      permutation.remove(current, new_entry);
   }
}

void permute(int new_entry, int degree, int *permutation)
/*
Pre:  permutation contains a linked permutation with entries in positions
      1 through new_entry - 1.
Post: All permutations with degree entries, built from the given
      permutation, have been constructed and processed.
Uses: Functions permute (recursively) and process_permutation.
*/
{
   int current = 0;
   do
   {
      permutation[new_entry] = permutation[current];
      permutation[current] = new_entry;
      if (new_entry == degree)
         process_permutation(permutation);
      else
         permute(new_entry + 1, degree, permutation);
      permutation[current] = permutation[new_entry];
      current = permutation[current];
   } while (current != 0);
}

main()
/*
Pre:  The user specifies the degree of permutations to construct.
Post: All permutations of a user-supplied degree are printed to the terminal.
*/
{
   int degree;
   int permutation[max_degree + 1];

   cout << "Number of elements to permute? ";
   cin >> degree;

   if (degree < 1 || degree > max_degree)
      cout << "Number must be between 1 and " << max_degree << endl;
   else
   {
      permutation[0] = 0;
      permute(1, degree, permutation);
   }
}

void process_permutation(int *permutation)
/*
Pre:  permutation is in linked form.
Post: The permutation has been printed to the terminal.
*/
{
   int current = 0;
   while (permutation[current] != 0)
   {
      cout << permutation[current] << " ";
      current = permutation[current];
   }
   cout << endl;
}

/*************************************************************************/
