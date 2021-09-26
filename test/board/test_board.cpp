#include "../test.hpp"
#include "reversi.hpp"

using namespace reversi;

SCENARIO("Verify a new board is correctly setup")
{
    GIVEN("A newly created board")
    {
        auto const board = createBoard();
        WHEN("Checking all positions")
        {
            THEN("The board setup is correct")
            {
                REQUIRE(board.size() == 64);
                REQUIRE(std::ranges::count_if(
                          board, [](auto t) { return t == empty; }) == 60);
                REQUIRE(tileAt(board, { 3, 3 }) == black);
                REQUIRE(tileAt(board, { 4, 4 }) == black);
                REQUIRE(tileAt(board, { 4, 3 }) == white);
                REQUIRE(tileAt(board, { 3, 4 }) == white);
            }
        }
    }
}
