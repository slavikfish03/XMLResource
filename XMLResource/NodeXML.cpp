#include "NodeXML.hpp"

NodeXML::NodeXML(const std::string& tag, const std::string& value, const ptr_xml_nodes& children) {
	_tag = tag;
	_value = value;
	_children = children;
}

