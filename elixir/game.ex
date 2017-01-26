defmodule Dice do
  def roll do
    :rand.uniform(6)
  end
end

defmodule Game do
  def play(dice, snakes, ladders) do
    play(0, dice, snakes, ladders)
  end

  def play(25, _dice, _snakes, _ladders) do
    IO.puts "done!"
  end

  def play(position, dice, snakes, ladders) do
    new_position = new_position(position, dice) |> validate_position(snakes, ladders)

    IO.puts "updated player position to #{new_position}"
    IO.puts "player finished: #{new_position == 25}"
    IO.puts "====="

    play(new_position, dice, snakes, ladders)
  end

  def new_position(position, dice) do
    dice_value = dice.roll()
    IO.puts "rolled #{dice_value}"

    position = position + dice_value
    IO.puts "updated player position to #{position}"

    position
  end

  def validate_position(position, snakes, ladders) when position > 25 do
    IO.puts "updating position with offset #{(25 - position)}"
    validate_position(25 - (position - 25), snakes, ladders)
  end

  def validate_position(position, snakes, ladders) do
    cond do
      Map.has_key?(snakes, position) ->
        IO.puts "updating position with offset #{snakes[position] - position} (Snake)"
        validate_position(snakes[position], snakes, ladders)
      Map.has_key?(ladders, position) ->
        IO.puts "updating position with offset #{ladders[position] - position} (Ladder)"
        validate_position(ladders[position], snakes, ladders)
      true ->
        IO.puts "updating position with offset 0 (Cell)"
        position
    end
  end
end

snakes = %{15 => 5, 21 => 10}
ladders = %{3 => 14, 12 => 23}

Game.play(Dice, snakes, ladders)
