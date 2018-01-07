#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	const float turnSpeed = 0.3f;
	const float splashSpeed = 0.1f;
	movementsDone.assign(32, 0);
	moduleCollision = new ModuleCollision();

	// Put checkpoints to false
	for (int i = 0; i < 8; i++)
	{
		checkpoint.push_back(false);
	}

	// Add player checkpoints
	/*1*/
	for (float i = 160; i < 179; i++)
	{
		checkpoint1.push_back({ 135, i });
	}
	/*2*/
	for (float i = 112; i < 177; i++)
	{
		checkpoint2.push_back({ i, 85 });
	}
	/*3*/
	for (float i = 58; i < 81; i++)
	{
		checkpoint3.push_back({ 220, i });
	}
	/*4*/
	for (float i = 228; i < 268; i++)
	{
		checkpoint4.push_back({ i, 50 });
	}
	/*5*/
	for (float i = 22; i < 44; i++)
	{
		checkpoint5.push_back({ 90, i });
	}
	/*6*/
	for (float i = 26; i < 66; i++)
	{
		checkpoint6.push_back({ i, 95 });
	}
	/*7*/
	for (float i = 100; i < 130; i++)
	{
		checkpoint7.push_back({ 220, i });
	}
	/*8*/
	for (float i = 220; i < 253; i++)
	{
		checkpoint8.push_back({ i, 150 });
	}

	// turn animation
	turn.frames.push_back({ 35, 12, 16, 9 });
	turn.frames.push_back({ 11, 12, 15, 9 });
	turn.frames.push_back({ 739, 11, 16, 10 });
	turn.frames.push_back({ 715, 10, 15, 11 });
	turn.frames.push_back({ 691, 9, 14, 12 });
	turn.frames.push_back({ 667, 9, 13, 12 });
	turn.frames.push_back({ 643, 9, 10, 12 });
	turn.frames.push_back({ 627, 8, 9, 13 });
	turn.frames.push_back({ 603, 8, 10, 13 });
	turn.frames.push_back({ 579, 8, 12, 13 });
	turn.frames.push_back({ 555, 8, 13, 13 });
	turn.frames.push_back({ 531, 8, 13, 13 });
	turn.frames.push_back({ 507, 8, 15, 13 });
	turn.frames.push_back({ 483, 9, 15, 12 });
	turn.frames.push_back({ 459, 10, 15, 11 });
	turn.frames.push_back({ 435, 10, 14, 11 });
	turn.frames.push_back({ 411, 11, 15, 10 });
	turn.frames.push_back({ 387, 12, 15, 9 });
	turn.frames.push_back({ 363, 12, 15, 9 });
	turn.frames.push_back({ 339, 11, 15, 10 });
	turn.frames.push_back({ 315, 10, 14, 11 });
	turn.frames.push_back({ 291, 9, 12, 12 });
	turn.frames.push_back({ 267, 9, 11, 12 });
	turn.frames.push_back({ 251, 9, 9, 12 });
	turn.frames.push_back({ 227, 9, 10, 12 });
	turn.frames.push_back({ 203, 9, 12, 12 });
	turn.frames.push_back({ 179, 9, 14, 12 });
	turn.frames.push_back({ 155, 9, 14, 12 });
	turn.frames.push_back({ 131, 9, 15, 12 });
	turn.frames.push_back({ 107, 10, 16, 11 });
	turn.frames.push_back({ 83, 10, 16, 11 });
	turn.frames.push_back({ 59, 11, 16, 10 });
	turn.speed = turnSpeed;

	// little bump right side animation
	littleBumpRightSide.frames.push_back({ 403, 203, 15, 10 });
	littleBumpRightSide.frames.push_back({ 35, 201, 15, 12 });
	littleBumpRightSide.frames.push_back({ 11, 249, 15, 12 });
	littleBumpRightSide.frames.push_back({ 11, 199, 16, 14 });
	littleBumpRightSide.frames.push_back({ 347, 248, 15, 13 });
	littleBumpRightSide.frames.push_back({ 331, 271, 13, 14 });
	littleBumpRightSide.frames.push_back({ 331, 221, 11, 16 });
	littleBumpRightSide.frames.push_back({ 307, 221, 10, 16 });
	littleBumpRightSide.frames.push_back({ 283, 221, 11, 16 });
	littleBumpRightSide.frames.push_back({ 259, 221, 13, 16 });
	littleBumpRightSide.frames.push_back({ 659, 30, 13, 15 });
	littleBumpRightSide.frames.push_back({ 635, 31, 14, 14 });
	littleBumpRightSide.frames.push_back({ 611, 33, 14, 12 });
	littleBumpRightSide.frames.push_back({ 243, 105, 15, 12 });
	littleBumpRightSide.frames.push_back({ 587, 35, 14, 10 });
	littleBumpRightSide.frames.push_back({ 219, 108, 16, 9 });
	littleBumpRightSide.frames.push_back({ 619, 82, 16, 11 });
	littleBumpRightSide.frames.push_back({ 627, 132, 15, 9 });
	littleBumpRightSide.frames.push_back({ 603, 130, 15, 11 });
	littleBumpRightSide.frames.push_back({ 579, 128, 15, 13 });
	littleBumpRightSide.frames.push_back({ 555, 126, 15, 15 });
	littleBumpRightSide.frames.push_back({ 531, 125, 13, 16 });
	littleBumpRightSide.frames.push_back({ 515, 173, 12, 16 });
	littleBumpRightSide.frames.push_back({ 499, 102, 8, 15 });
	littleBumpRightSide.frames.push_back({ 475, 101, 13, 16 });
	littleBumpRightSide.frames.push_back({ 107, 55, 12, 14 });
	littleBumpRightSide.frames.push_back({ 83, 55, 14, 14 });
	littleBumpRightSide.frames.push_back({ 59, 56, 15, 13 });
	littleBumpRightSide.frames.push_back({ 107, 298, 10, 11 });
	littleBumpRightSide.frames.push_back({ 83, 299, 14, 10 });
	littleBumpRightSide.frames.push_back({ 427, 204, 16, 9 });
	littleBumpRightSide.frames.push_back({ 59, 203, 15, 10 });
	littleBumpRightSide.speed = turnSpeed;

	// little bump left side animation
	littleBumpLeftSide.frames.push_back({ 11, 83, 15, 10 });
	littleBumpLeftSide.frames.push_back({ 11, 132, 13, 9 });
	littleBumpLeftSide.frames.push_back({ 731, 85, 13, 8 });
	littleBumpLeftSide.frames.push_back({ 723, 107, 13, 10 });
	littleBumpLeftSide.frames.push_back({ 715, 247, 15, 14 });
	littleBumpLeftSide.frames.push_back({ 691, 246, 13, 15 });
	littleBumpLeftSide.frames.push_back({ 675, 246, 9, 15 });
	littleBumpLeftSide.frames.push_back({ 683, 270, 9, 15 });
	littleBumpLeftSide.frames.push_back({ 643, 197, 10, 16 });
	littleBumpLeftSide.frames.push_back({ 619, 198, 11, 15 });
	littleBumpLeftSide.frames.push_back({ 595, 197, 12, 16 });
	littleBumpLeftSide.frames.push_back({ 571, 198, 12, 15 });
	littleBumpLeftSide.frames.push_back({ 603, 247, 13, 14 });
	littleBumpLeftSide.frames.push_back({ 579, 246, 13, 15 });
	littleBumpLeftSide.frames.push_back({ 555, 199, 9, 14 });
	littleBumpLeftSide.frames.push_back({ 555, 249, 13, 12 });
	littleBumpLeftSide.frames.push_back({ 563, 275, 12, 10 });
	littleBumpLeftSide.frames.push_back({ 531, 253, 12, 8 });
	littleBumpLeftSide.frames.push_back({ 539, 276, 10, 9 });
	littleBumpLeftSide.frames.push_back({ 539, 34, 12, 11 });
	littleBumpLeftSide.frames.push_back({ 507, 253, 10, 8 });
	littleBumpLeftSide.frames.push_back({ 523, 59, 12, 10 });
	littleBumpLeftSide.frames.push_back({ 131, 32, 9, 13 });
	littleBumpLeftSide.frames.push_back({ 483, 77, 9, 16 });
	littleBumpLeftSide.frames.push_back({ 107, 33, 11, 12 });
	littleBumpLeftSide.frames.push_back({ 483, 55, 12, 14 });
	littleBumpLeftSide.frames.push_back({ 83, 34, 13, 11 });
	littleBumpLeftSide.frames.push_back({ 59, 79, 14, 14 });
	littleBumpLeftSide.frames.push_back({ 459, 55, 15, 14 });
	littleBumpLeftSide.frames.push_back({ 435, 57, 16, 12 });
	littleBumpLeftSide.frames.push_back({ 59, 35, 16, 10 });
	littleBumpLeftSide.frames.push_back({ 35, 37, 16, 8 });
	littleBumpLeftSide.speed = turnSpeed;

	// little bump bottom side animation
	littleBumpBottomSide.frames.push_back({ 403, 301, 15, 8 });
	littleBumpBottomSide.frames.push_back({ 11, 300, 15, 9 });
	littleBumpBottomSide.frames.push_back({ 731, 296, 15, 13 });
	littleBumpBottomSide.frames.push_back({ 355, 297, 16, 12 });
	littleBumpBottomSide.frames.push_back({ 715, 224, 16, 13 });
	littleBumpBottomSide.frames.push_back({ 691, 223, 15, 14 });
	littleBumpBottomSide.frames.push_back({ 683, 198, 11, 15 });
	littleBumpBottomSide.frames.push_back({ 667, 197, 9, 16 });
	littleBumpBottomSide.frames.push_back({ 643, 197, 10, 16 });
	littleBumpBottomSide.frames.push_back({ 619, 198, 11, 15 });
	littleBumpBottomSide.frames.push_back({ 659, 269, 12, 16 });
	littleBumpBottomSide.frames.push_back({ 635, 270, 15, 15 });
	littleBumpBottomSide.frames.push_back({ 611, 271, 16, 14 });
	littleBumpBottomSide.frames.push_back({ 587, 274, 15, 11 });
	littleBumpBottomSide.frames.push_back({ 587, 35, 14, 10 });
	littleBumpBottomSide.frames.push_back({ 219, 108, 16, 9 });
	littleBumpBottomSide.frames.push_back({ 595, 84, 16, 9 });
	littleBumpBottomSide.frames.push_back({ 563, 38, 14, 7 });
	littleBumpBottomSide.frames.push_back({ 571, 84, 15, 9 });
	littleBumpBottomSide.frames.push_back({ 571, 154, 15, 11 });
	littleBumpBottomSide.frames.push_back({ 547, 154, 16, 11 });
	littleBumpBottomSide.frames.push_back({ 523, 151, 14, 14 });
	littleBumpBottomSide.frames.push_back({ 507, 125, 11, 16 });
	littleBumpBottomSide.frames.push_back({ 499, 174, 9, 15 });
	littleBumpBottomSide.frames.push_back({ 483, 125, 10, 16 });
	littleBumpBottomSide.frames.push_back({ 475, 174, 10, 15 });
	littleBumpBottomSide.frames.push_back({ 451, 174, 12, 15 });
	littleBumpBottomSide.frames.push_back({ 451, 102, 14, 15 });
	littleBumpBottomSide.frames.push_back({ 427, 103, 15, 14 });
	littleBumpBottomSide.frames.push_back({ 403, 106, 15, 11 });
	littleBumpBottomSide.frames.push_back({ 411, 59, 16, 10 });
	littleBumpBottomSide.frames.push_back({ 35, 300, 15, 9 });
	littleBumpBottomSide.speed = turnSpeed;

	// little bump top side animation
	littleBumpTopSide.frames.push_back({ 11, 37, 16, 8 });
	littleBumpTopSide.frames.push_back({ 35, 276, 16, 9 });
	littleBumpTopSide.frames.push_back({ 355, 35, 16, 10 });
	littleBumpTopSide.frames.push_back({ 739, 58, 15, 11 });
	littleBumpTopSide.frames.push_back({ 339, 84, 12, 9 });
	littleBumpTopSide.frames.push_back({ 331, 33, 11, 12 });
	littleBumpTopSide.frames.push_back({ 707, 84, 12, 9 });
	littleBumpTopSide.frames.push_back({ 691, 84, 8, 9 });
	littleBumpTopSide.frames.push_back({ 299, 84, 12, 9 });
	littleBumpTopSide.frames.push_back({ 299, 84, 12, 9 });
	littleBumpTopSide.frames.push_back({ 667, 83, 12, 10 });
	littleBumpTopSide.frames.push_back({ 667, 83, 12, 10 });
	littleBumpTopSide.frames.push_back({ 643, 82, 15, 11 });
	littleBumpTopSide.frames.push_back({ 643, 82, 15, 11 });
	littleBumpTopSide.frames.push_back({ 275, 83, 16, 10 });
	littleBumpTopSide.frames.push_back({ 251, 84, 16, 9 });
	littleBumpTopSide.frames.push_back({ 243, 133, 16, 8 });
	littleBumpTopSide.frames.push_back({ 571, 61, 16, 8 });
	littleBumpTopSide.frames.push_back({ 547, 60, 14, 9 });
	littleBumpTopSide.frames.push_back({ 547, 60, 14, 9 });
	littleBumpTopSide.frames.push_back({ 523, 59, 12, 10 });
	littleBumpTopSide.frames.push_back({ 515, 301, 11, 8 });
	littleBumpTopSide.frames.push_back({ 507, 253, 10, 8 });
	littleBumpTopSide.frames.push_back({ 499, 301, 8, 8 });
	littleBumpTopSide.frames.push_back({ 491, 253, 9, 8 });
	littleBumpTopSide.frames.push_back({ 491, 253, 9, 8 });
	littleBumpTopSide.frames.push_back({ 467, 253, 13, 8 });
	littleBumpTopSide.frames.push_back({ 467, 253, 13, 8 });
	littleBumpTopSide.frames.push_back({ 475, 299, 12, 10 });
	littleBumpTopSide.frames.push_back({ 451, 299, 15, 10 });
	littleBumpTopSide.frames.push_back({ 443, 252, 15, 9 });
	littleBumpTopSide.frames.push_back({ 419, 253, 16, 8 });
	littleBumpTopSide.speed = turn.speed;

	// big bump right side animation
	bigBumpRightSide.frames.push_back({ 35, 226, 14, 11 });
	bigBumpRightSide.frames.push_back({ 11, 224, 13, 13 });
	bigBumpRightSide.frames.push_back({ 11, 224, 13, 13 });
	bigBumpRightSide.frames.push_back({ 723, 274, 13, 11 });
	bigBumpRightSide.frames.push_back({ 707, 198, 14, 15 });
	bigBumpRightSide.frames.push_back({ 699, 271, 11, 14 });
	bigBumpRightSide.frames.push_back({ 699, 271, 11, 14 });
	bigBumpRightSide.frames.push_back({ 683, 270, 9, 15 });
	bigBumpRightSide.frames.push_back({ 659, 269, 12, 16 });
	bigBumpRightSide.frames.push_back({ 659, 30, 13, 15 });
	bigBumpRightSide.frames.push_back({ 659, 30, 13, 15 });
	bigBumpRightSide.frames.push_back({ 635, 31, 14, 14 });
	bigBumpRightSide.frames.push_back({ 611, 33, 14, 12 });
	bigBumpRightSide.frames.push_back({ 243, 105, 15, 12 });
	bigBumpRightSide.frames.push_back({ 619, 156, 13, 9 });
	bigBumpRightSide.frames.push_back({ 595, 156, 15, 9 });
	bigBumpRightSide.frames.push_back({ 603, 130, 15, 11 });
	bigBumpRightSide.frames.push_back({ 563, 176, 14, 13 });
	bigBumpRightSide.frames.push_back({ 539, 174, 14, 15 });
	bigBumpRightSide.frames.push_back({ 515, 173, 12, 16 });
	bigBumpRightSide.frames.push_back({ 515, 104, 12, 13 });
	bigBumpRightSide.frames.push_back({ 155, 59, 12, 10 });
	bigBumpRightSide.frames.push_back({ 131, 55, 10, 14 });
	bigBumpRightSide.frames.push_back({ 131, 300, 10, 9 });
	bigBumpRightSide.frames.push_back({ 491, 228, 10, 9 });
	bigBumpRightSide.frames.push_back({ 475, 229, 9, 8 });
	bigBumpRightSide.frames.push_back({ 107, 298, 10, 11 });
	bigBumpRightSide.frames.push_back({ 451, 228, 11, 9 });
	bigBumpRightSide.frames.push_back({ 83, 253, 13, 8 });
	bigBumpRightSide.frames.push_back({ 83, 253, 13, 8 });
	bigBumpRightSide.frames.push_back({ 59, 251, 14, 10 });
	bigBumpRightSide.frames.push_back({ 59, 251, 14, 10 });
	bigBumpRightSide.speed = turnSpeed;

	// big bump left side animation
	bigBumpLeftSide.frames.push_back({ 35, 106, 15, 11 });
	bigBumpLeftSide.frames.push_back({ 35, 80, 14, 13 });
	bigBumpLeftSide.frames.push_back({ 35, 129, 13, 12 });
	bigBumpLeftSide.frames.push_back({ 35, 58, 15, 11 });
	bigBumpLeftSide.frames.push_back({ 739, 58, 15, 11 });
	bigBumpLeftSide.frames.push_back({ 715, 55, 13, 14 });
	bigBumpLeftSide.frames.push_back({ 691, 54, 10, 15 });
	bigBumpLeftSide.frames.push_back({ 691, 54, 10, 15 });
	bigBumpLeftSide.frames.push_back({ 259, 245, 8, 16 });
	bigBumpLeftSide.frames.push_back({ 667, 55, 12, 14 });
	bigBumpLeftSide.frames.push_back({ 667, 55, 12, 14 });
	bigBumpLeftSide.frames.push_back({ 643, 57, 13, 12 });
	bigBumpLeftSide.frames.push_back({ 643, 57, 13, 12 });
	bigBumpLeftSide.frames.push_back({ 243, 245, 9, 16 });
	bigBumpLeftSide.frames.push_back({ 219, 197, 10, 16 });
	bigBumpLeftSide.frames.push_back({ 611, 295, 13, 14 });
	bigBumpLeftSide.frames.push_back({ 611, 295, 13, 14 });
	bigBumpLeftSide.frames.push_back({ 587, 296, 13, 13 });
	bigBumpLeftSide.frames.push_back({ 563, 299, 14, 10 });
	bigBumpLeftSide.frames.push_back({ 539, 302, 13, 7 });
	bigBumpLeftSide.frames.push_back({ 515, 301, 11, 8 });
	bigBumpLeftSide.frames.push_back({ 507, 253, 10, 8 });
	bigBumpLeftSide.frames.push_back({ 523, 276, 8, 9 });
	bigBumpLeftSide.frames.push_back({ 523, 276, 8, 9 });
	bigBumpLeftSide.frames.push_back({ 499, 274, 10, 11 });
	bigBumpLeftSide.frames.push_back({ 499, 274, 10, 11 });
	bigBumpLeftSide.frames.push_back({ 475, 275, 14, 10 });
	bigBumpLeftSide.frames.push_back({ 475, 275, 14, 10 });
	bigBumpLeftSide.frames.push_back({ 83, 101, 11, 16 });
	bigBumpLeftSide.frames.push_back({ 83, 101, 11, 16 });
	bigBumpLeftSide.frames.push_back({ 59, 104, 13, 13 });
	bigBumpLeftSide.frames.push_back({ 59, 104, 13, 13 });
	bigBumpLeftSide.speed = turnSpeed;

	// big bump bottom side animation
	bigBumpBottomSide.frames.push_back({ 11, 62, 15, 7 });
	bigBumpBottomSide.frames.push_back({ 11, 300, 15, 9 });
	bigBumpBottomSide.frames.push_back({ 731, 296, 15, 13 });
	bigBumpBottomSide.frames.push_back({ 355, 297, 16, 12 });
	bigBumpBottomSide.frames.push_back({ 715, 224, 16, 13 });
	bigBumpBottomSide.frames.push_back({ 691, 223, 15, 14 });
	bigBumpBottomSide.frames.push_back({ 307, 197, 11, 16 });
	bigBumpBottomSide.frames.push_back({ 667, 197, 9, 16 });
	bigBumpBottomSide.frames.push_back({ 643, 197, 10, 16 });
	bigBumpBottomSide.frames.push_back({ 619, 198, 11, 15 });
	bigBumpBottomSide.frames.push_back({ 659, 269, 12, 16 });
	bigBumpBottomSide.frames.push_back({ 635, 270, 15, 15 });
	bigBumpBottomSide.frames.push_back({ 611, 271, 16, 14 });
	bigBumpBottomSide.frames.push_back({ 587, 274, 15, 11 });
	bigBumpBottomSide.frames.push_back({ 587, 35, 14, 10 });
	bigBumpBottomSide.frames.push_back({ 219, 108, 16, 9 });
	bigBumpBottomSide.frames.push_back({ 595, 84, 16, 9 });
	bigBumpBottomSide.frames.push_back({ 563, 38, 14, 7 });
	bigBumpBottomSide.frames.push_back({ 571, 84, 15, 9 });
	bigBumpBottomSide.frames.push_back({ 571, 154, 15, 11 });
	bigBumpBottomSide.frames.push_back({ 547, 154, 16, 11 });
	bigBumpBottomSide.frames.push_back({ 523, 151, 14, 14 });
	bigBumpBottomSide.frames.push_back({ 507, 125, 11, 16 });
	bigBumpBottomSide.frames.push_back({ 499, 174, 9, 15 });
	bigBumpBottomSide.frames.push_back({ 483, 125, 10, 16 });
	bigBumpBottomSide.frames.push_back({ 475, 174, 10, 15 });
	bigBumpBottomSide.frames.push_back({ 451, 174, 12, 15 });
	bigBumpBottomSide.frames.push_back({ 451, 102, 14, 15 });
	bigBumpBottomSide.frames.push_back({ 427, 103, 15, 14 });
	bigBumpBottomSide.frames.push_back({ 403, 106, 15, 11 });
	bigBumpBottomSide.frames.push_back({ 411, 59, 16, 10 });
	bigBumpBottomSide.frames.push_back({ 35, 300, 15, 9 });
	bigBumpBottomSide.speed = turnSpeed;

	// big bump top side animation
	bigBumpTopSide.frames.push_back({ 379, 38, 16, 7 });
	bigBumpTopSide.frames.push_back({ 379, 38, 16, 7 });
	bigBumpTopSide.frames.push_back({ 363, 85, 13, 8 });
	bigBumpTopSide.frames.push_back({ 363, 85, 13, 8 });
	bigBumpTopSide.frames.push_back({ 339, 84, 12, 9 });
	bigBumpTopSide.frames.push_back({ 339, 84, 12, 9 });
	bigBumpTopSide.frames.push_back({ 323, 83, 8, 10 });
	bigBumpTopSide.frames.push_back({ 691, 84, 8, 9 });
	bigBumpTopSide.frames.push_back({ 299, 84, 12, 9 });
	bigBumpTopSide.frames.push_back({ 299, 84, 12, 9 });
	bigBumpTopSide.frames.push_back({ 675, 134, 12, 7 });
	bigBumpTopSide.frames.push_back({ 675, 134, 12, 7 });
	bigBumpTopSide.frames.push_back({ 651, 132, 15, 9 });
	bigBumpTopSide.frames.push_back({ 651, 132, 15, 9 });
	bigBumpTopSide.frames.push_back({ 299, 180, 14, 9 });
	bigBumpTopSide.frames.push_back({ 299, 180, 14, 9 });
	bigBumpTopSide.frames.push_back({ 275, 181, 16, 8 });
	bigBumpTopSide.frames.push_back({ 275, 181, 16, 8 });
	bigBumpTopSide.frames.push_back({ 251, 180, 16, 9 });
	bigBumpTopSide.frames.push_back({ 171, 201, 10, 12 });
	bigBumpTopSide.frames.push_back({ 155, 204, 9, 9 });
	bigBumpTopSide.frames.push_back({ 155, 204, 9, 9 });
	bigBumpTopSide.frames.push_back({ 147, 252, 10, 9 });
	bigBumpTopSide.frames.push_back({ 131, 254, 8, 7 });
	bigBumpTopSide.frames.push_back({ 107, 252, 12, 9 });
	bigBumpTopSide.frames.push_back({ 107, 206, 13, 7 });
	bigBumpTopSide.frames.push_back({ 107, 206, 13, 7 });
	bigBumpTopSide.frames.push_back({ 83, 205, 15, 8 });
	bigBumpTopSide.frames.push_back({ 83, 205, 15, 8 });
	bigBumpTopSide.frames.push_back({ 107, 229, 16, 8 });
	bigBumpTopSide.frames.push_back({ 107, 229, 16, 8 });
	bigBumpTopSide.frames.push_back({ 83, 228, 16, 9 });
	bigBumpTopSide.speed = turnSpeed;

	// fill standard shadows vector
	standardShadows.frames.push_back({ 35, 324, 16, 9 });
	standardShadows.frames.push_back({ 11, 324, 15, 9 });
	standardShadows.frames.push_back({ 739, 323, 16, 10 });
	standardShadows.frames.push_back({ 715, 322, 15, 11 });
	standardShadows.frames.push_back({ 691, 322, 14, 12 });
	standardShadows.frames.push_back({ 667, 321, 13, 12 });
	standardShadows.frames.push_back({ 643, 321, 10, 12 });
	standardShadows.frames.push_back({ 627, 320, 9, 13 });
	standardShadows.frames.push_back({ 603, 320, 10, 13 });
	standardShadows.frames.push_back({ 579, 320, 12, 13 });
	standardShadows.frames.push_back({ 555, 320, 13, 13 });
	standardShadows.frames.push_back({ 531, 320, 13, 13 });
	standardShadows.frames.push_back({ 507, 320, 15, 13 });
	standardShadows.frames.push_back({ 483, 321, 15, 12 });
	standardShadows.frames.push_back({ 459, 322, 15, 11 });
	standardShadows.frames.push_back({ 435, 322, 14, 11 });
	standardShadows.frames.push_back({ 411, 323, 15, 10 });
	standardShadows.frames.push_back({ 387, 324, 15, 9 });
	standardShadows.frames.push_back({ 363, 324, 15, 9 });
	standardShadows.frames.push_back({ 339, 323, 15, 10 });
	standardShadows.frames.push_back({ 315, 322, 14, 11 });
	standardShadows.frames.push_back({ 291, 321, 12, 12 });
	standardShadows.frames.push_back({ 267, 321, 11, 12 });
	standardShadows.frames.push_back({ 251, 321, 9, 12 });
	standardShadows.frames.push_back({ 227, 321, 10, 12 });
	standardShadows.frames.push_back({ 203, 321, 12, 12 });
	standardShadows.frames.push_back({ 179, 321, 14, 12 });
	standardShadows.frames.push_back({ 155, 321, 14, 12 });
	standardShadows.frames.push_back({ 131, 321, 15, 12 });
	standardShadows.frames.push_back({ 107, 322, 16, 11 });
	standardShadows.frames.push_back({ 83, 322, 16, 11 });
	standardShadows.frames.push_back({ 59, 323, 16, 10 });
	standardShadows.speed = turnSpeed;

	// Define splash animation
	splash.frames.push_back({ 203, 378, 9, 11 });
	splash.frames.push_back({ 219, 378, 13, 11 });
	splash.frames.push_back({ 243, 375, 16, 14 });
	splash.frames.push_back({ 267, 374, 16, 15 });
	splash.frames.push_back({ 291, 374, 16, 15 });
	splash.frames.push_back({ 315, 376, 16, 13 });
	splash.frames.push_back({ 339, 379, 14, 10 });
	splash.frames.push_back({ 363, 381, 14, 8 });
	splash.frames.push_back({ 387, 379, 13, 10 });
	splash.frames.push_back({ 411, 378, 14, 11 });
	splash.frames.push_back({ 435, 377, 16, 12 });
	splash.frames.push_back({ 459, 377, 16, 12 });
	splash.speed = splashSpeed;
}

