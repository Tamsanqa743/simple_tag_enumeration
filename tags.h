#ifndef _tags_h
#define _tags_h

#include <vector>
#include <cstdlib>
#include <string>
#include <stack>


struct tag_struct {
    std::string name;
    int number_of_pairs;
    std::string text;
};

void print_tags(void); // method that prints all tags

void dump_tags(void); // method dumps all tags into a file called tag.txt

void list_tag_data(std::string tag_name); // prints out all data for specified tag

void extract_tags(std::string filename); // extracts tags with their infomation and stores them in a vector

void read_file(std::string filename); // reads in file data

void clear(void); // clears terminal window

size_t find_tag(std::string tag_name);

void extract_nested_tags(std::string filename); // extracts tags including nested ones

void read_file_to_stack(std::string filename); // stores file lines into stack

void print_stack(); // test method to print stack

void process_string(std::string current_string);

void process_tags();

#endif