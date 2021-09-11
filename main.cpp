#include <iostream>
#include <raylib.h>
#include <fstream>	//write last score and maybe store in history file			//2 player (todo maybe)

using namespace std;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;
int main()
{
	bool titlescreen = true;
	bool intro = true;
	std::string name;
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Bad Ball Hitler (120 Target FPS)");
	InitAudioDevice();              // Initialize audio device
	Music music = LoadMusicStream("theme.mp3");
	Sound fxWav = LoadSound("border.wav");
	Sound fxlvlup = LoadSound("AUGUGHHGG.ogg");
	Sound fxlvldown = LoadSound("kraisofv.ogg");
	PlayMusicStream(music);
	ifstream my_file1("nicht oeffnen pls.txt");
	if (!my_file1.is_open())
	{
		my_file1.open("nicht oeffnen pls.txt");
		my_file1.close();
		ofstream mafile("nicht oeffnen pls.txt");;
		mafile << 0;
	}
	ifstream myfile("nicht oeffnen pls.txt");;
	int priorhs;
	myfile >> priorhs;
	int HS = priorhs;
	myfile.close();
	int score = 0;
	int fs = 0;
start:
	int cock = 0;
	int ballb = 10;
	ofstream my_file("nicht oeffnen pls.txt");
	if (score > HS)
	{
		my_file << score;
		my_file.close();
		ifstream myfile("nicht oeffnen pls.txt");;
		myfile >> HS;
		myfile.close();
	}
	score = 0;
	int highscoretest = 0;
	float i;
	int o;
	bool ballbad = true;						//ball bad
	bool ball2bad = true;						//ball bad2
	bool circle = 1;
	bool targetx = false;						//bad
	bool targety = false;						//bad
	bool target2x = false;						//bad2
	bool target2y = false;						//bad2
	bool collision = false;						//collision		
	Rectangle boxCollision = { 0 };				//collision
	Rectangle badboxcollision = { 0 };			//badcollision
	bool badcollision = false;					//badcollision
	Rectangle bad2boxcollision = { 0 };			//badcollision2
	bool bad2collision = false;					//badcollision2
	float PositionX;
	float PositionY;
	Vector2 target = { GetRandomValue(690, 100), rand() % 330 + 100 };									//bad ball movement
	Vector2 target2 = { GetRandomValue(690, 100), rand() % 330 + 100 };									//bad 2 ball movement
	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };							//ball spawn
	Vector2 hitlerball = { 100, 100 };																	//bad ball
	Vector2 eichmann = { 100, 100 };																	//bad 2 ball
	Vector2 ballPosition2 = { PositionX = rand() % 690 + 100, PositionY = rand() % 330 + 100 };			//ball eat spawn
	SetTargetFPS(120);																																	//build 2 versions (60 and 120 fps)  60 fps version 3 balls 120 = 2 balls
	float size = 5; //playable ball size
	Texture2D texture = LoadTexture("logo.png");
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		if (circle)
		{
			if (score == 9)
			{
				ballPosition2.x = 700;		//new position for eaten ball
				ballPosition2.y = 400;		//new position for eaten ball
			}
			else
			{
				ballPosition2.x = GetRandomValue(690, 100); //new position for eaten ball
				ballPosition2.y = rand() % 330 + 100;		//new position for eaten ball
			}
		}
		Rectangle boxA = { ballPosition.x, ballPosition.y, size * 2, size * 2};			//hitbox?  //collision
		Rectangle boxB = { ballPosition2.x, ballPosition2.y, size, size };				//hitbox?  //collision
		Rectangle boxC = { hitlerball.x, hitlerball.y, size, size };					//bad ball
		Rectangle boxD = { eichmann.x, eichmann.y, size + 10, size + 10 };				// bad 2 ball
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.5f;				//controls
		else if (IsKeyDown(KEY_D)) ballPosition.x += 2.5f;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.5f;				//controls
		else if (IsKeyDown(KEY_A)) ballPosition.x -= 2.5f;
		if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.5f;					//controls
		else if (IsKeyDown(KEY_W)) ballPosition.y -= 2.5f;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.5f;				//controls
		else if (IsKeyDown(KEY_S)) ballPosition.y += 2.5f;
		if (IsKeyReleased(KEY_F))
		{
			if (fs == 0)
			{
				fs = fs + 1;
			}
			else if (fs == 1)
			{
				fs = fs - 1;
			}
		}
		if (ballbad)													//bad
		{
			Vector2 target = { GetRandomValue(690, 100), rand() % 330 + 100 };
			ballbad = false;
		}
		if (targetx == false)
		{
			if (hitlerball.x > target.x)
			{
				hitlerball.x -= 1; //1 is the speed
			}
			else if (hitlerball.x < target.x)
			{
				hitlerball.x += 1; //1 is the speed
			}
			else if (hitlerball.x == target.x)
			{
				targetx = true;
			}
		}
		if (targety == false)
		{
			if (hitlerball.y > target.y)
			{
				hitlerball.y -= 1; //1 is the speed
			}
			else if (hitlerball.y < target.y)
			{
				hitlerball.y += 1; //1 is the speed
			}
			else if (hitlerball.y == target.y)
			{
				targety = true;
			}
		}
		if (targetx || targety)
		{
			//Vector2 target = { GetRandomValue(690, 100), rand() % 330 + 100 };
			target.x = GetRandomValue(690, 100);
			target.y = rand() % 330 + 100;
			ballbad = true;
			targetx = false;
			targety = false;
		}
		if (score >= 10)
		{
			if (ball2bad)													//bad
			{
				if (score == 10)
				{
					Vector2 target2 = { 0, 0 };
				}
				else
				{
					Vector2 target2 = { GetRandomValue(690, 100), rand() % 330 + 100 };
				}
				ball2bad = false;
			}
			if (target2x == false)
			{
				if (eichmann.x > target2.x)
				{
					eichmann.x -= 1; //1 is the speed
				}
				else if (eichmann.x < target2.x)
				{
					eichmann.x += 1; //1 is the speed
				}
				else if (eichmann.x == target2.x)
				{
					target2x = true;
				}
			}
			if (target2y == false)
			{
				if (eichmann.y > target2.y)
				{
					eichmann.y -= 1; //1 is the speed
				}
				else if (eichmann.y < target2.y)
				{
					eichmann.y += 1; //1 is the speed
				}
				else if (eichmann.y == target2.y)
				{
					target2y = true;
				}
			}
			if (target2x || target2y)
			{
				//Vector2 target = { GetRandomValue(690, 100), rand() % 330 + 100 };
				target2.x = GetRandomValue(690, 100);
				target2.y = rand() % 330 + 100;
				ball2bad = true;
				target2x = false;
				target2y = false;
			}
		}
		collision = CheckCollisionRecs(boxA, boxB);							//collision
		if (collision) boxCollision = GetCollisionRec(boxA, boxB);			//collision
		badcollision = CheckCollisionRecs(boxA, boxC);						//badcollision
		if (badcollision) badboxcollision = GetCollisionRec(boxA, boxC);	//badcollision
		if (score >= 10)
		{
			bad2collision = CheckCollisionRecs(boxA, boxD);						//badcollision2
			if (bad2collision) bad2boxcollision = GetCollisionRec(boxA, boxD);	//badcollision2
		}
		int cringe = 0;
		int yoinks = 0;
		BeginDrawing();
		ClearBackground(RAYWHITE);
		while (titlescreen)
		{
			cringe++;
			if (cringe == 300)
			{
				UnloadTexture(texture);
				titlescreen = false;
				break;
			}
			BeginDrawing();
			DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);		//random ass logo made in ms paint
			EndDrawing();
		}
		while (intro)
		{
			if (yoinks == 1)
			{
				UnloadTexture(texture);
				intro = false;
				break;
			}
			BeginDrawing();
			DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
			DrawText(TextFormat("W"), 100, 50, 100, LIGHTGRAY);
			DrawText(TextFormat("S"), 105, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("A"), 30, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("D"), 180, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("U"), 600, 50, 100, LIGHTGRAY);
			DrawText(TextFormat("D"), 605, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("L"), 530, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("R"), 680, 130, 100, LIGHTGRAY);
			DrawText(TextFormat("PRESS SPACE TO PLAY"), screenWidth / 2 - 125, screenHeight / 2 + 100, 20, LIGHTGRAY);
			DrawText(TextFormat("F"), screenWidth / 2, screenHeight / 2 + 150, 20, LIGHTGRAY);
			DrawText(TextFormat("FOR FPS"), screenWidth / 2 - 42, screenHeight / 2 + 170, 20, LIGHTGRAY);
			if (IsKeyPressed(KEY_SPACE)) yoinks = 1;
			EndDrawing();
		}
		int fps = GetFPS();
		if (fs == 1)
		{
			DrawText(TextFormat("%02i", fps), screenWidth / 2 - 1, 430, 20, LIGHTGRAY);	//displays fps
		}
		if (ballPosition.x + size >= 800) 					//world boarder check, if true, equal opposite force as movement
		{
			ballPosition.x -= 10.0f;
			PlaySound(fxWav);
		}
		if (ballPosition.x - size <= 0) 					//world boarder check, if true, equal opposite force as movement
		{
			ballPosition.x += 10.0f;
			PlaySound(fxWav);
		}
		if (ballPosition.y + size >= 450)					//world boarder check, if true, equal opposite force as movement
		{
			ballPosition.y -= 10.0f;
			PlaySound(fxWav);
		}
		if (ballPosition.y - size <= 0)					//world boarder check, if true, equal opposite force as movement
		{
			ballPosition.y += 10.0f;
			PlaySound(fxWav);
		}
		DrawText(TextFormat("%03i", HS), screenWidth / 2 - 10, 0, 20, LIGHTGRAY);
		DrawText(TextFormat("%03i", score), screenWidth / 2 - 160, screenHeight / 2 - 100, 200, LIGHTGRAY);
		DrawCircleV(ballPosition, size, MAROON);			//draw playable ball
		DrawCircleV(hitlerball, size, BLACK);
		if (score >= 10)
		{
			DrawCircleV(eichmann, size + 10, BLACK);
		}
		DrawCircleV(ballPosition2, ballb, BLUE);			//draw edible ball
		//DrawRectangle(ballPosition.x, ballPosition.y, size, size, MAROON);
		//DrawRectangle(ballPosition2.x, ballPosition2.y, 10, 10, BLUE);
		if (circle)		//prevents new coordinates for edible ball
		{
			circle = 0;
		}
		if (collision)
		{
			if (size != 50)								//and if belopw 10
			{
				size = size + 5;						//increase size untiil 10 times ball eaten
				highscoretest = highscoretest + 1;
			}
			if (highscoretest != 0)
			{
				score = score + 1;
			}
			PlaySound(fxlvlup);
			circle = 1;									//allow for new coordinates if ball eaten
		}
		if (badcollision)
		{
			PlaySound(fxlvldown);
			cout << "copyright PizzaWaifu\n";
			for (cock; cock < 100; cock++)
			{
				cout << ".\n";
			}
			goto start;
		}
		if (bad2collision)
		{
			PlaySound(fxlvldown);
			cout << "copyright pizzuswaifu\n";
			for (cock; cock < 100; cock++)
			{
				cout << ".\n";
			}
			goto start;
		}
		EndDrawing();
	}
	UnloadTexture(texture);
	UnloadMusicStream(music);   // Unload music stream buffers from RAM
	UnloadSound(fxWav);
	CloseAudioDevice();
	CloseWindow();
	ofstream mafile("nicht oeffnen pls.txt");;
	mafile << HS;
	mafile.close();
	return 0;
}