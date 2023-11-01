#pragma once

#include "TreeXML.hpp"

#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>

class XMLResource {
private:
	XMLResource() = default;
	TreeXML _treeXML;

	std::stringstream ConvertToNormalForm(std::ifstream& input_xml);
	void LoadInTreeXML(std::stringstream& xml_file);

	bool IsTag(const std::string& line);
	bool IsValue(const std::string& line);
public:
	static std::unique_ptr<XMLResource> Create();
	void Load(const std::string& filename);



};