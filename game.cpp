#include "game.hpp"
#include "font8x16_png.h"
#include "sprites_png.h"
#include "palettes.hpp"
#include "wiiInput.hpp"
#include <stdlib.h>
#include "wiiuse/wpad.h"

// Input
static WiiInput input;

// Sprite indices

static const short tilesPerRow = 49;

static short getSpriteIndex(short x, short y)
{
    return tilesPerRow * y + x;
}

static float randf() 
{
    return (float)rand()/(float)RAND_MAX;
}

const short playerIndex = getSpriteIndex(24, 1);
const short treeIndex = getSpriteIndex(0,1);
const short orcIndex = getSpriteIndex(25, 2);
const short cursorIndex = getSpriteIndex(19, 14);
const short heartIndex = getSpriteIndex(39, 10);
const short cheeseIndex = getSpriteIndex(34, 16);
const short fireIndex = getSpriteIndex(15, 10);
const short amount = 128;

static Unit CreateUnit(short x, short y, float speed, short index)
{
    return {glm::vec2(x, y), glm::vec2(0,0), speed, index};
}

bool Game::Init()
{
    bool fontOk = fontImage.LoadImageBuffer(font8x16_png, font8x16_png_size, gdl::Nearest, gdl::RGBA8);
    if (fontOk)
    {
        font.BindSheet(fontImage, 8, 16);
    }
// 0x28282eFF,
    gdl::SetClearColor(0x28, 0x28, 0x2e, 0xFF);

    // TODO Make a sprite system 
    fontOk = fontOk && spriteSheet.LoadImageBuffer(sprites_png, sprites_png_size, gdl::Nearest, gdl::RGBA8);

    gdl::SpriteSetConfig cfg = {1078, 22, tilesPerRow, 16, 16};
    fontOk = fontOk && sprites.LoadSprites(cfg, &spriteSheet);

    // Create units
    srand(0);
    short w = gdl::ScreenXres;
    short h = gdl::ScreenYres;
    player = CreateUnit(w/2, h/2, 2.0f, playerIndex);
    enemies.reserve(amount);
    fires.reserve(amount);
    trees.reserve(amount);
    for (short i = 0; i < amount; i++) {
        enemies.push_back(CreateUnit(rand()%w, rand()%h, 0.1f + randf() * 1.1f, orcIndex));
        trees.push_back(CreateUnit(rand()%w, rand()%h, 0.0f, treeIndex));
        fires.push_back(CreateUnit(0, 0, 0.0f, fireIndex));
    }
    cursor = CreateUnit(w/2, h/2, 0.0f, cursorIndex);


    score = 0;
    fireRingIndex = 0;
    input.Init();

    return fontOk;
}

void Game::Run()
{


}

void Game::Update()
{
    input.StartFrame();
    for (short u = 0; u < 5; u++)
    {
        short upi = rand()%amount;
        glm::vec2 toPlayer = player.position - enemies[upi].position;
        if (glm::length(toPlayer) < 16)
        {
            enemies[upi].direction = glm::vec2(0,0);
        }
        else 
        {
            enemies[upi].direction = glm::normalize(toPlayer);
        }
        fires[upi].position += glm::vec2(randf()*0.1f -0.05f, randf()*0.1f -0.05f);
    }
    for (short i = 0; i < amount; i++) {
        UpdateUnit(enemies[i]);
        fires[i].speed -= gdl::Delta;
    }

    cursor.position = input.GetCursorPosition();
    if (input.ButtonHeld(WIIMOTE_BUTTON_A))
    {
        fires[fireRingIndex].speed = 300.0f;
        fires[fireRingIndex].position = cursor.position;
        fireRingIndex = (fireRingIndex + 1) % amount;
    }
    player.direction = input.GetNunchukJoystickDirection(0.1f);

    UpdateUnit(player);
}

void Game::UpdateUnit(Unit &u)
{
    u.position += u.direction * u.speed * gdl::Delta;
}

void Game::DrawUnit(Unit &u)
{
    sprites.Put(u.position.x, u.position.y, u.spriteIndex);
}

void Game::Draw()
{
    font.DrawText("Firemancer", 10, 10, 2, palette[6]);
    font.Printf(10, 10 + 2 * 16, 2, palette[2], "Score %d", score);

    for (short i = 0; i < amount; i++) {
        DrawUnit(enemies[i]);
        DrawUnit(trees[i]);
        if (fires[i].speed > 0.0f) {
            DrawUnit(fires[i]);
        }
    }
    DrawUnit(player);
    DrawUnit(cursor);
}