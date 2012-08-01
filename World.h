#ifndef WORLD
#define WORLD

#include "Direction.h"
#include "RelativeDirection.h"
#include "Action.h"

#include "WorldCell.h"
#include "Pet.h"
#include "PetIntention.h"
#include "PetState.h"

#include <list>
#include <map>

#include <SFML/Graphics.hpp>

class World{

	public:

	World();
	~World();
	
	static const int width = 300;
	static const int height = 200;
	static const int initialPopulationSize = 1000;

//	protected:
	
	sf::Image image;

	WorldCell cells[width*height];
	std::list<Pet *> pets;
	std::map<Pet *, PetState> petStates;
	std::list<Pet *> petArchive;
	
	bool addPet(Pet *newPet, PetState const &newState);
	void removePet(Pet *pet);
	void regeneratePopulation();
	
	public:

	int coordinateToIndex(int x, int y) const;
	void indexToCoordinate(int position, int &x, int &y) const;
	int movePosition(int position, Direction direction) const;
	Direction offsetDirectionByRelativeDirection(Direction direction, RelativeDirection relativeDirection) const;
	RelativeDirection relativeDirectionBetweenDirections(Direction direction, Direction comparedToDirection) const;

	void buildCage(int sideLength, Direction openingDirection);
	void buildWalls();
	void sprinklePlants(int numPlants);
	int addPetAndPlaceRandomly(Pet *newPet, PetState newState);
	void render(sf::RenderWindow &window);
	bool step();
	void applyPetIntentionToPet(Pet *pet, PetIntention petIntention);
};

#endif