#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include "Satellite.hpp"
#include "Collection.hpp"
#include "Simulation.hpp"
#include "Parsing.hpp"

void parseInput(const char* input_file) {

	int cptSatellites; // compteur d�croissant de satellites

	std::ifstream input(input_file); // on cr�e un buffer de stream

	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}

	std::string line; // ligne actuelle
	ReadState t = ReadState::NumberOfTurns; // �tat de l'automate de lecture

	Simulation simulation;

	while (std::getline(input, line))
	{
		int cpt = 0; // compteur d'�l�ment dans une ligne
		std::istringstream iss(line); // buffer de string

		std::string result;
		std::string result2;

		if (std::getline(iss, result, '\n'))
		{

			std::istringstream iss2(result); // deuxi�me buffer pour parser a l'int�rieur des lignes
			//std::cout << "in : " << result << std::endl;

			switch (t) {

				case ReadState::NumberOfTurns:
					std::cout << " nombre de tours : " << result << std::endl;
					simulation.setDuration(std::stoi(result));
					t = ReadState::SatellitesNumber;
					break;

				case ReadState::SatellitesNumber:
					std::cout << " nombre de satellites : " << result << std::endl;
					cptSatellites = std::stoi(result);
					simulation.setSatellitesNumber(cptSatellites);
					t = ReadState::Satellites;
					break;

				case ReadState::Satellites:
				{
					SatelliteLine satelliteLine;
					std::cout << cptSatellites << std::endl;

					// lecture de la ligne � d�couper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						satelliteLine.at(cpt) = result2;
						// on passe a l'arg suivant de la ligne
						cpt++;
					}

					Satellite* s = new Satellite(&simulation, satelliteLine);
					// on ajoute le satellite a la simulation
					simulation.addSatellite(s);

					std::cout << *s << std::endl;
					cptSatellites--; // next

					if (cptSatellites == 0) { // une fois qu'on a ajout� tous les satellites
						t = ReadState::Test; // TODO use real state
					}
				}
					break;

				case ReadState::Collection:
					std::cout << result << std::endl;
					cpt = std::stoi(result);
					break;

				case ReadState::Photograph:
					break;

				case ReadState::TimeRange:
					break;

				case ReadState::Test:
					std::cout << "lala" << std::endl;
					return;
					break;
				}
		}
	}

	input.close();
}
