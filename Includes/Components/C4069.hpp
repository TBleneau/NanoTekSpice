//
// EPITECH PROJECT, 2018
// C4069.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4069_HPP_
	#define C4069_HPP_

	#include <map>
	#include "IComponent.hpp"

	namespace nts {
		class C4069 : public IComponent {
		public:
			C4069(std::string const &) noexcept;
			~C4069() noexcept;
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
			std::map<std::size_t, std::size_t> _not;
			void validPin(std::size_t const &) const;
			nts::Tristate gateNot(nts::Tristate const &) noexcept;
		};
	}

#endif //C4069_HPP_
