//
//  PhysicalSprite.cpp
//  Box2d
//
//  Created by RyanJulius on 15-3-26.
//
//

#include "PhysicalSprite.h"

PhysicSprite::PhysicSprite():m_pBody(NULL)
{
    this->initWithFile("Icon-57.png");
    hp = 5;
}

void PhysicSprite::setPhysicBody(b2Body *body)
{
    m_pBody = body;
}