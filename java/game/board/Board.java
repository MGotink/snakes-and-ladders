package game.board;

import game.cell.*;

public class Board {
  private int size;
  private Cell[] board;

  public Board(int width, int height) {
    size = width * height;

    // + 1 is for convenience, so we can start outside the board at 0 and the position is the array index
    board = new Cell[size + 1];
    
    for(int i = 0; i < size + 1; i++) {
      board[i] = new Cell();
    }
  }

  public void addSnake(int from, int to) {
    board[from] = new SnakeCell(to - from);
  }

  public void addLadder(int from, int to) {
    board[from] = new LadderCell(to - from);
  }

  public Cell cellAt(int position) {
    if(position >= board.length) {
      return new OutsideGridCell((size - position) * 2);
    }

    return board[position];
  }

  public int getNewPosition(int position) {
    int offset = cellAt(position).offset();

    System.out.println("updating position with offset " + offset + " (" + cellAt(position).getClass().getSimpleName() + ")");

    if(offset != 0) {
      position = getNewPosition(position + offset);
    }

    return position;
  }

  public boolean isFinished(int position) {
    return position >= size;
  }
}
