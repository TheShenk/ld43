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

USING_NS_CC;

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }

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


        Game::setAngle();
    };


    return true;
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

void Game::update(float dt){

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


}


