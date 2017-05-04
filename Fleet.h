#pragma once

#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <ctime>
#include <fstream>

#define SPEED_OF_LIGHT (2.998 * pow (10,8))
#define ALPHA 10
#define DISTANCE_TO_GAIA ((3.122 * pow (10, 17)) / (9.461 * pow (10, 15))) // Number of lightyears to gaia = 33 lightyears

using namespace std;

static bool planetEmpty = true;
static string colonizer;
static int colonizerPopulation = 0;
mutex theLock;
mutex secondLock;

class Ship
{
public:

	Ship() {
	
	};

	Ship(string shipName, int energyConsumed, int theCost, int theWeight) {
		name = shipName;
		energyConsumption = energyConsumed;
		cost = theCost;
		weight = theWeight;
	};

	~Ship() {

	};

	// Returns energy  consumption of a ship   
	int getEnergyConsumption() const {
		return energyConsumption;
	}

	// Returns weight of  a ship   
	int getWeight() const {
		return weight;
	}

	// Returns cost of a  ship   
	int getCost() const {
		return cost;
	}

	// Returns the ship  type, e.g. Ferry, Cruiser, or Ebulient. 
	string getTypeName() const {
		return name;
	}

	// Returns true if  the ship is destroyed, false otherwise   
	bool isDestroyed() const {
		return true;
	}


protected:

	string name;
	int cost, weight, energyConsumption;
};

class ColonyShip : public Ship {
	public:

		// Creating the appropriate fleet
		ColonyShip(int num) {
			if (num == 1) { // Ferry
				name = "Ferry";
				colonistNum = 100;
				cost = 500;
				weight = 10;
				energyConsumption = 5;		
			}
			else if (num == 2) { //Liner
				name = "Liner";
				colonistNum = 250;
				cost = 1000;
				weight = 20;
				energyConsumption = 7;
			}
			else { //Cloud
				name = "Cloud";
				colonistNum = 750;
				cost = 2000;
				weight = 30;
				energyConsumption = 9;
			}
		};

		ColonyShip(string theName) {
			if (theName == "Ferry") { // Ferry
				name = "Ferry";
				colonistNum = 100;
				cost = 500;
				weight = 10;
				energyConsumption = 5;
			}
			else if (theName == "Liner") { //Liner
				name = "Liner";
				colonistNum = 250;
				cost = 1000;
				weight = 20;
				energyConsumption = 7;
			}
			else { //Cloud
				name = "Cloud";
				colonistNum = 750;
				cost = 2000;
				weight = 30;
				energyConsumption = 9;
			}
		};

		// Returns nr of  colonists of a ship
		int getColonistCount() const {
			return colonistNum;
		}

		// Infects a colony  ship   
		void infect() {			
			colonistNum = 0;
		}

		// Returns True if  the ship is infected with a disease, False otherwise 
		bool isInfected() const {
			if (colonistNum == 0) {
				return true;
			}
			else {
				return false;
			}
		}


	private:

		int colonistNum;
		
};

class SolarSailShip : public Ship {
	public:

		// Creating the appropriate solar sail ship
		SolarSailShip(int num) {
			if (num == 1) {
				name = "Radiant";
				energyProduction = 50;
				cost = 50;
				weight = 3;
				energyConsumption = 5;
			}
			else {
				name = "Ebulient";
				energyProduction = 500;
				cost = 250;
				weight = 50;
				energyConsumption = 5;
			}
		};

		SolarSailShip(string theName) {
			if (theName == "Radiant") {
				name = "Radiant";
				energyProduction = 50;
				cost = 50;
				weight = 3;
				energyConsumption = 5;
			}
			else {
				name = "Ebulient";
				energyProduction = 500;
				cost = 250;
				weight = 50;
				energyConsumption = 5;
			}
		};

		// Returns energy  production of Solar Sail Ship   
		int getEnergyProduction () const {
			return energyProduction;
		}

	private:

		int energyProduction;
};

class MilitaryEscortShip : public Ship {
public:

