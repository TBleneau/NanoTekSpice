//
// EPITECH PROJECT, 2018
// Input.cpp
// File description:
// Created by Thomas BLENEAU
//

#include "Components/Input.hpp"
#include "Exception.hpp"

nts::Input::Input(std::string const &name) noexcept
	: _name(name), _type("input"), _state(nts::UNDEFINED)
{}

nts::Input::~Input(void) noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::Input::compute(std::size_t const &pin)
{
	validPin(pin);
	return _state;
}

void nts::Input::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_link[pinC - 1]._component = &otherC;
	_link[pinC - 1]._pin = otherPin;
}

void nts::Input::dump(void)
{}

std::string const &nts::Input::getType(void) const noexcept
{
	return _type;
}

void nts::Input::setTristate(nts::Tristate const &state) noexcept
{
	_state = state;
}

nts::Tristate const &nts::Input::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::Input::validPin(std::size_t const &pin) const
{
	if (pin > 1)
		throw Exception(E_PIN);
}

std::string const &nts::Input::getName(void) const noexcept
{
	return _name;
}
