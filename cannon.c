#include "primlib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct target {
  int x;
  int y;
  int target_bullet_x;
  int target_bullet_y;
  int x_velocity;
  int y_velocity;
  int explosion;
  float radius;
  int target_size;
  int is_shooting;
  int active;
};

struct ship {
  int player_x;
  int player_y;
  int ship_speed;
  int rocket_under_ship;
};

struct bullet {
  int x_bullet;
  int y_bullet;
  int radius_bullet;
};

void draw_bullet(const struct bullet *b) {
  gfx_filledCircle(b->x_bullet, b->y_bullet, b->radius_bullet, RED);
  gfx_filledCircle(b->x_bullet, b->y_bullet, b->radius_bullet * 0.8, YELLOW);
  gfx_filledCircle(b->x_bullet, b->y_bullet, b->radius_bullet * 0.6, RED);
  gfx_filledCircle(b->x_bullet, b->y_bullet, b->radius_bullet * 0.4, YELLOW);

  gfx_filledCircle(b->x_bullet - 38, b->y_bullet + 25, b->radius_bullet * 0.4,
                   RED);
  gfx_filledCircle(b->x_bullet - 38, b->y_bullet + 25, b->radius_bullet * 0.3,
                   YELLOW);
  gfx_filledCircle(b->x_bullet - 38, b->y_bullet + 25, b->radius_bullet * 0.2,
                   RED);
  gfx_filledCircle(b->x_bullet - 38, b->y_bullet + 25, b->radius_bullet * 0.1,
                   YELLOW);

  gfx_filledCircle(b->x_bullet + 38, b->y_bullet + 25, b->radius_bullet * 0.4,
                   RED);
  gfx_filledCircle(b->x_bullet + 38, b->y_bullet + 25, b->radius_bullet * 0.3,
                   YELLOW);
  gfx_filledCircle(b->x_bullet + 38, b->y_bullet + 25, b->radius_bullet * 0.2,
                   RED);
  gfx_filledCircle(b->x_bullet + 38, b->y_bullet + 25, b->radius_bullet * 0.1,
                   YELLOW);
}

void draw_target_bullet(const struct target *t) {
  if (t->is_shooting) {
    gfx_filledCircle(t->target_bullet_x, t->target_bullet_y, 5, RED);
    gfx_filledCircle(t->target_bullet_x, t->target_bullet_y, 2, YELLOW);
  }
}

void draw_hearts(int x_heart, int y_heart, int radius_heart, int color_heart) {
  gfx_filledCircle(x_heart - 9, y_heart - 1, radius_heart, color_heart);
  gfx_filledCircle(x_heart + 9, y_heart - 1, radius_heart, color_heart);

  gfx_filledTriangle(x_heart - 22, y_heart, x_heart, y_heart + 25, x_heart + 22,
                     y_heart, color_heart);
}

void drawExplosion(int x, int y, float radius) {
  gfx_filledTriangle(x - 7 * radius, y, x + 7 * radius, y, x, y - 15 * radius,
                     RED);
  gfx_filledTriangle(x - 7 * radius, y, x + 7 * radius, y, x, y + 15 * radius,
                     RED);
  gfx_filledTriangle(x, y - 7 * radius, x, y + 7 * radius, x - 15 * radius, y,
                     RED);
  gfx_filledTriangle(x, y - 7 * radius, x, y + 7 * radius, x + 15 * radius, y,
                     RED);

  gfx_filledTriangle(x - 5 * radius, y, x + 5 * radius, y, x, y - 13 * radius,
                     YELLOW);
  gfx_filledTriangle(x - 5 * radius, y, x + 5 * radius, y, x, y + 13 * radius,
                     YELLOW);
  gfx_filledTriangle(x, y - 5 * radius, x, y + 5 * radius, x - 13 * radius, y,
                     YELLOW);
  gfx_filledTriangle(x, y - 5 * radius, x, y + 5 * radius, x + 13 * radius, y,
                     YELLOW);

  gfx_filledTriangle(x - 3 * radius, y, x + 3 * radius, y, x, y - 11 * radius,
                     RED);
  gfx_filledTriangle(x - 3 * radius, y, x + 3 * radius, y, x, y + 11 * radius,
                     RED);
  gfx_filledTriangle(x, y - 3 * radius, x, y + 3 * radius, x - 11 * radius, y,
                     RED);
  gfx_filledTriangle(x, y - 3 * radius, x, y + 3 * radius, x + 11 * radius, y,
                     RED);
}

