//
// EPITECH PROJECT, 2018
// C4013.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/C4013.hpp"
#include "Exception.hpp"

nts::C4013::C4013(std::string const &name) noexcept
	: _name(name), _type("4013"), _state(nts::UNDEFINED)
{
	_dualOut.emplace(1, nts::UNDEFINED);
	_dualOut.emplace(2, nts::UNDEFINED);
	_dualOut.emplace(12, nts::UNDEFINED);
	_dualOut.emplace(13, nts::UNDEFINED);
}

nts::C4013::~C4013() noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::C4013::compute(std::size_t const &pin)
{
	nts::Tristate ret = nts::UNDEFINED;

	validPin(pin);
	if (_dualOut.find(pin) == _dualOut.end()) {
		if (_links[pin - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
					<< std::endl;
		else
			ret = _links[pin - 1]._component->compute(_links[pin - 1]._pin);
	} else {
		if (pin == 1 || pin == 2)
			ret = firstFlop(pin);
		else if (pin == 13 || pin == 12)
			ret = secondFlop(pin);
	}
	return ret;
}

void nts::C4013::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_links[pinC - 1]._pin = otherPin;
	_links[pinC - 1]._component = &otherC;
}

void nts::C4013::dump(void)
{}

std::string const &nts::C4013::getType(void) const noexcept
{
	return _type;
}

void nts::C4013::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::C4013::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

nts::Tristate nts::C4013::firstFlop(std::size_t const &pin)
{
	if (_links[2]._component == nullptr
		||_links[3]._component == nullptr
		|| _links[4]._component == nullptr
		|| _links[5]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		_dualOut[1] = _links[5]._component->compute(_links[5]._pin);
		_dualOut[2] = _links[3]._component->compute(_links[3]._pin);
		if (_dualOut[2] == nts::FALSE && _dualOut[1] == nts::FALSE)
			computeFlipFlop(1);
	}
	return (pin == 1) ? _dualOut[1] : _dualOut[2];
}

nts::Tristate nts::C4013::secondFlop(std::size_t const &pin)
{
	if (_links[7]._component == nullptr
		||_links[8]._component == nullptr
		|| _links[9]._component == nullptr
		|| _links[10]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		_dualOut[12] = _links[7]._component->compute(_links[7]._pin);
		_dualOut[13] = _links[9]._component->compute(_links[9]._pin);
		if (_dualOut[12] == nts::FALSE && _dualOut[13] == nts::FALSE)
			computeFlipFlop(2);
	}
	return (pin == 12) ? _dualOut[12] : _dualOut[13];
}

void nts::C4013::computeFlipFlop(std::size_t const &index)
{
	nts::Tristate state1 = (index == 1) ? _links[2]._component->compute(_links[2]._pin)
		: _links[10]._component->compute(_links[10]._pin);
	nts::Tristate state2 = (index == 1) ? _links[4]._component->compute(_links[4]._pin)
		: _links[8]._component->compute(_links[8]._pin);

	if (index == 1) {
		_dualOut[1] = (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED) ?
			nts::UNDEFINED : _dualOut[1];
		_dualOut[2] = (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED) ?
			nts::UNDEFINED : _dualOut[1];
		if (_dualOut[1] != nts::UNDEFINED && _dualOut[2] != nts::UNDEFINED) {
			_dualOut[1] = (state1 == nts::TRUE && state2 == nts::TRUE) ?
				nts::TRUE : nts::FALSE;
			_dualOut[2] = (state1 == nts::TRUE && state2 == nts::TRUE) ?
				nts::FALSE : nts::TRUE;
		}
	} else {
		_dualOut[12] = (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED) ?
			nts::UNDEFINED : _dualOut[12];
		_dualOut[13] = (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED) ?
			nts::UNDEFINED : _dualOut[13];
		if (_dualOut[12] != nts::UNDEFINED && _dualOut[13] != nts::UNDEFINED) {
			_dualOut[13] = (state1 == nts::TRUE && state2 == nts::TRUE) ?
				nts::TRUE : nts::FALSE;
			_dualOut[12] = (state1 == nts::TRUE && state2 == nts::TRUE) ?
				nts::FALSE : nts::TRUE;
		}
	}
}

void nts::C4013::validPin(std::size_t const &pin) const
{
	if (pin == 0 || pin == 7 || pin >= 14)
		throw Exception(E_PIN);
}

std::string const &nts::C4013::getName(void) const noexcept
{
	return _name;
}
