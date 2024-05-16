#include "tags.h"
#include <iostream>
#include <fstream>

std::vector<tag_struct> all_tags; // vector containing all tag structs
std::vector<std::string> file_data; // vector to store lines from file

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
    read_file(filename);
    for(int i = 0; i < file_data.size(); ++i){

        std::string current_string = file_data[i];
        tag_struct new_tag;
        int opening_tag_index = current_string.find_first_of(">");
        int closing_tag_index = current_string.find_last_of("<");

        std::string new_tag_name = current_string.substr(1, opening_tag_index - 1);
        std::string current_tag_text = current_string.substr(opening_tag_index + 1, closing_tag_index - opening_tag_index - 1);

        if(all_tags.size() != 0){
            for(int j = 0; j < all_tags.size(); ++j){
                if(all_tags[j].name == new_tag_name){
                    new_tag.text = all_tags[j].text + ":" + current_tag_text;
                    new_tag.number_of_pairs = all_tags[j].number_of_pairs + 1;
                    new_tag.name = new_tag_name;
                    all_tags[j] = new_tag;
                    break;
                }
            }

            new_tag.name = new_tag_name;
            new_tag.number_of_pairs = 1;
            new_tag.text = current_tag_text;
            all_tags.push_back(new_tag); 

        }
        else{
            new_tag.name = new_tag_name;
            new_tag.number_of_pairs = 1;
            new_tag.text = current_tag_text;
            all_tags.push_back(new_tag);
        }
    }
}

void dump_tags(){
    std::ofstream output_file("tags.txt");
    for(int i = 0; i < all_tags.size(); ++i){
        output_file << all_tags[i].name << ", " << all_tags[i].number_of_pairs << ", " << all_tags[i].text << std::endl;
    }
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
/*
 * clears the system terminal when called
*/
void clear(void){
    system("clear");
}