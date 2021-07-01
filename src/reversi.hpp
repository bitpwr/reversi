#include <array>
#include <cstddef>
#include <vector>

static constexpr auto boardSize{ 8 };
static constexpr auto empty{ '-' };
static constexpr auto white{ 'O' };
static constexpr auto black{ 'X' };

struct Position
{
    size_t x;
    size_t y;
};

using Board = std::array<char, boardSize * boardSize>;

Board createBoard();
auto setTile(Board& board, size_t x, size_t y, char tile) -> void;
auto setTiles(Board& board, std::vector<Position> const& positions, char tile)
  -> void;
auto flippedTiles(Board const& board, size_t x, size_t y, char tile)
  -> std::vector<Position>;
auto print(Board& board) -> void;
