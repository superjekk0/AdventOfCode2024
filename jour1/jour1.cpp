#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<std::string> lireFichier() {
    std::fstream fichier{ "input.txt" };
    std::vector<std::string> resultat{};

    std::string temp;

    while (! fichier.eof())
    {
        std::getline(fichier, temp);
        resultat.push_back(temp);
    }

    return resultat;
}

int main()
{
    //auto liste = std::vector<std::string>{"3   4","4   3",
    //"2   5",
    //"1   3",
    //"3   9",
    //"3   3"};

    auto liste{ lireFichier() };

    std::vector<long> listeDroite{};
    std::vector<long> listeGauche{};

    for (auto& ligne : liste) {
        listeDroite.push_back(std::stol(ligne.substr(0, ligne.find_first_of(' '))));
        listeGauche.push_back(std::stol(ligne.substr(ligne.find_last_of(' ') + 1)));
    }

    std::sort(listeDroite.begin(), listeDroite.end());
    std::sort(listeGauche.begin(), listeGauche.end());

    long differenceTotale{ 0l };

    for (std::size_t i{ 0 }; i < listeDroite.size() && i < listeGauche.size(); ++i) {
        differenceTotale += std::abs(listeDroite[i] - listeGauche[i]);
    }

    std::cout << differenceTotale << '\n';

    long cummulatif{ 0l };

    for (auto elementGauche : listeGauche) {
        long nombreOccurence{static_cast<long>( std::count(listeDroite.begin(),
            listeDroite.end(), elementGauche))
        };

        cummulatif += elementGauche * nombreOccurence;
    }

    std::cout << cummulatif << '\n';

    return 0;
}
