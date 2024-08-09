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

#include "HelloWorldScene.h"

USING_NS_CC;

// �߶�ռ����
const int kHeightInGrids = 20;
// ���ռ����
const int kWidthInGrids = 10;
// ���ӱ߳�
const float kGridSize = 18.0F;
// ��Ϸ�������Ͻ�����
const float X = 28;
const float Y = 449;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in "
           "front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr) {
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //} else {
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr) {
    //    problemLoading("'HelloWorld.png'");
    //} else {
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(
    //            Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}

    // add background
    auto background = Sprite::create("background.png");
    if (background == nullptr) {
        problemLoading("'background.png'");
    } else {
        background->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        addChild(background, 0);
    }

    int _type = 0;
    // add tetromino
    for (size_t i = 0; i < kBlockNum; ++i) {
        _current_block[i].sprite = Sprite::create("tetromino.png", Rect(0, 0, kGridSize, kGridSize));
        if (_current_block[i].sprite == nullptr) {
            problemLoading("'tetromino.png'");
        } else {
            /*_current_block[i]->setPosition(
                    Vec2(X + kGridSize / 2 + origin.x + kGridSize * 10,
                         Y - kGridSize / 2 + origin.y - kGridSize * i));
            addChild(_current_block[i], 0);*/
            _current_block[i].x = _figures[_type][i] % 2 * -1;
            _current_block[i].y = (_figures[_type][i] + 1) / 2;
            addChild(_current_block[i].sprite, 0);
        }
    }

    // ���ü����¼�������
    auto event_listener = EventListenerKeyboard::create();
    event_listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::OnKeyPressed, this);
    event_listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::OnKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(event_listener, this);

    // ���������ڳ����ƶ�
    this->schedule(SEL_SCHEDULE(&HelloWorld::UpdatePosition), 0.1f);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    // Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the
   * application  ,do not use Director::getInstance()->end() as given
   * above,instead trigger a custom event created in RootViewController.mm as
   * below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _is_left_pressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _is_right_pressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        _is_up_pressed = true;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _is_down_pressed = true;
        break;
    default:
        break;
    }
}

// �����ͷ��¼�����
void HelloWorld::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _is_left_pressed = false;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _is_right_pressed = false;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        _is_up_pressed = false;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _is_down_pressed = false;
        break;
    default:
        break;
    }
}

void HelloWorld::UpdatePosition(float dt) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (size_t i = 0; i < kBlockNum; ++i) {
        // ʹ�� dt �����ƶ��ٶȣ�������� 10 ��Ϊ��ʹ�ƶ��ٶȸ���
        float move_speed = dt * 10;

        if (_is_left_pressed) {
            _current_block[i].x -= move_speed;
        }
        if (_is_right_pressed) {
            _current_block[i].x += move_speed;
        }
        if (_is_up_pressed) {
            _current_block[i].y += move_speed;
        }
        if (_is_down_pressed) {
            _current_block[i].y -= move_speed;
        }

        // ���¾���λ��
        //_current_block[i]->setPosition(position);
        _current_block[i].sprite->setPosition(
                Vec2(X + kGridSize / 2 + origin.x + _current_block[i].x * kGridSize,
                     Y - kGridSize / 2 + origin.y + _current_block[i].y * kGridSize));
    }
}