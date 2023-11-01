#pragma once

#include <vector>
#include <string>
#include <memory>

using ptr_xml_nodes = std::vector<std::shared_ptr<NodeXML>>;

class NodeXML {
private:
	std::string tag;
	int value;
	ptr_xml_nodes children;
public:
};