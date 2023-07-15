#include <stdio.h>
#include "raylib.h"
#include <stdbool.h>

// window config
int window_width = 800;
int window_height = 600;

// ball params
float ball_size = 15;

Rectangle plattform_position;
Vector2 ball_position;
bool isStarted = false;
bool lose = false;
Vector2 ball_force;

void setup(){
  // plattform`
  plattform_position.width = 100;
  plattform_position.height = 20;
  plattform_position.x = (window_width / 2) - (plattform_position.width / 2);
  plattform_position.y = window_height - 40;

  // ball
  ball_position.x = plattform_position.x + (plattform_position.width / 2);
  ball_position.y = plattform_position.y - ball_size;

  // window init
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetTargetFPS(60);
  InitWindow(window_width, window_height, "My game break");
}

void update(){
  // check plattform collision with ball
  if(CheckCollisionCircleRec(ball_position, ball_size, plattform_position)){
    if(ball_force.y < 0){
      ball_force.y = -ball_force.y;
      ball_position.y = ball_position.y - (ball_force.y * GetFrameTime());
    }
  }
   
  if(IsKeyDown(KEY_D) && plattform_position.x < (window_width - plattform_position.width)){
    plattform_position.x = plattform_position.x + (500 * GetFrameTime());
  }
 
  if(IsKeyDown(KEY_A) && plattform_position.x > 0){
    plattform_position.x = plattform_position.x - (500 * GetFrameTime());
  }

    // vertical top collision
  if((ball_position.y - ball_size) > 0){   
    ball_position.y = ball_position.y - (ball_force.y * GetFrameTime());
  }else{
    ball_force.y = ball_force.y * -1;
    ball_position.y = ball_position.y - (ball_force.y * GetFrameTime());
  }

  // vertical bottom collision
  if((ball_position.y + ball_size) >= window_height){
    /* ball_force.y = -ball_force.y; */
    /* ball_position.y = ball_position.y - (ball_force.y * GetFrameTime()); */
    lose = true;
  }

  // horizontal right collision
  if(ball_position.x < (window_width - ball_size)){
    ball_position.x = ball_position.x + (ball_force.x * GetFrameTime());
  }else{
    ball_force.x = ball_force.x * -1;
    ball_position.x = ball_position.x + (ball_force.x * GetFrameTime());
  }

  // horizontal left collision
  if((ball_position.x - ball_size) <= 0){
    ball_force.x = -ball_force.x;
    ball_position.x = ball_position.x + (ball_force.x * GetFrameTime());
  }
}

void draw_plattform(Rectangle rec){
  DrawRectangleRounded(rec, 0.7f, 5, BLACK);
}

void draw_ball(Vector2 ball_pos){
  DrawCircleV(ball_pos, ball_size, BLACK);
}

void draw_welcome(){
  char* welcome = "Press space bar to start!!";
  int textWidth = MeasureText(welcome, 32);
  DrawText(welcome,(window_width / 2) - (textWidth / 2), window_height / 2, 32, BLACK);  
}

void draw_restart(){
  char* restart = "Press space bar to restart!!";
  int textWidth = MeasureText(restart, 32);
  DrawText(restart,(window_width / 2) - (textWidth / 2), window_height / 2, 32, BLACK);  
}

void start(){
  isStarted = true;

  ball_force.x = 600;
  ball_force.y = 600; 
}

void restart(){
  // plattform
  plattform_position.width = 100;
  plattform_position.height = 20;
  plattform_position.x = (window_width / 2) - (plattform_position.width / 2);
  plattform_position.y = window_height - 40;

  // ball
  ball_position.x = plattform_position.x + (plattform_position.width / 2);
  ball_position.y = plattform_position.y - ball_size;
  lose = false;
}

int main(){
  setup();

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(WHITE);
    if(isStarted && !lose){
      update();
    }
    if(!isStarted && !lose){
      draw_welcome();
      if(IsKeyDown(KEY_SPACE)){
	start();
      }    
    }

    if(isStarted && lose){
      draw_restart();
      if(IsKeyDown(KEY_SPACE)){
	restart();
      }    
    }
    draw_plattform(plattform_position);
    draw_ball(ball_position);
    EndDrawing();
  }

  CloseWindow();
  
  return 0;
}
