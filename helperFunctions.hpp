#pragma once
#include "include/raylib.h"

#include <stdint.h>

#define SpriteFlipNone 0
#define SpriteFlipX 0x02
#define SpriteFlipY 0x04
#define SpriteFlipDiagonal 0x08



void InitResources();
void InitAudio();

int LoadSoundFile(const char* sound_file);

void UpdateLoad();
void UpdateAudio();

void FinalizeLoad();

void PlaySound(int sound);

void StartBGM(const char* music_file);
void StopBGM();

void ShutdownAudio();

void CleanupResources();

Texture& GetTexture(int id);
// const Texture& GetTexture(int id);

void LoadSpriteFrames(int texture_id, int columns, int rows, int spacing);
void SetSpriteOrigin(int sprite_id, int x, int y);
void SetSpriteBorders(int sprite_id, int left, int top, int right, int bottom);
void SetSpriteBorders(int sprite_id, int inset);
void CenterSprite(int sprite_id);

// void DrawSprite(int sprite_id, float x, float y, float rotation = 0, float scale = 1, Color tint = { 255, 255, 255, 255 }, uint8_t flip = SpriteFlipNone);
void FillRectWithSprite(int sprite_id, const Rectangle& rect, Color tint = { 255, 255, 255, 255 }, uint8_t flip = SpriteFlipNone);

void SetupWindow();
