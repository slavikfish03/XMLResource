#pragma once
#include "NodeXML.hpp"

#include <memory>

template <typename T>
class IteratorXML : public std::iterator<std::input_iterator_tag, T> {
	friend class TreeXML;
private:
	T* _p;

	IteratorXML(T* p);
public:
	using reference = T&;
	IteratorXML(const IteratorXML& it);

	bool operator != (IteratorXML const& other_it) const;
	bool operator == (IteratorXML const& other_it) const;
	typename IteratorXML::reference operator*() const;
	IteratorXML& operator++();

	IteratorXML& Upward(IteratorXML const& iter);
};

class TreeXML {
private:
	std::unique_ptr<NodeXML> _root;
public:
	using iterator = IteratorXML<NodeXML>;
	using const_iterator = IteratorXML<const NodeXML>;

	TreeXML();

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;


	void PrintTree();

};