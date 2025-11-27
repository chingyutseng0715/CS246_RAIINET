export module Observer;

import <iostream>;
import <string>;

export class Observer {
	protected:
		std::string name;
		
	public:
		// Notifies the player's to download a link
		virtual void download(char link_char) = 0;
		virtual void addLink(char link_char) = 0;
		virtual void addAbility(char ability_char) = 0;
		virtual char removeAbility() = 0;
		virtual void printPlayer(std::ostream &os, bool hidden) = 0;
		std::string getName();
		explicit Observer(std::string name);
};
