#ifndef GAME_H
#define GAME_H

#include <vector>
#include <cmath>

struct TObject{
    float x,y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
    float horizSpeed;
};

class Game {
public:
    Game();
    ~Game();

    void init();
    void update();
    void handleInput(int key, bool pressed);
    
    const TObject& getMario() const { return mario; }
    const std::vector<TObject>& getBricks() const { return bricks; }
    const std::vector<TObject>& getMovings() const { return movings; }
    int getScore() const { return score; }
    int getLevel() const { return level; }
    float getMapWidth() const { return mapWidth; }
    float getMapHeight() const { return mapHeight; }

    bool keyLeft = false;
    bool keyRight = false;
    bool keySpace = false;

private:
    void create_level(int lvl);
    void check_mario_collision();
    void move_map_horizontally(float dx);
    void move_obj_horizontally(TObject* obj);
    void move_obj_vertically(TObject* obj);
    void player_dead();
    bool is_collision(const TObject* o1, const TObject* o2);
    void init_object(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType);
    void set_object_pos(TObject *obj, float xPos, float yPos);
    void delete_moving(int index);

    TObject mario;
    std::vector<TObject> bricks;
    std::vector<TObject> movings;
    
    int level = 1;
    int score = 0;
    int levelStartScore = 0;
    int maxLvl = 3;
    
    const float mapWidth = 80;
    const float mapHeight = 25;
};

#endif 
