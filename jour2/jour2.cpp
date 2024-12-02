#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

class Resultat {
    std::vector<int> _serie{};
public:
    Resultat(const std::string& ligne) {
        std::size_t index{};
        while (index != ligne.npos)
        {
            _serie.push_back(std::stoi(ligne.substr(index, ligne.find_first_of(' ', index + 1))));
            index = ligne.find_first_of(' ', index + 1);
        }
    }

    bool valid() const {

    }
};

int main()
{
    std::vector<std::string> data{ "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1", "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9"};
    std::vector<Resultat> resultat{};

    for (auto& element : data) {
        resultat.push_back(element);
    }

    return 0;
}
