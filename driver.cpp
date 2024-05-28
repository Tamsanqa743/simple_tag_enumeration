#include <iostream>
#include <string>
#include "tags.h"

int main(void){
    for(;;){
       
        std::cout << "r: Read and process tag file\np: Print all tags\nd: Dump all tags to text file\nl: List specified tag and its data\nq: Quit\n";
        std::string user_input;
        std::cout << "Enter an option (r,p,d,l) or q to quit, and press return..." << std::endl;
        std::cin >> user_input;
        if(user_input == "r"){
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            extract_tags(filename);
            read_file_to_stack(filename);
            print_stack();
        }
        else if (user_input == "p"){
            print_tags();
        }
        else if(user_input == "d"){
            dump_tags();
        }
        else if(user_input == "l"){
            std::string tag_name;
            std::cout << "Enter tag name: ";
            std::cin >> tag_name;
            list_tag_data(tag_name);
        }
        if(user_input == "q"){
            break;
        }
    }
    return 0;
}