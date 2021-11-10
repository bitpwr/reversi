
#include "reversi.hpp"

#include <iostream>

int main(int, char**)
{
    std::cout << "Welcome, you are " << reversi::white << std::endl;

    auto board = reversi::createBoard();
    reversi::print(board);

    const auto read_coord = []() -> std::optional<reversi::Position> {
        reversi::Position pos;
        std::string input;
        std::cout << "Enter positions for " << reversi::white << std::endl;
        std::cin >> input;
        if (std::isdigit(input.front())) {
            pos.x = std::stoi(input);
        } else {
            return std::nullopt;
        }
        std::cin >> input;
        if (std::isdigit(input.front())) {
            pos.y = std::stoi(input);
        } else {
            return std::nullopt;
        }
        return pos;
    };

    reversi::Position pos;
    for (;;) {
        auto tiles = std::vector<reversi::Position>{};

        while (tiles.empty()) {
            const auto coord = read_coord();
            if (coord) {
                pos = coord.value();
            } else {
                std::cout << "Good bye" << std::endl;
                return EXIT_SUCCESS;
            }

            --pos.x;
            --pos.y;
            tiles = reversi::flippedTiles(board, pos, reversi::white);

            if (!tiles.empty()) {
                setTiles(board, tiles, reversi::white);
            } else {
                std::cout << "Bad move" << std::endl;
            }
        }
        reversi::print(board);

        auto const move = reversi::bestMove(board, reversi::black);
        if (move) {
            std::cout << "Computer move " << move->x + 1 << ',' << move->y + 1
                      << std::endl;

            tiles = reversi::flippedTiles(board, *move, reversi::black);

            if (!tiles.empty()) {
                setTiles(board, tiles, reversi::black);
            }
        } else {
            std::cout << "NO MOVE" << std::endl;
        }

        reversi::print(board);
    }
}
