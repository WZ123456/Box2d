#include "HelloWorldScene.h"
#include "PhysicalSprite.h"
#define PTM_RADTIO 32
USING_NS_CC;



CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    layer->setTouchEnabled(true);
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png", this,menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    initPhysical();
    this->setTouchMode(kCCTouchesOneByOne);
    this->scheduleUpdate();
    addNewSpriteAtPosition(ccp(100, 100));
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{

	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    CCDirector::sharedDirector()->end();

}

void HelloWorld::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    world->Step(dt, velocityIterations, positionIterations);
    
    for (b2Body * body = world->GetBodyList(); body; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            PhysicSprite * sprite = (PhysicSprite *)body->GetUserData();
            if (sprite->hp<0) {
                sprite->removeFromParent();
                world->DestroyBody(body);
                continue;
            }
            sprite->setPosition(CCPointMake(body->GetPosition().x*PTM_RADTIO, body->GetPosition().y*PTM_RADTIO));
            sprite->setRotation(-1*CC_RADIANS_TO_DEGREES(body->GetAngle()));
        }
    }
}

void HelloWorld::initPhysical()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    b2Vec2 vect;
    vect.Set(0, -10);
    world = new b2World(vect);
    world->SetAllowSleeping(true);//允许休眠
    world->SetContinuousPhysics(true);//允许连续碰撞检测
    
    //创建世界边界
    //1.地面
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body * groundBody = world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, 0), b2Vec2(winSize.width/PTM_RADTIO, 0));
    groundBody->CreateFixture(&groundBox, 0);
    
    //2.天花板
    groundBox.Set(b2Vec2(0, winSize.height/PTM_RADTIO), b2Vec2(winSize.width/PTM_RADTIO, winSize.height/PTM_RADTIO));
    groundBody->CreateFixture(&groundBox,0);
    
    //3.左边
    groundBox.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height/PTM_RADTIO));
    groundBody->CreateFixture(&groundBox,0);
    //4.右边
    groundBox.Set(b2Vec2(winSize.width/PTM_RADTIO/2, 0), b2Vec2(winSize.width/PTM_RADTIO/2, winSize.height/PTM_RADTIO/2-1));
    groundBody->CreateFixture(&groundBox,0);
    
    groundBox.Set(b2Vec2(winSize.width/PTM_RADTIO/2, winSize.height/PTM_RADTIO/2+1), b2Vec2(winSize.width/PTM_RADTIO/2, winSize.height/PTM_RADTIO));
    groundBody->CreateFixture(&groundBox,0);
    
}

void HelloWorld::addNewSpriteAtPosition(cocos2d::CCPoint p)
{
    PhysicSprite * sprite = new PhysicSprite();
    sprite->setPosition(p);
    this->addChild(sprite);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RADTIO, p.y/PTM_RADTIO);
    
    bodyDef.userData = sprite;
    b2Body * body = world->CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(0.6f, 0.6f);
    //参数是边长的一半
    CCLog("contentsize : %f",sprite->getContentSize().width);
    dynamicBox.SetAsBox(sprite->getContentSize().width/PTM_RADTIO/2, sprite->getContentSize().height/PTM_RADTIO/2);
    b2FixtureDef fixtuerDef;
    fixtuerDef.shape = &dynamicBox;
    fixtuerDef.density = 10.0f;
    fixtuerDef.friction = 0.0f;
    fixtuerDef.restitution = 1.5f;
    body->CreateFixture(&fixtuerDef);
    sprite->setPhysicBody(body);
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("touch");
    return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    HelloWorld::addNewSpriteAtPosition(pTouch->getLocation());
}

















