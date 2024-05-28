#include "tags.h"
#include <iostream>
#include <fstream>


std::vector<tag_struct> all_tags; // vector containing all tag structs
std::vector<std::string> file_data; // vector to store lines from file
std::stack<std::string> file_data_stack; // stack containg lines from file 
/**
 * prints all tags and their data contained in the tags vector
 * 
*/
void print_tags(void){
    std::cout << "---------------------------\n";
    for(int i = 0; i < all_tags.size(); ++i){
        tag_struct current_tag = all_tags[i];
        std::cout << current_tag.name << "," << current_tag.number_of_pairs << "," << current_tag.text;
        std::cout << std::endl;
    }
    std::cout << "---------------------------\n";
}

/**
 *  prints out all data for the specified tag
*/

void list_tag_data(std::string tag_name){
    std::cout << "---------------------------\n";
    for(int i = 0; i < all_tags.size(); ++i){
        if(all_tags[i].name == tag_name){
            std::cout << all_tags[i].name << "," << all_tags[i].number_of_pairs << "," << all_tags[i].text;
            std::cout << std::endl;
            break;
        }
    }
}
/**
 * extracts tags with their infomation and stores them in a vector
*/
void extract_tags(std::string filename){
    read_file(filename);
    for(int i = 0; i < file_data.size(); ++i){

        std::string current_string = file_data[i];
        tag_struct new_tag;
        int opening_tag_index = current_string.find_first_of(">");
        int closing_tag_index = current_string.find_last_of("<");

        std::string new_tag_name = current_string.substr(1, opening_tag_index - 1);
        std::string current_tag_text = current_string.substr(opening_tag_index + 1, closing_tag_index - opening_tag_index - 1);

        new_tag.name = new_tag_name;
        new_tag.number_of_pairs = 1;
        new_tag.text = current_tag_text;

        if(!all_tags.empty()){
            
            size_t tag_index = find_tag(new_tag_name);
            if(tag_index < all_tags.size()){
                all_tags[tag_index].number_of_pairs += 1;
                all_tags[tag_index].text = all_tags[tag_index].text + ":" + current_tag_text;
            }
            else{
                all_tags.push_back(new_tag);
            }
        }
        else{
            all_tags.push_back(new_tag);
        }
    }
}

size_t find_tag(std::string tag_name){
    size_t index = -1;
    if(all_tags.size() > 0){
        for(size_t i = 0; i < all_tags.size(); ++i){
            if(all_tags[i].name == tag_name){
                index = i;
            }
        }
    }
    return index;
}

void dump_tags(){
    std::cout << "Dumping tags..." << std::endl;
    std::ofstream output_file("tags.txt");
    for(int i = 0; i < all_tags.size(); ++i){
        output_file << all_tags[i].name << "," << all_tags[i].number_of_pairs << "," << all_tags[i].text << std::endl;
    }
    std::cout << "Done!" << std::endl;
}
/**
 * reads file data line by line and stores it in vector
*/
void read_file(std::string filename){
    std::ifstream input_file_stream(filename);
    std::string read_data;
    while(std::getline(input_file_stream, read_data)){
        file_data.push_back(read_data);
    }
    input_file_stream.close(); // close file input stream
}

void read_file_to_stack(std::string filename){
    std::ifstream input_file_stream(filename);
    std::string read_data;
    while(std::getline(input_file_stream, read_data)){
        file_data_stack.push(read_data);
    }
    input_file_stream.close(); // close file input stream
}

void extract_nested_tags(std::string filename){

}

void print_stack(){
    std::cout << file_data_stack.top() << std::endl;
}
/*
 * clears the system terminal when called
*/
void clear(void){
    system("clear");
}