ModulePlayer::~ModulePlayer()
{
	delete moduleCollision;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	StartingInitials();
	graphics = App->textures->Load("general_sprites.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// PreUpdate
update_status ModulePlayer::PreUpdate()
{
	CalculateDeltatime();
	DetectBumps();
	DetectPlayerCheckPoints();
	moduleCollision->DetectCarCollisions();
	if (carCollision) ApplyCarCollisionEffect();

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		right = true;
		still = false;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		right = false;
		still = false;
	}
	else
	{
		still = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		if (acceleration == accelerationCondition)
		{
			/*LOG("positionX: %f", position.x);
			LOG("positionY: %f", position.y);*/

			repeater++;
			SetDirection();
			MoveCar();

			acceleration = initialAcceleration;
			if (accelerationCondition > 1 && repeater % 2 == 0)
			{
				accelerationCondition--;
			}
		}

		acceleration++;
	}
	else
	{
		if (acceleration == accelerationCondition)
		{
			repeater--;
			SetDirection();
			MoveCar();

			acceleration = initialAcceleration;
			if (accelerationCondition < initialAccelerationCondition && repeater % 2 == 0)
			{
				accelerationCondition++;
			}
		}

		if (accelerationCondition < initialAccelerationCondition)
		{
			acceleration++;
		}
		else 
		{
			repeater = 0;
			bounce = false;
			bounceRecoil = 0;
		}
	}

	if (DetectPool())
	{
		App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentSplashAnimation->GetCurrentFrame());
	}

	if (still)
	{
		App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentStaticFrame());
		App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentStaticFrame());
	}
	else
	{
		if (right)
		{
			App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentFrame());
			App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentFrame());
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentInverseFrame());
			App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentInverseFrame());
		}
	}

	CheckIfLapCompleted();
	CheckIfWinner();
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::StartingInitials()
{
	// Put time to 0
	deltaTime = 0.0;
	thisTime = 0;
	lastTime = 0;

	position.x = 177;
	position.y = 176;
	acceleration = initialAcceleration;
	accelerationCondition = initialAccelerationCondition;
	lastFramePosition = position;
	right = true;
	repeater = 0;
	bounce = false;
	collision = false;
	still = true;
	bounceRecoil = 0;
	frameReference = 17;
	carCollision = false;
	lap = 1;
	winner = false;

	// Define car start sprite and start animation
	turn.current_frame = 17.0f;
	standardShadows.current_frame = 17.0f;
	currentAnimation = &turn;
	currentShadowsAnimation = &standardShadows;
	currentSplashAnimation = &splash;

	// Put checkpoints to false
	for (int i = 0; i < checkpoint.size(); i++)
	{
		checkpoint[i] = false;
	}
}

