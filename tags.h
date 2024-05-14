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

void print_tags(void);

void dump_tags(void);

void list_tag_data(std::string tag_name);

#endif