package game.dice;

public class SixSidedDice implements Dice {
  public int roll() {
    return (int)(Math.random() * 6) + 1;
  }
}
