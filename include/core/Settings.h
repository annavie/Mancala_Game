#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>

class Settings {
public:
    std::vector<std::string> playerNames;
    Settings() : playerNames({"Player 1", "Player 2"}) {}
};

#endif // SETTINGS_H
