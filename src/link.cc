export module Link;

import <string>;

export class Link {
	char link_char;
	std::string name;
	int strength;
	bool revealed;
	bool downloaded;
	int move_per_step;
	
	auto operator<=>(const Link &other);
};
