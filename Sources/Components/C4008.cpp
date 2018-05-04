//
// EPITECH PROJECT, 2018
// C4008.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <iostream>
#include "Components/C4008.hpp"
#include "Exception.hpp"

nts::C4008::C4008(std::string const &name) noexcept
	: _name(name), _type("4008"), _state(nts::UNDEFINED)
{
	_adder.emplace(std::make_pair(10, std::make_pair(6, 7)));
	_adder.emplace(std::make_pair(11, std::make_pair(4, 5)));
	_adder.emplace(std::make_pair(12, std::make_pair(2, 3)));
	_adder.emplace(std::make_pair(13, std::make_pair(1, 15)));
	_out.emplace(std::make_pair(10, nts::UNDEFINED));
	_out.emplace(std::make_pair(11, nts::UNDEFINED));
	_out.emplace(std::make_pair(12, nts::UNDEFINED));
	_out.emplace(std::make_pair(13, nts::UNDEFINED));
	_carryOUT.push_back(nts::UNDEFINED);
	_carryOUT.push_back(nts::UNDEFINED);
	_carryOUT.push_back(nts::UNDEFINED);
	_carryOUT.push_back(nts::UNDEFINED);
}

nts::C4008::~C4008() noexcept
{}

/////////////////////////////// METHOD INTERFACE //////////////////////////////

nts::Tristate nts::C4008::compute(std::size_t const &pin)
{
	nts::Tristate ret = nts::UNDEFINED;

	validPin(pin);
	firstSum();
	if (_out.find(pin) == _out.end()) {
		if (_links[pin - 1]._component == nullptr)
			std::cerr << "Usage Error: Compute error, this pin isn't linked"
				  << std::endl;
		if (pin - 1 == 13)
			ret = _carryOUT[3];
		else
			ret = _links[pin - 1]._component->compute( _links[pin - 1]._pin);
	} else
		ret = _out[pin];
	return ret;
}

void nts::C4008::setLink(std::size_t const &pinC, IComponent &otherC,
				std::size_t const &otherPin)
{
	validPin(pinC);
	_links[pinC - 1]._pin = otherPin;
	_links[pinC - 1]._component = &otherC;
}

void nts::C4008::dump(void)
{}

std::string const &nts::C4008::getType(void) const noexcept
{
	return _type;
}

void nts::C4008::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::C4008::getTristate() const noexcept
{
	return _state;
}

///////////////////////////////////////////////////////////////////////////////

void nts::C4008::firstSum()
{
	nts::Tristate state1;
	nts::Tristate state2;
	nts::Tristate stateCIN;
	std::vector<nts::Tristate> tmp;

	if (_links[5]._component == nullptr ||
		_links[6]._component == nullptr ||
		_links[8]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		state1 = _links[5]._component->compute(_links[5]._pin);
		state2 = _links[6]._component->compute(_links[6]._pin);
		stateCIN = _links[8]._component->compute(_links[8]._pin);
		_out[10] = gateXor(gateXor(state1, state2), stateCIN);
		_carryOUT[0] = gateOr(gateAnd(gateXor(state1, state2),
						stateCIN), gateAnd(state1, state2));
		secondSum();
	}
}

void nts::C4008::secondSum()
{
	nts::Tristate state1;
	nts::Tristate state2;
	nts::Tristate stateCIN;
	std::vector<nts::Tristate> tmp;

	if (_links[3]._component == nullptr ||
		_links[4]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		state1 = _links[3]._component->compute(_links[3]._pin);
		state2 = _links[4]._component->compute(_links[4]._pin);
		stateCIN = _carryOUT[0];
		_out[11] = gateXor(gateXor(state1, state2), stateCIN);
		_carryOUT[1] = gateOr(gateAnd(gateXor(state1, state2),
						stateCIN), gateAnd(state1, state2));
		thirdSum();
	}
}

void nts::C4008::thirdSum()
{
	nts::Tristate state1;
	nts::Tristate state2;
	nts::Tristate stateCIN;
	std::vector<nts::Tristate> tmp;

	if (_links[1]._component == nullptr ||
		_links[2]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		state1 = _links[1]._component->compute(_links[1]._pin);
		state2 = _links[2]._component->compute(_links[2]._pin);
		stateCIN = _carryOUT[1];
		_out[12] = gateXor(gateXor(state1, state2), stateCIN);
		_carryOUT[2] = gateOr(gateAnd(gateXor(state1, state2),
						stateCIN), gateAnd(state1, state2));
		fourthSum();
	}
}

void nts::C4008::fourthSum()
{
	nts::Tristate state1;
	nts::Tristate state2;
	nts::Tristate stateCIN;
	std::vector<nts::Tristate> tmp;

	if (_links[0]._component == nullptr ||
		_links[14]._component == nullptr)
		std::cerr << "Usage Error: Compute error, this pin isn't linked"
				<< std::endl;
	else {
		state1 = _links[0]._component->compute(_links[0]._pin);
		state2 = _links[14]._component->compute(_links[14]._pin);
		stateCIN = _carryOUT[2];
		_out[13] = gateXor(gateXor(state1, state2), stateCIN);
		_carryOUT[3] = gateOr(gateAnd(gateXor(state1, state2),
						stateCIN), gateAnd(state1, state2));
	}
}

nts::Tristate nts::C4008::gateOr(nts::Tristate const &state1,
					nts::Tristate const &state2) noexcept
{
	nts::Tristate ret = nts::FALSE;

	if (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED)
		ret = nts::UNDEFINED;
	else if (state1 == nts::TRUE || state2 == nts::TRUE)
		ret = nts::TRUE;
	return ret;
}

nts::Tristate nts::C4008::gateXor(nts::Tristate const &state1,
				nts::Tristate const &state2) noexcept
{
	nts::Tristate ret = nts::TRUE;

	if (state1 == state2)
		ret = nts::FALSE;
	else if (state1 == nts::UNDEFINED || state2 == nts::UNDEFINED)
		ret = nts::UNDEFINED;
	return ret;
}

nts::Tristate nts::C4008::gateAnd(nts::Tristate const &state1,
				nts::Tristate const &state2) noexcept
{
	nts::Tristate ret = nts::UNDEFINED;

	if (state1 == nts::FALSE || state2 == nts::FALSE)
		ret = nts::FALSE;
	else if (state1 == nts::TRUE && state2 == nts::TRUE)
		ret = nts::TRUE;
	return ret;
}

void nts::C4008::validPin(std::size_t const &pin) const
{
	if (pin == 0 || pin == 8 || pin >= 16)
		throw Exception(E_PIN);
}

std::string const &nts::C4008::getName(void) const noexcept
{
	return _name;
}
