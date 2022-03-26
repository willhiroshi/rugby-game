// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter
#define nMoves 9

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t possibleDirectionsDefender[nMoves] = {
    DIR_STAY,
    DIR_UP,
    DIR_UP_RIGHT,
    DIR_RIGHT,
    DIR_DOWN_RIGHT,
    DIR_DOWN,
    DIR_DOWN_LEFT,
    DIR_LEFT,
    DIR_UP_LEFT};

int probabilitiesDefender[nMoves] = {
    0,  // DIR_STAY
    50, // DIR_UP
    0,  // DIR_UP_RIGHT
    0,  // DIR_RIGHT
    0,  // DIR_DOWN_RIGHT
    50, // DIR_DOWN
    0,  // DIR_DOWN_LEFT
    0,  // DIR_LEFT
    0   // DIR_UP_LEFT
};

bool equal_direction_defender(direction_t previousMovement, direction_t nextMovement)
{
  return nextMovement.i == previousMovement.i && nextMovement.j == previousMovement.j;
}

direction_t random_movement_defender()
{
  direction_t generatedMovement;
  int probSum[nMoves];
  memset(probSum, 0, sizeof probSum);

  probSum[0] = probabilitiesDefender[0];
  for (int i = 1; i < nMoves; i++)
    probSum[i] = probSum[i - 1] + probabilitiesDefender[i];

  int r = (rand() % 100) + 1;
  if (r <= probSum[0])
    generatedMovement = possibleDirectionsDefender[0];

  for (int i = 1; i < nMoves; i++)
    if (r > probSum[i - 1] && r <= probSum[i])
      generatedMovement = possibleDirectionsDefender[i];

  return generatedMovement;
}

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy)
{
  UNUSED(attacker_spy);

  long long int seed = time(0) * (defender_position.i + rand()) * 42 + (defender_position.j + rand());
  srand(seed);

  static position_t previousPosition = INVALID_POSITION;
  static direction_t previousMovement = DIR_STAY;

  direction_t nextMovement = random_movement_defender();
  if (equal_positions(previousPosition, defender_position))
    while (equal_direction_defender(previousMovement, nextMovement))
      nextMovement = random_movement_defender();

  return nextMovement;
}

/*----------------------------------------------------------------------------*/
