#pragma once
#include "NodeXML.hpp"

#include <memory>

class TreeXML {
private:
	std::unique_ptr<NodeXML> _root;
public:
	TreeXML();

	void PrintTree();

};