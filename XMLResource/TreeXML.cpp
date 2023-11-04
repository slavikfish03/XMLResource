#include "TreeXML.hpp"

TreeXML::TreeXML() {
	_root = nullptr;
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
	if (_p.GetChildren().empty()) {

	}
}

template <typename T>
IteratorXML<T>& IteratorXML<T>::Upward(IteratorXML const& iter) {

}