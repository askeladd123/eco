//
// Created by askso on 30/05/2022.
//

#ifndef ECO_COLLISION_H
#define ECO_COLLISION_H

#include <cmath>

struct point  {int x, y;};
struct box    {int x, y, w, h;};
struct circle {int x, y, r;};
struct line   {int x1, y1, x2, y2;};

struct response {bool intersects;};
struct points_response {int points; point a, b;};


response collision(point a, point b)
{
  return {a.x == b.x && a.y == b.y};
}

bool collision(box a, box b)
{
  return
  b.x < a.x + a.w &&
  a.x < b.x + b.w &&
  b.y < a.y + a.h &&
  a.y < b.y + b.h;
}

bool collision(line a, line b);

bool collision(circle a, circle b)
{
  int x = b.x - a.x;
  int y = b.y - a.y;
  return sqrt(x * x + y * y) < b.r - a.r;
}

bool collision(box b, circle c);
bool collision(circle c, box b);

bool collision(box b, line l);
bool collision(line l, box b);

bool collision(line l, circle c);
bool collision(circle c, line l);

#endif //ECO_COLLISION_H