void ModulePlayer::SetDirection()
{
	if (((int)currentAnimation->current_frame) == 0)
	{
		currentDirection = { 1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 1)
	{
		switch (movementsDone[1])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[1] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[1] = 2;
			break;
		case 2:
			currentDirection = { 1, 0 };
			movementsDone[1] = 3;
			break;

		case 3:
			currentDirection = { 1, 0 };
			movementsDone[1] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 2)
	{
		switch (movementsDone[2])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[2] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[2] = 2;
			break;
		case 2:
			currentDirection = { 1, 0 };
			movementsDone[2] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 3)
	{
		switch (movementsDone[3])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[3] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[3] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 4)
	{
		currentDirection = { 1, 1 };
	}
	else if (((int)currentAnimation->current_frame) == 5)
	{
		switch (movementsDone[5])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[5] = 1;
			break;

		case 1:
			currentDirection = { 1, 1 };
			movementsDone[5] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[5] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 6)
	{
		switch (movementsDone[6])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[6] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[6] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 7)
	{
		switch (movementsDone[7])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[7] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[7] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[7] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 8)
	{
		switch (movementsDone[8])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[8] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[8] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[8] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 9)
	{
		switch (movementsDone[9])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[9] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[9] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 10)
	{
		switch (movementsDone[10])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[10] = 1;
			break;

		case 1:
			currentDirection = { -1, 1 };
			movementsDone[10] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[10] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 11)
	{
		currentDirection = { -1, 1 };
	}
	else if (((int)currentAnimation->current_frame) == 12)
	{
		switch (movementsDone[12])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[12] = 1;
			break;

		case 1:
			currentDirection = { -1, 1 };
			movementsDone[12] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[12] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 13)
	{
		switch (movementsDone[13])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[13] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[13] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 14)
	{
		switch (movementsDone[14])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[14] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[14] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[14] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 15)
	{
		switch (movementsDone[15])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[15] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[15] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[15] = 3;
			break;

		case 3:
			currentDirection = { -1, 0 };
			movementsDone[15] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 16)
	{
		currentDirection = { -1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 17)
	{
		currentDirection = { -1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 18)
	{
		switch (movementsDone[18])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[18] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[18] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[18] = 3;
			break;

		case 3:
			currentDirection = { -1, 0 };
			movementsDone[18] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 19)
	{
		switch (movementsDone[19])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[19] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[19] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[19] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 20)
	{
		switch (movementsDone[20])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[20] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[20] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 21)
	{
		currentDirection = { -1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 22)
	{
		switch (movementsDone[22])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[22] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[22] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 23)
	{
		switch (movementsDone[23])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[23] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[23] = 2;
			break;

		case 2:
			currentDirection = { 0, -1 };
			movementsDone[23] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 24)
	{
		switch (movementsDone[24])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[24] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[24] = 2;
			break;

		case 2:
			currentDirection = { 0, -1 };
			movementsDone[24] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 25)
	{
		switch (movementsDone[25])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[25] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[25] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 26)
	{
		currentDirection = { 1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 27)
	{
		currentDirection = { 1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 28)
	{
		switch (movementsDone[28])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[28] = 1;
			break;

		case 1:
			currentDirection = { 1, -1 };
			movementsDone[28] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[28] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 29)
	{
		switch (movementsDone[29])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[29] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[29] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 30)
	{
		switch (movementsDone[30])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[30] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[30] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[30] = 0;
			break;
		}
	}
	else if (((int)currentAnimation->current_frame) == 31)
	{
		switch (movementsDone[31])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[31] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[31] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[31] = 3;
			break;

		case 3:
			currentDirection = { 1, 0 };
			movementsDone[31] = 0;
			break;
		}
	}
}

void ModulePlayer::MoveCar()
{
	collision = false;

	if (!DetectFences(position))
	{
		lastFramePosition = position;
	}

	if (!bounce && !collision)
	{
		position.x += currentDirection[0] * deltaTime;
		position.y += currentDirection[1] * deltaTime;
	}
	else if (collision && !bounce)
	{
		fPoint tempPos;
		tempPos.x = position.x + (currentDirection[0] * deltaTime);
		tempPos.y = position.y + (currentDirection[1] * deltaTime);

		if (!DetectFences(tempPos))
		{
			position = tempPos;
		}
	}
	else
	{
		ApplyBounceEffect();
		bounceRecoil++;

		if (bounceRecoil == 10)
		{
			bounce = false;
			bounceRecoil = 0;
			acceleration = initialAcceleration;
			accelerationCondition = initialAccelerationCondition;
			repeater = 0;
		}
	}
}

bool ModulePlayer::DetectFences(fPoint position)
{
	bool fenceDetected = false;

	for each (std::vector<std::vector<int>> fences in moduleCollision->fenceContainer)
	{
		for (int i = 0; i < fences.size(); i++)
		{
			/* Debug fences */
			//SDL_RenderDrawPoint(App->renderer->renderer, fences[i][0], fences[i][1]);

			if (fabs(position.x - fences[i][0]) < errorMargin && fabs(position.y - fences[i][1]) < errorMargin)
			{
				float intersection_carLastFrame = sqrt(pow(position.x - lastFramePosition.x, 2) + pow(position.y - lastFramePosition.y, 2));
				float intersection_colliderOrigin = sqrt(pow(position.x - fences.front()[0], 2) + pow(position.y - fences.front()[1], 2));
				float carLastFrame_colliderOrigin = sqrt(pow(lastFramePosition.x - fences.front()[0], 2) + pow(lastFramePosition.y - fences.front()[1], 2));

				float radianAngle = acos((pow(intersection_carLastFrame, 2) + pow(intersection_colliderOrigin, 2) - pow(carLastFrame_colliderOrigin, 2)) / (2 * intersection_carLastFrame * intersection_colliderOrigin));
				float angle = radianAngle * 180 / M_PI;

				/*LOG("intersection_carLastFrame: %f", intersection_carLastFrame);
				LOG("intersection_colliderOrigin: %f", intersection_colliderOrigin);
				LOG("carLastFrame_colliderOrigin: %f", carLastFrame_colliderOrigin);
				LOG("angle: %f", angle);*/

				collision = true;

				if (angle >= 88 && angle <= 92)
				{
					bounce = true;
					SetBounceDirection(fences);
				}
				else if (angle >= 0 && angle < 88)
				{
					right = SetRotationDirection(fences);
				}
				else if (angle <= 180 && angle > 92)
				{
					right = !SetRotationDirection(fences);
				}

				fenceDetected = true;
				break;
			}
		}
	}

	return fenceDetected;
}

bool ModulePlayer::SetRotationDirection(std::vector<std::vector<int>> fences)
{
	bool rotationRight = true;

	if (fences == moduleCollision->fence1_1 ||
		fences == moduleCollision->fence2_1 ||
		fences == moduleCollision->fence2_3 ||
		fences == moduleCollision->fence3_1 ||
		fences == moduleCollision->fence3_4 ||
		fences == moduleCollision->fence4_1 ||
		fences == moduleCollision->fence4_2 ||
		fences == moduleCollision->fence4_3 ||
		fences == moduleCollision->fence5_2 ||
		fences == moduleCollision->fence5_4 ||
		fences == moduleCollision->fence5_6 ||
		fences == moduleCollision->fenceDiagonalReinforcement1)
	{
		rotationRight = false;
	}

	still = false;

	return rotationRight;
}

void ModulePlayer::SetBounceDirection(std::vector<std::vector<int>> fences)
{
	if (fences == moduleCollision->fence1_1 ||
		fences == moduleCollision->fence2_1 ||
		fences == moduleCollision->fence3_1 ||
		fences == moduleCollision->fence4_1 ||
		fences == moduleCollision->fence5_2)
	{
		// position.y--
		bounceType = 0;
	}
	else if (fences == moduleCollision->fence1_2 ||
		fences == moduleCollision->fence1_4 ||
		fences == moduleCollision->fence2_2 ||
		fences == moduleCollision->fence3_2 ||
		fences == moduleCollision->fence5_1)
	{
		// position.x--
		bounceType = 1;
	}
	else if (fences == moduleCollision->fence3_3 ||
		fences == moduleCollision->fenceDiagonalReinforcement2 ||
		fences == moduleCollision->fenceDiagonalReinforcement3)
	{
		// position.x--
		// position.y++
		bounceType = 2;
	}
	else if (fences == moduleCollision->fence3_4 ||
		fences == moduleCollision->fence2_3 ||
		fences == moduleCollision->fence4_3 ||
		fences == moduleCollision->fence5_4 ||
		fences == moduleCollision->fence5_6)
	{
		// position.x++
		bounceType = 3;
	}
	else if (fences == moduleCollision->fence4_2 ||
		fences == moduleCollision->fenceDiagonalReinforcement1)
	{
		// position.x++
		// position.y--
		bounceType = 4;
	}
	else if (fences == moduleCollision->fence1_3 ||
		fences == moduleCollision->fence4_4 ||
		fences == moduleCollision->fence5_3 ||
		fences == moduleCollision->fence5_5)
	{
		// position.y++
		bounceType = 5;
	}
}

void ModulePlayer::ApplyBounceEffect()
{
	switch (bounceType)
	{
		case 0:
			position.y -= 1 * deltaTime;
			break;

		case 1:
			position.x -= 1 * deltaTime;
			break;

		case 2:
			position.x -= 1 * deltaTime;
			position.y += 1 * deltaTime;

		case 3:
			position.x += 1 * deltaTime;

		case 4:
			position.x += 1 * deltaTime;
			position.y -= 1 * deltaTime;

		case 5:
			position.y += 1 * deltaTime;
	}
}

void ModulePlayer::ApplyCarCollisionEffect()
{
	fPoint tempPos;

	switch (carCollisionType)
	{
		case 1:
			tempPos.x = position.x;
			tempPos.y = position.y + (1 * deltaTime);
			break;

		case 2:
			tempPos.x = position.x - (1 * deltaTime);
			tempPos.y = position.y + (1 * deltaTime);
			break;

		case 3:
			tempPos.x = position.x - (1 * deltaTime);
			tempPos.y = position.y;
			break;

		case 4:
			tempPos.x = position.x - (1 * deltaTime);
			tempPos.y = position.y - (1 * deltaTime);
			break;

		case 5:
			tempPos.x = position.x;
			tempPos.y = position.y - (1 * deltaTime);
			break;

		case 6:
			tempPos.x = position.x + (1 * deltaTime);
			tempPos.y = position.y - (1 * deltaTime);
			break;

		case 7:
			tempPos.x = position.x + (1 * deltaTime);
			tempPos.y = position.y;
			break;

		case 8:
			tempPos.x = position.x + (1 * deltaTime);
			tempPos.y = position.y + (1 * deltaTime);
			break;
	}

	bool fenceDetected = false;

	for each (std::vector<std::vector<int>> fences in moduleCollision->fenceContainer)
	{
		for (int i = 0; i < fences.size(); i++)
		{
			if (fabs(tempPos.x - fences[i][0]) < errorMargin && fabs(tempPos.y - fences[i][1]) < errorMargin)
			{
				fenceDetected = true;
				break;
			}
		}
	}

	if (!fenceDetected)
	{
		position = tempPos;
	}

	carCollision = false;
}

void ModulePlayer::DetectBumps()
{
	bool littleBumpRightSideDetected = false;
	bool littleBumpLeftSideDetected = false;
	bool littleBumpBottomSideDetected = false;
	bool littleBumpTopSideDetected = false;

	bool bigBumpRightSideDetected = false;
	bool bigBumpLeftSideDetected = false;
	bool bigBumpBottomSideDetected = false;
	bool bigBumpTopSideDetected = false;

	SDL_Rect playerCar;
	playerCar.x = position.x;
	playerCar.y = position.y;
	playerCar.w = 15;
	playerCar.h = 11;

	for each (SDL_Rect bump in moduleCollision->littleBumpRightSideContainer)
	{
		//App->renderer->DrawQuad(bump, 255, 0, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpRightSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->littleBumpLeftSideContainer)
	{
		//App->renderer->DrawQuad(bump, 0, 255, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpLeftSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->littleBumpBottomSideContainer)
	{
		//App->renderer->DrawQuad(bump, 0, 0, 255, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpBottomSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->littleBumpTopSideContainer)
	{
		//App->renderer->DrawQuad(bump, 255, 255, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpTopSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->bigBumpRightSideContainer)
	{
		//App->renderer->DrawQuad(bump, 255, 0, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			bigBumpRightSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->bigBumpLeftSideContainer)
	{
		//App->renderer->DrawQuad(bump, 0, 255, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			bigBumpLeftSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->bigBumpBottomSideContainer)
	{
		//App->renderer->DrawQuad(bump, 0, 0, 255, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			bigBumpBottomSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->bigBumpTopSideContainer)
	{
		//App->renderer->DrawQuad(bump, 255, 255, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			bigBumpTopSideDetected = true;
			break;
		}
	}

	if (littleBumpRightSideDetected)
	{
		littleBumpRightSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpRightSide;
	}
	if (littleBumpLeftSideDetected)
	{
		littleBumpLeftSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpLeftSide;
	}
	if (littleBumpBottomSideDetected)
	{
		littleBumpBottomSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpBottomSide;
	}
	if (littleBumpTopSideDetected)
	{
		littleBumpTopSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpTopSide;
	}
	if (bigBumpBottomSideDetected)
	{
		bigBumpBottomSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &bigBumpBottomSide;
	}
	if (bigBumpRightSideDetected)
	{
		bigBumpRightSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &bigBumpRightSide;
	}
	if (bigBumpLeftSideDetected)
	{
		bigBumpLeftSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &bigBumpLeftSide;
	}
	if (bigBumpTopSideDetected)
	{
		bigBumpTopSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &bigBumpTopSide;
	}
	if (!littleBumpRightSideDetected &&
		!littleBumpLeftSideDetected &&
		!littleBumpBottomSideDetected &&
		!littleBumpTopSideDetected &&
		!bigBumpRightSideDetected &&
		!bigBumpLeftSideDetected &&
		!bigBumpBottomSideDetected &&
		!bigBumpTopSideDetected)
	{
		turn.current_frame = currentAnimation->current_frame;
		currentAnimation = &turn;
	}
}

bool ModulePlayer::DetectPool()
{
	bool overPool = false;

	SDL_Rect playerCar;
	playerCar.x = position.x;
	playerCar.y = position.y;
	playerCar.w = 15;
	playerCar.h = 11;

	//App->renderer->DrawQuad(moduleCollision->poolCollider, 255, 0, 0, 80);

	if (SDL_HasIntersection(&playerCar, &moduleCollision->poolCollider))
	{
		overPool = true;
	}
	
	return overPool;
}

bool ModulePlayer::CheckIfFinishLine()
{
	bool flag = false;

	for (int i = 0; i < moduleCollision->finishLine.size(); i++)
	{
		/* Debug finish line */
		//SDL_RenderDrawPoint(App->renderer->renderer, moduleCollision->finishLine[i][0], moduleCollision->finishLine[i][1]);

		if (fabs(position.x - moduleCollision->finishLine[i][0]) < distanceOffset && fabs(position.y - moduleCollision->finishLine[i][1]) < distanceOffset)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

void ModulePlayer::CheckIfLapCompleted()
{
	bool allCheckpoints = true;

	for each (bool cp in checkpoint)
	{
		if (!cp)
		{
			allCheckpoints = false;
		}
	}

	if (allCheckpoints && CheckIfFinishLine())
	{
		lap++;

		for (int i = 0; i < checkpoint.size(); i++)
		{
			checkpoint[i] = false;
		}
	}
}

void ModulePlayer::DetectPlayerCheckPoints()
{
	for each (fPoint cp1 in checkpoint1)
	{
		if (position.DistanceTo(cp1) <= distanceOffset)
		{
			checkpoint[0] = true;
		}
	}

	for each (fPoint cp2 in checkpoint2)
	{
		if (position.DistanceTo(cp2) <= distanceOffset)
		{
			checkpoint[1] = true;
		}
	}

	for each (fPoint cp3 in checkpoint3)
	{
		if (position.DistanceTo(cp3) <= distanceOffset)
		{
			checkpoint[2] = true;
		}
	}

	for each (fPoint cp4 in checkpoint4)
	{
		if (position.DistanceTo(cp4) <= distanceOffset)
		{
			checkpoint[3] = true;
		}
	}

	for each (fPoint cp5 in checkpoint5)
	{
		if (position.DistanceTo(cp5) <= distanceOffset)
		{
			checkpoint[4] = true;
		}
	}

	for each (fPoint cp6 in checkpoint6)
	{
		if (position.DistanceTo(cp6) <= distanceOffset)
		{
			checkpoint[5] = true;
		}
	}

	for each (fPoint cp7 in checkpoint7)
	{
		if (position.DistanceTo(cp7) <= distanceOffset)
		{
			checkpoint[6] = true;
		}
	}

	for each (fPoint cp8 in checkpoint8)
	{
		if (position.DistanceTo(cp8) <= distanceOffset)
		{
			checkpoint[7] = true;
		}
	}
}

void ModulePlayer::CheckIfWinner()
{
	if (lap == 7)
	{
		winner = true;
	}
}

void ModulePlayer::CalculateDeltatime()
{
	thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 12;
	lastTime = thisTime;
}