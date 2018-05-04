//
// EPITECH PROJECT, 2018
// C4040.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/C4040.hpp"
#include "Exception.hpp"

nts::C4040::C4040(std::string const &name) noexcept
	: _name(name), _type("4040"), _state(nts::UNDEFINED)
{
}

nts::C4040::~C4040() noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::C4040::compute(std::size_t const &pin)
{
	nts::Tristate ret = nts::UNDEFINED;

	validPin(pin);
	return ret;
}

void nts::C4040::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_links[pinC - 1]._pin = otherPin;
	_links[pinC - 1]._component = &otherC;
}

void nts::C4040::dump(void)
{}

std::string const &nts::C4040::getType(void) const noexcept
{
	return _type;
}

void nts::C4040::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::C4040::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::C4040::validPin(std::size_t const &pin) const
{
	if (pin == 0 || pin == 8 || pin >= 16)
		throw Exception(E_PIN);
}

std::string const &nts::C4040::getName(void) const noexcept
{
	return _name;
}
