//
// EPITECH PROJECT, 2018
// Circuit.cpp
// File description:
// Created by Thomas BLENEAU
//

#include <csignal>
#include <algorithm>
#include "Circuit/Circuit.hpp"
#include "Components/Input.hpp"
#include "Components/Output.hpp"
#include "Components/True.hpp"
#include "Components/False.hpp"
#include "Components/Clock.hpp"
#include "Components/C4081.hpp"
#include "Components/C4011.hpp"
#include "Components/C4001.hpp"
#include "Components/C4071.hpp"
#include "Components/C4030.hpp"
#include "Components/C4069.hpp"
#include "Components/C4008.hpp"
#include "Components/C4013.hpp"

bool nts::Circuit::_quit = false;

nts::Circuit::Circuit(void) noexcept
	: _type("circuit"), _state(nts::UNDEFINED)
{}

nts::Circuit::~Circuit(void) noexcept
{}

void nts::Circuit::quit(int signal)
{
	(void) signal;
	nts::Circuit::_quit = false;
}

void nts::Circuit::initCircuit(void)
{
	_createFunc.emplace(std::make_pair("input", &nts::Circuit::createInput));
	_createFunc.emplace(std::make_pair("output", &nts::Circuit::createOutput));
	_createFunc.emplace(std::make_pair("true", &nts::Circuit::createTrue));
	_createFunc.emplace(std::make_pair("false", &nts::Circuit::createFalse));
	_createFunc.emplace(std::make_pair("clock", &nts::Circuit::createClock));
	_createFunc.emplace(std::make_pair("4081", &nts::Circuit::create4081));
	_createFunc.emplace(std::make_pair("4011", &nts::Circuit::create4011));
	_createFunc.emplace(std::make_pair("4001", &nts::Circuit::create4001));
	_createFunc.emplace(std::make_pair("4071", &nts::Circuit::create4071));
	_createFunc.emplace(std::make_pair("4030", &nts::Circuit::create4030));
	_createFunc.emplace(std::make_pair("4069", &nts::Circuit::create4069));
	_createFunc.emplace(std::make_pair("4008", &nts::Circuit::create4008));
	_createFunc.emplace(std::make_pair("4013", &nts::Circuit::create4013));
}

void nts::Circuit::initShell(void)
{
	_running = true;
	signal(SIGINT, nts::Circuit::quit);
	_shellFunc.emplace(std::make_pair("dump", &nts::Circuit::dump));
	_shellFunc.emplace(std::make_pair("loop", &nts::Circuit::loop));
	_shellFunc.emplace(std::make_pair("display", &nts::Circuit::display));
	_shellFunc.emplace(std::make_pair("simulate", &nts::Circuit::simulate));
	_shellFunc.emplace(std::make_pair("exit", &nts::Circuit::exit));
}

///////////////////////////// METHOD INTERFACE /////////////////////////////////

nts::Tristate nts::Circuit::compute(std::size_t const &pin)
{
	(void) pin;
	return nts::UNDEFINED;
}

void nts::Circuit::setLink(std::size_t const &pin, nts::IComponent &otherC,
			std::size_t const &otherPin)
{
	(void) pin;
	(void) otherC;
	(void) otherPin;
}

std::string const &nts::Circuit::getType(void) const noexcept
{
	return _type;
}

void nts::Circuit::setTristate(nts::Tristate const &state) noexcept
{
	(void) state;
}

nts::Tristate const &nts::Circuit::getTristate() const noexcept
{
	return _state;
}

void nts::Circuit::dump(void)
{}

void nts::Circuit::loop(void)
{
	nts::Circuit::_quit = true;

	while (nts::Circuit::_quit)
		simulate();
}

void nts::Circuit::display(void)
{
	std::map<std::string, std::unique_ptr<nts::IComponent>>::iterator ite;

	for (ite = _components.begin(); ite != _components.end(); ite++) {
		if (ite->second->getType() == "output")
			ite->second->dump();
	}
}

void nts::Circuit::simulate(void)
{
	std::map<std::string, std::unique_ptr<nts::IComponent>>::iterator ite;

	for (ite = _components.begin(); ite != _components.end(); ite++) {
		if (ite->second->getType() == "clock")
			changeState(ite->first);
		if (ite->second->getType() == "output")
			ite->second->compute();
	}
}

