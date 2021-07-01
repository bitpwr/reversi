
#include "reversi.hpp"

#include <iostream>

int main(int, char**)
{
    std::cout << "Welcome, you are " << white << std::endl;

    auto board = createBoard();
    print(board);

    size_t x{};
    size_t y{};

    for (;;) {
        std::cout << "Enter positions for " << white << std::endl;
        std::cin >> x;
        std::cin >> y;
        --x;
        --y;
        auto tiles = flippedTiles(board, x, y, white);

        if (!tiles.empty()) {
            setTiles(board, tiles, white);
        }
        print(board);

        std::cout << "Enter positions for " << black << std::endl;
        std::cin >> x;
        std::cin >> y;
        --x;
        --y;
        tiles = flippedTiles(board, x, y, black);

        if (!tiles.empty()) {
            setTiles(board, tiles, black);
        }
        print(board);
    }
}
