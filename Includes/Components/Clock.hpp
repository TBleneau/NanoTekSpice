//
// EPITECH PROJECT, 2018
// Clock.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef CLOCK_HPP_
	#define CLOCK_HPP_

	#include <string>
	#include "IComponent.hpp"

	namespace nts {
		class Clock : public IComponent {
		public:
			Clock(std::string const &) noexcept;
			~Clock(void) noexcept;
			Tristate compute(std::size_t const & = 1);
			void setLink(std::size_t const &,
						IComponent &,
						std::size_t const &);
			void dump(void);
			std::string const &getType(void) const noexcept;
			void setTristate(nts::Tristate const &) noexcept;
			nts::Tristate const &getTristate() const noexcept;
			std::string const &getName(void) const noexcept;
		private:
			std::string _name;
			std::string _type;
			nts::Tristate _state;
			Link _link[1];
			void validPin(std::size_t const &) const;
		};
	}

#endif //CLOCK_HPP
