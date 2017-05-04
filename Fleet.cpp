// G52CPP Coursework.cpp

#include "stdafx.h"
#include "Fleet.h"

using namespace std;

int main()
{

	int gameAnswer = 1;
	while (gameAnswer != 2) {

		vector<Fleet *> fleetList;
		int createAnswer = 1;
		cout << "Welcome to the race to conquer Gaia! " << endl
			<< "Please compose a fleet " << endl << endl;

		ofstream theFile;
		theFile.open("023493-fleet.dat");

		string tempShipName;
		int count = 0;
		// Compose a fleet
		while (createAnswer != 2) {
			Fleet *theFleet = Fleet::userInterfaceCreateFleet();

			// Debugging - Output the fleet that is constructed
			vector<Ship *> theShips = theFleet->shipList();

			cout << "Your fleet: " << endl;
			cout << "Corporation Name: " << theFleet->getCorporationName() << endl << endl;

			cout << "Ships in fleet: " << endl;

			theFile << theFleet->getCorporationName() << endl;

			tempShipName = theShips[0]->getTypeName();

			for (int x = 0; x < theShips.size(); x++) {
				cout << theShips[x]->getTypeName() << " ship " << endl;

				if (theShips[x]->getTypeName() == tempShipName) {
					count++;
					if (x == (theShips.size() - 1)) {
						theFile << tempShipName << " " << count << endl;
						count = 0;
					}
				}
				else {
					theFile << tempShipName << " " << count << endl;
					tempShipName = theShips[x]->getTypeName();
					count = 1;
				}
			}

			

			cout << "Fleet weight: " << theFleet->getWeight() << endl;
			cout << "Colonist count: " << theFleet->getColonistCount() << endl;
			cout << "Total cost: " << theFleet->getCost() << endl;

			cout << endl << endl;

			// Enter the fleet into a vector of fleets for the race 
				fleetList.push_back(theFleet);

			cout << "Would you like to create another fleet?: Press 1 for Yes or 2 for No: ";
			cin >> createAnswer;
		}

		theFile.close();

		// Sort the vector of fleet based on fleet speed
		sort(fleetList.begin(), fleetList.end(), sortFleetSpeed);

		// Debugging - Output contents of vector

		cout << "Fleets that will be racing to Gaia: " << endl;
		for (int a = 0; a < fleetList.size(); a++) {
			cout << fleetList[a]->getCorporationName() << " Corporation"<< endl;
		}

		// Begin the race for all fleets
		cout << endl << endl << "Let the race to conquer Gaia begin!" << endl << endl;
		vector<thread> fleetThreadList;

		for (int y = 0; y < fleetList.size(); y++) {
			fleetThreadList.push_back(thread(startRace, fleetList[y]));
		}

		// Begin the race
		for (int z = 0; z < fleetThreadList.size(); z++) {
			fleetThreadList[z].join();
		}

		planetEmpty = true;
		colonizerPopulation = 0;
		fleetList.clear();
		cout << "The winner is Corporation " << colonizer << endl << endl;
		cout << "Would you like to play the game again? Press 1 for Yes or 2 for No: ";
		cin >> gameAnswer;
		
	}
    return 0;
}

