//
// EPITECH PROJECT, 2018
// C4001.hpp
// File description:
// Created by Thomas BLENEAU
//

#ifndef C4001_HPP_
	#define C4001_HPP_

	#include <map>
	#include "IComponent.hpp"

	namespace nts {
		class C4001 : public IComponent {
		public:
			C4001(std::string const &) noexcept;
			~C4001() noexcept;
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
			std::map<std::size_t, std::pair<std::size_t, std::size_t>> _nor;
			void validPin(std::size_t const &) const;
			nts::Tristate gateNor(nts::Tristate const &,
						nts::Tristate const &) noexcept;
		};
	}

#endif //C4001_HPP_
