export module Player;

import <iostream>;
import <vector>;
import <string>;
import Observer;
import Board;
import Link;
import Ability;

export class Player : public Observer {
	std::string player_name;
	int downloaded_virus_amount;
    int downloaded_data_amount;
	std::vector<Ability> abilities;
	std::vector<Link> links;
	std::vector<Link*> downloaded_links;
	public:
		std::string getPlayerName();
		int getDownloadedVirusAmount();
		int getDownloadedDataAmount();
		int getAbilityAmount();
		void printAbility();
		void notify(Link *link) override;
		void usingAbility(int ability_id);
		void movingLink(char link_char, char direction);
	friend ostream &operator<<(ostream &, const Player &);
};

export ostream &operator<<(ostream &os, const Player &player);
