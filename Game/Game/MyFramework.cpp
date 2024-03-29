#include "MyFramework.h"
#include <stdio.h>
#include "Platform.h"
#include "Ball.h"
#include <math.h>
#include "Utils.h"
#include "enumSide.h"
#include "ShieldBonus.h"
#include "ShieldObj.h"
#include "GameState.h"
#include "BounceResult.h"
#include "Brick.h"
#include "BombObj.h"

GameState gs = GameState::Init;
const int brickMapW = 11;
const int brickMapH = 6;
const int totalBricks = brickMapW * brickMapH;
int bricksDestroyed = 0;

const float NORMAL_LEFT[2] = { -1, 0 };
const float NORMAL_RIGHT[2] = { 1, 0 };
const float NORMAL_DOWN[2] = { 0, 1 };
const float NORMAL_UP[2] = { 0, -1 };
float NORMAL_LEFT_UP[2] = { -1, -1 };
float NORMAL_RIGHT_UP[2] = { 1, -1 };

Brick brickMap[brickMapH][brickMapW];
ShieldBonus shieldBonus;
ShieldObj shieldObj;
BombObj bomb;
Ball ball;
Platform platform;
bool shieldActive = false;
bool shieldBonusExists = false;
bool bombExists = false;
unsigned int shieldLiveTicks = 0;


#pragma region DeltaTicks
unsigned int deltaTicks = 0;
unsigned int lastTicks = 0;

void calculateDeltaTicks()
{
	int ticks = getTickCount();
	deltaTicks = ticks - lastTicks;
	lastTicks = ticks;
}
#pragma endregion DeltaTicks

#pragma region Map
int mWidth;
int mHeight;

Brick createBrick(int posX, int posY, const char* spritePath, int width = 0, int height = 0)
{
	Sprite* s = createSprite(spritePath);
	setSpriteSize(s, width, height);
	Brick b = Brick(posX, posY, s, width, height);
	
	return b;
}

void fillBrickMap()
{
	int brickW = mWidth / brickMapW;
	int brickH = brickW / 3;

	int wOffset = 0;
	int hOffset = 0;

	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			brickMap[i][k] = createBrick(wOffset, hOffset, "data/12.png", brickW, brickH);
			wOffset += brickW;
		}
		wOffset = 0;
		hOffset += brickH;
	}
}

void drawBrickMap()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (brickMap[i][k].destroyed == false)
			{
				drawSprite(brickMap[i][k].sprite, brickMap[i][k].posX, brickMap[i][k].posY);
#if defined(DEBUG_G)
#pragma region DEBUG
				drawSprite(brickMap[i][k].d_s_0, brickMap[i][k].upCenterBorderPos[0], brickMap[i][k].upCenterBorderPos[1]);
				drawSprite(brickMap[i][k].d_s_1, brickMap[i][k].downCenterBorderPos[0], brickMap[i][k].downCenterBorderPos[1]);
				drawSprite(brickMap[i][k].d_s_2, brickMap[i][k].rightCenterBorderPos[0], brickMap[i][k].rightCenterBorderPos[1]);
				drawSprite(brickMap[i][k].d_s_3, brickMap[i][k].leftCenterBorderPos[0], brickMap[i][k].leftCenterBorderPos[1]);
#pragma endregion DEBUG
#endif

			}
		}
	}
}

void moveBricksDown()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (brickMap[i][k].destroyed == false)
			{
				brickMap[i][k].Move(0, mHeight/500 * 0.005f);
			}
		}
	}
}

bool checkBrickFallCompletelly()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (brickMap[i][k].posY + brickMap[i][k].h >= mHeight)
			{
				return true;
			}
		}
	}
	return false;
}

void checkBonusesFallCompletelly()
{
	if (bomb.posY + bomb.h >= mHeight)
	{
		bombExists = false;
	}
	
	if (shieldBonus.posY + shieldBonus.h >= mHeight)
	{
		shieldBonusExists = false;
	}
}

void createShieldBonus(Brick b)
{
	shieldBonus = ShieldBonus(b.posX, b.posY, b.w, b.h);
	shieldBonusExists = true;
}

