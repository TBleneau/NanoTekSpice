//
// EPITECH PROJECT, 2018
// IComponent.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef ICOMPONENT_HPP_
	#define ICOMPONENT_HPP_

	#include <string>
	#include <cstddef>

	namespace nts
	{
		enum Tristate {
			UNDEFINED = (-true),
			TRUE = true,
			FALSE = false
		};
		class IComponent {
		public:
			virtual ~IComponent(void) = default;
			virtual Tristate compute(std::size_t const & = 1) = 0;
			virtual void setLink(std::size_t const &, IComponent &,
						std::size_t const &) = 0;
			virtual void dump(void) = 0;
			virtual std::string const &getType(void)
				const noexcept = 0;
			virtual void setTristate(nts::Tristate const &)
				noexcept = 0;
			virtual nts::Tristate const &getTristate()
				const noexcept = 0;
		};
		class Link {
		public:
			Link(std::size_t pin = 1,
			     nts::IComponent *component = nullptr) noexcept
				{ _pin = pin; _component = component; }
			~Link(void) noexcept = default;
			std::size_t _pin;
			nts::IComponent *_component;
		};
	}

#endif // !ICOMPONENT_HPP_
