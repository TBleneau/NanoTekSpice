//
// EPITECH PROJECT, 2018
// Exception.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef EXCEPTION_HPP_
	#define EXCEPTION_HPP_

	#include <exception>
	#include <string>

	enum e_error {
		E_USE,
		E_ARGS,
		E_INPUT,
		E_FILE,
		E_OPEN,
		E_NB_FILE,
		E_TYPE,
		E_LINK,
		E_EXIST,
		E_NAME,
		E_PIN,
		E_OUTPUT,
		E_CIRCUIT,
		E_ICIRCUIT
	};

	static char const *const e_exception[] = {
		[E_USE] = "Usage Error: ./nanotekspice file.nts [input=value] [..]",
		[E_ARGS] = "Usage Error: Wrong Argument",
		[E_INPUT] = "Usage Error: Input value must be 0 or 1",
		[E_FILE] = "Usage Error: Invalid file",
		[E_OPEN] = "Usage Error: No such file",
		[E_NB_FILE] = "Usage Error: No more than one file.nts",
		[E_TYPE] = "Usage Error: Invalid type of component in {file}.nts",
		[E_LINK] = "Usage Error: You can't link a pin to itself",
		[E_EXIST] = "Usage Error: Component name already used",
		[E_NAME] = "Usage Error: Link error, component name unknow",
		[E_PIN] = "Usage Error: Link error, invalid pin used",
		[E_OUTPUT] = "Usage Error: Link error, output not linked",
		[E_CIRCUIT] = "Usage Error: This component doesn't exist",
		[E_ICIRCUIT] = "Usage Error: This component isn't an input"
	};

	class Exception : public std::exception {
		public:
		explicit Exception(enum e_error const &except) {
			this->_except = except;
		};
		~Exception() override = default;
		const char *what() const noexcept override {
			return e_exception[this->_except];
		};
	private:
		enum e_error _except;
	};

#endif // EXCEPTION_HPP_
