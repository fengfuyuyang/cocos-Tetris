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
const float Y = 107;

int field[kHeightInGrids][kWidthInGrids] = {0};

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

    std::random_device rd;
    _random_engine = std::mt19937(rd());

    // ���ü����¼�������
    auto event_listener = EventListenerKeyboard::create();
    event_listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::OnKeyPressed, this);
    event_listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::OnKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(event_listener, this);

    // ���������ڳ����ƶ�
    this->schedule(SEL_SCHEDULE(&HelloWorld::UpdatePosition), 0.08f);

    // �Զ�����
    this->schedule(SEL_SCHEDULE(&HelloWorld::Drop), 0.7f);

    GetNewBlock();

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
    if (_is_left_pressed) {
        Move(-1, 0);
    }
    if (_is_right_pressed) {
        Move(1, 0);
    }
    if (_is_up_pressed) {
        Rotate();
    }
    if (_is_down_pressed) {
        Move(0, -1);
    }

    for (size_t i = 0; i < kBlockNum; ++i) {
        SetPosition(_current_block[i]);
        _current_block[i].sprite->setVisible(_current_block[i].y < kHeightInGrids);
    }
}

void HelloWorld::RotatePoint90(int pos) {
    Point center = _current_block[pos]; // ��ת����
    for (auto& it : _current_block) {
        int x = it.y - center.y;
        int y = it.x - center.x;
        it.x = center.x - x;
        it.y = center.y + y;
    }
}

void HelloWorld::RotatePointNeg90(int pos) {
    Point center = _current_block[pos]; // ��ת����
    for (auto& it : _current_block) {
        int x = it.y - center.y;
        int y = it.x - center.x;
        it.x = center.x + x;
        it.y = center.y - y;
    }
}

void HelloWorld::Rotate() {
    memcpy(_previous_block, _current_block, sizeof(_current_block));
    switch (_type) {
    case BlockType::I: {
        if (_current_block[1].x != _current_block[2].x) {
            RotatePointNeg90(2);
        } else {
            RotatePoint90(2);
        }

        break;
    }
    case BlockType::J: {
        if (_current_block[0].x > _current_block[1].x) {
            Move(1, 0);
        }
        RotatePoint90(2);
        if (_current_block[0].x > _current_block[1].x) {
            Move(-1, 0);
        }
        break;
    }
    case BlockType::L: {
        if (_current_block[0].x > _current_block[1].x) {
            Move(-1, 0);
        }
        RotatePoint90(2);
        if (_current_block[0].x > _current_block[1].x) {
            Move(1, 0);
        }
        break;
    }
    case BlockType::O:
        break;
    case BlockType::S: {
        if (_current_block[1].x != _current_block[2].x) {
            RotatePointNeg90(1);
        } else {
            RotatePoint90(1);
        }

        break;
    }
    case BlockType::T: {
        RotatePoint90(1);
        break;
    }
    case BlockType::Z: {
        if (_current_block[1].x != _current_block[2].x) {
            RotatePoint90(1);
        } else {
            RotatePointNeg90(1);
        }

        break;
    }
    default:
        break;
    }

    if (!IsValidPosition()) {
        memcpy(_current_block, _previous_block, sizeof(_previous_block));
    }
}

void HelloWorld::Move(int dx, int dy) {
    memcpy(_previous_block, _current_block, sizeof(_current_block));
    for (int i = 0; i < kBlockNum; ++i) {
        _current_block[i].x += dx;
        _current_block[i].y += dy;
    }
    if (!IsValidPosition()) {
        memcpy(_current_block, _previous_block, sizeof(_previous_block));
    }
}

bool HelloWorld::IsValidPosition() {
    for (auto& it : _current_block) {
        if (it.x < 0 || it.x >= kWidthInGrids || it.y < 0 || it.y >= kHeightInGrids + kBlockNum) {
            return false;
        } else if (it.y < kHeightInGrids && field[it.y][it.x]) {
            return false;
        }
    }
    return true;
}

