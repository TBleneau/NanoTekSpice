//
// EPITECH PROJECT, 2018
// C4081.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/C4081.hpp"
#include "Exception.hpp"

nts::C4081::C4081(std::string const &name) noexcept
	: _name(name), _type("4081"), _state(nts::UNDEFINED)
{
	_and.emplace(std::make_pair(3, std::make_pair(1, 2)));
	_and.emplace(std::make_pair(4, std::make_pair(5, 6)));
	_and.emplace(std::make_pair(10, std::make_pair(8, 9)));
	_and.emplace(std::make_pair(11, std::make_pair(12, 13)));
}

nts::C4081::~C4081() noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::C4081::compute(std::size_t const &pin)
{
	std::size_t pin1;
	std::size_t pin2;
	nts::Tristate ret = nts::UNDEFINED;

	validPin(pin);
	if (_and.find(pin) == _and.end()) {
		if (_links[pin - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
					<< std::endl;
		else
			ret = _links[pin - 1]._component->compute( _links[pin - 1]._pin);
	} else {
		pin1 = _and[pin].first;
		pin2 = _and[pin].second;
		if (_links[pin1 - 1]._component == nullptr ||
			_links[pin2 - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
					<< std::endl;
		else
			ret = gateAnd(_links[pin1 - 1]._component->compute( _links[pin1 - 1]._pin),
				_links[pin2 - 1]._component->compute( _links[pin2 - 1]._pin));
	}
	return ret;
}

void nts::C4081::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_links[pinC - 1]._pin = otherPin;
	_links[pinC - 1]._component = &otherC;
}

void nts::C4081::dump(void)
{}

std::string const &nts::C4081::getType(void) const noexcept
{
	return _type;
}

void nts::C4081::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::C4081::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

nts::Tristate nts::C4081::gateAnd(nts::Tristate const &state1,
					nts::Tristate const &state2) noexcept
{
	nts::Tristate ret = nts::UNDEFINED;

	if (state1 == nts::FALSE || state2 == nts::FALSE)
		ret = nts::FALSE;
	else if (state1 == nts::TRUE && state2 == nts::TRUE)
		ret = nts::TRUE;
	return ret;
}

void nts::C4081::validPin(std::size_t const &pin) const
{
	if (pin == 0 || pin == 7 || pin >= 14)
		throw Exception(E_PIN);
}

std::string const &nts::C4081::getName(void) const noexcept
{
	return _name;
}
