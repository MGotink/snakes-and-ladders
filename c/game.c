#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Snake {
  int Position;
  int Offset;
};

struct Ladder {
  int Position;
  int Offset;
};

void CreateSnakes(struct Snake *Snakes);
void CreateLadders(struct Ladder *Ladders);
void PlayGame(unsigned int BoardSize, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders);
unsigned int RollDice(void);
unsigned int UpdatePosition(unsigned int BoardSize, unsigned int Position, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders);
unsigned int GetSpecialCellOffset(unsigned int BoardSize, unsigned int Position, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders);

int main(int argc, char *argv[]) {
  unsigned int BoardSize = 5 * 5;
  struct Snake Snakes[2];
  CreateSnakes(&Snakes[0]);
  struct Ladder Ladders[2];
  CreateLadders(&Ladders[0]);
  unsigned int NumberOfSnakes = sizeof(Snakes) / sizeof(Snakes[0]);
  unsigned int NumberOfLadders = sizeof(Ladders) / sizeof(Ladders[0]);

  srand(time(NULL));
  
  PlayGame(BoardSize, &Snakes[0], NumberOfSnakes, &Ladders[0], NumberOfLadders);
}

void CreateSnakes(struct Snake *Snakes) {
  Snakes[0].Position = 15;
  Snakes[0].Offset = -10;
  Snakes[1].Position = 21;
  Snakes[1].Offset = -11;
}

void CreateLadders(struct Ladder *Ladders) {
  Ladders[0].Position = 3;
  Ladders[0].Offset = 11;
  Ladders[1].Position = 12;
  Ladders[1].Offset = 11;
}

void PlayGame(unsigned int BoardSize, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders) {
  bool Finished = false;
  unsigned int Position = 0;

  do {
    unsigned int DiceValue = RollDice();
    printf("rolled %d\n", DiceValue);
    
    Position += DiceValue;
    printf("updated player position to %d\n", Position);

    Position = UpdatePosition(BoardSize, Position, &Snakes[0], NumberOfSnakes, &Ladders[0], NumberOfLadders);
    printf("updated player position to %d\n", Position);
    
    Finished = Position == BoardSize;
    printf("player finished: %s\n", Finished? "true" : "false"); 
  } while(!Finished);
}

unsigned int RollDice(void) {
  return 1 + (rand() % 6);
}

unsigned int UpdatePosition(unsigned int BoardSize, unsigned int Position, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders) {
  int Offset = GetSpecialCellOffset(BoardSize, Position, Snakes, NumberOfSnakes, Ladders, NumberOfLadders);

  if(Offset == 0) {
    return Position;
  }

  printf("updating position with offset %d\n", Offset);

  return UpdatePosition(BoardSize, Position + Offset, Snakes, NumberOfSnakes, Ladders, NumberOfLadders);
}

unsigned int GetSpecialCellOffset(unsigned int BoardSize, unsigned int Position, struct Snake *Snakes, unsigned int NumberOfSnakes, struct Ladder *Ladders, unsigned int NumberOfLadders) {
  if(Position > BoardSize) {
    return (BoardSize - Position) * 2;
  }

  for(int i = 0; i < NumberOfSnakes; i++) {
    if(Snakes[i].Position == Position) {
      return Snakes[i].Offset;
    }
  }

  for(int i = 0; i < NumberOfLadders; i++) {
    if(Ladders[i].Position == Position) {
      return Ladders[i].Offset;
    }
  }

  return 0;
}

