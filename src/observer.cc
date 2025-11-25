export module Observer;

import <string>;

export class Observer {
	protected:
		std::string name;
	public:
		virtual void download(char link_char) = 0; // the notify is used to notify the player to download the link
		virtual void addLink(char link_char) = 0;
		virtual void addAbility(char ability_char) = 0;
		virtual char removeAbility() = 0;
		std::string getName();
		explicit Observer(std::string name);
		virtual ~Observer();
};
