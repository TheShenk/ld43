/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "globals.h"

#include <unistd.h>


USING_NS_CC;

int leverMode = 0;
int leverStat = 0;
int animNum = 0;
int inventory = 0;

Scene* Game::createScene()
{
    return Game::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{

    leverMode = 0;
    leverStat = 0;
    animNum = 0;
    inventory = 0;


    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("infWorld.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);

    auto grass = Sprite::create("mnogo_grass.png");
    grass->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(grass);

    auto rails = Sprite::create("infWorldRail.png");
    rails->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    rails->setScale(2);
    this->addChild(rails);

    sprite = Sprite::create("man.png");
    if (sprite == nullptr)
    {
        problemLoading("'man.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        this->addChild(sprite, 0);
    }

    train = Sprite::create("train_head.png");
    train->setPosition(Vec2(0, 294));
    this->addChild(train);

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        switch (keyCode){

            case EventKeyboard::KeyCode::KEY_W:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                up = true;
                break;
            case EventKeyboard::KeyCode::KEY_S:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                down = true;
                break;
            case EventKeyboard::KeyCode::KEY_D:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                right = true;
                break;
            case EventKeyboard::KeyCode::KEY_A:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                left = true;
                break;
            default:
                log("Another button dispetcher");
                auto nowActive = Game::checkActiveCollission();
                if (nowActive){
                    nowActive->activate();
                }
                break;
        }

        Game::setAngle();

    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        switch (keyCode){

            case EventKeyboard::KeyCode::KEY_W:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                up = false;
                break;
            case EventKeyboard::KeyCode::KEY_S:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                down = false;
                break;
            case EventKeyboard::KeyCode::KEY_D:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                right = false;
                break;
            case EventKeyboard::KeyCode::KEY_A:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                left = false;
                break;

        }

        this->setAngle();

    };

    this->createCollision();
    this->createActive();

    inventorySprite = Sprite::create("emptyItem.png");
    inventorySprite->setPosition(Vec2(sprite->getPositionX()+250, sprite->getPositionY()-150));
    inventorySprite->setScale(2.5);
    this->addChild(inventorySprite);

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    this->scheduleUpdate();


    return true;
}

void Game::trainMove() {


    switch (animNum){
        case 0:
            if (train->getPosition().x >= 760){
                animNum++;
                leverStat = leverMode;
                log("lever stat is %d", leverStat);
            }
            train->setPosition(train->getPositionX()+TRAIN_SPEED, train->getPositionY());
            break;
        case 1:
            if (abs(train->getRotation()) == 45){
                animNum++;
            }
            if (leverStat){
                train->setRotation(train->getRotation()-TRAIN_SPEED);
            } else{
                train->setRotation(train->getRotation()+TRAIN_SPEED);
            }
            break;
        case 2:
            if (abs(train->getRotation()) == 0){
                animNum++;
            }
            if (leverStat){
                train->setRotation(train->getRotation()+TRAIN_SPEED);
                train->setPosition(train->getPositionX()+TRAIN_SPEED, train->getPositionY()+TRAIN_SPEED);
            } else{
                train->setRotation(train->getRotation()-1);
                train->setPosition(train->getPositionX()+TRAIN_SPEED, train->getPositionY()-TRAIN_SPEED);
            }
            break;
        case 3:
            train->setPosition(train->getPositionX()+TRAIN_SPEED, train->getPositionY());
    }

    if (train->getPositionX() > 1000) {
        auto director = Director::getInstance();
        director->popScene();

    }

}

void Game::createCollision(){
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    collisionObjects.push_back(train);


}

void Game::checkMove(){

    auto beforeChangePossition = sprite->getPosition();

    if (up && right){

        sprite->setPosition(sprite->getPositionX()+SPEED, sprite->getPositionY()+SPEED);


    }

    else if (up && left){

        sprite->setPosition(sprite->getPositionX()-SPEED, sprite->getPositionY()+SPEED);

    }

    else if (down && right){

        sprite->setPosition(sprite->getPositionX()+SPEED, sprite->getPositionY()-SPEED);


    }
    else if (down && left){

        sprite->setPosition(sprite->getPositionX()-SPEED, sprite->getPositionY()-SPEED);


    }

    else if (up){
        sprite->setPosition(sprite->getPositionX(), sprite->getPositionY()+SPEED);

    }


    else if (down){
        sprite->setPosition(sprite->getPositionX(), sprite->getPositionY()-SPEED);

    }


    else if (right){
        sprite->setPosition(sprite->getPositionX()+SPEED, sprite->getPositionY());

    }


    else if (left){
        sprite->setPosition(sprite->getPositionX()-SPEED, sprite->getPositionY());

    }

    if (!this->checkCollision()){
        sprite->setPosition(beforeChangePossition);
    }

    Camera::getDefaultCamera()->setPosition(sprite->getPosition());
    inventorySprite->setPosition(Vec2(sprite->getPositionX()+250, sprite->getPositionY()-150));



}

void Game::setAngle(){

    if (up && right){


        sprite->runAction(RotateTo::create(ANIM_TIME, -45));

    }

    else if (up && left){


        sprite->runAction(RotateTo::create(ANIM_TIME, -135));

    }

    else if (down && right){


        sprite->runAction(RotateTo::create(ANIM_TIME, 45));

    }
    else if (down && left){


        sprite->runAction(RotateTo::create(ANIM_TIME, 135));

    }

    else if (up){

        sprite->runAction(RotateTo::create(ANIM_TIME, -90));
    }


    else if (down){

        sprite->runAction(RotateTo::create(ANIM_TIME, 90));
    }


    else if (right){

        sprite->runAction(RotateTo::create(ANIM_TIME, 0));
    }


    else if (left){

        sprite->runAction(RotateTo::create(ANIM_TIME, 180));
    }

}

bool oneCollisionCheck(Node* obj1, Node* obj2){
    int x1 = obj1->getPosition().x;
    obj2->getPosition();
    int x2 = obj2->getPosition().x;
    int y1 = obj1->getPosition().y;
    int y2 = obj2->getPosition().y;
    int w1 = obj1->getBoundingBox().size.width/2;
    int h1 = obj1->getBoundingBox().size.height/2;
    int w2 = obj2->getBoundingBox().size.width/2;
    int h2 = obj2->getBoundingBox().size.height/2;

    if(obj2->getBoundingBox().size.height - 40 < 0.001) {
        h2 /= 2;
        y2-=10;
    }

    if (abs(x2-x1) < w1 + w2 && abs(y1-y2) < h1 + h2) {
        return true;
    }
    return false;
}

bool oneActiveCollisionCheck(Node* obj1, Node* obj2){
    int x1 = obj1->getPosition().x;
    obj2->getPosition();
    int x2 = obj2->getPosition().x;
    int y1 = obj1->getPosition().y;
    int y2 = obj2->getPosition().y;
    int w1 = obj1->getBoundingBox().size.width/2;
    int h1 = obj1->getBoundingBox().size.height/2;
    int w2 = obj2->getBoundingBox().size.width/2;
    int h2 = obj2->getBoundingBox().size.height/2;

    if (abs(x2-x1) < (w1 + w2+20) && abs(y1-y2) < (h1 + h2+20)) {
        return true;
    }
    return false;
}

bool Game::checkCollision() {

    for (int i=0; i<collisionObjects.size(); i++){
        if (oneCollisionCheck(sprite, collisionObjects[i])){
            return false;
        }
    }
    return true;
}

void Game::createActive(){

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto leverSprite = Sprite::create("lever0.png");
    leverSprite->setScale(0.2);
    leverSprite->setPosition(Vec2(750, 250));
    auto lever = new ActiveObject();
    lever->node = leverSprite;

    lever->actFunc = [=](){
        if (leverMode == 0) {
            leverSprite->setSpriteFrame(SpriteFrame::create("lever1.png", leverSprite->getTextureRect()));
            leverMode = 1;
        }
        else {
            leverSprite->setSpriteFrame(SpriteFrame::create("lever0.png", leverSprite->getTextureRect()));
            leverMode = 0;
        }
    };
    this->addChild(lever->node);
    activeObjects.push_back(lever);

    auto axeSprite = Sprite::create("axe.png");
    axeSprite->setScale(3);
    axeSprite->setPosition(Vec2(300, 450));
    ActiveObject* axe = new ActiveObject();
    axe->node = axeSprite;
    axe->actFunc = [=]{
        if (inventory == 0) {
            inventory = 1;
            inventorySprite->setSpriteFrame(SpriteFrame::create("axeItem.png", inventorySprite->getTextureRect()));
            axeSprite->setVisible(false);
        }
    };
    this->addChild(axeSprite);
    activeObjects.push_back(axe);

    Sprite* woodSprite;

    for (int i=0; i<24; i++){

        woodSprite = Sprite::create("tree5.png");

        woodSprite->setPosition(Vec2(rand()%1600, rand()%1600));
        ActiveObject* wood = new ActiveObject();
        wood->node = woodSprite;
        wood->actFunc = [=]{
            if (inventory == 1) {
                inventory = 2;
                inventorySprite->setSpriteFrame(SpriteFrame::create("brevnoItem.png", inventorySprite->getTextureRect()));
                woodSprite->setVisible(false);
                collisionObjects.erase(std::remove(collisionObjects.begin(), collisionObjects.end(), woodSprite), collisionObjects.end());             }
        };
        this->addChild(woodSprite);
        activeObjects.push_back(wood);
        collisionObjects.push_back(woodSprite);

        ActiveObject* trainActive = new ActiveObject();
        trainActive->node = train;
        trainActive->actFunc = [=]{
            if (inventory == 2 || inventory == 3){
                auto director = Director::getInstance();
                director->popScene();
            }
        };

        activeObjects.push_back(trainActive);

        auto keyWoodSprite = Sprite::create("tree5.png");
        keyWoodSprite->setPosition(Vec2(0, 0));
        ActiveObject* keyWood = new ActiveObject();
        keyWood->node = keyWoodSprite;
        keyWood->actFunc = [=] {
            inventory = 3;
            inventorySprite->setSpriteFrame(SpriteFrame::create("keyItem.png", inventorySprite->getTextureRect()));
        };

        this->addChild(keyWoodSprite);
        activeObjects.push_back(keyWood);
    };




}

ActiveObject* Game::checkActiveCollission() {


    for (int i=0; i<activeObjects.size(); i++){
        if (oneActiveCollisionCheck(sprite, activeObjects[i]->node)){
            return activeObjects[i];
        }
    }
    return nullptr;

}


void Game::update(float dt){

    this->checkMove();
    this->trainMove();

}
