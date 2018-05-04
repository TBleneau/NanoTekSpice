//
// EPITECH PROJECT, 2018
// NTSParser.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef NTSPARSER_HPP_
	#define NTSPARSER_HPP_

	#include <iostream>
	#include <fstream>
	#include <string>
	#include <vector>
	#include <type_traits>
	#include <unordered_map>
	#include "IComponent.hpp"
	#include "Circuit/Circuit.hpp"

	namespace nts {

		static char const LINKS[] = {'.', 'l', 'i', 'n', 'k',
						's', '\0'};
		static char const CHIPSETS[] = {'.', 'c', 'h', 'i', 'p',
						's', 'e', 't', 's', '\0'};
		static char const FILE_EXT[] = {'.', 'n', 't', 's', '\0'};
		static size_t const EXT_SIZE = 4;
		static char const INPUT_ON[] = {'1', '\0'};
		static char const INPUT_OFF[] = {'0', '\0'};
		static char const FILE_SEP = '.';
		static char const INPUT_SEP = '=';
		static char const COMMENT_SEP = '#';
		static char const SPACE_SEP = ' ';
		static char const TAB_SEP = '\t';
		static char const *const type_c[] = {
			"input",
			"output",
			"clock",
			"true",
			"false",
			"4081",
			"4011",
			"4001",
			"4071",
			"4030",
			"4069",
			NULL
		};

		class NTSParser {
		public:
			NTSParser(std::size_t const &,
					char const *const *const) noexcept;
			~NTSParser() noexcept;
			void parseArgs(Circuit &);
		private:
			std::size_t _argc;
			std::vector<std::string> _argv;

			std::pair<std::string, std::size_t> getArgs(
				std::string const &);
			void getFile(std::string const &, Circuit &) const;
			void validParams() const;
			void validArgs(std::string const &) const;
			void validFile(std::string const &) const;
			void checkType(std::string const &) const;
			void fillComponent(std::string const &, Circuit &)
				const;
			void setLink(std::string const &, Circuit &) const;
			void setInputState(Circuit &);
			std::unordered_map<std::string, std::size_t> _valInput;
		};
	}

#endif // !NTSPARSER_HPP_
