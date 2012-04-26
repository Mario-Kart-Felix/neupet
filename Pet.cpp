#include "Pet.h"

#include "Direction.h"
#include "RelativeDirection.h"
#include "Action.h"

#include "WorldCell.h"
#include "PetIntention.h"
#include "SensoryInput.h"

#include <stdlib.h>


PetIntention Pet::getPetIntentionForSensoryInput(SensoryInput sensory){
	//		collectInput();
	//		processInput();
	//		respondToInput();
	
	RelativeDirection relativeDirection;
	
	// Pick direction randomly, preferring forward, but turning (forward) left or right sometimes.
	float random = rand() / (float) RAND_MAX;
	if(random < .1) {
		relativeDirection = forwardLeft;
	} else if(random < .1+.1) {
		relativeDirection = forwardRight;
	} else {
		relativeDirection = forward;
	}

	// Use all directions as backup in case the preferred one is blocked.		
	RelativeDirection backupRelativeDirections[] = {
		forward,
		forwardLeft,
		forwardRight,
		backwardLeft,
		backwardRight,
		backward
	};
	for(int i=0; i<6; ++i){
		WorldCell cell = sensory.touchedCells[relativeDirection];
		if(cell.pet || cell.impassable){
			relativeDirection = backupRelativeDirections[i];
		} else {
			break;
		}
	}
	
	return PetIntention(static_cast<Action>(mate | battle | move), relativeDirection);
}



/*
 
 f   G   H
 g   b   C   I
 h	c  a  D   J
 i   d   e   K
 j   k   l
 
 
 a
 b-B
 b+B
 c-C
 c+C
 ...
 
 Instead of sampling b, B, c, C... I sample b-B, b+B, c-C, c+C... to make the nn insensitive to direction.
 */


//	const int numLayers = 1; // Arbitrary
//	const int layerSize = 4; // Arbitrary
//
//	const int numInputPositions = 7; // All positions within 1 steps.
//	const int numInputChannels = 3; // Other pets mate-abillity, nutricient, danger.
//	const int numOutputPositions = 7; // All positions within 1 steps.
//	const int numGeneralOutputs = 2; // Mate, scent.
//
//	const int numInputNeurons = numInputPositions*numInputChannels;
//	const int numProcessingNeurons = numLayers*layerSize;
//	const int numOutputNeurons = numOutputPositions + numGeneralOutputs;
//
//	const int numInputConnections = numInputPositions*numInputChannels*layerSize;
//	const int numProcessingConnections = (numLayers-1)*layerSize*layerSize;
//	const int numOutputConnections = (numOutputPositions + numGeneralOutputs)*layerSize;
//
//	float inputNeurons[numInputNeurons];
//	float processingNeurons[numProcessingNeurons];
//	float outputNeurons[numOutputNeurons];
//
//	float inputConnections[numinputConnections];
//	float processingConnections[numProcessingConnections];
//	float outputConnections[numOutputConnections];


//	void collectInput(){
//
//		for(Channels channel = 0; i<numChannels; ++i)
//			for(Directions direction = 0; i<numDirections; ++i)
//				inputNeurons[channel*numDirections + direction] = world.sample(position, facingDirection, direction, channel);
//	}


//	void processInput(){
//		// First layer takes input directly from input neurons.
//		for(int write=0; write<layerSize; ++write){
//			processingNeurons[write] = 0;
//			for(int read=0; read<numInputNeurons; ++read)
//				processingNeurons[write] = inputNeurons[read] * inputConnections[write*layerSize + read];
//		}
//
//		// Propagate through the rest of the processing layers.
//		for(int layer=1; layer<numLayers; ++layer)
//			for(int write=0; write<layerSize; ++write){
//				processingNeurons[layer*layerSize + write] = 0;
//				for(int read=0; read<layerSize; ++read)
//					processingNeurons[layer*layerSize + write] += processingNeurons[(layer-1)*layerSize + read] * processingConnections[write*layerSize + read];
//			}
//
//		// Output neurons read from the last layer.
//		for(int write=0; write<numOutputNeurons; ++write){
//			outputNeurons[write] = 0;
//			for(int read=0; read<layerSize; ++read)
//				outputNeurons[write] = processingNeurons[(numLayers-1)*layerSize + read] * outputConnections[read*layerSize + write];
//		}
//	}
