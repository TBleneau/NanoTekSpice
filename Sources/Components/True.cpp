//
// EPITECH PROJECT, 2018
// True.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/True.hpp"
#include "Exception.hpp"

nts::True::True(std::string const &name) noexcept
	: _name(name), _type("true"), _state(nts::TRUE)
{}

nts::True::~True(void) noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::True::compute(std::size_t const &pin)
{
	validPin(pin);
	return _state;
}

void nts::True::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_link[pinC - 1]._component = &otherC;
	_link[pinC - 1]._pin = otherPin;
}

void nts::True::dump(void)
{}

std::string const &nts::True::getType(void) const noexcept
{
	return _type;
}

void nts::True::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
	std::cerr << "You can't change state of this component" << std::endl;
}

nts::Tristate const &nts::True::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::True::validPin(std::size_t const &pin) const
{
	if (pin > 1)
		throw Exception(E_PIN);
}

std::string const &nts::True::getName(void) const noexcept
{
	return _name;
}
