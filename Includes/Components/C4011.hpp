//
// EPITECH PROJECT, 2018
// C4011.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4011_HPP_
	#define C4011_HPP_

	#include <map>
	#include "IComponent.hpp"

	namespace nts {
		class C4011 : public IComponent {
		public:
			C4011(std::string const &) noexcept;
			~C4011() noexcept;
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
			Link _links[14];
			std::map<std::size_t, std::pair<std::size_t, std::size_t>> _nand;
			void validPin(std::size_t const &) const;
			nts::Tristate gateNAnd(nts::Tristate const &,
						nts::Tristate const &) noexcept;
		};
	}

#endif //C4011_HPP_