void createBomb(Brick b)
{
	bomb = BombObj(b.posX, b.posY, b.w, b.h);
	bombExists = true;
}
#pragma endregion Map

#pragma region Platform
bool movingLeft = false;
bool movingRight = false;

void createPlatform()
{
	int pW = mWidth / brickMapW * 2;
	int pH = pW / 4;
	platform = Platform((mWidth * 0.5f) - (pW * 0.5f), mHeight - pH, pW, pH);
	platform.hp = 3;
}

void drawPlatform()
{
	drawSprite(platform.GetSprite(), platform.posX, platform.posY);
#if defined(DEBUG_G)
#pragma region DEBUG
	drawSprite(platform.d_s_0, platform.upCenterBorderPos[0], platform.upCenterBorderPos[1]);
	drawSprite(platform.d_s_1, platform.downCenterBorderPos[0], platform.downCenterBorderPos[1]);
	drawSprite(platform.d_s_2, platform.rightCenterBorderPos[0], platform.rightCenterBorderPos[1]);
	drawSprite(platform.d_s_3, platform.leftCenterBorderPos[0], platform.leftCenterBorderPos[1]);
#pragma endregion DEBUG
#endif
}

void tryMovePlatform()
{
	int xVel = 0;

	if (movingRight && platform.posX + platform.w < mWidth)
	{
		xVel = deltaTicks;
		platform.MoveHorisontal(xVel);
	}
	else if (movingLeft && platform.posX > 0)
	{
		xVel = deltaTicks * -1;
		platform.MoveHorisontal(xVel);
	}
}

bool checkBrickCollisionWithPlatform()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (platform.CheckCollideSide(brickMap[i][k], enumSide::Up))
			{
				return true;
			}
		}
	}
	return false;
}

bool checkShieldBonusCollision()
{
	if (shieldBonusExists)
	{
		if (platform.CheckCollideSide(shieldBonus, enumSide::Up))
		{
			shieldBonusExists = false;
			shieldActive = true;
			return true;
		}
	}
}

bool checkBombCollision()
{
	if (bombExists)
	{
		if (platform.CheckCollideSide(bomb, enumSide::Up))
		{
			platform.GetDamage(bomb.damage);
			if (platform.hp <= 0)
			{
				gs = GameState::End;
			}
			bombExists = false;
			return true;
		}
	}
}

bool checkShieldBonusCollisionWithBricks()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (shieldBonus.CheckCollideSide(brickMap[i][k], enumSide::Down))
			{
				return true;
			}
		}
	}
	return false;
}

bool checkBombCollisionWithBricks()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (bomb.CheckCollideSide(brickMap[i][k], enumSide::Down))
			{
				return true;
			}
		}
	}
	return false;
}
#pragma endregion Platform

#pragma region Ball

void createBall()
{
	int bW = platform.w / 10;
	int bH = bW;
	ball = Ball(platform.centerPosX - bW / 2, platform.centerPosY, bW, bH);
}

void drawBall()
{
	drawSprite(ball.sprite0, ball.posX, ball.posY);
#if defined(DEBUG_G)
#pragma region DEBUG
	drawSprite(ball.d_s_0, ball.upCenterBorderPos[0], ball.upCenterBorderPos[1]);
	drawSprite(ball.d_s_1, ball.downCenterBorderPos[0], ball.downCenterBorderPos[1]);
	drawSprite(ball.d_s_2, ball.rightCenterBorderPos[0], ball.rightCenterBorderPos[1]);
	drawSprite(ball.d_s_3, ball.leftCenterBorderPos[0], ball.leftCenterBorderPos[1]);
#pragma endregion DEBUG
#endif DEBUG
}

void tryMoveBall()
{
	int bW = platform.w / 10;
	int bH = bW;
	switch (gs)
	{
		case GameState::Init:
			ball.SetPos(platform.centerPosX - bW / 2, platform.posY - bH);
			break;
		case GameState::Playing:
			ball.MoveToDir();
			break;
		case GameState::End:
			break;
		default:
			break;
	}
}

