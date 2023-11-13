#pragma once

const int ScreenWidth = 800;
const int ScreenHeight = 600;

const float Gravity = 180.0f;
const float JumpYVelocity = -230.0f;

const float PlayerHeight = 60.0f;
const float PlayerWidth = 40.0f;
const float PlayerSpeed = 155.0f;
const float PlayerJumpTime = 0.7f;
const float PlayerDefaultSpawnX = ScreenWidth * 0.5f;
const float PlayerDefaultSpawnY = ScreenHeight * 0.5f;

const float CoinRadius = 17.0f;

const float BallRadius = 5.0f;
const float BallBounciness = 0.9f;
const int   BallMaxCount = 3;
const float BallReloadTime = 3.0f;
const float BallThrowDelay = 0.5f;
const float BallOffsetToMouse = 2.0f;
const float BallLifetime = 10.0f;

const int GridSize = 16;

const float TileSizeX = ScreenWidth / (float)GridSize;
const float TileSizeY = ScreenHeight / (float)GridSize;
