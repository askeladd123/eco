//
// Created by askso on 31/05/2022.
//

#ifndef ECO_COMMON_H
#define ECO_COMMON_H

struct instructions
{
  float rotation, velocity;
};

struct senses
{
  std::vector<float>* reseptors;
};

#endif //ECO_COMMON_H
