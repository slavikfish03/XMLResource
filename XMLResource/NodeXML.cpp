#include "NodeXML.hpp"

NodeXML::NodeXML(const std::string& tag, const std::string& value) {
	_tag = tag;
	_value = value;
	_parent = nullptr;
}

//bool NodeXML::operator!=(NodeXML const& other_node) const {
//	return (_tag != other_node.GetTag() ||
//		_value != other_node.GetValue() ||
//		_children != other_node.GetChildren());
//}
//
//bool NodeXML::operator==(NodeXML const& other_node) const {
//	return (_tag == other_node.GetTag() &&
//		_value == other_node.GetValue() &&
//		_children == other_node.GetChildren());
//}
//
//NodeXML& NodeXML::operator++() {
//	if (!_children.empty()) {
//		return *(_children.front());
//	}
//
//	if (_children.empty() && (*(std::prev(_parent->GetChildren().end()))).get() == this) {
//		return _parent->GetParent()->GetChildren();
//
//		_parent->GetParent()->GetChildren().;
//	}
//}

void NodeXML::AppendChild(const std::shared_ptr<NodeXML>& child) {
	_children.push_back(child);
	//child->_parent = shared_from_this();

}

void NodeXML::RemoveChild(const std::shared_ptr<NodeXML>& child) {
	if (!_children.empty()) {
		auto NewEnd = std::remove(std::begin(_children),
			std::end(_children), child);

		_children.erase(NewEnd, std::end(_children));
	}
}

void NodeXML::SetTag(const std::string& new_tag) {
	_tag = new_tag;
}

void NodeXML::SetValue(const std::string& new_value) {
	_value = new_value;
}

//void NodeXML::SetChildren(const PtrXmlNodes& new_children) {
//	_children = new_children;
//}

void NodeXML::SetParent(std::shared_ptr<NodeXML> new_parent) {
	_parent = new_parent;
	//_parent->RemoveChild(shared_from_this());
	//new_parent->AppendChild(shared_from_this());
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