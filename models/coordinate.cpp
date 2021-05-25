#include "coordinate.hpp"

Coordinate::Coordinate(Position point){
  this->point = point;
}

void Coordinate::setPosition(Position point){
  this->point = point;
}

Position Coordinate::getPosition(){
  return this->point;
}

char Coordinate::getCharacter(){
  return point.character;
}