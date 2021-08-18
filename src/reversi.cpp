#include "reversi.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

namespace reversi {

auto index(Position const& pos) -> size_t
{
    return pos.y * boardSize + pos.x;
}

auto position(size_t index) -> Position
{
    return { index % boardSize, index / boardSize };
}

auto tileCount(Board const& board, Tile tile) -> size_t
{
    return std::ranges::count_if(board, [tile](auto t) { return t == tile; });
}

auto onBoard(size_t x, size_t y) -> bool
{
    return x < boardSize && y < boardSize;
}

auto onBoard(size_t index) -> bool
{
    return index < (boardSize * boardSize);
}

auto tileAt(Board const& board, size_t x, size_t y) -> std::optional<Tile>
{
    if (onBoard(x, y)) {
        return board[index({ x, y })];
    }
    return std::nullopt;
}

auto free(Board const& board, size_t x, size_t y) -> bool
{
    return onBoard(x, y) && tileAt(board, x, y) == empty;
}

auto free(Board const& board, size_t index) -> bool
{
    return onBoard(index) && board[index] == empty;
}

auto clone(Board const& board) -> Board
{
    return Board{ board };
}

auto otherTile(Tile const tile)
{
    return tile == black ? white : black;
}

auto boardScore(Board const& board, Tile tile) -> double
{
    return tileCount(board, tile) * 1.5 - tileCount(board, otherTile(tile));
}

Board createBoard()
{
    auto board = Board{};

    for (auto& tile : board) {
        tile = empty;
    }

    setTile(board, { 3, 3 }, black);
    setTile(board, { 3, 4 }, white);
    setTile(board, { 4, 3 }, white);
    setTile(board, { 4, 4 }, black);

    return board;
}

auto setTile(Board& board, const Position pos, Tile tile) -> void
{
    board[index(pos)] = tile;
}

auto setTiles(Board& board, std::vector<Position> const& positions, Tile tile)
  -> void
{
    for (auto const& pos : positions) {
        setTile(board, pos, tile);
    }
}

auto flippedTiles(Board const& board, Position const pos, Tile const tile)
  -> std::vector<Position>
{
    std::vector<Position> tiles;
    std::vector<std::pair<int, int>> directions = { { 1, 0 },  { 1, 1 },
                                                    { 0, 1 },  { -1, 1 },
                                                    { -1, 0 }, { -1, -1 },
                                                    { 0, -1 }, { 1, -1 } };

    auto const opponentTile = otherTile(tile);

    if (free(board, pos.x, pos.y)) {
        for (auto const& direction : directions) {
            auto testX = pos.x + direction.first;
            auto testY = pos.y + direction.second;

            if (onBoard(testX, testY) &&
                tileAt(board, testX, testY) == opponentTile) {
                while (tileAt(board, testX, testY) == opponentTile) {
                    testX += direction.first;
                    testY += direction.second;
                }

                if (tileAt(board, testX, testY) == tile) {
                    testX -= direction.first;
                    testY -= direction.second;
                    while (tileAt(board, testX, testY) == opponentTile) {
                        tiles.emplace_back(testX, testY);
                        testX -= direction.first;
                        testY -= direction.second;
                    }
                }
            }
        }
    }

    if (!tiles.empty()) {
        tiles.push_back(pos);
    }

    return tiles;
}

auto bestMove(Board const& board, Tile tile) -> std::optional<Position>
{
    //  - for all free positions
    //   - if flippedTiles returns a list
    //    - clone board and apply list
    //    - put clone in a list
    //
    //  for all in list of cloned board
    //   - get the board with highest value, return that position

    std::vector<std::tuple<Position, double>> moves;

    for (auto index :
         std::views::iota(1) | std::views::take(boardSize * boardSize)) {
        if (free(board, index)) {
            auto const flipped = flippedTiles(board, position(index), tile);
            if (!flipped.empty()) {
                auto copy = clone(board);
                setTiles(copy, flipped, tile);
                moves.emplace_back(position(index), boardScore(copy, tile));
            }
        }
    }

    if (!moves.empty()) {
        auto const maxIt =
          std::ranges::max_element(moves, [](auto const& m1, auto const& m2) {
              return std::get<1>(m1) < std::get<1>(m2);
          });
        if (maxIt != moves.end()) {
            return std::get<0>(*maxIt);
        }
    }
    return std::nullopt;
}

void print(Board& board)
{
    constexpr auto numbers = std::views::iota(1) | std::views::take(boardSize);

    std::cout << "  ";
    for (auto i : numbers) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (size_t y = 0; y < boardSize; ++y) {
        std::cout << (y + 1) << ' ';
        for (size_t x = 0; x < boardSize; ++x) {
            std::cout << board[index({ x, y })] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << black << ": " << tileCount(board, black) << '\n'
              << white << ": " << tileCount(board, white) << std::endl;
}

}