void draw_ship(const struct ship *s) {
  gfx_filledRect( // skrzyadlo lewe
      s->player_x - 28 + s->ship_speed, s->player_y - 15,
      s->player_x - 10 + s->ship_speed, s->player_y - 10, WHITE);
  gfx_filledTriangle(s->player_x - 38 + s->ship_speed, s->player_y - 15,
                     s->player_x - 28 + s->ship_speed, s->player_y - 10,
                     s->player_x - 28 + s->ship_speed, s->player_y - 15, WHITE);
  gfx_filledTriangle(s->player_x - 10 + s->ship_speed, s->player_y - 15,
                     s->player_x - 10 + s->ship_speed, s->player_y - 10,
                     s->player_x + s->ship_speed, s->player_y - 15, WHITE);

  gfx_filledRect( // skrzydlo prawe
      s->player_x + 10 + s->ship_speed, s->player_y - 15,
      s->player_x + 28 + s->ship_speed, s->player_y - 10, WHITE);
  gfx_filledTriangle(s->player_x + 28 + s->ship_speed, s->player_y - 15,
                     s->player_x + 28 + s->ship_speed, s->player_y - 10,
                     s->player_x + 38 + s->ship_speed, s->player_y - 15, WHITE);
  gfx_filledTriangle(s->player_x + s->ship_speed, s->player_y - 15,
                     s->player_x + 10 + s->ship_speed, s->player_y - 10,
                     s->player_x + 10 + s->ship_speed, s->player_y - 15, WHITE);

  gfx_filledTriangle( // czarny podklad
      s->player_x - 41 + s->ship_speed, s->player_y - 13,
      s->player_x + s->ship_speed, s->player_y - 67,
      s->player_x + 41 + s->ship_speed, s->player_y - 13, BLACK);
  gfx_filledTriangle( // bialy trojkat
      s->player_x - 38 + s->ship_speed, s->player_y - 15,
      s->player_x + s->ship_speed, s->player_y - 64,
      s->player_x + 38 + s->ship_speed, s->player_y - 15, WHITE);
  gfx_filledRect( // czarny pasek
      s->player_x - 10 + s->ship_speed, s->player_y - 55,
      s->player_x + 10 + s->ship_speed, s->player_y - 54, BLACK);
  gfx_filledRect( // bialy pasek
      s->player_x - 9 + s->ship_speed, s->player_y - 58,
      s->player_x + 9 + s->ship_speed, s->player_y - 55, WHITE);
  gfx_filledRect( // lewe dzialo
      s->player_x - 41 + s->ship_speed, s->player_y - 42,
      s->player_x + 36 + s->ship_speed, s->player_y - 35, BLUE);

  gfx_filledRect( // okno
      s->player_x - 5 + s->ship_speed, s->player_y - 54,
      s->player_x + 5 + s->ship_speed, s->player_y - 35, CYAN);
  gfx_filledCircle(s->player_x, s->player_y - 56, 5, CYAN);

  gfx_filledCircle( // swiatelko dziala
      s->player_x - 38, s->player_y - 27, 3, RED);
  gfx_filledCircle(s->player_x + 38, s->player_y - 27, 3, RED);
  gfx_circle(s->player_x + 38, s->player_y - 27, 1, WHITE);
  gfx_circle(s->player_x - 38, s->player_y - 27, 1, WHITE);

  gfx_filledTriangle( // skrzydla na srodku statku
      s->player_x + 6 + s->ship_speed, s->player_y - 25,
      s->player_x + 6 + s->ship_speed, s->player_y - 35,
      s->player_x + 15 + s->ship_speed, s->player_y - 25, RED);
  gfx_filledTriangle(s->player_x - 6 + s->ship_speed, s->player_y - 25,
                     s->player_x - 6 + s->ship_speed, s->player_y - 35,
                     s->player_x - 15 + s->ship_speed, s->player_y - 25, RED);
  gfx_filledTriangle(s->player_x + 6 + s->ship_speed, s->player_y - 25,
                     s->player_x + 15 + s->ship_speed, s->player_y - 8,
                     s->player_x + 15 + s->ship_speed, s->player_y - 25, RED);
  gfx_filledTriangle(s->player_x - 6 + s->ship_speed, s->player_y - 25,
                     s->player_x - 15 + s->ship_speed, s->player_y - 8,
                     s->player_x - 15 + s->ship_speed, s->player_y - 25, RED);

  gfx_filledCircle( // rakieta  nr 1
      s->player_x + s->ship_speed, s->player_y - 7 + s->rocket_under_ship, 8,
      RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 7, RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 6, RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 5, RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 4, RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 3, YELLOW);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 7 + s->rocket_under_ship, 2, RED);

  gfx_filledCircle( // rakieta nr 2
      s->player_x + s->ship_speed, s->player_y - 4 + s->rocket_under_ship, 5,
      RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 4 + s->rocket_under_ship, 4, YELLOW);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 4 + s->rocket_under_ship, 3, RED);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 4 + s->rocket_under_ship, 2, YELLOW);
  gfx_filledCircle(s->player_x + s->ship_speed,
                   s->player_y - 4 + s->rocket_under_ship, 1, RED);
}

