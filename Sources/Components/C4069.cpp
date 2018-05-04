//
// EPITECH PROJECT, 2018
// C4069.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/C4069.hpp"
#include "Exception.hpp"

nts::C4069::C4069(std::string const &name) noexcept
	: _name(name), _type("4069"), _state(nts::UNDEFINED)
{
	_not.emplace(std::make_pair(2, 1));
	_not.emplace(std::make_pair(4, 3));
	_not.emplace(std::make_pair(6, 5));
	_not.emplace(std::make_pair(8, 9));
	_not.emplace(std::make_pair(10, 11));
	_not.emplace(std::make_pair(12, 13));
}

nts::C4069::~C4069() noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::C4069::compute(std::size_t const &pin)
{
	std::size_t pin1;
	nts::Tristate ret = nts::UNDEFINED;

	validPin(pin);
	if (_not.find(pin) == _not.end()) {
		if (_links[pin - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
					<< std::endl;
		else
			ret = _links[pin - 1]._component->compute( _links[pin - 1]._pin);
	} else {
		pin1 = _not[pin];
		if (_links[pin1 - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
					<< std::endl;
		else
			ret = gateNot(_links[pin1 - 1]._component->compute( _links[pin1 - 1]._pin));
	}
	return ret;
}

void nts::C4069::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_links[pinC - 1]._pin = otherPin;
	_links[pinC - 1]._component = &otherC;
}

void nts::C4069::dump(void)
{}

std::string const &nts::C4069::getType(void) const noexcept
{
	return _type;
}

void nts::C4069::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::C4069::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

nts::Tristate nts::C4069::gateNot(nts::Tristate const &state) noexcept
{
	nts::Tristate ret = nts::UNDEFINED;

	if (state == nts::FALSE)
		ret = nts::TRUE;
	else if (state == nts::TRUE)
		ret = nts::FALSE;
	return ret;
}

void nts::C4069::validPin(std::size_t const &pin) const
{
	if (pin == 0 || pin == 7 || pin >= 14)
		throw Exception(E_PIN);
}

std::string const &nts::C4069::getName(void) const noexcept
{
	return _name;
}
