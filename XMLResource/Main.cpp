#include "XMLResource.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>


int main() {
    std::string filename = "..\\example1.xml"; // this path is necessary for CMake

    std::unique_ptr<XMLResource> xml_resource = XMLResource::Create();

    std::cout << "Tree output: " << std::endl;
    xml_resource->LoadFromFile(filename);
    xml_resource->GetTreeXML().PrintTree();
    std::cout << "End of tree output\n____" << std::endl;

    std::cout << "Example of adding an element to a tree: " << std::endl;
    TreeXML::iterator head_iter = xml_resource->GetTreeXML().Find("head", "7");
    std::cout << (*head_iter).GetTag() << (*head_iter).GetValue() << std::endl;
    xml_resource->GetTreeXML().Add("c", "5", head_iter);
    xml_resource->GetTreeXML().PrintTree();
    std::cout << "End of the example of adding an element to the tree\n____" << std::endl;

    std::cout << "Attempt to delete a non-existent element" << std::endl;
    TreeXML::iterator d_iter = xml_resource->GetTreeXML().Find("d", "9");
    xml_resource->GetTreeXML().Erase(d_iter);
    xml_resource->GetTreeXML().PrintTree();
    std::cout << "End of attempt to delete a non-existent element\n____" << std::endl;

    xml_resource->SaveInFile("..\\output_example.xml"); // this path is necessary for CMake

    return 0;
}