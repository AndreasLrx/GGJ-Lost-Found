/*
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Entity
*/

#include "Entity/Entity.hpp"
#include "States/GameState.hpp"

void Entity::spawnProjectile(GameDataRef gameData, AbstractProjectile* projectile)
{
	State* state = gameData->machine.GetActiveState().get();
	GameState* gameState = static_cast<GameState *>(state);

	gameState->spawnProjectile(projectile, this);
}