	// Creating the appropriate military ship
	MilitaryEscortShip(string theName) {
		if (theName == "Cruiser") { //Cruiser
			name = "Cruiser";
			cost = 300;
			weight = 2;
			energyConsumption = 10;
			nrProtected = 1;
		} 
		else if (theName == "Frigate") { //Frigate
			name = "Frigate";
			cost = 1000;
			weight = 7;
			energyConsumption = 20;
			nrProtected = 6; 
		}
		else { //Destroyer
			name = "Destroyer";
			cost = 2000;
			weight = 19;
			energyConsumption = 30;
			nrProtected = 12;
		}
	};

	MilitaryEscortShip(int num) {
		if (num == 1) { //Cruiser
			name = "Cruiser";
			cost = 300;
			weight = 2;
			energyConsumption = 10;
			nrProtected = 1;
		}
		else if (num == 2) { //Frigate
			name = "Frigate";
			cost = 1000;
			weight = 7;
			energyConsumption = 20;
			nrProtected = 6;
		}
		else { //Destroyer
			name = "Destroyer";
			cost = 2000;
			weight = 19;
			energyConsumption = 30;
			nrProtected = 12;
		}
	};

	// Returns nr  of colony ships protected by this ship  
	int getNrProtected () const{
		return nrProtected;
	}
private:

	int nrProtected;
};

class Fleet
{
public:

	Fleet() {

	};

	Fleet(string corpName) {
		corporationName = corpName;
	};

	// Returns cumulative  weight of fleet   
	int getWeight() const {
		int totalWeight = 0;
		for (int x = 0; x < theShips.size(); x++) {
			totalWeight += theShips[x]->getWeight();
		}

		return totalWeight;
	}

	// Returns cumulative  energy consumption of fleet  
	int getEnergyConsumption() const {
		int totalEnergyConsumed = 0;
		for (int x = 0; x < theShips.size(); x++) {
			totalEnergyConsumed += theShips[x]->getEnergyConsumption();
		}

		return totalEnergyConsumed;
	}

	// Returns cumulative colonist count of fleet 
	int getColonistCount() const {
		int totalColonistCount = 0;
		for (int x = 0; x < theShips.size(); x++) {
			if (theShips[x]->getTypeName() == "Ferry" || theShips[x]->getTypeName() == "Liner" || theShips[x]->getTypeName() == "Cloud") {
				ColonyShip* theColonyShip = (ColonyShip *)theShips[x];
				totalColonistCount += theColonyShip->getColonistCount();
			}
		}

		return totalColonistCount;
	}

	// Returns cumulative fleet cost
	int getCost() const {
		int totalCost = 0;
		for (int x = 0; x < theShips.size(); x++) {
			totalCost += theShips[x]->getCost();
		}

		return totalCost;
	}

	// Returns cumulative energy production of fleet
	int EnergyProduction() const {
		int totalEnergyProduced = 0;
		for (int x = 0; x < theShips.size(); x++) {

			if (theShips[x]->getTypeName() == "Radiant" || theShips[x]->getTypeName() == "Ebulient") {
				SolarSailShip* solarShip = (SolarSailShip *)theShips[x];
				totalEnergyProduced += solarShip->getEnergyProduction();
			}
		}

		return totalEnergyProduced;
	}

	// Returns nr of colony ships protected in fleet    
	int countProtectedShips() const {
		int totalShipsProtected = 0;
		for (int x = 0; x < theShips.size(); x++) {
			if (theShips[x]->getTypeName() == "Cruiser" || theShips[x]->getTypeName() == "Frigate" || theShips[x]->getTypeName() == "Destroyer") {
				MilitaryEscortShip* militaryShip = (MilitaryEscortShip *)theShips[x];
				totalShipsProtected += militaryShip->getNrProtected();
			}
		}

		return totalShipsProtected;
	}

	// Returns True if the fleet has a medic ship, false otherwise
	bool hasMedic() const {
		for (int x = 0; x < theShips.size(); x++) {
			if (theShips[x]->getTypeName() == "Medic") {
				return true;
			}
		}
		return false;
	}

	// Returns your  chosen name of your corporation.
	string getCorporationName() const {
		return corporationName;
	}

