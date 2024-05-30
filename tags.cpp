#include "tags.h"
#include <iostream>
#include <fstream>


std::vector<tag_struct> all_tags; // vector containing all tag structs
std::vector<std::string> file_data; // vector to store lines from file
std::stack<std::string> file_data_stack; // stack containg lines from file 
// std::string current_tag_name; // name of tag currently in processing
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
/**
 * extracts tags with their infomation and stores them in a vector
*/
void extract_tags(std::string filename){
    read_file(filename);
    for(int i = 0; i < file_data.size(); ++i){

        std::string current_string = file_data[i];
        process_string(current_string);
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
    while(!file_data_stack.empty()){
        std::string current_tag = file_data_stack.top();
        // file_data_stack.pop();

        int start_of_closing_tag = current_tag.find("</");
        int start_of_opening_tag = current_tag.find_first_of(">");

        if(start_of_closing_tag < start_of_opening_tag){
            // closing tag at the start of text/string
            

            std::cout << "Nested Tags: ";
            std::cout << current_tag << std::endl;

        }
        else if(start_of_closing_tag > start_of_opening_tag){
            // closing tag at the end of the text, therefore one tag type
            std::cout << "Straigt tags: ";
            process_string(current_tag);
            std::cout << current_tag << std::endl;
        }
        else if(start_of_closing_tag == -1 && start_of_opening_tag == -1){
            //tags not found in current text
            std::cout << "Clean text: " << current_tag << std::endl;
        }
    }
}

void process_tags(){

     for(int i = 0; i < file_data.size(); ++i){

        std::string current_string = file_data[i];
        // process_string(current_string);
        
        int closing_tag_start_index = current_string.find("</");
        int opening_tag_end_index = current_string.find_first_of(">");

        // std::cout << "end op: " << opening_tag_end_index << "; closing start: " << closing_tag_start_index << "; string: " <<  current_string << std::endl;

        if(closing_tag_start_index < opening_tag_end_index && closing_tag_start_index != -1){
            // opening tag only
            
            std::string tag_name = current_string.substr(2, opening_tag_end_index - 2);
            tag_names_stack.push(tag_name); // push tag name to stack
            std::cout << "top of stack " << tag_names_stack.top()<< std::endl;

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
            // std::cout << current_string << std::endl;
        }
        else if(closing_tag_start_index == -1 && opening_tag_end_index == -1){
            //tags not found in current text
            std::string tag_name = tag_names_stack.top(); // read tag from stack
            int tag_index = find_tag(tag_name);
            all_tags[tag_index].number_of_pairs += 1;
            all_tags[tag_index].text = all_tags[tag_index].text + ":" + current_string;

            // std::cout << "Clean text: " << current_string << std::endl;
        }
        else if(closing_tag_start_index == -1 && opening_tag_end_index != -1){
            // only opening tag in string
            int opening_tag_index = file_data[i].find_first_of(">");
            int closing_tag_index = file_data[i].find_last_of("<");
            std::string new_tag_name = get_tag_name(file_data[i], opening_tag_index);
            // std::cout << "tag name: " << new_tag_name << std::endl;
            tag_names_stack.push(new_tag_name);
            if(closing_tag_index < file_data[i].size()){
                int tag_index = find_tag(new_tag_name);
                if(tag_index >= 0){
                    all_tags[tag_index].number_of_pairs += 1;
                    all_tags[tag_index].text = all_tags[tag_index].text + ":" + file_data[i].substr(file_data[i].size() - opening_tag_index);

                }
                else{
                    // tag not found in tags vector; add it
                    tag_struct new_tag;
                    new_tag.name = new_tag_name;
                    new_tag.number_of_pairs = 1;
                    new_tag.text = file_data[i].substr(file_data[i].size() - opening_tag_index);
                    all_tags.push_back(new_tag); // add tag to tags vector
                }
            }
        }
    }
}

void print_stack(){
    std::cout << tag_names_stack.top() << std::endl;
}
/*
 * clears the system terminal when called
*/
void clear(void){
    system("clear");
}