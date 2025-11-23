export module Observer;

import <string>;

export class Observer {
	protected:
		std::string name;
	public:
		virtual void download(char link_char) = 0; // the notify is used to notify the player to download the link
		std::string getName();
		explicit Observer(std::string name);
		virtual ~Observer();
};
