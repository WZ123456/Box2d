//
//  PhysicalSprite.h
//  Box2d
//
//  Created by RyanJulius on 15-3-26.
//
//

#ifndef __Box2d__PhysicalSprite__
#define __Box2d__PhysicalSprite__
#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class PhysicSprite : public CCSprite {
private:
    b2Body * m_pBody;
    
public:
    PhysicSprite();
    void setPhysicBody(b2Body * body);
    int hp;
};


#endif /* defined(__Box2d__PhysicalSprite__) */
