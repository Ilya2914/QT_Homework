#include "game.h"
#include <algorithm>
#include <iostream>

Game::Game() {
    init();
}

Game::~Game() {
}

void Game::init() {
    level = 1;
    score = 0;
    levelStartScore = 0;
    create_level(level);
}

void Game::init_object(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType){
    set_object_pos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
    obj->cType = inType;
    obj->horizSpeed = 0.2;
    obj->IsFly = false;
}

void Game::set_object_pos(TObject *obj, float xPos, float yPos){
    obj->x = xPos;
    obj->y = yPos;
}

bool Game::is_collision(const TObject *o1, const TObject *o2){
    return ( o1->x + o1->width > o2->x &&  o1->x < o2->x + o2->width && o1->y + o1->height > o2->y && o1->y < o2->y + o2->height);
}

void Game::create_level(int lvl) {
    bricks.clear();
    movings.clear();
    
    init_object(&mario, 39, 10, 3, 3, '@');

    if (lvl == 1){
        bricks.resize(13);
        init_object(&bricks[0], 20, 20, 40, 5, '#');
        init_object(&bricks[1], 30, 10, 5, 3, '?');
        init_object(&bricks[2], 47, 10, 5, 3, '?');
        init_object(&bricks[3], 60, 15, 40, 10, '#');
        init_object(&bricks[4], 60, 5, 10, 3, '-');
        init_object(&bricks[5], 70, 5, 5, 3, '?');
        init_object(&bricks[6], 75, 5, 5, 3, '-');
        init_object(&bricks[7], 80, 5, 5, 3, '?');
        init_object(&bricks[8], 85, 5, 10, 3, '-');
        init_object(&bricks[9], 100, 20, 20, 5, '#');
        init_object(&bricks[10], 120, 15, 10, 10, '#');
        init_object(&bricks[11], 150, 20, 40, 5, '#');
        init_object(&bricks[12], 210, 15, 10, 10, '+');

        movings.resize(2);
        init_object(&movings[0], 25, 10, 3, 2, 'o');
        init_object(&movings[1], 80, 10, 3, 2, 'o');
    }
    else if (lvl == 2){
        bricks.resize(6);
        init_object(&bricks[0], 20, 20, 40, 5, '#');
        init_object(&bricks[1], 60, 15, 10, 10, '#');
        init_object(&bricks[2], 80, 20, 20, 5, '#');
        init_object(&bricks[3], 120, 15, 10, 10, '#');
        init_object(&bricks[4], 150, 20, 40, 5, '#');
        init_object(&bricks[5], 210, 15, 10, 10, '+');

        movings.resize(6);
        init_object(&movings[0], 25, 10, 3, 2, 'o');
        init_object(&movings[1], 80, 10, 3, 2, 'o');
        init_object(&movings[2], 65, 10, 3, 2, 'o');
        init_object(&movings[3], 120, 10, 3, 2, 'o');
        init_object(&movings[4], 160, 10, 3, 2, 'o');
        init_object(&movings[5], 175, 10, 3, 2, 'o');
    }
    else if (lvl == 3){
        bricks.resize(4);
        init_object(&bricks[0], 20, 20, 40, 5, '#');
        init_object(&bricks[1], 80, 20, 15, 5, '#');
        init_object(&bricks[2], 110, 15, 20, 8, '#');
        init_object(&bricks[3], 145, 10, 15, 10, '+');

        movings.resize(6);
        init_object(&movings[0], 25, 10, 3, 2, 'o');
        init_object(&movings[1], 50, 10, 3, 2, 'o');
        init_object(&movings[2], 80, 10, 3, 2, 'o');
        init_object(&movings[3], 90, 10, 3, 2, 'o');
        init_object(&movings[4], 120, 10, 3, 2, 'o');
        init_object(&movings[5], 130, 10, 3, 2, 'o');
    }
}

