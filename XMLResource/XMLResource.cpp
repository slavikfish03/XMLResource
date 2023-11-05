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
    std::vector<std::string> element; // this element stores a tag and a value, it 
    // is needed for convenient addition to the TreeXML

    std::vector<std::string> tag_stack;
    std::vector<std::string> value_stack;

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
                //_treeXML.root = nullptr;
                throw std::string{ "Error loading xml file (invalid xml file)" };
            }
            
            if (IsTag(line)) {
                if (line.find("/") == std::string::npos) {
                    tag = line.substr(position_open_parenthesis + 1, position_close_parenthesis - position_open_parenthesis - 1);
                    tag_stack.push_back(tag);
                    element.push_back(tag);
                }
                else {
                    tag_stack.pop_back();
                    value_stack.pop_back();
                }
            }

            if (IsValue(line)) {
                std::string value = line;
                value_stack.push_back(value);
                element.push_back(value);
                
                //TODO: добавление элемента в дерево

                if (_treeXML.IsEmpty()) {
                    _treeXML.AppendRoot(element.at(0), element.at(1));
                    //tag_stack.pop();
                    //value_stack.pop();
                }
                else {
                    std::string parent_tag = tag_stack.at(tag_stack.size() - 2);
                    std::string parent_value = value_stack.at(tag_stack.size() - 2);
                    TreeXML::iterator parent_iter = _treeXML.Find(parent_tag, parent_value);

                    _treeXML.Add(element.at(0), element.at(1), parent_iter);
                }

                element.clear();
            }

        }
        catch (const std::string& ex) {
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