	// Returns a vector  with ship numbers of protected colony ships 
	vector<Ship *> protectedShips() const {
		vector<Ship *> protectedColonyShips;
		vector<Ship *> colonyShipList = colonyShips();
		for (int x = 0; x < countProtectedShips(); x++) {
			protectedColonyShips.push_back(colonyShipList[x]);
		}

		return protectedColonyShips;
	}

	// Returns a vector  with ship numbers of unprotected colony ships 
	vector<Ship *> unprotectedShips() const {
		vector<Ship *> unprotectedColonyShips;
		vector<Ship *> colonyShipList = colonyShips();
		for (int x = this->countProtectedShips(); x < colonyShipList.size(); x++) {
			unprotectedColonyShips.push_back(colonyShipList[x]);
		}

		return unprotectedColonyShips;
	}

	// Returns a vector with ship numbers of all ships that are a colony ship 
	vector<Ship *> colonyShips() const {
		vector<Ship *> theColonyShips;
		for (int x = 0; x < theShips.size(); x++) {
			if (theShips[x]->getTypeName() == "Cloud") {
				theColonyShips.push_back(theShips[x]);
			}
			else if (theShips[x]->getTypeName() == "Liner") {
				theColonyShips.push_back(theShips[x]);
			}
			else if (theShips[x]->getTypeName() == "Ferry") {
				theColonyShips.push_back(theShips[x]);
			}
		}

		return theColonyShips;
	}

	// Adds a ship to the list of ships
	void addToFleet(Ship* i) {
		theShips.push_back(i);
	}

	// Returns a vector  with all ships in the fleet
	vector<Ship *> shipList() const {
		return theShips;
	}

	// Removes ship i  from the fleet
	void destroyShip(Ship* i) {
		for (int x = 0; x < theShips.size(); x++) {
			if (theShips[x] == i) {
				theShips.erase(theShips.begin() + x);
			}
		}
	}