void nts::Circuit::exit(void)
{
	_running = false;
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////// SHELL METHOD ////////////////////////////////////

void nts::Circuit::changeState(std::string const &name) noexcept
{
	nts::Tristate tmp;

	if (_components.find(name) != _components.end()) {
		tmp = _components[name]->getTristate();
		if (tmp == nts::TRUE)
			_components[name]->setTristate(nts::FALSE);
		else if (tmp == nts::FALSE)
			_components[name]->setTristate(nts::TRUE);
	}
}

void nts::Circuit::setInputState(std::string const &name,
				 nts::Tristate const &state, bool except)
{
	if (_components.find(name) == _components.end() && !except)
		std::cerr << "Usage Error: This component doesn't exist" << std::endl;
	else if (_components.find(name) == _components.end() && except)
		throw Exception(E_CIRCUIT);
	else if (_components[name]->getType() != "input" && !except)
			std::cerr << "Usage Error: This component isn't an input" << std::endl;
	else if (_components[name]->getType() != "input" && except)
		throw Exception(E_ICIRCUIT);
	else
		_components[name]->setTristate(state);
}

void nts::Circuit::getState(std::string &tmp)
{
	std::string name;
	std::string state;
	std::unique_ptr<nts::Input> input = nullptr;

	if (tmp.find_first_of("=") != std::string::npos) {
		name = tmp.substr(0, tmp.find_first_of("="));
		state = tmp.substr(tmp.find_first_of("=") + 1, tmp.size());
		if (state != "1" && state != "0")
			std::cerr << "Usage Error: The value of an input must be 1 or 0" << std::endl;
		else
			(state == "1") ? setInputState(name, nts::TRUE, false) :
				setInputState(name, nts::FALSE, false);
	} else
		std::cout << "'" << tmp << "': unknown command" << std::endl;
}

void nts::Circuit::cleanCommand(std::string &tmp)
{
	std::replace(tmp.begin(), tmp.end(), '\t', ' ');
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
}

void nts::Circuit::shellCommand(std::string &tmp)
{
	if (!tmp.empty()) {
		cleanCommand(tmp);
		(_shellFunc.find(tmp) != _shellFunc.end()) ?
			(this->*_shellFunc[tmp])() : getState(tmp);
	}
}

void nts::Circuit::displayPrompt(void) const noexcept
{
	std::cout << "> ";
}

void nts::Circuit::shell(void)
{
	std::string tmp;

	simulate();
	display();
	while (_running) {
		displayPrompt();
		if (!std::getline(std::cin, tmp))
			exit();
		else
			shellCommand(tmp);
	}
}

///////////////////////////////////////////////////////////////////////////////

void nts::Circuit::unknowComponent(std::string const &name)
{
	if (_components.find(name) == _components.end())
		throw Exception(E_NAME);
}

void nts::Circuit::setLink(std::pair<std::string, std::size_t> const &link1,
				std::pair<std::string, std::size_t> const &link2)
{
	std::string name1 = link1.first;
	std::string name2 = link2.first;
	std::size_t pin1 = link1.second;
	std::size_t pin2 = link2.second;

	unknowComponent(name1);
	unknowComponent(name2);
	_components[name1].get()->setLink(pin1,	*_components[name2].get(), pin2);
	_components[name2].get()->setLink(pin2,	*_components[name1].get(), pin1);
}

void nts::Circuit::pushComponent(std::string const &type, std::string const &name)
{
	std::map<std::string, std::unique_ptr<nts::IComponent>>::iterator ite;

	if (_components.find(name) != _components.end())
		throw Exception(E_EXIST);
	_components.emplace(name, std::move(this->createC(type, name)));
}

std::unique_ptr<nts::IComponent> nts::Circuit::createC(std::string const &type,
						std::string const &name)
{
	if (_createFunc.find(type) == _createFunc.end())
		throw Exception(E_TYPE);
	return (this->*_createFunc[type])(name);
}

std::unique_ptr<nts::IComponent> nts::Circuit::createInput(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::Input(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::createOutput(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::Output(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::createTrue(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::True(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::createFalse(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::False(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::createClock(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::Clock(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4081(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4081(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4011(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4011(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4001(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4001(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4071(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4071(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4030(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4030(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4069(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4069(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4008(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4008(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4013(std::string const &name)
	const noexcept
{
	nts::IComponent *tmp = new nts::C4013(name);

	return std::unique_ptr<nts::IComponent>(tmp);
}
