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
	Board* board;
	std::vector<Ability> abilities;
	std::vector<Link> owned_links;
	std::vector<Link*> downloaded_links;
	public:
		int getDownloadedVirusAmount();
		int getDownloadedDataAmount();
		int getAbilityAmount();
		std::vector<Ability> &getAbility();
		void download(Link *link) override;
		void usingAbility(int ability_id);
		void movingLink(char link_char, char direction);
	friend ostream &operator<<(ostream &, const Player &);
};

export ostream &operator<<(ostream &os, const Player &player);
