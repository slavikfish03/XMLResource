#include "TreeXML.hpp"

TreeXML::TreeXML() {
	_root = nullptr;
}

bool TreeXML::IsEmpty() {
	return (_root == nullptr);
}

void TreeXML::AppendRoot(const std::string& tag, const std::string& value) {
	std::shared_ptr<NodeXML> node = std::make_shared<NodeXML>(tag, value);
	//_root = std::move(node);
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
}


IteratorXML<NodeXML>& TreeXML::Add(const std::string& tag, const std::string& value, const IteratorXML<NodeXML>& iter_add) {
	std::shared_ptr<NodeXML> adding_node = std::make_shared<NodeXML>(tag, value);
	//std::shared_ptr<NodeXML> parent = std::make_shared<NodeXML>(*iter_add);
	std::shared_ptr<NodeXML> parent = (*iter_add).GetPtr();
	adding_node->SetParent(parent);
	//std::shared_ptr<NodeXML> parent2 = adding_node->GetParent();
	(*iter_add).AppendChild(adding_node);
	//std::vector<std::shared_ptr<NodeXML>> children1 = (*iter_add).GetChildren();
	//for (auto& child : children1) {
	//	std::cout << child->GetValue() << std::endl;
	//}
	//std::cout << "_________" << std::endl;
	////std::vector<std::shared_ptr<NodeXML>> children2 = parent2->GetChildren();
	//for (auto& child : children2) {
	//	std::cout << child->GetValue() << std::endl;
	//}
	IteratorXML<NodeXML> added_iter = Find(tag, value);
	return added_iter;
}

bool Erase(IteratorXML<NodeXML> iter_delete);

void TreeXML::PrintTree() {
	TreeXML::iterator begin_tree = begin();
	TreeXML::iterator end_tree = end();
	for (auto& it = begin_tree; it != end_tree; ++it) {
		std::cout << "<" << (*it).GetTag() << ">" << " " << (*it).GetValue() << std::endl;
	}
}

TreeXML::iterator TreeXML::begin() {
	return iterator(_root.get());
}

TreeXML::iterator TreeXML::end() {
	//return iterator((*(_root->GetChildren().end())).get());
	return nullptr;
}

TreeXML::const_iterator TreeXML::begin() const {
	return const_iterator(_root.get());
}

TreeXML::const_iterator TreeXML::end() const {
	//return const_iterator((*(_root->GetChildren().end())).get());
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
	//++_p;
	//return *this;
	auto children = _p->GetChildren();
	if (!children.empty()) {
		_p = children[0].get();
	}
	else {
		while (_p->GetParent() != nullptr) {
			bool found = false;
			std::shared_ptr<NodeXML> parent = _p->GetParent();
			PtrXmlNodes brothers = parent->GetChildren();
			//for (size_t i = 0; i < brothers.size() - 1; i++) {
			//	if (brothers[i].get() == _p) {
			//		_p = brothers[i + 1].get();
			//		found = true;
			//		break;
			//	}
			//}
			for (size_t i = 0; i < brothers.size() - 1; i++) {
				if (brothers[i].get() == _p) {
					_p = brothers[i + 1].get();
					found = true;
					break;
				}
				else {
					found = false;
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

//template <typename T>
//IteratorXML<T>& IteratorXML<T>::Upward(IteratorXML const& iter) {
//
//}