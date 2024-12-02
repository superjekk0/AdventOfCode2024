#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

class Resultat {
	std::vector<int> _serie{};

	const int max{ 3 };
	const int min{ 1 };

	bool validArray(const std::vector<int>& integerArray) const {
		int step{ integerArray[0] - integerArray[1] };
		bool negatif{ step < 0 };

		for (int i{ 0 }; i < integerArray.size() - 1; ++i) {
			if ((integerArray[i] - integerArray[i + 1] < 0) != negatif) {
				return false;
			}
		}

		for (int i{ 0 }; i < integerArray.size() - 1; ++i) {
			int difference{ integerArray[i] - integerArray[i + 1] };
			if (std::abs(difference) > max || std::abs(difference) < min) {
				return false;
			}
		}

		return true;
	}

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
		return validArray(_serie);
	}

	bool validV2() const {
		if (valid()) {
			return true;
		}

		for (int i{ 0 }; i < _serie.size(); ++i) {
			auto copie = _serie;
			copie.erase(copie.begin() + i);
			if (validArray(copie)) {
				return true;
			}
		}
		return false;
	}
};

static std::vector<std::string> lireFichier() {
	std::fstream fichier{ "input.txt" };
	std::vector<std::string> resultat{};

	std::string temp;

	while (!fichier.eof())
	{
		std::getline(fichier, temp);
		resultat.push_back(temp);
	}

	return resultat;
}

int main()
{
	std::vector<std::string> data{lireFichier()}; //{ "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1", "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9"};
	std::vector<Resultat> resultat{};

	for (auto& element : data) {
		resultat.push_back(element);
	}

	std::cout << std::count_if(resultat.begin(), resultat.end(), [](Resultat& element) {
		return element.valid();
		}) << '\n';

	std::cout << std::count_if(resultat.begin(), resultat.end(), [](Resultat& element) {
		return element.validV2();
		}) << '\n';

	return 0;
}
