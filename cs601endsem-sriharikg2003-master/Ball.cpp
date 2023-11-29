#include "Ball.h"

Ball::Ball() : pi(3.0) {}


Ball::Ball(int r) : pi(3.0), radius(r) {}


BasketBall::BasketBall(int rad, int col) : Ball(rad), color(col) {}