void draw_target(const struct target *t) {
  if (!t->explosion) {
    gfx_filledCircle(t->x, t->y, t->target_size, GREEN);
    gfx_filledCircle(t->x, t->y, t->target_size * 0.8, BLUE);
    gfx_filledRect(t->x - 35, t->y - 20, t->x - 27, t->y + 25, GREEN);
    gfx_filledRect(t->x + 35, t->y - 20, t->x + 27, t->y + 25, GREEN);
  } else {
    drawExplosion(t->x, t->y, t->radius);
  }
}

void move_target(struct target *t) {
  int random = rand() % (gfx_screenWidth() - 150);
  int random2 = rand() % gfx_screenHeight() / 4;

  if (!t->explosion) {
    t->x = t->x + t->x_velocity;
    t->y = t->y + t->y_velocity;

    if ((t->y > gfx_screenHeight() / 2) || (t->y < 0)) {
      t->y_velocity = -(t->y_velocity);
    }

    if ((t->x > gfx_screenWidth() - 20) || (t->x < 0)) {
      t->x_velocity = -(t->x_velocity);
    }
  }

  if (t->explosion) {
    t->radius += 0.2;
  }

  if (t->explosion && (t->radius > 3.0)) {
    t->explosion = 0;
    t->x = random;
    t->y = random2;
    t->y_velocity = -(t->y_velocity);
    t->x_velocity = -(t->x_velocity);
  }
}

