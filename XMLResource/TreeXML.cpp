#include "TreeXML.hpp"

TreeXML::TreeXML() {
	_root = nullptr;
}

bool TreeXML::IsEmpty() {
	return (_root == nullptr);
}

void TreeXML::AppendRoot(const std::string& tag, const std::string& value) {
	std::shared_ptr<NodeXML> node = std::make_shared<NodeXML>(tag, value);
	_root = node;
}

IteratorXML<NodeXML>& TreeXML::Find(const std::string& tag, const std::string& value) {
	TreeXML::iterator begin_tree = begin();
	TreeXML::iterator end_tree = end();
	for (auto& it = begin_tree; it != end_tree; ++it) {
		if (it._p->GetTag() == tag && it._p->GetValue() == value) {
			IteratorXML<NodeXML> iter_find = it;
			return iter_find;
		}
	}
	return end_tree;
}


IteratorXML<NodeXML>& TreeXML::Add(const std::string& tag, const std::string& value, const IteratorXML<NodeXML>& iter_add) {
	std::shared_ptr<NodeXML> adding_node = std::make_shared<NodeXML>(tag, value);
	std::shared_ptr<NodeXML> parent = (*iter_add).GetPtr();

	adding_node->SetParent(parent);
	(*iter_add).AppendChild(adding_node);

	IteratorXML<NodeXML> added_iter = Find(tag, value);
	return added_iter;
}

bool TreeXML::Erase(const IteratorXML<NodeXML>& iter_delete) {
	/*
	the Erase function deletes the node along with its children, I found it more logical in the context of an XML tree
	*/

	try {
		if (iter_delete == end()) {
			throw std::string{ "Error adding a node to the tree (non-existent element)" };
		}

		std::shared_ptr<NodeXML> parent = (*iter_delete).GetParent();
		PtrXmlNodes children = (*iter_delete).GetChildren();
		std::string tag = (*iter_delete).GetTag();
		std::string value = (*iter_delete).GetValue();

		if ((parent == nullptr && iter_delete != begin()) || tag.empty() || value.empty()) {	
			throw std::string{ "Error adding a node to the tree (non-existent element)" };
		}
	
		auto result_search_in_children = std::find(parent->GetChildren().begin(), parent->GetChildren().end(), (*iter_delete).GetPtr());
		if (result_search_in_children == parent->GetChildren().end()) {
			throw std::string{ "Error adding a node to the tree (non-existent element)" };
		}


		(*iter_delete).SetParent(nullptr);
		for (auto& child : (*iter_delete).GetChildren()) {
			child = nullptr;
		}
		children.clear();

		parent->GetChildren().erase(result_search_in_children);
		return true;
	}
	catch (const std::string& ex) {
		std::cout << ex << std::endl;
		return false;
	}
	catch (...) {
		std::cout << "Error adding a node to the tree (invalid iterator)" << std::endl;
		return false;
	}

};

void TreeXML::PrintTree() {
	TreeXML::iterator begin_tree = begin();
	PrintChildren(*begin_tree);
}

void TreeXML::PrintChildren(NodeXML& node) {

	std::string tag, value;
	PtrXmlNodes children;
	tag = node.GetTag();
	value = node.GetValue();
	children = node.GetChildren();

	bool empty_children = false;
	bool all_children_checked = false;

	std::cout << "<" << tag << ">" << "\n" << value << std::endl;
	while (!empty_children) {
		if (children.empty() || all_children_checked) {
			empty_children = true;
			std::cout << "</" << tag << ">" << std::endl;
		}
		else {
			for (const auto& child : children) {

				PrintChildren(*child);
				if (child == children.at(children.size() - 1)) {
					all_children_checked = true;
				}
			}
		}
	}
}

void TreeXML::SaveTreeInFile(std::ofstream& output_xml) {
	TreeXML::iterator begin_tree = begin();
	try {
		if (!output_xml.is_open()) {
			throw std::string{ "Error writing to XML file" };
		}
	}
	catch (const std::string& ex) {
		std::cout << ex << std::endl;
		return;
	}
	SaveChildrenInFile(*begin_tree, output_xml);
}

void TreeXML::SaveChildrenInFile(NodeXML& node, std::ofstream& output_xml) {

	std::string tag, value;
	PtrXmlNodes children;
	tag = node.GetTag();
	value = node.GetValue();
	children = node.GetChildren();

	bool empty_children = false;
	bool all_children_checked = false;
	try {
		output_xml << "<" << tag << ">" << "\n" << value << "\n";
		while (!empty_children) {
			if (children.empty() || all_children_checked) {
				empty_children = true;
				output_xml << "</" << tag << ">" << "\n";
			}
			else {
				for (const auto& child : children) {

					SaveChildrenInFile(*child, output_xml);
					if (child == children.at(children.size() - 1)) {
						all_children_checked = true;
					}
				}
			}
		}
	}
	catch (...) {
		output_xml.close();
		std::cout << "Error writing to XML file" << std::endl;
	}
}

TreeXML::iterator TreeXML::begin() {
	return iterator(_root.get());
}

TreeXML::iterator TreeXML::end() {
	return nullptr;
}

TreeXML::const_iterator TreeXML::begin() const {
	return const_iterator(_root.get());
}

TreeXML::const_iterator TreeXML::end() const {
	return nullptr;
}

// ITERATOR

template <typename T>
IteratorXML<T>::IteratorXML(T* p) {
	_p = p;
}

template <typename T>
IteratorXML<T>::IteratorXML(const IteratorXML& it) {
	_p = it._p;
}

template <typename T>
bool IteratorXML<T>::operator!=(IteratorXML const& other_it) const {
	return _p != other_it._p;
}

template <typename T>
bool IteratorXML<T>::operator==(IteratorXML const& other_it) const {
	return _p == other_it._p;
}

template <typename T>
typename IteratorXML<T>::reference IteratorXML<T>::operator*() const {
	return *_p;
}

template <typename T>
IteratorXML<T>& IteratorXML<T>::operator++() {
	auto children = _p->GetChildren();
	if (!children.empty()) {
		_p = children[0].get();
	}
	else {
		while (_p->GetParent() != nullptr) {
			bool found = false;
			std::shared_ptr<NodeXML> parent = _p->GetParent();
			PtrXmlNodes brothers = parent->GetChildren();
			for (size_t i = 0; i < brothers.size() - 1; i++) {
				if (brothers[i].get() == _p) {
					_p = brothers[i + 1].get();
					found = true;
					break;
				}
			}
			if (!found) {
				_p = _p->GetParent().get();
			}
			else {
				break;
			}
		}
		if (_p->GetParent() == nullptr) {
			_p = nullptr;
		}
	}
	return *this;
}