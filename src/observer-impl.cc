module Observer;

import <string>;

std::string Observer::getName() { return name; }

Observer::Observer(std::string name) : name{name} {}

Observer::~Observer() {}
