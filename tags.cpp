#include "tags.h"
#include <iostream>
#include <fstream>

std::vector<tag_struct> all_tags; // vector containing all tag structs

/**
 * prints all tags and their data contained in the tags vector
 * 
*/
void print_tags(void){
    for(int i = 0; i < all_tags.size(); ++i){
        tag_struct current_tag = all_tags[i];
        std::cout << current_tag.name << ", " << current_tag.number_of_pairs << ", " << current_tag.text;
        std::cout << std::endl;
    }
}

/**
 *  prints out all data for the specified tag
*/

void list_tag_data(std::string tag_name){
    for(int i = 0; i < all_tags.size(); ++i){
        if(all_tags[i].name == tag_name){
            std::cout << all_tags[i].name << ", " << all_tags[i].number_of_pairs << ", " << all_tags[i].text;
            std::cout << std::endl;
        }
        else{
            std::cout << "The specified tag was not found!" << std::endl;
        }
    }
}
/**
 * extracts tags with their infomation and stores them in a vector
*/
void extract_tags(std::string filename){
    std::vector<std::string> file_data = read_file(filename);
    std::cout << file_data[0];

}

void dump_tags(){

}

std::vector<std::string> read_file(std::string filename){
    std::ifstream input_file_stream(filename);
    std::vector<std::string> file_data;
    std::string read_data;
    while(std::getline(input_file_stream, read_data)){
        file_data.push_back(read_data);
    }

    return file_data;
}
/*
 * clears the system terminal when called
*/
void clear(void){
    system("clear");
}