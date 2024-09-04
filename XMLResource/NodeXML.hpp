#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class NodeXML;

using PtrXmlNodes = std::vector<std::shared_ptr<NodeXML>>;

class NodeXML : public std::enable_shared_from_this<NodeXML> {
private:
	std::string _tag;
	std::string _value;
	PtrXmlNodes _children;
	std::shared_ptr<NodeXML> _parent;
public:
	NodeXML(const std::string& tag, const std::string& value);

	void AppendChild(const std::shared_ptr<NodeXML>& child);
	void SetParent(std::shared_ptr<NodeXML> new_parent);

	std::string GetTag() const;
	std::string GetValue() const;
	PtrXmlNodes& GetChildren();
	std::shared_ptr<NodeXML> GetParent();

	std::shared_ptr<NodeXML> GetPtr();
};