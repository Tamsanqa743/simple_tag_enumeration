#ifndef _tags_h
#define _tags_h

#include <vector>
#include <cstdlib>
#include <string>

struct tag_struct {
    std::string name;
    int number_of_pairs;
    std::string text;
};

std::vector<tag_struct> all_tags; // vector containing all tag structs

void print_tags(void); // method that prints all tags

void dump_tags(void); // method dumps all tags into a file called tag.txt

void list_tag_data(std::string tag_name); // prints out all data for specified tag

void extract_tags(std::string filename); // extracts tags with their infomation and stores them in a vector

void clear(void); // clears terminal window

#endif