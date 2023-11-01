#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>



std::stringstream ConvertToNormalForm(const std::string& filename) {
    //std::ifstream file(filename);
    //if (!file.is_open()) 
    //    std::cout << "Error File" << std::endl;
    //std::stringstream content;
    //std::stringstream ss_for_parsing;
    //std::stringstream output;
    //content << file.rdbuf();
    //file.close();

    //std::string line;
    //while (std::getline(content, line)) {
    //    if (line.empty()) {
    //        continue;
    //    }

    //    size_t position_tabulation = line.find("\t");
    //    while (position_tabulation != std::string::npos) {
    //        line.erase(position_tabulation, 1);
    //        position_tabulation = line.find("\t", position_tabulation);
    //    }

    //    size_t position_close_parenthesis = line.find(">");
    //    while (position_close_parenthesis != std::string::npos) {
    //        if (line[position_close_parenthesis + 1] != '\n') {
    //            line.insert(position_close_parenthesis + 1, "\n");
    //        }
    //        position_close_parenthesis = line.find(">", position_close_parenthesis + 1);
    //    }

    //    ss_for_parsing << line;
    //}

    //std::string ee = ss_for_parsing.str();
    //size_t position_two_linefeed = ss_for_parsing.str().find("\n\n");
    //while (position_two_linefeed != std::string::npos) {
    //    ss_for_parsing.str().replace(position_two_linefeed, 2, "\n");
    //    position_two_linefeed = ss_for_parsing.str().find("\n\n", position_two_linefeed);
    //}

    //std::string uu = ss_for_parsing.str();
    //output = std::stringstream(ss_for_parsing.str());
    //return output;

    std::string line;
    std::ifstream xml_file(filename);
    std::stringstream output;

    while (std::getline(xml_file, line)) {
        if (line.empty()) {
            continue;
        }

        size_t position_tabulation = line.find("\t");
        while (position_tabulation != std::string::npos) {
            line.erase(position_tabulation, 1);
            position_tabulation = line.find("\t", position_tabulation);
        }

        size_t position_close_parenthesis = line.find(">");
        while (position_close_parenthesis != std::string::npos) {
            if (line[position_close_parenthesis + 1] != '\n') {
                line.insert(position_close_parenthesis + 1, "\n");
            }
            position_close_parenthesis = line.find(">", position_close_parenthesis + 1);
        }

        size_t position_open_parenthesis = line.find("<");
        while (position_open_parenthesis != std::string::npos) {
            if (position_open_parenthesis == 0) {
                line.insert(position_open_parenthesis, "\n");
            }
            else if (line[position_open_parenthesis - 1] != '\n') {
                line.insert(position_open_parenthesis, "\n");
            }
            position_open_parenthesis = line.find("<", position_open_parenthesis + 2);
        }

        output << line;
    }

    //while (std::getline(ss_for_parsing, line)) {
    //    std::cout << "LINE: " << line << std::endl;
    //}

    return output;
}


int main() {
    std::string filename = "example1.xml";

    std::stringstream xml_file = ConvertToNormalForm(filename);

    //std::cout << xml_file.str() << std::endl;

    return 0;
}