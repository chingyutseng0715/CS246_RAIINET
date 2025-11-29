export module Observer;

import <iostream>;
import <string>;

export class Observer {
	protected:
		std::string name;
		
	public:
		// download(link_char) Pure Virtual function (description in subclass)
		virtual void download(char link_char) = 0;

		// addLink(link_char) Pure Virtual function (description in subclass)
		virtual void addLink(char link_char) = 0;

		// addAbility(ability_char) Pure Virtual function (description in subclass)
		virtual void addAbility(char ability_char) = 0;

		// removeAbility() Pure Virtual function (description in subclass)
		virtual char removeAbility() = 0;

		// printPlayer(os, hidden)  Pure Virtual function (description in subclass)
		virtual void printPlayer(std::ostream &os, bool hidden) = 0;

		// getName() return the Observer's name
		std::string getName();

		// Basic Constructor
		explicit Observer(std::string name);
};
