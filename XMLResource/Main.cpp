#include "XMLResource.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>


int main() {
    std::string filename = "example1.xml";

    std::unique_ptr<XMLResource> xml_resource = XMLResource::Create();

    xml_resource->Load(filename);

    return 0;
}