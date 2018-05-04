//
// EPITECH PROJECT, 2018
// NTSParser.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <regex>
#include "Exception.hpp"
#include "NTSParser/NTSParser.hpp"

nts::NTSParser::NTSParser(std::size_t const &argc, char const *const *const argv)
	noexcept : _argc(argc)
{
	for (std::size_t inc = 1; inc < this->_argc; inc++)
		_argv.push_back(argv[inc]);
}

nts::NTSParser::~NTSParser() noexcept
{}

void nts::NTSParser::validFile(std::string const &file) const
{
	std::string tmp;
	std::string line;
	std::ifstream content(file);
	static size_t nbFile = 0;

	nbFile += 1;
	if (nbFile > 1)
		throw Exception(E_NB_FILE);
	if (content.is_open()) {
		while (getline(content, line))
			tmp += line;
		if (tmp.empty() == true)
			throw Exception(E_FILE);
	} else
		throw Exception(E_OPEN);
}

void nts::NTSParser::validParams() const
{
	std::string tmp;
	std::size_t pos = 0;
	std::size_t inc = 0;

	for (inc = 0; inc < _argv.size(); inc++) {
		pos = _argv[inc].find(FILE_SEP);
		if (_argv[inc].size() > 4 && pos < _argv[inc].size()) {
			tmp = _argv[inc].substr(pos, EXT_SIZE);
			if (tmp.compare(FILE_EXT) == 0)
				validFile(_argv[inc]);
			else
				throw Exception(E_USE);
		} else
			validArgs(_argv[inc]);
	}
}

void nts::NTSParser::validArgs(std::string const &args) const
{
	bool ret = false;
	std::string tmp;
	std::size_t pos = 0;
	std::size_t inc[2] = {0, 0};

	for (inc[0] = 0; inc[0] < args.size(); inc[0]++) {
		if (args[inc[0]] == INPUT_SEP)
			inc[1] += 1;
	} if (inc[1] == 1) {
		pos = args.find(INPUT_SEP);
		tmp = args.substr(pos + 1, args.size() - pos);
		ret = (tmp.compare(INPUT_ON) == 0 ||
			tmp.compare(INPUT_OFF) == 0) ? false : true;
	} else
		throw Exception(E_ARGS);
	if (ret == true)
		throw Exception(E_INPUT);
}

std::pair<std::string, std::size_t> nts::NTSParser::getArgs(
	std::string const &args)
{
	std::size_t pos = args.find(INPUT_SEP);

	return std::pair<std::string, std::size_t>(args.substr(0, pos),
		stoi(args.substr(pos + 1, args.size() - pos), 0, 10));
}

void nts::NTSParser::parseArgs(Circuit &circuit)
{
	std::size_t pos = 0;
	std::size_t inc = 0;

	(void) circuit;
	validParams();
	for (inc = 0; inc < _argv.size(); inc++) {
		pos = _argv[inc].find(FILE_SEP);
		if (_argv[inc].size() > 4 && pos < _argv[inc].size())
			getFile(_argv[inc], circuit);
		else
			this->_valInput.insert(getArgs(_argv[inc]));
	}
	setInputState(circuit);
}

void nts::NTSParser::getFile(std::string const &file, Circuit &circuit) const
{
	std::string tmp;
	bool cursor = false;
	std::ifstream content(file);

	while (getline(content, tmp) && (tmp.compare(0, 6, LINKS) != 0)) {
		if (!tmp.empty() && (tmp.compare(0, 9, CHIPSETS) == 0 ||
					cursor == true)) {
			fillComponent(tmp, circuit);
			cursor = true;
		}
	} while (getline(content, tmp)) {
		if (!tmp.empty())
			setLink(tmp, circuit);
	}
}

void nts::NTSParser::setLink(std::string const &link, Circuit &circuit) const
{
	std::smatch linkM;
	std::pair<std::string, std::size_t> link1;
	std::pair<std::string, std::size_t> link2;
	std::regex reg("^(\\S+):(\\d+)\\s+(\\S+):(\\d+)");

	if (std::regex_search(link, linkM, reg)) {
		link1 = std::make_pair(linkM.str(1), stoi(linkM.str(2)));
		link2 = std::make_pair(linkM.str(3), stoi(linkM.str(4)));
		if (link1 == link2)
			throw Exception(E_LINK);
		circuit.setLink(link1, link2);
	} else
		throw Exception(E_FILE);
}

void nts::NTSParser::fillComponent(std::string const &chipset, Circuit &circuit)
	const
{
	std::smatch val;
	std::regex reg("^(\\S+)\\s+([^\\s(]+)(?:\\(([^\\s]+)\\))?$");

	if (chipset.compare(0, 9, CHIPSETS) != 0) {
		if (std::regex_search(chipset, val, reg))
			circuit.pushComponent(val.str(1), val.str(2));
		else
			throw Exception(E_FILE);
	}
}

void nts::NTSParser::checkType(std::string const &type) const
{
	size_t inc = 0;
	size_t valid = 0;

	while (type_c && type_c[inc]) {
		if (type.compare(type_c[inc]) == 0)
			valid += 1;
		inc += 1;
	}
	if (valid != 1)
		throw Exception(E_TYPE);
}

void nts::NTSParser::setInputState(Circuit &circuit)
{
	std::unordered_map<std::string, std::size_t>::iterator ite;

	for (ite = _valInput.begin(); ite != _valInput.end(); ite++) {
		switch (ite->second) {
		case 1:
			circuit.setInputState(ite->first, nts::TRUE, true);
			break;
		case 0:
			circuit.setInputState(ite->first, nts::FALSE, true);
			break;
		default:
			break;
		}
	}
}
