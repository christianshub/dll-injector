#include "ConfigParser.h"

unsigned int ParseDelay(std::string& delay)
{
    // Remove spaces
    ReplaceAllSubStr(delay, " ", "");

    if (delay == "")
    {
        return 0;
    }

    // Check for non-numerics
    if (delay.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Delay can only contain numbers: 0123456789" << std::endl;
        std::exit(1);
    }

    return std::stoi(delay);
}

std::vector<std::string> ParseFileNames(std::string& names)
{
    std::vector<std::string> container = {};

    if (names == "") 
    {
        return container;
    }
    // Remove spaces
    ReplaceAllSubStr(names, " ", "");

    // Insert signatures into container
    std::stringstream ss(names);
    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, ',');
        container.push_back(substr);
    }

    return container;
}