void Game::update() {
    if (mario.IsFly == false && keySpace){
        mario.vertSpeed = - 1.1;
    }
    if (keyLeft) {
        move_map_horizontally(1.0f);
    }
    if (keyRight) {
        move_map_horizontally(-1.0f);
    }

    if (mario.y > mapHeight){
        player_dead();
    }

    move_obj_vertically(&mario);
    check_mario_collision();
    
    for (size_t i = 0; i < movings.size(); i++){
        move_obj_vertically(&movings[i]);
        move_obj_horizontally(&movings[i]);
        if (movings[i].y > mapHeight){
            delete_moving(i);
            i--;
            continue;
        }
    }
}

void Game::move_map_horizontally(float dx) {
    mario.x -= dx;
    for(const auto& brick : bricks){
        if (is_collision(&mario, &brick)){
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;
    for (auto& brick : bricks){
        brick.x += dx;
    }
    for (auto& moving : movings){
        moving.x += dx;
    }
}

void Game::move_obj_horizontally(TObject* obj) {
    obj->x += obj->horizSpeed;

    for (const auto& brick : bricks){
        if (is_collision(obj, &brick)){
            obj->x -= obj->horizSpeed;
            obj->horizSpeed = -obj->horizSpeed;
            return;
        }
    }
    if (obj->cType == 'o'){
        TObject tmp = *obj;
        tmp.IsFly = true;
        tmp.vertSpeed += 0.05;
        tmp.y += tmp.vertSpeed;
        
        bool supported = false;
        for (const auto& brick : bricks){
             if (is_collision(&tmp, &brick)){
                 supported = true;
                 break;
             }
        }
        
        
        TObject tempObj = *obj;
        tempObj.vertSpeed += 0.05;
        tempObj.y += tempObj.vertSpeed;
        bool collision = false;
        for(const auto& brick : bricks) {
            if(is_collision(&tempObj, &brick)) {
                collision = true;
                break;
            }
        }
        
        if (!collision) { 
             obj->x -= obj->horizSpeed;
             obj->horizSpeed = -obj->horizSpeed;
        }
    }
}

void Game::move_obj_vertically(TObject* obj) {
    obj->IsFly = true;
    obj->vertSpeed += 0.05;
    set_object_pos(obj, obj->x, obj->y + obj->vertSpeed);
    
    for (auto& brick : bricks){
        if (is_collision(obj, &brick)){
            if (obj->vertSpeed > 0){
                obj->IsFly = false;
            }
            if (brick.cType == '?' && obj->vertSpeed < 0 && obj == &mario){
                brick.cType = '-';
                
                TObject newMoving;
                init_object(&newMoving, brick.x, brick.y - 3, 3, 2, '$');
                newMoving.vertSpeed = -0.7;
                movings.push_back(newMoving);
            }
            
            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;
            
            if (brick.cType == '+' && obj == &mario){
                level++;
                if (level > maxLvl){
                    level = 1;
                }
                if (level == 1) {
                    score = 0;
                }
                create_level(level);
                levelStartScore = score;
            }
            break;
        }
    }
}

void Game::check_mario_collision() {
    for (size_t i = 0; i < movings.size(); i++){
        if (is_collision(&mario, &movings[i])){
            if (movings[i].cType == 'o'){
                if (mario.IsFly && mario.vertSpeed > 0 && (mario.y + mario.height < movings[i].y + movings[i].height * 0.5)){
                    score += 50;
                    delete_moving(i);
                    i--;
                    continue;
                }
                else{
                    player_dead();
                }
            }
            if (movings[i].cType == '$'){
                score += 100;
                delete_moving(i);
                i--;
                continue;
            }
        }
    }
}

void Game::player_dead() {
    score = levelStartScore;
    create_level(level);
}

void Game::delete_moving(int index) {
    if (index >= 0 && index < movings.size()) {
        movings.erase(movings.begin() + index);
    }
}

void Game::handleInput(int key, bool pressed) {
    if (key == 0) keyLeft = pressed;
    if (key == 1) keyRight = pressed;
    if (key == 2) keySpace = pressed;
}
