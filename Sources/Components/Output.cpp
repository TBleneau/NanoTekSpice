//
// EPITECH PROJECT, 2018
// Output.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/Output.hpp"
#include "Exception.hpp"

nts::Output::Output(std::string const &name) noexcept
	: _name(name), _type("output"), _state(nts::UNDEFINED)
{}

nts::Output::~Output(void) noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::Output::compute(std::size_t const &pin)
{
	validPin(pin);
	validLink(pin);
	_state = _link[pin - 1]._component->compute(_link[pin - 1]._pin);
	return _state;
}

void nts::Output::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_link[pinC - 1]._pin = otherPin;
	_link[pinC - 1]._component = &otherC;
}

void nts::Output::dump(void)
{
	switch (_state) {
	case nts::TRUE:
		std::cout << _name << "=1" << std::endl;
		break;
	case nts::FALSE:
		std::cout << _name << "=0" << std::endl;
		break;
	case nts::UNDEFINED:
		std::cout << _name << "=U" << std::endl;
		break;
	}
}

std::string const &nts::Output::getType(void) const noexcept
{
	return _type;
}

void nts::Output::setTristate(nts::Tristate const &state) noexcept
{
	_state = state;
}

nts::Tristate const &nts::Output::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::Output::validPin(std::size_t const &pin) const
{
	if (pin > 1)
		throw Exception(E_PIN);
}

void nts::Output::validLink(std::size_t const &pin) const
{
	if (_link[pin - 1]._component == nullptr)
		throw Exception(E_OUTPUT);
}

std::string const &nts::Output::getName(void) const noexcept
{
	return _name;
}