BounceResult tryBounceBallFromWall()
{
	if (ball.rightCenterBorderPos[0] >= mWidth)
	{
		ball.Bounce(NORMAL_LEFT);
		return BounceResult::Left;
	}

	if (ball.leftCenterBorderPos[0] <= 0)
	{
		ball.Bounce(NORMAL_RIGHT);
		return BounceResult::Right;
	}

	if (ball.downCenterBorderPos[1] >= mHeight)
	{
		ball.Bounce(NORMAL_UP);
		return BounceResult::Up;
	}

	if (ball.upCenterBorderPos[1] <= 0)
	{
		ball.Bounce(NORMAL_DOWN);
		return BounceResult::Down;
	}

	return BounceResult::None;
}

BounceResult tryBounceFromPlatform()
{
	if (ball.CheckCollideSide(platform, enumSide::Down))
	{
		ball.Bounce(NORMAL_UP);
		return BounceResult::Up;
	}

	if (ball.CheckCollideSide(platform, enumSide::Right))
	{
		ball.dir[0] = (NORMAL_LEFT_UP[0]);
		ball.dir[1] = (NORMAL_LEFT_UP[1]);
		return BounceResult::LeftUp;
	}
	
	if (ball.CheckCollideSide(platform, enumSide::Left))
	{
		ball.dir[0] = (NORMAL_RIGHT_UP[0]);
		ball.dir[1] = (NORMAL_RIGHT_UP[1]);
		return BounceResult::RightUp;
	}
	return BounceResult::None;
}

bool trySpawnShieldBonus(Brick* b)
{
	if (shieldActive == false && shieldBonusExists == false)
	{
		if (b->TrySpawn())
		{
			createShieldBonus(*b);
			shieldLiveTicks = 0;
			return true;
		}
	}
	return false;
}

bool trySpawnBomb(Brick* b)
{
	if (bombExists == false)
	{
		if (b->TrySpawn())
		{
			createBomb(*b);
			return true;
		}
	}
	return false;
}

BounceResult tryBounceFromBrick()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (ball.CheckCollideSide(brickMap[i][k], enumSide::Down))
			{
				ball.Bounce(NORMAL_UP);
				if (trySpawnShieldBonus(&brickMap[i][k]) == false)
				{
					trySpawnBomb(&brickMap[i][k]);
				}
				brickMap[i][k].Destroy();
				bricksDestroyed++;
				return BounceResult::Up;
			}
			else if (ball.CheckCollideSide(brickMap[i][k], enumSide::Up))
			{
				ball.Bounce(NORMAL_DOWN);
				if (trySpawnShieldBonus(&brickMap[i][k]) == false)
				{
					trySpawnBomb(&brickMap[i][k]);
				}
				brickMap[i][k].Destroy();
				bricksDestroyed++;
				return  BounceResult::Down;
			}
			else if (ball.CheckCollideSide(brickMap[i][k], enumSide::Right))
			{
				ball.Bounce(NORMAL_LEFT);
				if (trySpawnShieldBonus(&brickMap[i][k]) == false)
				{
					trySpawnBomb(&brickMap[i][k]);
				}
				brickMap[i][k].Destroy();
				bricksDestroyed++;
				return BounceResult::Left;
			}
			else if (ball.CheckCollideSide(brickMap[i][k], enumSide::Left))
			{
				ball.Bounce(NORMAL_RIGHT);
				if (trySpawnShieldBonus(&brickMap[i][k]) == false)
				{
					trySpawnBomb(&brickMap[i][k]);
				}
				brickMap[i][k].Destroy();
				bricksDestroyed++;
				return BounceResult::Right;
			}
		}
	}
	return BounceResult::None;
}

BounceResult tryBounceFromShieldObject()
{
	if (ball.CheckCollideSide(shieldObj, enumSide::Down))
	{
		ball.Bounce(NORMAL_UP);
		return BounceResult::Up;
	}
	else if (ball.CheckCollideSide(shieldObj, enumSide::Up))
	{
		ball.Bounce(NORMAL_DOWN);
		return  BounceResult::Down;
	}
	else if (ball.CheckCollideSide(shieldObj, enumSide::Right))
	{
		ball.Bounce(NORMAL_LEFT);
		return BounceResult::Left;
	}
	else if (ball.CheckCollideSide(shieldObj, enumSide::Left))
	{
		ball.Bounce(NORMAL_RIGHT);
		return BounceResult::Right;
	}
	return BounceResult::None;
}
#pragma endregion Ball

