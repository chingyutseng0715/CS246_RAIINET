export module Observer;

export class Observer {
	public:
		virtual void download(char link_char) = 0; // the notify is used to notify the player to download the link
		virtual ~Observer();
};
