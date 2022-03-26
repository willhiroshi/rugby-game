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
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter
#define nMoves 9

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t possibleDirectionsAttacker[nMoves] = {
    DIR_STAY,
    DIR_UP,
    DIR_UP_RIGHT,
    DIR_RIGHT,
    DIR_DOWN_RIGHT,
    DIR_DOWN,
    DIR_DOWN_LEFT,
    DIR_LEFT,
    DIR_UP_LEFT};

int probabilitiesAttacker[nMoves] = {
    0,  // DIR_STAY
    5,  // DIR_UP
    15, // DIR_UP_RIGHT
    30, // DIR_RIGHT
    15, // DIR_DOWN_RIGHT
    5,  // DIR_DOWN
    10, // DIR_DOWN_LEFT
    10, // DIR_LEFT
    10  // DIR_UP_LEFT
};

bool equal_direction_attacker(direction_t previousMovement, direction_t nextMovement)
{
  return nextMovement.i == previousMovement.i && nextMovement.j == previousMovement.j;
}

direction_t random_movement_attacker()
{
  direction_t generatedMovement;
  int probSum[nMoves];
  memset(probSum, 0, sizeof probSum);

  probSum[0] = probabilitiesAttacker[0];
  for (int i = 1; i < nMoves; i++)
    probSum[i] = probSum[i - 1] + probabilitiesAttacker[i];

  int r = (rand() % 100) + 1;
  if (r <= probSum[0])
    generatedMovement = possibleDirectionsAttacker[0];

  for (int i = 1; i < nMoves; i++)
    if (r > probSum[i - 1] && r <= probSum[i])
      generatedMovement = possibleDirectionsAttacker[i];

  return generatedMovement;
}

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy)
{
  UNUSED(defender_spy);

  long long int seed = time(0) * (attacker_position.i + rand()) * 42 + (attacker_position.j + rand());
  srand(seed);

  static position_t previousPosition = INVALID_POSITION;
  static direction_t previousMovement = DIR_STAY;

  direction_t nextMovement = random_movement_attacker();
  if (equal_positions(previousPosition, attacker_position))
    while (equal_direction_attacker(previousMovement, nextMovement))
      nextMovement = random_movement_attacker();

  return nextMovement;
}

/*----------------------------------------------------------------------------*/
