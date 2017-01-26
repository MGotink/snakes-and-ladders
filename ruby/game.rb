class Cell
  attr_reader :offset
  
  def initialize(offset=0)
    @offset = offset
  end
end

class SnakeCell < Cell; end

class LadderCell < Cell; end

class OutsideGridCell < Cell; end

class Board
  def initialize(width, height)
    @size = width * height

    # '+ 1' because we're starting at 1 for convenience, first cell (0) is start cell
    @board = Array.new(@size + 1) do |i|
      Cell.new
    end
  end

  def add_snake(at, to)
    @board[at] = SnakeCell.new(to - at)
  end

  def add_ladder(at, to)
    @board[at] = LadderCell.new(to - at)
  end

  def get_new_position(current_position)
    offset = cell_at(current_position).offset

    puts "updating position with offset #{offset} (#{cell_at(current_position).class})"
    current_position = get_new_position(current_position + offset) if offset != 0

    current_position
  end

  def is_finished?(position)
    position >= @size
  end

  private
  def cell_at(index)
    @board.fetch(index) do |i|
      OutsideGridCell.new((@size - i) * 2)
    end
  end
end

class Dice
  def roll
    raise "implement Dice#roll!"
  end
end

class SixSidedDice < Dice
  def roll
    1 + rand(6)
  end
end

class Player
  attr_reader :position
  attr_accessor :finished

  def initialize
    @position = 0
    @finished = false
  end

  def increment_position(offset)
    @position += offset
  end

  def set_position(position)
    @position = position
  end

  def finished?
    @finished
  end
end

class Game
  def initialize(dice)
    @board = Board.new(5, 5)
    setup_board(@board)

    @player = Player.new
    @dice = dice
  end

  def next_round
    dice_value = @dice.roll
    puts "rolled #{dice_value}"

    @player.increment_position(dice_value)
    puts "updated player position to #{@player.position}"

    @player.set_position(@board.get_new_position(@player.position))
    puts "updated player position to #{@player.position}"

    @player.finished = @board.is_finished?(@player.position)
    puts "player finished: #{@player.finished}"
  end

  def finished?
    @player.finished?
  end

  private
  def setup_board(board)
    board.add_snake(15, 5)
    board.add_snake(21, 10)
    board.add_ladder(3, 14)
    board.add_ladder(12, 23)
  end
end

game = Game.new(SixSidedDice.new)

while !game.finished? do
  game.next_round
  puts "====="
end

puts "done!"

