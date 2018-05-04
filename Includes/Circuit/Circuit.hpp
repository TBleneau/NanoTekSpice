//
// EPITECH PROJECT, 2018
// Circuit.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef CIRCUIT_HPP_
	#define CIRCUIT_HPP_

	#include <iostream>
	#include <cstddef>
	#include <string>
	#include <vector>
	#include <map>
	#include <memory>
	#include "IComponent.hpp"
	#include "Exception.hpp"

	namespace nts {
		class Circuit;
	}
	using creatorPtr = std::unique_ptr<nts::IComponent>(nts::Circuit::*)(const std::string &value)
			const noexcept;
	using shellPtr = void (nts::Circuit::*)(void);

	namespace nts {
		class Circuit : public IComponent {
		public:
			Circuit(void) noexcept;
			~Circuit(void) noexcept;
			void initCircuit(void);
			void initShell(void);
			Tristate compute(std::size_t const & = 1);
			void setLink(std::size_t const &, IComponent &,
					std::size_t const &);
			void setLink(std::pair<std::string, std::size_t> const &,
					std::pair<std::string, std::size_t> const &);
			void dump(void);
			std::string const &getType(void) const noexcept;
			void setTristate(nts::Tristate const &) noexcept;
			nts::Tristate const &getTristate() const noexcept;
			void setInputState(std::string const &, nts::Tristate const &, bool);
			void pushComponent(std::string const &, std::string const &);
			void shell(void);
		private:
			std::string _type;
			nts::Tristate _state;
			std::map<std::string, creatorPtr> _createFunc;
			std::map<std::string, shellPtr> _shellFunc;
			std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
			bool _running;
			static void quit(int);
			static bool _quit;
			void unknowComponent(std::string const &);
			void loop(void);
			void display(void);
			void simulate(void);
			void exit(void);
			void displayPrompt(void) const noexcept;
			void shellCommand(std::string &);
			void cleanCommand(std::string &);
			void getState(std::string &);
			void changeState(std::string const &) noexcept;
			std::unique_ptr<nts::IComponent> createC(std::string const &, std::string const &);
			std::unique_ptr<nts::IComponent> createInput(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> createOutput(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> createTrue(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> createFalse(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> createClock(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4081(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4011(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4001(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4071(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4030(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4069(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4008(std::string const &)
				const noexcept;
			std::unique_ptr<nts::IComponent> create4013(std::string const &)
				const noexcept;
		};
	}

#endif // !CIRCUIT_HPP_
