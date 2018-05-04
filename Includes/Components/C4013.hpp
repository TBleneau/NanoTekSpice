//
// EPITECH PROJECT, 2018
// C4013.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4013_HPP_
	#define C4013_HPP_

	#include <map>
	#include <vector>
	#include "IComponent.hpp"

	namespace nts {
		class C4013 : public IComponent {
		public:
			C4013(std::string const &) noexcept;
			~C4013() noexcept;
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
			std::map<std::size_t, nts::Tristate> _dualOut;
			void validPin(std::size_t const &) const;
			nts::Tristate firstFlop(std::size_t const &);
			nts::Tristate secondFlop(std::size_t const &);
			void computeFlipFlop(std::size_t const &);
		};
	}

#endif //C4013_HPP_
