//
// EPITECH PROJECT, 2018
// Main.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "Exception.hpp"
#include "Circuit/Circuit.hpp"
#include "NTSParser/NTSParser.hpp"

int main(int argc, char **argv)
{
	std::size_t ret = 0;
	nts::NTSParser parser(argc, argv);
	nts::Circuit circuit;

	try {
		circuit.initCircuit();
		circuit.initShell();
		parser.parseArgs(circuit);
		circuit.shell();
	} catch (Exception &exception) {
		std:: cout << exception.what() << std::endl;
		ret = 84;
	}
	return (ret);
}