#pragma region MyFramework
MyFramework::MyFramework(int nW, int nH)
{
	w = nW;
	h = nH;
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = w;
	height = h;
	mWidth = width;
	mHeight = height;
	fullscreen = false;
}

bool MyFramework::Init() {
	bricksDestroyed = 0;
	fillBrickMap();
	createPlatform();
	createBall();
	shieldBonusExists = false;
	shieldActive = false;
	bombExists = false;
	shieldObj = ShieldObj(0, mHeight -2, createSprite("data/10.png"), mWidth, 4);
	setSpriteSize(shieldObj.sprite, mWidth, 4);
	showCursor(true);
	Utils::normalize(NORMAL_LEFT_UP);
	Utils::normalize(NORMAL_RIGHT_UP);
	return true;
}

void MyFramework::Close() {

}

bool MyFramework::Tick() {
	calculateDeltaTicks();

	drawTestBackground();
	Sprite* back = createSprite("data/17.png");
	setSpriteSize(back, mWidth, mHeight);
	drawSprite(back, 0, 0);
	drawBrickMap();
	drawPlatform();
	
	drawBall();
	tryMovePlatform();
	tryMoveBall();
	BounceResult bounceResult = BounceResult::None;

	switch (gs)
	{
	case GameState::Init:
		break;
	case GameState::Playing:
#pragma region CheckWallsBounce
		bounceResult = tryBounceBallFromWall();
		if (bounceResult == BounceResult::Up)
		{
			gs = GameState::End;
		}
#pragma endregion CheckWallsBounce

#pragma region CheckPlatformBounce
		tryBounceFromPlatform();
#pragma endregion CheckPlatformBounce
		tryBounceFromBrick();

		if (shieldBonusExists)
		{
			drawSprite(shieldBonus.sprite, shieldBonus.posX, shieldBonus.posY);
			if (checkShieldBonusCollisionWithBricks() == false)
			{
				shieldBonus.MoveToDir();
			}
		}
		if (bombExists)
		{
			drawSprite(bomb.sprite, bomb.posX, bomb.posY);
			if (checkBombCollisionWithBricks() == false)
			{
				bomb.MoveToDir();
			}
		}
		checkShieldBonusCollision();
		checkBombCollision();
		if (shieldActive)
		{
			shieldLiveTicks += deltaTicks;
			drawSprite(shieldObj.sprite, shieldObj.posX, shieldObj.posY);
			tryBounceFromShieldObject();
			if (shieldLiveTicks >= 10000)
			{
				shieldActive = false;
			}
		}
		checkBonusesFallCompletelly();

		moveBricksDown();
		if (bricksDestroyed >= totalBricks || checkBrickCollisionWithPlatform() || checkBrickFallCompletelly())
		{
			gs = GameState::End;
		}
		break;
	case GameState::End:
		Init();
		gs = GameState::Init;
		break;
	default:
		break;
	}	

	
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	if (gs == GameState::Init)
	{
		ball.dir[0] = x - ball.posX;
		ball.dir[1] = y - ball.posY;

		Utils::normalize(ball.dir);
	}
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (gs == GameState::Init)
	{
		gs = GameState::Playing;
		showCursor(false);
	}
}

void MyFramework::onKeyPressed(FRKey k) {
	if (k == FRKey::RIGHT)
	{
		movingLeft = false;
		movingRight = true;
	}
	else if (k == FRKey::LEFT)
	{
		movingLeft = true;
		movingRight = false;
		platform.MoveHorisontal(deltaTicks * -1);
	}
}

void MyFramework::onKeyReleased(FRKey k) {
	if (k == FRKey::RIGHT)
	{
		movingRight = false;
	}
	else if (k == FRKey::LEFT)
	{
		movingLeft = false;
	}
}

unsigned int MyFramework::GetDeltaTicks()
{
	return deltaTicks;
}

const char* MyFramework::GetTitle()
{
	return "Arcanoid";
}
#pragma endregion MyFramework