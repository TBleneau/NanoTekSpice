//
// EPITECH PROJECT, 2018
// False.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/False.hpp"
#include "Exception.hpp"

nts::False::False(std::string const &name) noexcept
	: _name(name), _type("false"), _state(nts::FALSE)
{}

nts::False::~False(void) noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::False::compute(std::size_t const &pin)
{
	validPin(pin);
	return _state;
}

void nts::False::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_link[pinC - 1]._component = &otherC;
	_link[pinC - 1]._pin = otherPin;
}

void nts::False::dump(void)
{}

std::string const &nts::False::getType(void) const noexcept
{
	return _type;
}

void nts::False::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
	std::cerr << "You can't change state of this component" << std::endl;
}

nts::Tristate const &nts::False::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::False::validPin(std::size_t const &pin) const
{
	if (pin > 1)
		throw Exception(E_PIN);
}

std::string const &nts::False::getName(void) const noexcept
{
	return _name;
}
