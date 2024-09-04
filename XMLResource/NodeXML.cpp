#include "NodeXML.hpp"

NodeXML::NodeXML(const std::string& tag, const std::string& value) {
	_tag = tag;
	_value = value;
	_parent = nullptr;
}

void NodeXML::AppendChild(const std::shared_ptr<NodeXML>& child) {
	_children.push_back(child);
}

void NodeXML::SetParent(std::shared_ptr<NodeXML> new_parent) {
	_parent = new_parent;
}

std::string NodeXML::GetTag() const {
	return _tag;
}

std::string NodeXML::GetValue() const {
	return _value;
}

PtrXmlNodes& NodeXML::GetChildren() {
	return _children;
}

std::shared_ptr<NodeXML> NodeXML::GetParent() {
	return _parent;
}

std::shared_ptr<NodeXML> NodeXML::GetPtr() { 
	return shared_from_this(); 
}