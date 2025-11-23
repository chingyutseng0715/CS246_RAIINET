export module Player;

import <iostream>;
import <memory>;
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
	std::vector<std::shared_ptr<Ability>> abilities;
	std::vector<Link*> downloaded_links;
	public:
		Player(std::string name, Board *board, std::string abilitychosen);
		int getDownloadedVirusAmount();
		int getDownloadedDataAmount();
		int getAbilityAmount();
		Ability *getAbility(int ability_id);
		void download(char link_char) override;
		void addAbility(char ability_char) override;
		void removeAbility(int ability_id) override;
		void usingAbility(int ability_id, std::string command);
		void movingLink(std::string command);
		void displayAbility(std::ostream &os);
		void printPlayerView(std::ostream &os);
};