void HelloWorld::Drop(float dt) {
    memcpy(_previous_block, _current_block, sizeof(_current_block));
    for (auto& it : _current_block) {
        it.y -= 1;
    }
    if (!IsValidPosition()) {
        memcpy(_current_block, _previous_block, sizeof(_previous_block));
        FixBlock();
    }
}

void HelloWorld::GetNewBlock() {
    std::uniform_int_distribution<int> block_type_dist(0, kTypeSize - 1);
    std::uniform_int_distribution<int> sprite_dist(0, 7);
    std::uniform_int_distribution<int> rotation_dist(0, 3);

    _type = static_cast<BlockType>(block_type_dist(_random_engine));
    int current_sprite = sprite_dist(_random_engine);

    for (size_t i = 0; i < kBlockNum; ++i) {
        _current_block[i].sprite = Sprite::create(
                "tetromino.png", Rect(kGridSize * current_sprite, 0, kGridSize, kGridSize));
         
        if (_current_block[i].sprite == nullptr) {
            problemLoading("'tetromino.png'");
        } else {
            _current_block[i].x = (_figures[_type][i] + 1) % 2 + kBlockNum;
            _current_block[i].y = (_figures[_type][i] - 1) / 2 + kHeightInGrids;
            addChild(_current_block[i].sprite, 0);
        }
    }

    // ��ʼ������ת
    int rotation = rotation_dist(_random_engine);
    for (int i = 0; i < rotation; ++i) {
        Rotate();
    }

    // ����λ�þ���
    int min_x = kWidthInGrids, max_x = 0;
    for (int i = 0; i < kBlockNum; ++i) {
        if (_current_block[i].x < min_x) {
            min_x = _current_block[i].x;
        }
        if (_current_block[i].x > max_x) {
            max_x = _current_block[i].x;
        }
    }
    int offset_x = (kWidthInGrids / 2) - ((max_x - min_x + 1) / 2 + min_x);
    for (int i = 0; i < kBlockNum; ++i) {
        _current_block[i].x += offset_x;
    }
}

void HelloWorld::FixBlock() {
    for (auto& it : _current_block) {
        field[it.y][it.x] = 1;
        _points.push_back(it);
    }
    ClearLines();
    GetNewBlock();
}

void HelloWorld::ClearLines() {
    int num_lines_cleared = 0;

    for (int y = 0; y < kHeightInGrids; ++y) {
        bool is_line_full = true;

        for (int x = 0; x < kWidthInGrids; ++x) {
            if (field[y][x] == 0) {
                is_line_full = false;
                break;
            }
        }

        if (is_line_full) {
            num_lines_cleared++;
            for (int x = 0; x < kWidthInGrids; ++x) {
                field[y][x] = 0;
            }

            // ʹ��remove_if��erase�Ƴ���ǰ�е����з���
            //_points.remove_if([y](const Point& point) { return point.y == y; });
            for (auto it = _points.begin(); it != _points.end(); /*��*/) {
                if (it->y == y) {
                    // ��ִ��removeChild����
                    removeChild(it->sprite);

                    // Ȼ���Ƴ��õ�
                    it = _points.erase(it);
                } else {
                    ++it;
                }
            }

            // ���Ϸ������з��������ƶ�һ��
            for (auto& point : _points) {
                if (point.y > y) {
                    point.y -= 1;
                    SetPosition(point);
                }
            }

            // ���Ϸ��������������ƶ�һ��
            for (int row = y; row + 1 < kHeightInGrids; ++row) {
                for (int col = 0; col < kWidthInGrids; ++col) {
                    field[row][col] = field[row + 1][col];
                }
            }

            // ���¼�鵱ǰ��
            --y;
        }
    }
}

void HelloWorld::SetPosition(Point& point) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    point.sprite->setPosition(Vec2(X + kGridSize / 2 + origin.x + point.x * kGridSize,
                                   Y - kGridSize / 2 + origin.y + point.y * kGridSize));
}