	// User interface to compose a fleet
	static Fleet* userInterfaceCreateFleet() {

		bool insufficientMoney = false, completeFleet = true;
		string corporationName;
		int mainAnswer = 1, subAnswer = 1, medicShipAnswer = 0;

		while (mainAnswer != 2) {

			// Setting the ship numbers to their original values
			int  money = 10000;

			// Enter corporation name
			cout << "Enter your corporation name: ";
			cin >> corporationName;
			cout << endl << endl;

			// Create new Fleet
			Fleet *newFleet = new Fleet(corporationName);

			// Input for colony ships
			cout << "Colony Ships" << endl << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << "Name	Colonists	Cost	Weight	Energy Consumption" << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << "Ferry	100		500	10	5" << endl;
			cout << "Liner	250		1000	20	7" << endl;
			cout << "Cloud	750		2000	30	9" << endl << endl;
			cout << "Money: " << money << endl;

			cout << "Would you like to purchase a colony ships? Enter 1 for Yes or 2 for No: ";
			cin >> subAnswer;

			while (subAnswer == 1) {

				int colonyShipName = 0, colonyShipNum = 0;

				// Error checking for input
				while (colonyShipName < 1 || colonyShipName > 3) {
					cout << "Enter the type of colony ship you want (Enter 1 for Ferry, 2 for Liner, or 3 for Cloud)" << endl
						<< "and the number of ships for that particular colony ship, separated by a space: ";
					cin >> colonyShipName >> colonyShipNum;
				}

				if (colonyShipName == 1) {
					if (money - colonyShipNum * 500 >= 0) {
						money = money - colonyShipNum * 500;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				else if (colonyShipName == 2) {
					if (money - colonyShipNum * 1000 >= 0) {
						money = money - colonyShipNum * 1000;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				else if (colonyShipName == 3) {
					if (money - colonyShipNum * 2000 >= 0) {
						money = money - colonyShipNum * 2000;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				// Check for insufficient funds
				if (insufficientMoney) {
					cout << "Insufficient funds! " << endl << endl;
					subAnswer = 1;
				}
				else {
					for (int x = 0; x < colonyShipNum; x++) {
						ColonyShip *newColony = new ColonyShip(colonyShipName);
						newFleet->addToFleet(newColony);
					}
				}
				// If there is not enough money left to purchase
				if (money < 500) {
					cout << "You do not have enough money to purchase a colony ship anymore" << endl << endl;
					break;
				}
				cout << endl << endl << "Money: " << money << endl;
				cout << "Would you like to purchase more colony ships? Enter 1 for Yes or 2 for No: ";
				cin >> subAnswer;
			}

			cout << endl << endl;

			// Input for military ships
			subAnswer = 1;
			cout << "Military Escort Ships (Protect Against Alien Attacks)" << endl << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Name		Fighters	Cost	Weight	Energy Consumption" << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Cruiser		0		300	2	10" << endl;
			cout << "Frigate		10		1000	7	20" << endl;
			cout << "Destroyer	25		2000	19	30" << endl << endl;
			cout << "Money: " << money << endl;

			// Check whether there's enough money to buy a military escort ship
			if (money < 300) {
				cout << "Sorry you don't have enough money to purchase a military escort ship" << endl << endl;
				subAnswer = 2;
			}
			else {
				cout << "Would you like to purchase a military escort ship? Enter 1 for Yes or 2 for No: ";
				cin >> subAnswer;
			}

			while (subAnswer != 2) {

				int militaryShipName = 0, militaryShipNum = 0;

				// Error checking for input
				while (militaryShipName < 1 || militaryShipName > 3) {
					cout << "Enter the type of colony ship you want (Enter 1 for Cruise, 2 for Frigate, or 3 for Destroyer)" << endl
						<< "and the number of ships for that particular military escort ship, separated by a space: ";
					cin >> militaryShipName >> militaryShipNum;
				}


				if (militaryShipName == 1) {
					if (money - militaryShipNum * 500 >= 0) {
						money = money - militaryShipNum * 500;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				else if (militaryShipName == 2) {
					if (money - militaryShipNum * 1000 >= 0) {
						money = money - militaryShipNum * 1000;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				else if (militaryShipName == 3) {
					if (money - militaryShipNum * 2000 >= 0) {
						money = money - militaryShipNum * 2000;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				// Check for insufficient funds
				if (insufficientMoney) {
					cout << "Insufficient funds! " << endl << endl;
					subAnswer = 1;
				}
				else {
					for (int x = 0; x < militaryShipNum; x++) {
						MilitaryEscortShip *militaryShip = new MilitaryEscortShip(militaryShipName);
						newFleet->addToFleet(militaryShip);
					}
				}

				// If there is not enough money left to purchase
				if (money < 300) {
					cout << "You do not have enough money to purchase a military ship anymore" << endl << endl;
					break;
				}

				cout << endl << endl << "Money: " << money << endl;
				cout << "Would you like to purchase more military escort ships? Enter 1 for Yes or 2 for No: ";
				cin >> subAnswer;

			}
			cout << endl << endl;

			// Input for medic ships
			cout << "Medic Ship (Protects against diseases)" << endl << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Name		Cost	Weight	Energy Consumption" << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Medic		1000	1	1" << endl << endl;
			cout << "Money: " << money << endl;

			// Check whether there's enough money to buy a medic ship
			if (money >= 1000) {
				cout << "Would you like to purchase a medic ship?: Press 1 for Yes or 2 for No: ";
				cin >> medicShipAnswer;
				if (medicShipAnswer == 1) {
					money = money - 1000;
					Ship *medicShip = new Ship("Medic", 1, 1000, 1);
					newFleet->addToFleet(medicShip);
				}
			}
			else {
				cout << "You do not have enough money to purchase a medic ship" << endl << endl;
			}

			cout << endl << endl;

			// Input for solar ships
			subAnswer = 1;
			cout << "Solar Sail Ships (Provides Energy to Fleet)" << endl;
			cout << "COMPULSORY PURCHASE or your fleet will not move!" << endl << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Name		Energy Generation	Cost	Weight	Energy Consumption" << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Radiant		50			50	3	5" << endl;
			cout << "Ebulient	500			250	50	5" << endl << endl;
			cout << "Energy consumed: " << newFleet->getEnergyConsumption() << endl;
			cout << "Money: " << money << endl;

			// Check whether there's enough money to buy a solar sail ship
			if (money < 50) {
				completeFleet = false;
				subAnswer = 2;
			}

			while (subAnswer != 2) {

				int solarShipName = 0, solarShipNum = 0;

				while (solarShipName < 1 || solarShipName >2 || solarShipNum <= 0) {
					cout << "Enter the type of solar sail ship you want (Enter 1 for Radiant or 2 for Ebulient)" << endl
						<< "and the number of ships for that particular solar sail ship, separated by a space: ";
					cin >> solarShipName >> solarShipNum;
				}


				if (solarShipName == 1) {
					if (money - solarShipNum * 50 >= 0) {
						money = money - solarShipNum * 50;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				else if (solarShipName == 2) {
					if (money - solarShipNum * 250 >= 0) {
						money = money - solarShipNum * 250;
						insufficientMoney = false;
					}
					else {
						insufficientMoney = true;
					}
				}

				// Check for insufficient funds
				if (insufficientMoney) {
					cout << "Insufficient funds! " << endl << endl;
					subAnswer = 1;
				}
				else {
					for (int x = 0; x < solarShipNum; x++) {
						SolarSailShip *solarSailShip = new SolarSailShip(solarShipName);
						newFleet->addToFleet(solarSailShip);
					}
				}

				// If there is not enough money left to purchase
				if (money < 500) {
					cout << "You do not have enough money to purchase a solar sail ship anymore" << endl << endl;
					break;
				}

				cout << endl << endl << "Energy produced: " << newFleet->EnergyProduction()
					<< ", Energy consumed: " << newFleet->getEnergyConsumption() << endl;
				cout << "Money: " << money << endl;
				cout << "Would you like to purchase more solar sail ships? Enter 1 for Yes or 2 for No: ";
				cin >> subAnswer;

			}

			cout << endl << endl;

			// Check whether user composed a complete fleet or not
			if (newFleet->getEnergyConsumption() > newFleet->EnergyProduction())
				completeFleet = false;

			if (completeFleet) {
					return newFleet;
			}
			// If user did not meet the requirements for a valid fleet 
			else {
				delete newFleet;
				cout << "System cannot construct your fleet because either " << endl << "1) you did not purchase a solar sail ship " << endl;
				cout << "2) the energy consumption of your fleet is greater than the energy production of your fleet." << endl;
				cout << "Therefore you must create a new fleet again" << endl << endl;
				completeFleet = true;
				mainAnswer = 1;
			}
		}
	}

	// Calculate speed of the fleet
	double getFleetSpeed() {

		// Converting from m/sec to lightyear/sec
		return ((SPEED_OF_LIGHT * ALPHA) / (sqrt(this->getWeight()))) / (9.461 * pow(10, 15));
	}


	// Return distance traveled by fleet
	double getDistanceTraveled() {
		return distanceTraveled;
	}

	// Distance covered by fleet
	void updateDistanceTraveled() {
		// Distance is updated per year
		distanceTraveled += (this->getFleetSpeed() * (3.154 * pow(10, 7)));
	}

	~Fleet() {

	};

private:

	vector<Ship *> theShips;
	string corporationName;
	double distanceTraveled = 0.0;

};

void startRace(Fleet* theFleet) {

	theLock.lock();
	bool halfway = false;

	// Fleet about to embark on journey to planet Gaia
	cout << "Fleet " << theFleet->getCorporationName() << " has embarked on the journey to Gaia" << endl << endl;
	int increaseRate = colonizerPopulation*0.05;
	while (theFleet->getDistanceTraveled() < DISTANCE_TO_GAIA) {

		colonizerPopulation += increaseRate;

		theFleet->updateDistanceTraveled();
	
		cout << "Distance to Gaia: " << DISTANCE_TO_GAIA << endl;
		cout << "How far fleet has traveled: " << theFleet->getDistanceTraveled() << endl;
	
		if (round(theFleet->getDistanceTraveled()) == floor(DISTANCE_TO_GAIA / 2) && halfway == false) {

			cout << endl << endl << "Fleet " << theFleet->getCorporationName() << " is halfway there" << endl << endl;

			// Alien attack will commence

			int indexDestroyed = -1, indexTemp = -1, size;
			vector<Ship *> unprotectedShips = theFleet->unprotectedShips();
			cout << endl << "Fleet " << theFleet->getCorporationName() << " is under attack by aliens!" << endl;

			// If all ships are protected, skip
			if (unprotectedShips.size() != 0) {

				cout << "Colony ships destroyed: " << endl;
				if (unprotectedShips.size() < 4) {
					size = 1;
				}
				else {
					size = unprotectedShips.size() / 4;
				}
				srand(time(0));
				for (int x = 0; x < size; x++) {

					// To prevent from deleting at the same index twice
					while (indexTemp == indexDestroyed) {
						indexTemp = rand() % unprotectedShips.size();
					}
					indexDestroyed = indexTemp;

					// Destroy the colony ship
					theFleet->destroyShip(unprotectedShips[indexDestroyed]);

					cout << unprotectedShips[indexDestroyed]->getTypeName() << " ship" << endl;

				}
			}
			else {
				cout << "No ships are harmed" << endl << endl;
			}

			// Disease outbreak will commence
			if (theFleet->hasMedic() == false) {

				cout << endl << endl << "Oh no! Fleet " << theFleet->getCorporationName() << " is infected by disease!" << endl << endl;
				ColonyShip* theShip = (ColonyShip *)theFleet->colonyShips()[rand() % theFleet->colonyShips().size() ];
				theShip->infect();
				cout << "Colonies on the " << theShip->getTypeName() << " Ship has been wiped out" << endl << endl;
			}
			halfway = true;
		}
	}

	// After fleet has reached planet Gaia

	cout << endl << endl << "Fleet " << theFleet->getCorporationName() << " has reached planet Gaia" << endl
		<< "Current population on planet Gaia: " << colonizerPopulation << " people" << endl
		<< "Number of colonists on Fleet " << theFleet->getCorporationName() << ": " << theFleet->getColonistCount()
		<< endl << endl;

	if (planetEmpty == true || theFleet->getColonistCount() >= colonizerPopulation) {
		colonizer = theFleet->getCorporationName();
		colonizerPopulation = theFleet->getColonistCount();
		planetEmpty = false;

		cout << "Corporation " << colonizer << " is now the ruler planet Gaia" << endl 
		     << "New population on planet Gaia: " << colonizerPopulation << " people" << endl << endl;
	}
	else {
		cout << "Corporation " << colonizer << " remains as the ruler planet Gaia" << endl << endl;
	}
	
	theLock.unlock();
}

bool sortFleetSpeed(Fleet * fleet1, Fleet * fleet2) {
	return fleet1->getFleetSpeed() > fleet2->getFleetSpeed();
}

// Read user's fleet from file
Fleet* readFleetFromFile(string userName) {

	bool solarPresence = false;
	string name;
	int num, money = 0;
	Fleet* newFleet = new Fleet(userName);
	ifstream theFile("023493-fleet.dat");
	
	// Read ships from file
	if (theFile.is_open())
	{
		while (theFile >> name >> num)
		{
			for (int x = 0; x < num; x++) {
				if (name == "Ferry" || name == "Liner" || name == "Cloud") {
					ColonyShip *newColony = new ColonyShip(name);
					newFleet->addToFleet(newColony);
					money += newColony->getCost();
				}
				else if (name == "Ebulient" || name == "Radiant") {
					SolarSailShip *newSolarSail = new SolarSailShip(name);
					newFleet->addToFleet(newSolarSail);
					money += newSolarSail->getCost();
					solarPresence = true;
				}
				else if (name == "Cruiser" || name == "Frigate" || name == "Destroyer") {
					MilitaryEscortShip *newMilitaryShip = new MilitaryEscortShip(name);
					newFleet->addToFleet(newMilitaryShip);
					money += newMilitaryShip->getCost();
				}
				else {
					Ship *medicShip = new Ship("Medic", 1, 1000, 1);
					newFleet->addToFleet(medicShip);
					money += 1000;
				}
			}
		}
		theFile.close();
	}
	else {
		cout << "Unable to open file";
		return NULL;
	}

	// Check whether user composed a complete fleet or not
	if (money > 10000 || newFleet->getEnergyConsumption() > newFleet->EnergyProduction() || solarPresence == false) {
		newFleet = NULL;
	}
		return newFleet;
}