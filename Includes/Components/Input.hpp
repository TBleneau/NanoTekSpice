//
// EPITECH PROJECT, 2018
// Input.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef INPUT_HPP_
	#define INPUT_HPP_

	#include <string>
	#include "IComponent.hpp"

	namespace nts {
		class Input : public IComponent {
		public:
			Input(std::string const &) noexcept;
			~Input(void) noexcept;
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

#endif //INPUT_HPP
