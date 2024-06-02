#include "tags.h"
#include <iostream>
#include <fstream>


std::vector<tag_struct> all_tags; // vector containing all tag structs
std::stack<std::string> tag_names_stack; // name of tags not fully processed
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


std::string get_tag_name(std::string input_string, int opening_tag_index){
    
    std::string new_tag_name = input_string.substr(1, opening_tag_index - 1);
    return new_tag_name;
}

void process_string(std::string input_string){
    tag_struct new_tag;

    int opening_tag_index = input_string.find_first_of(">");
    int closing_tag_index = input_string.find_last_of("<");
    std::string new_tag_name = get_tag_name(input_string, opening_tag_index);
    std::string current_tag_text = input_string.substr(opening_tag_index + 1, closing_tag_index - opening_tag_index - 1);

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
        process_tag(read_data);
    }
    input_file_stream.close(); // close file input stream
}
/**
 * process tags line by line including nested tags
*/

void process_tag(std::string current_string){
        
    int closing_tag_start_index = current_string.find("</");
    int opening_tag_end_index = current_string.find_first_of(">");

    if(closing_tag_start_index < opening_tag_end_index && closing_tag_start_index != -1){
        // closing tag only
        std::string tag_name = current_string.substr(2, opening_tag_end_index - 1);
        tag_names_stack.pop();

    }
    else if(closing_tag_start_index > opening_tag_end_index){
        // closing tag at the end of the text, therefore one tag type
        int opening_tag_index = current_string.find_first_of(">");
        int closing_tag_index = current_string.find_last_of("<");
        std::string tag_name = get_tag_name(current_string, opening_tag_index);
        tag_names_stack.push(tag_name);
        process_string(current_string);
        if(!tag_names_stack.empty()){
            tag_names_stack.pop();
        }
    }
    else if(closing_tag_start_index == -1 && opening_tag_end_index == -1){
        //tags not found in current text
        std::string tag_name = tag_names_stack.top(); // read tag from stack
        int tag_index = find_tag(tag_name);
        all_tags[tag_index].text = (all_tags[tag_index].text == "" ? current_string : all_tags[tag_index].text + " " + current_string);
    }
    else if(closing_tag_start_index == -1 && opening_tag_end_index != -1){
        // only opening tag in string
        int opening_tag_index = current_string.find_first_of(">");
        int closing_tag_index = current_string.find_last_of("<");
        std::string new_tag_name = get_tag_name(current_string, opening_tag_index);
        tag_names_stack.push(new_tag_name);
        if(closing_tag_index < current_string.size()){
            int tag_index = find_tag(new_tag_name);
            if(tag_index >= 0){
                all_tags[tag_index].text = all_tags[tag_index].text + current_string.substr(opening_tag_index + 1,closing_tag_index - opening_tag_index);

            }
            else{
                // tag not found in tags vector; add it
                tag_struct new_tag;
                new_tag.name = new_tag_name;
                new_tag.number_of_pairs = 1;
                new_tag.text = current_string.substr(opening_tag_index + 1,closing_tag_index - opening_tag_index);
                all_tags.push_back(new_tag); // add tag to tags vector
            }
        }
    }
}
/*
 * clears the system terminal when called
*/
void clear(void){
    system("clear");
}