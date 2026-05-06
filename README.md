# Dungeon Escape

**Dungeon Escape** is a small first-person Unreal Engine C++ demo project built to practice gameplay programming, interaction systems, reusable components, and simple puzzle mechanics.

This project is not intended to be a full game. It is a learning/demo project created to prove core Unreal Engine C++ concepts through a playable dungeon escape scenario.

## Overview

The player explores a dungeon environment, collects key items, interacts with locks, activates pressure plates, and triggers moving or rotating level geometry such as walls, doors, and gates.

The main focus of this project is on building reusable gameplay systems in C++ rather than visual polish.

## Features

- First-person player controller
- Enhanced Input-based interaction
- Camera-based sphere sweep interaction system
- Collectable key items
- Simple player inventory using item names
- Lock and key interaction logic
- Pressure plate trigger system
- Reusable mover component for doors, walls, and moving objects
- Support for moving root components or specific child components
- Configurable movement and rotation thresholds
- One-time movement behavior for objects that should open once and stay open
- Actor tag-based gameplay filtering
- Debug logs and visual debug helpers

## Gameplay Systems

### Player Interaction

The player can interact with objects using a sphere sweep from the first-person camera.

The interaction system checks whether the hit actor is:

- A collectable item
- A lock
- Another interactable object

Example interaction behavior:

- If the player interacts with a collectable item, the item is added to the player's inventory and destroyed from the world.
- If the player interacts with a lock, the system checks whether the player has the required key item.
- If the correct key exists in the inventory, the key is placed in the lock and removed from the inventory.
