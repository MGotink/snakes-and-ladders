package game.cell;

public class Cell {
  private int offset;

  public Cell() {
    this(0);
  }

  public Cell(int offset) {
    this.offset = offset;
  }

  public int offset() {
    return offset;
  }
}
