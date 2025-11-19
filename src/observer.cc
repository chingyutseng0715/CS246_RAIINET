export module Observer;

import Link;

export class Observer {
	public:
		virtual void download(Link *link) = 0; // the notify is used to notify the player to download the link
		virtual ~Observer();
};
