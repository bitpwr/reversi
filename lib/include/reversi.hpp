#include <array>
#include <cstddef>
#include <optional>
#include <vector>

namespace reversi {

static constexpr auto boardSize{ 8 };
static constexpr auto empty{ '-' };
static constexpr auto white{ 'O' };
static constexpr auto black{ 'X' };

using Tile = char;
using Board = std::array<Tile, boardSize * boardSize>;

struct Position
{
    size_t x;
    size_t y;
};

auto createBoard() -> Board;
auto tileAt(Board const& board, const Position pos) -> std::optional<Tile>;

auto setTile(Board& board, const Position pos, Tile tile) -> void;
auto setTiles(Board& board, std::vector<Position> const& positions, Tile tile)
  -> void;
auto flippedTiles(Board const& board, Position const pos, Tile const tile)
  -> std::vector<Position>;
auto bestMove(Board const& board, Tile tile) -> std::optional<Position>;
auto print(Board& board) -> void;

}
