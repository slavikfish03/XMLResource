#include "XMLResource.hpp"

std::unique_ptr<XMLResource> XMLResource::Create() {
    std::unique_ptr<XMLResource> ptr_xml_resource(new XMLResource());
	return std::move(ptr_xml_resource);
}

std::stringstream XMLResource::ConvertToNormalForm(std::ifstream& input_xml) {
    std::string line;
    std::stringstream output;

    while (std::getline(input_xml, line)) {
        if (line.empty()) {
            continue;
        }

        size_t position_tabulation = line.find("\t");
        while (position_tabulation != std::string::npos) {
            line.erase(position_tabulation, 1);
            position_tabulation = line.find("\t", position_tabulation);
        }

        //TODO: следить за количеством тегов, чтобы < и > одинаковое кол-во

        try {
            if (line.find(">") == std::string::npos && line.find("<") != std::string::npos ||
                line.find("<") == std::string::npos && line.find(">") != std::string::npos) 
            {
                input_xml.close();
                throw std::string{ "Error loading xml file (invalid xml file)" };
            }
        } 
        catch (const std::string& ex) {
            std::cout << ex << std::endl;
            return std::stringstream();
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

    return output;
}

bool XMLResource::IsTag(const std::string& line) {
    return (line.find("<") != std::string::npos && line.find(">") != std::string::npos);
}

bool XMLResource::IsValue(const std::string& line) {
    return (line.find("<") == std::string::npos && line.find(">") == std::string::npos);
}

void XMLResource::LoadInTreeXML(std::stringstream& xml_file) {
    std::string line;
    std::string tag;
    while (std::getline(xml_file, line)) {
        std::cout << "LINE: " << line << std::endl;
        if (line.empty()) {
            continue;
        }

        try {
            size_t position_open_parenthesis = line.find("<");
            size_t position_close_parenthesis = line.find(">");
            if (line.find(">") == std::string::npos && line.find("<") != std::string::npos ||
                line.find("<") == std::string::npos && line.find(">") != std::string::npos)
            {
                throw std::string{ "Error loading xml file (invalid xml file)" };
            }
            
            if (IsTag(line)) {
                tag = line.substr(position_open_parenthesis, position_close_parenthesis - position_open_parenthesis);
                //TODO: TreeXML adding NodeXML
            }

        }
        catch(const std::string& ex) {
            std::cout << ex << std::endl;
            return;
        }
    }
}

void XMLResource::Load(const std::string& filename) {
	std::ifstream input_xml(filename);
	std::stringstream xml_file = ConvertToNormalForm(input_xml);
    LoadInTreeXML(xml_file);
    input_xml.close();
}

