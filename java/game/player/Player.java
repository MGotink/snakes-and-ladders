package game.player;

public class Player {
  private int position;
  private boolean finished;

  public void incrementPosition(int amount) {
    position += amount;
  }

  public void setPosition(int position) {
    this.position = position;
  }

  public int getPosition() {
    return position;
  }

  public void setFinished(boolean finished) {
    this.finished = finished;
  }

  public boolean isFinished() {
    return finished;
  }
}
