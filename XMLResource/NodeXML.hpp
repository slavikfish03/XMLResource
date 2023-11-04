#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class NodeXML;

using PtrXmlNodes = std::vector<std::shared_ptr<NodeXML>>;

class NodeXML {
private:
	std::string _tag;
	std::string _value;
	PtrXmlNodes _children;
	std::shared_ptr<NodeXML> _parent;
public:
	NodeXML(const std::string& tag, const std::string& value, const PtrXmlNodes& children);

	//bool operator != (NodeXML const& other_node) const;
	//bool operator == (NodeXML const& other_node) const;
	//NodeXML& operator++();

	void SetTag(const std::string& new_tag);
	void SetValue(const std::string& new_value);
	void SetChildren(const PtrXmlNodes& new_children);
	void SetParent(const std::shared_ptr<NodeXML>& new_parent);

	std::string GetTag() const;
	std::string GetValue() const;
	PtrXmlNodes GetChildren() const;
	std::shared_ptr<NodeXML> GetParent() const;
};