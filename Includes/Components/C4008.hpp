//
// EPITECH PROJECT, 2018
// C4008.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4008_HPP_
	#define C4008_HPP_

	#include <map>
	#include <vector>
	#include "IComponent.hpp"

	namespace nts {
		class C4008 : public IComponent {
		public:
			C4008(std::string const &) noexcept;
			~C4008() noexcept;
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
			std::map<std::size_t, std::pair<std::size_t, std::size_t>> _adder;
			std::map<std::size_t, nts::Tristate> _out;
			std::vector<nts::Tristate> _carryOUT;
			void validPin(std::size_t const &) const;
			void firstSum();
			void secondSum();
			void thirdSum();
			void fourthSum();
			nts::Tristate gateXor(nts::Tristate const &state1,
					nts::Tristate const &state2) noexcept;
			nts::Tristate gateOr(nts::Tristate const &state1,
					nts::Tristate const &state2) noexcept;
			nts::Tristate gateAnd(nts::Tristate const &state1,
					nts::Tristate const &state2) noexcept;
		};
	}

#endif //C4008_HPP_
