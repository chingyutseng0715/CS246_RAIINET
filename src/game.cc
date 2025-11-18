export module Game;

import <vector>;
import Observer;
import Link;

export class Game {
	vector<Observer*> observers;
	public:
		void notifyObservers(Link *link);
		void attach(Observer *observer);
		void detach(Observer *observer);
		virtual ~Game() = 0;
};
