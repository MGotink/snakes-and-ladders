package game;

import game.cell.*;
import game.dice.Dice;
import game.board.Board;
import game.player.Player;

public class Game {
  private Dice dice;
  private Board board;
  private Player player;

  public Game(int width, int height, Dice dice) {
    this.dice = dice;

    player = new Player();

    board = new Board(width, height);
    setupBoard();
  }

  private void setupBoard() {
    board.addSnake(15, 5);
    board.addSnake(21, 10);
    board.addLadder(3, 14);
    board.addLadder(12, 23);
  }

  public void nextRound() {
    int dice_value = dice.roll();
    System.out.println("rolled " + dice_value);

    player.incrementPosition(dice_value);
    System.out.println("updated player position to " + player.getPosition());

    player.setPosition(board.getNewPosition(player.getPosition()));
    System.out.println("updated player position to " + player.getPosition());

    player.setFinished(board.isFinished(player.getPosition()));
    System.out.println("player finished: " + player.isFinished());
  }

  public boolean isFinished() {
    return player.isFinished();
  }
}