int main() {
  if (gfx_init())
    exit(3);
  srand(time(NULL));

  const int bullet_speed = 2;
  int is_shooting = 0;
  int points = 0;
  int num_hearts = 3;
  int num_bullets = 1;
  int num_targets = 1;
  int num_ship = 1;
  int level = 0;
  int level_changing = 0;
  void *tmp;

  struct bullet b[num_bullets];
  for (int i = 0; i < num_bullets; i++) {
    b[i].radius_bullet = 15;
  }

  struct ship s[num_ship];
  s[0].player_x = gfx_screenWidth() / 2;
  s[0].player_y = gfx_screenHeight() - 20;
  s[0].ship_speed = 0;
  s[0].rocket_under_ship = -1;

  struct target *t =
      (struct target *)malloc(num_targets * sizeof(struct target));
  if (t == NULL) {
    printf("Memory leak error!");
    return -1;
  }

  for (int i = 0; i < num_targets; i++) {
    t[i].is_shooting = 0;
    t[i].x = (rand() % 45) * 15;
    t[i].y = (rand() % 5) * 35;
    t[i].x_velocity = -1;
    t[i].y_velocity = -1;
    t[i].target_bullet_x = 0;
    t[i].target_bullet_y = 0;
    t[i].explosion = 0;
    t[i].active = 0;
    t[i].target_size = 20;
  }

  while (1) {

    if (num_hearts > 0){
      gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);

      for (int i = 0; i < num_targets; i++) {
        draw_target_bullet(&(t[i]));
        draw_target(&(t[i]));
      }
      for (int i = 0; i < num_ship; i++)
        draw_ship(&(s[i]));
      for (int i = 0; i < num_hearts; i++) {
        draw_hearts(gfx_screenWidth() - 30 - (50 * i), gfx_screenHeight() - 30,
                    12, RED);
      }
      if (is_shooting) {
        for (int i = 0; i < num_bullets; i++) {
          draw_bullet(&(b[i]));
        }
      }

      char score[10];
      snprintf(score, sizeof(score), "Score: %d", points);
      gfx_textout(10, 10, score, WHITE);

      char stage[10];
      snprintf(stage, sizeof(stage), "Level: %d", level);
      gfx_textout(10, 50, stage, WHITE);
    }

    if (num_hearts < 1) {
      gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
      num_targets = 0;

      char game_over[10];
      snprintf(game_over, sizeof(game_over), "GAME OVER");
      gfx_textout(gfx_screenWidth() / 2 - 10, gfx_screenHeight() / 2, game_over,
                  WHITE);
      
      char press_q[20];
      snprintf(press_q, sizeof(press_q), "PRESS 'Q' TO QUIT");
      gfx_textout(gfx_screenWidth() / 2 - 38, gfx_screenHeight() / 2 + 50, press_q,
                  WHITE);
    }

    // if (level > 4){
    //   gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
    //   num_targets = 0;

    //   char victory[20];
    //   snprintf(victory, sizeof(victory), "VICTORY!");
    //   gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2, victory,
    //               WHITE);

    //   char press_q[20];
    //   snprintf(press_q, sizeof(press_q), "PRESS 'Q' TO QUIT");
    //   gfx_textout(gfx_screenWidth() / 2 - 38, gfx_screenHeight() / 2 + 50, press_q,
    //               WHITE);
    // }

    gfx_updateScreen();

    if(num_hearts > 0){
      for (int i = 0; i < num_targets; i++) {
        move_target(&(t[i]));
        if ((abs(t[i].x - s->player_x) < 100) && !t[i].is_shooting) {
          t[i].is_shooting = 1;
          t[i].target_bullet_x = t[i].x;
          t[i].target_bullet_y = t[i].y;
        }

        if (t[i].is_shooting) {
          t[i].target_bullet_y += bullet_speed;
        }
        if (t[i].is_shooting && (t[i].target_bullet_y > gfx_screenHeight())) {
          t[i].is_shooting = 0;
        }
        for (int i = 0; i < num_targets; i++) {
          if (t[i].is_shooting &&
              hypot(s->player_x - t[i].target_bullet_x,
                    s->player_y - t[i].target_bullet_y) < 50) {
            t[i].is_shooting = 0;
            num_hearts -= 1;
          }
        }
      }

      if (is_shooting) {
        for (int i = 0; i < num_targets; i++) {
          if ((t[i].explosion != 1) &&
              (hypot(b->x_bullet - t[i].x, b->y_bullet - t[i].y) < 90)) {
            t[i].explosion = 1;
            t[i].radius = 0.0;
            points += 1;

            if (points % 5 == 0){
              level += 1;
              level_changing = 1;
            }

            if (points % 5 == 0 && num_hearts < 4) {
              num_hearts += 1;
            }
          }
        }
        b->y_bullet -= 12;
      }

      s->rocket_under_ship += 10;
      if (s->rocket_under_ship > 30) {
        s->rocket_under_ship = 0;
      }

      if ((is_shooting) && ((b->y_bullet < 0) || (b->x_bullet < 0) ||
                            (b->x_bullet > gfx_screenWidth()))) {
        is_shooting = 0;
      }

      for (int i = 0; i < num_targets; ++i)
        move_target(&(t[i]));

      if (gfx_isKeyDown(SDLK_RIGHT) && (s->player_x < gfx_screenWidth()))
        s->player_x += 7;
      s->player_x += s->ship_speed;
      if (gfx_isKeyDown(SDLK_LEFT) && (s->player_x > 0))
        s->player_x -= 7;
      s->player_x -= s->ship_speed;
      if (gfx_isKeyDown(SDLK_SPACE) && !is_shooting) {
        is_shooting = 1;
        b->x_bullet = s->player_x;
        b->y_bullet = s->player_y;
      }

      if (level_changing) {
        num_targets += 1;
        if ((tmp = (struct target *)realloc(
                t, num_targets * sizeof(struct target))) == NULL) {
          printf("Blad alokacji pamieci");
          num_targets -= 1;
          level_changing = 0;
        } else {
          t = tmp;
          level_changing = 0;
        }
        for (int i = 1; i < num_targets; i++) {
          t[i].is_shooting = 0;
          t[i].x = (rand() % 45) * 15;
          t[i].y = (rand() % 5) * 35;
          t[i].x_velocity = -1;
          t[i].y_velocity = -1;
          t[i].target_bullet_x = 0;
          t[i].target_bullet_y = 0;
          t[i].explosion = 0;
          t[i].active = 0;
          t[i].target_size = 20;
        }
      }
      // printf("num targets: %d \n", num_targets);
    }
    if (gfx_isKeyDown(SDLK_q)) {
      free(t);
      return 0;
    }

    SDL_Delay(10);
  };
  free(t);
  return 0;
}
