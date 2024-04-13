#pragma once
#include <mgdl-wii.h>
#include "glm/glm.hpp"
#include <vector>

struct Unit
{
    glm::vec2 position;
    glm::vec2 direction;
    float speed;
    short spriteIndex;
};


class Game
{
    public:
        bool Init();
        void Run();
        void Update();
        void Draw();

    private:
        void DrawUnit(Unit &u);
        void UpdateUnit(Unit &u);
        gdl::Image	fontImage;
        gdl::FFont	font;

        gdl::Image spriteSheet;
        gdl::SpriteSet sprites;

        Unit player;
        Unit cursor;

        std::vector<Unit> enemies;
        std::vector<Unit> trees;
        std::vector<Unit> fires;
        short fireRingIndex;

        // Game state
        short score;
};
