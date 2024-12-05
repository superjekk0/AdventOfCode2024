#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using Lignes = std::vector<std::string>;

enum class OrdreScan {
    droite,
    gauche,
    haut,
    bas,
    droite_haut,
    droite_bas,
    gauche_haut,
    gauche_bas,
    max
};

static void scanBas(const Lignes& donnees, Lignes& fin) {
    for (int i{ 0 }; i < donnees[0].size(); ++i) {
        std::string temp{ "" };
        for (int j{ static_cast<int>(donnees.size()) - 1 }; j >= 0; --j) {
            temp += donnees[j][i];
        }
        fin.push_back(temp);
    }
}
static void scanHaut(const Lignes& donnees, Lignes& fin) {
    for (int i{ 0 }; i < donnees[0].size(); ++i) {
        std::string temp{ "" };
        for (int j{ 0 }; j < donnees.size(); ++j) {
            temp += donnees[j][i];
        }
        fin.push_back(temp);
    }
}
static void scanGauche(const Lignes& donnees, Lignes& fin) {
    for (auto& donnee : donnees) {
        fin.push_back(donnee);
    }
}
static void scanDroite(const Lignes& donnees, Lignes& fin) {
    for (auto& donnee : donnees) {
        std::string temp{ "" };
        for (int i{ static_cast<int>(donnee.size()) - 1 }; i >= 0; --i) {
            temp += donnee[i];
        }
        fin.push_back(temp);
    }
}
static void scanHautDroite(const Lignes& donnees, Lignes& fin) {
    // On s'arrête verticalement à l'avant-dernière ittération
    for (int i{ 0 }; i < donnees.size() - 1; ++i) {
        std::string temp{ "" };
        for (int indexVertical{ i }, indexHorizontal{ 0 };
            indexHorizontal < donnees[0].size() && indexVertical >= 0;
            ++indexHorizontal, --indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }

    // On regarde sur l'autre axe
    for (int i{ 0 }; i < donnees[0].size(); ++i) {
        std::string temp{ "" };
        for (int indexVertical{static_cast<int>(donnees.size()) - 1}, indexHorizontal{0};
            indexHorizontal < donnees[0].size() && indexVertical >= 0;
            ++indexHorizontal, --indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }
}
static void scanHautGauche(const Lignes& donnees, Lignes& fin) {
    // On s'arrête verticalement à l'avant-dernière ittération
    for (int i{ 0 }; i < donnees.size() - 1; ++i) {
        std::string temp{ "" };
        for (int indexVertical{ i }, indexHorizontal{ static_cast<int>(donnees[0].size()) - 1};
            indexHorizontal >= 0 && indexVertical >= 0;
            --indexHorizontal, --indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }

    // On regarde sur l'autre axe
    for (int i{ static_cast<int>(donnees[0].size()) - 1}; i >= 0; --i) {
        std::string temp{ "" };
        for (int indexVertical{ static_cast<int>(donnees.size()) - 1 }, indexHorizontal{ 0 };
            indexHorizontal < donnees[0].size() && indexVertical >= 0;
            --indexHorizontal, --indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }
}
static void scanBasDroite(const Lignes& donnees, Lignes& fin) {
    for (int i{ static_cast<int>(donnees.size()) - 1 }; i > 0; --i) {
        std::string temp{ "" };
        for (int indexHorizontal{ 0 }, indexVertical{ i };
            indexHorizontal < donnees[0].size() && indexVertical > donnees.size();
            ++indexHorizontal, ++indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }

    for (int i{ 0 }; i < donnees[0].size(); ++i) {
        std::string temp{ "" };
        for (int indexHorizontal{ i }, indexVertical{ 0 };
            indexHorizontal < donnees[0].size() && indexVertical > donnees.size();
            ++indexHorizontal, ++indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }
}
static void scanBasGauche(const Lignes& donnees, Lignes& fin) {
    for (int i{ static_cast<int>(donnees.size()) - 1 }; i > 0; --i) {
        std::string temp{ "" };
        for (int indexHorizontal{ static_cast<int>(donnees[0].size()) - 1}, indexVertical{i};
            indexHorizontal >= 0 && indexVertical > donnees.size();
            --indexHorizontal, ++indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }

    for (int i{ static_cast<int>(donnees[0].size()) - 1}; i >= 0; --i) {
        std::string temp{ "" };
        for (int indexHorizontal{ i }, indexVertical{ 0 };
            indexHorizontal >= 0 && indexVertical > donnees.size();
            --indexHorizontal, ++indexVertical) {
            temp += donnees[indexVertical][indexHorizontal];
        }
        fin.push_back(temp);
    }
}

static Lignes lignesScannees(const Lignes& donnees) {
    Lignes fin{};
    for (int i{ 0 }; i < static_cast<int>(OrdreScan::max); ++i) {
        switch (static_cast<OrdreScan>(i))
        {
        case OrdreScan::bas:
            scanBas(donnees, fin);
            break;
        case OrdreScan::haut:
            scanHaut(donnees, fin);
            break;
        case OrdreScan::droite:
            scanDroite(donnees, fin);
            break;
        case OrdreScan::gauche:
            scanGauche(donnees, fin);
            break;
        case OrdreScan::droite_bas:
            scanBasDroite(donnees, fin);
            break;
        case OrdreScan::droite_haut:
            scanHautDroite(donnees, fin);
            break;
        case OrdreScan::gauche_bas:
            scanBasGauche(donnees, fin);
            break;
        case OrdreScan::gauche_haut:
            scanHautDroite(donnees, fin);
            break;
        default:
            break;
        }
    }

    return fin;
}

int main()
{
    Lignes donnees{
        "MMMSXXMASM",
"MSAMXMSMSA",
"AMXSXMAAMM",
"MSAMASMSMX",
"XMASAMXAMM",
"XXAMMXXAMA",
"SMSMSASXSS",
"SAXAMASAAA",
"MAMMMXMMMM",
"MXMXAXMASX"
    };

    Lignes lignesApresScan{ lignesScannees(donnees) };

    long long nbOccurences1{ 0ll };

    for (auto& ligne : lignesApresScan) {
        for (int i{ static_cast<int>(ligne.find("XMAS", 0)) }; i != ligne.npos; i = ligne.find("XMAS", i + 1)) {
            ++nbOccurences1;
        }
    }

    std::cout << nbOccurences1 << '\n';

    std::cout << "Hello World!\n";
}