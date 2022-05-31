//
// Created by askso on 30/05/2022.
//
#ifndef ECO_BLOB_H
#define ECO_BLOB_H

#include "logic.h"
#include "brain.h"
#include "graphics.h"

class Blob
{
public:
  Logic logic;
  Brain brain;
  Graphics graphics;

public:
  Blob(Logic logic, Brain brain, Graphics graphics):
      logic(logic),
      brain(brain),
      graphics(graphics){}
};

#endif //ECO_BLOB_H
