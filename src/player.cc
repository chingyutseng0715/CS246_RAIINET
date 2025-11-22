export module Player;

import <iostream>;
import <map>;
import <vector>;
import <string>;
import Observer;
import Board;
import Link;
import Ability;

export class Player : public Observer {
	int downloaded_virus_amount;
    int downloaded_data_amount;
	Board* board;
	std::map<int, Ability> abilities;
	std::vector<Link*> owned_links;
	std::vector<Link*> downloaded_links;
	public:
		Player(std::string name, Board *board, std::string abilitychosen);
		int getDownloadedVirusAmount();
		int getDownloadedDataAmount();
		int getAbilityAmount();
		std::vector<Ability> &getAbility();
		void download(char link_char) override;
		void usingAbility(int ability_id, std::string command);
		void movingLink(char link_char, char direction);
	friend std::ostream &operator<<(std::ostream &, const Player &);
};

export std::ostream &operator<<(std::ostream &os, const Player &player);
