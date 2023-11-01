#pragma once

#include <vector>
#include <string>
#include <memory>

class NodeXML;

using ptr_xml_nodes = std::vector<std::shared_ptr<NodeXML>>;

class NodeXML {
private:
	std::string _tag;
	std::string _value;
	ptr_xml_nodes _children;
public:
	void SetTag(std::string new_tag);
	void SetValue(std::string new_value);
	void SetChildren(ptr_xml_nodes new_children);

	NodeXML(const std::string& tag, const std::string& value, const ptr_xml_nodes& children);

	std::string& GetTag() const;
	std::string& GetValue() const;
	ptr_xml_nodes& GetChildren() const;

};