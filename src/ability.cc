export module Ability;

import <string>;

export class Ability {
	protected:
		std::string name;
		std::string description; 	
	public:
		virtual void operatingAbility() = 0;
	friend ostream &operator<<(ostream &os, const Ability &);
};

export ostream &operator<<(ostream &os, const Ability &ability);
