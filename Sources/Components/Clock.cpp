//
// EPITECH PROJECT, 2018
// Clock.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "Components/Clock.hpp"
#include "Exception.hpp"

nts::Clock::Clock(std::string const &name) noexcept
	: _name(name), _type("clock"), _state(nts::FALSE)
{}

nts::Clock::~Clock(void) noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::Clock::compute(std::size_t const &pin)
{
	validPin(pin);
	return _state;
}

void nts::Clock::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_link[pinC - 1]._component = &otherC;
	_link[pinC - 1]._pin = otherPin;
}

void nts::Clock::dump(void)
{}

std::string const &nts::Clock::getType(void) const noexcept
{
	return _type;
}

void nts::Clock::setTristate(nts::Tristate const &state) noexcept
{
	_state = state;
}

nts::Tristate const &nts::Clock::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::Clock::validPin(std::size_t const &pin) const
{
	if (pin > 1)
		throw Exception(E_PIN);
}

std::string const &nts::Clock::getName(void) const noexcept
{
	return _name;
}
