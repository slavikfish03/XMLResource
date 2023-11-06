#pragma once
#include "NodeXML.hpp"

#include <memory>
#include <iostream>
#include <fstream>
#include <stack>

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
};

class TreeXML {
private:
	std::shared_ptr<NodeXML> _root;
public:
	using iterator = IteratorXML<NodeXML>;
	using const_iterator = IteratorXML<const NodeXML>;

	TreeXML();

	void AppendRoot(const std::string& tag, const std::string& value);
	bool IsEmpty();

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	IteratorXML<NodeXML>& Find(const std::string& tag, const std::string& value);
	IteratorXML<NodeXML>& Add(const std::string& tag, const std::string& value, const IteratorXML<NodeXML>& iter_add);
	bool Erase(const IteratorXML<NodeXML>& iter_delete);

	void PrintTree();
	void PrintChildren(NodeXML& node);

	void SaveTreeInFile(std::ofstream& output_xml);
	void SaveChildrenInFile(NodeXML& node, std::ofstream& output_xml);

};