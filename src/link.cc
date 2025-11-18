export module Link;

import <string>;

export struct Link {
	char link_char;
	std::string type;
	std::string name;
	int strength;
	bool revealed;
	bool downloaded;
	int move_per_step;
	
	auto operator<=>(const Link &other);
};
