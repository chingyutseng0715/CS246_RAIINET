module Player;

import <iostream>;
import <sstream>;
import <memory>;
import <map>;
import <vector>;
import <stdexcept>;
import <string>;
import Observer;
import Board;
import Link;
import Ability;
import Download;
import Firewall; 
import LinkBoost;
import Scan;
import Polarize;

Player::Player(std::string name, Board *board, std::string abilitychosen) : Observer{name}, downloaded_virus_amount{0},
  downloaded_data_amount{0}, board{board} {
	char input = ' ';
	std::istringstream iss{abilitychosen};
	std::cout << abilitychosen;
	while (iss >> input) {
		std::cout << input << '\n';
		addAbility(input);
	}
}

int Player::getDownloadedVirusAmount() { return downloaded_virus_amount; }

int Player::getDownloadedDataAmount() { return downloaded_data_amount; }

int Player::getAbilityAmount() { return abilities.size(); }

Ability *Player::getAbility(int ability_id) { return abilities[ability_id - 1].get(); }

void Player::download(char link_char) {
	Link* link = board->getLink(link_char);
	link->Download();
	if (link->isVirus()) {
		downloaded_virus_amount += 1;
	} else if (link->isInfected()) {
		if (downloaded_virus_amount == 0) {
			for (Link *owned_link: owned_links) {
				if (!owned_link->isVirus()) {
					owned_link->setType('V');
				}
			}
		} else {
			for (Link *downloaded_link: downloaded_links) {
				if (!downloaded_link->isVirus()) {
					if (!downloaded_link->isInfected()) {
						downloaded_data_amount -= 1;
					}
					downloaded_link->setType('V');
					downloaded_virus_amount += 1;
				}
			}
		}			
	} else {
		downloaded_data_amount += 1;
	}
	downloaded_links.emplace_back(link);
}

void Player::addLink(char link_char) {
	owned_links.emplace_back(board->getLink(link_char));
}

void Player::addAbility(char ability_char) {
	if (ability_char == 'D') {
		abilities.emplace_back(std::make_shared<Download>(this, board));
	} else if (ability_char == 'F') {
        abilities.emplace_back(std::make_shared<Firewall>(this, board));
    } else if (ability_char == 'L') {
        abilities.emplace_back(std::make_shared<LinkBoost>(this, board));
    } else if (ability_char == 'S') {
        abilities.emplace_back(std::make_shared<Scan>(this, board));
    } else if (ability_char == 'P') {
        abilities.emplace_back(std::make_shared<Polarize>(this, board));
    } else {
		throw std::invalid_argument("Invalid ability symbol.");
	}
}

void Player::removeAbility(int ability_id) {
	Ability *ability = getAbility(ability_id);
	if (ability->isUsed()) {
		throw std::invalid_argument("Ability used or stolen.");
	}
	ability->markUsed();
}

void Player::usingAbility(int ability_id, std::string command) {
	getAbility(ability_id)->operatingAbility(command);
}

void Player::movingLink(std::string command) {
	std::istringstream iss{command};
	char link_char;
	std::string direction;
	if (!(iss >> link_char >> direction)) {
        throw std::invalid_argument("Invalid moving command.");
    }
	board->updateLink(link_char, direction);
}

void Player::displayAbility(std::ostream &os) {
	for (int i = 0 ; i < abilities.size(); ++i) {
		os << *getAbility(i + 1);
	}
}

void Player::printPlayerView(std::ostream &os) {
	os << name << ":\n";
	os << "Downloaded: " << downloaded_data_amount << "D, " << downloaded_virus_amount << "V\n";
	os << "Abilities: " << getAbilityAmount() << '\n';
	os << *board;
	/* incomplete */
}
