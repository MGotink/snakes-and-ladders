package game;

import game.Game;
import game.dice.*;

public class GameRunner {
  public static void main(String[] args) {
    Dice dice = new SixSidedDice();
    Game game = new Game(5, 5, dice);

    while(!game.isFinished()) {
      game.nextRound();
    }
  }
}
