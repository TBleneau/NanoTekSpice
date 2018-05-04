//
// EPITECH PROJECT, 2018
// C4040.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4040_HPP_
	#define C4040_HPP_

	#include <map>
	#include <vector>
	#include "IComponent.hpp"

	namespace nts {
		class C4040 : public IComponent {
		public:
			C4040(std::string const &) noexcept;
			~C4040() noexcept;
			Tristate compute(std::size_t const & = 1);
			void setLink(std::size_t const &, IComponent &,
					std::size_t const &);
			void dump(void);
			std::string const &getType(void) const noexcept;
			std::string const &getName(void) const noexcept;
			void setTristate(nts::Tristate const &)
				noexcept;
			nts::Tristate const &getTristate() const noexcept;
		private:
			std::string _name;
			std::string _type;
			nts::Tristate _state;
			Link _links[16];
			std::map<std::size_t, std::pair<std::size_t, std::size_t>> _counter;
			void validPin(std::size_t const &) const;
		};
	}

#endif //C4040_HPP_
