 //
// EPITECH PROJECT, 2018
// Output.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef OUTPUT_HPP_
	#define OUTPUT_HPP_

	#include <string>
	#include "IComponent.hpp"

	namespace nts {
		class Output : public IComponent {
		public:
			Output(std::string const &) noexcept;
			~Output(void) noexcept;
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
			void validLink(std::size_t const &) const;
		};
	}

#endif //OUTPUT_HPP
