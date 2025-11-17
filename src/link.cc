export module Link;

export struct Link {
    int getStrength();
    std::string getName();
    std::string getType();
    void setStrength(int strength);
    void setType(std::string type);
    auto operator<=>(const Link &other);
};
