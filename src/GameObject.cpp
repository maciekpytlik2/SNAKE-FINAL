#include "GameObject.h"

GameObject::GameObject(Position startPosition) : position(startPosition) {}

Position GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(Position newPosition) {
    position = newPosition;
}
