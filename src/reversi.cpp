#include "reversi.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

namespace {
auto index(size_t x, size_t y) -> size_t
{
    return y * boardSize + x;
}

auto position(size_t index) -> Position
{
    return { index % boardSize, index / boardSize };
}

auto tileCount(Board const& board, char tile) -> size_t
{
    return std::ranges::count_if(board, [tile](auto t) { return t == tile; });
}

auto onBoard(size_t x, size_t y) -> bool
{
    return x < boardSize && y < boardSize;
}

auto tileAt(Board const& board, size_t x, size_t y) -> std::optional<char>
{
    if (onBoard(x, y)) {
        return board[index(x, y)];
    }
    return std::nullopt;
}

auto free(Board const& board, size_t x, size_t y) -> bool
{
    return onBoard(x, y) && tileAt(board, x, y) == empty;
}

}

Board createBoard()
{
    Board board;

    for (auto& tile : board) {
        tile = empty;
    }

    setTile(board, 3, 3, black);
    setTile(board, 3, 4, white);
    setTile(board, 4, 3, white);
    setTile(board, 4, 4, black);

    return board;
}

auto setTile(Board& board, size_t x, size_t y, char tile) -> void
{
    board[index(x, y)] = tile;
}

auto setTiles(Board& board, std::vector<Position> const& positions, char tile)
  -> void
{
    for (auto const& pos : positions) {
        setTile(board, pos.x, pos.y, tile);
    }
}

auto flippedTiles(Board const& board, size_t x, size_t y, char tile)
  -> std::vector<Position>
{
    std::vector<Position> tiles;
    std::vector<std::pair<int, int>> directions = { { 1, 0 },  { 1, 1 },
                                                    { 0, 1 },  { -1, 1 },
                                                    { -1, 0 }, { -1, -1 },
                                                    { 0, -1 }, { 1, -1 } };

    auto const otherTile = tile == black ? white : black;

    if (free(board, x, y)) {
        for (auto const& direction : directions) {
            auto testX = x + direction.first;
            auto testY = y + direction.second;

            if (onBoard(testX, testY) &&
                tileAt(board, testX, testY) == otherTile) {
                while (tileAt(board, testX, testY) == otherTile) {
                    testX += direction.first;
                    testY += direction.second;
                }

                if (tileAt(board, testX, testY) == tile) {
                    testX -= direction.first;
                    testY -= direction.second;
                    while (tileAt(board, testX, testY) == otherTile) {
                        tiles.emplace_back(testX, testY);
                        testX -= direction.first;
                        testY -= direction.second;
                    }
                }
            }
        }
    }

    if (!tiles.empty()) {
        tiles.emplace_back(x, y);
    }

    return tiles;
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
            std::cout << board[index(x, y)] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << black << ": " << tileCount(board, black) << '\n'
              << white << ": " << tileCount(board, white) << std::endl;
}
