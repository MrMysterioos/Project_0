#include "Character.h"

bool Character::initWithBehavior(Behavior * behavior) {
	Actor::initWithBehavior(behavior);

	return true;
}
