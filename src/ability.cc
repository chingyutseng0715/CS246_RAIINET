export module Ability;

import <string>;
import Observer;
import Board;

export class Ability {
    protected:
        std::string name;
        std::string description;
        bool used;
        Observer *player;
        Board *board;
    public:
        Ability(std::string name, std::string description, Observer *owner, Board *board);
        bool isUsed();
		void markUsed();
        virtual ~Ability();
        virtual void operatingAbility(std::string command) = 0;
    friend std::ostream &operator<<(std::ostream &os, const Ability &);
};

export std::ostream &operator<<(std::ostream &os, const Ability &ability);
