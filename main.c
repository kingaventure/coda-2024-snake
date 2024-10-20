#include "main.h"

void add_to_end(serpent **list) {
  if (list == NULL || *list == NULL) return; 
    serpent *tmp = *list;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }

  serpent *item = malloc(sizeof(*item));
  if (item == NULL) return; 
  item->x = 0;  
  item->y = 0;
  item->type = '='; 
  item->next = NULL;

  tmp->next = item;
  tmp->type = '-';
}

void display_list(serpent **list) {
  if (list == NULL || *list == NULL) return;
  serpent *tmp = *list;

  while (tmp != NULL) {
    tmp = tmp->next;
  }
}

serpent *create_list_1() {
  serpent *first = malloc(sizeof(*first));
  if (first == NULL) return NULL;

  first->y = 416;
  first->x = 128;
  first->type = 'o';
  first->next = NULL;

  return first;
}

void create_list_2(serpent **list, int pos_y, int pos_x, char type) {
  if (list == NULL || *list == NULL) return;
  serpent *tmp = *list;

  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  serpent *too_add = malloc(sizeof(*too_add));
  if (too_add == NULL) return; 
  too_add->y = pos_y;
  too_add->x = pos_x;
  too_add->type = type;
  too_add->next = NULL;

  tmp->next = too_add;
}

void delete_list(serpent **list) {
  if (list == NULL || *list == NULL) return;
  serpent *tmp = *list;

  while (tmp != NULL) {
    serpent *to_remove = tmp;
    tmp = tmp->next;
    free(to_remove);
  }

  *list = NULL;
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    printf("Error SDL2 Init: %s\n", SDL_GetError());
    return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Erreur d'initialisation de la SDL_Image\n");
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    printf("Error while creating a window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Erreur à la création du renderer\n");
    return 1;
  }

  SDL_Surface* surface_back = IMG_Load("back.png");
  SDL_Surface* surface_serpent = IMG_Load("Snake_Body.png");
  SDL_Surface* surface_fruit = IMG_Load("Fruit.png");
  SDL_Rect fruit_pos;
  if (surface_back == NULL || surface_serpent == NULL || surface_fruit == NULL) {
    printf("Error loading image %s\n", IMG_GetError());
    return 1; 
  }
  SDL_Texture* texture_fruit = SDL_CreateTextureFromSurface(renderer, surface_fruit);
  SDL_Texture* texture_back = SDL_CreateTextureFromSurface(renderer, surface_back);
  SDL_Texture* texture_serpent = SDL_CreateTextureFromSurface(renderer, surface_serpent);
  if (texture_back == NULL || texture_serpent == NULL || texture_fruit == NULL) {
    printf("Error creating texture\n");
    return 1;
  }
  SDL_FreeSurface(surface_fruit);
  SDL_FreeSurface(surface_back);
  SDL_FreeSurface(surface_serpent);

  srand(time(NULL));

  fruit_pos.x = (rand() % 23) * 32 + 32;
  fruit_pos.y = (rand() % 23) * 32 + 32;
  fruit_pos.w = 32;
  fruit_pos.h = 32;

  serpent *Snake = create_list_1();
  create_list_2(&Snake, 416, 96, '=');
  create_list_2(&Snake, 416, 64, '-');

  SDL_Rect background = {0, 0, 800, 800};

  SDL_Rect tête_serpent_droite = {64, 0, 32, 32};
  SDL_Rect tête_serpent_gauche = {64, 64, 32, 32};
  SDL_Rect tête_serpent_haut = {32, 0, 32, 32};
  SDL_Rect tête_serpent_bas = {64, 32, 32, 32};

  SDL_Rect queue_serpent_droite = {0, 0, 32, 32};
  SDL_Rect queue_serpent_gauche = {0, 64, 32, 32};
  SDL_Rect queue_serpent_haut = {0, 96, 32, 32};
  SDL_Rect queue_serpent_bas = {0, 32, 32, 32};

  SDL_Rect corps_serpent_horizontal = {32, 32, 32, 32};
  SDL_Rect corps_serpent_verticale = {32, 64, 32, 32};

  int direction_x = 1;  
  int direction_y = 0; 
  int speed = 32;      
  Uint32 delay = 300;   

  Uint32 last_time = SDL_GetTicks();  

  while (1) {
    Uint32 current_time = SDL_GetTicks();  
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
      } else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.scancode == SDL_SCANCODE_W && direction_y == 0) { 
          direction_x = 0;
          direction_y = -1;
        } else if (e.key.keysym.scancode == SDL_SCANCODE_S && direction_y == 0) { 
          direction_x = 0;
          direction_y = 1;
        } else if (e.key.keysym.scancode == SDL_SCANCODE_A && direction_x == 0) { 
          direction_x = -1; 
          direction_y = 0;
        } else if (e.key.keysym.scancode == SDL_SCANCODE_D && direction_x == 0) { 
          direction_x = 1;
          direction_y = 0;
        }
      }
    }
    
    if (current_time - last_time > delay) {
      last_time = current_time;
      int new_x = Snake->x + (direction_x * speed);
      int new_y = Snake->y + (direction_y * speed);
      if (new_x < 32 || new_x >= 768 || new_y < 32 || new_y >= 768) {
        printf("le serpent c'est mangé un mur !\n");
        SDL_Quit();
        exit(0);
      }    
      serpent *tmp = Snake;
      int previous_x = tmp->x;
      int previous_y = tmp->y;
      tmp->x = new_x;
      tmp->y = new_y;
      tmp = tmp->next;
      while (tmp != NULL) {
      int current_x = tmp->x;
      int current_y = tmp->y;
      tmp->x = previous_x;
      tmp->y = previous_y;
      previous_x = current_x;
      previous_y = current_y;
      tmp = tmp->next;
      serpent *tmp = Snake->next;
      while (tmp != NULL) {
      if (Snake->x == tmp->x && Snake->y == tmp->y) {
        printf("le serpent c'est mordu\n");
        SDL_Quit();
        exit(0);
      }
      tmp = tmp->next;
}
      }

      if (Snake->x == fruit_pos.x && Snake->y == fruit_pos.y) {
        fruit_pos.x = (rand() % 23) * 32 + 32;  
        fruit_pos.y = (rand() % 23) * 32 + 32;  
        add_to_end(&Snake);
      }        
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture_back, NULL, &background);
      tmp = Snake;
      SDL_Rect position;
      while (tmp != NULL) {
      position.x = tmp->x;
      position.y = tmp->y;
      position.w = 32;
      position.h = 32;
      if (tmp->type == 'o') {
        SDL_RenderCopy(renderer, texture_serpent, &tête_serpent_droite, &position);
      } else if (tmp->type == '-' && tmp->next == NULL) {
        SDL_RenderCopy(renderer, texture_serpent, &queue_serpent_droite, &position);
      } else {
        SDL_RenderCopy(renderer, texture_serpent, &corps_serpent_horizontal, &position);
      }
      tmp = tmp->next;
    }
    SDL_RenderCopy(renderer, texture_fruit, NULL, &fruit_pos);
    SDL_RenderPresent(renderer);
   }
  SDL_Delay(10);  
  }

  delete_list(&Snake);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}