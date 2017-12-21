/**
 * \file "board.h"
 * \author joH1
 *
 * \version 0.1
 *
 * \brief This file contains the definition of the structure representing a
 *        board of the <b>Game of Life</b>.
 *
 * This game is a 0-player game, which means its evolution only depends on its
 * initial state and the set of \a rules that order it.
 *
 * The principle of the game is simple: given a (virtually) infinite
 * 2-dimensional grid of cells, each \e cell can be either \b dead or \b alive,
 * and on the next step of the game (within the biological register, we speak of
 * \e generations) the state of the cell is determined by the state of its
 * \b eight closest neighbors (\e Moore neighborhood).
 * The rules are as following:
 *
 * - if the cell has less than \c 2 alive neighbors, it dies (underpopulation)
 * - if the cell is alive and has \c 2 or \c 3 alive neighbors, it remains alive
 *   (survival)
 * - if the cell is alive and has more than \c 3 alive neighbors, it dies
 *   (overpopulation)
 * - and if the cell is dead and has exactly \c 3 alive neighbors, it is born
 *   (reproduction).
 *
 * The rules guiding the evolution of a Game of Life board can be reduced to a
 * simpler expression, containing only the number of alive neighbors a cell
 * needs to be born and the number of alive neighbors it needs to stay alive, or
 * in a short form:
 * \code B<number of alive neighbors to be born>S<numberof neighbors to survive> \endcode.
 * So the original rules of the Game of Life as designed by Conway can be
 * expressed as \c B2S23.
 *
 * Some famouse other rules are :
 * - \b Seeds, of form \c B2S, in this scheme, <em>no cell survives more than a
 *   single generation</em>;
 * - \b HighLife, of rule B36S23,
 * - <b>Day & Night</b>, a cellular automaton were the \e dead and \e alive
 *   states are symmetrical, meaning that dead cells mirror in behavior that of
 *   alive cells.
 */

#ifndef BOARD_H
#define BOARD_H


#include <stdbool.h>


/**
 * \brief The default number of cells in a row of the board.
 */
#define DEFAULT_BOARD_WIDTH  80

/**
 * \brief The default number of cells in a column of the board.
 */
#define DEFAULT_BOARD_HEIGHT 60

/**
 * \brief The type representing the board of the game.
 */
typedef struct board {
	unsigned int w,
	/**< The width of the board. */
	             h;
	/**< The height of the board. */
	bool *cells;
	/**< The data of the board cells. */
	const char *rules;
	/**< The rules determining the evolution of the game, as a string of format
	     \c "B<m>/S<n>". */
	bool *(*getCell)(const struct board*, int, int);
	/**< The function the board uses to retrieve a cell on itself (depends on
	     whether the board's walls wrap or not). */
} Board;


/**
 * \brief Initializes an uninitialized board with custom parameters.
 *
 * \param[in,out] board  The board to initialize
 * \param[in]     width  The number of cells in one row
 * \param[in]     height The number of cells in one column
 * \param[in]     wrap   If \c true, set up the grid as toroidal
 *
 * \return \c true iff the board was correctly initialized
 */
bool initBoard(Board *board, unsigned int width, unsigned int height, bool wrap);

/**
 * \brief Deallocates memory used by a board.
 *
 * \param[in,out] board The board to free
 */
void freeBoard(Board *board);


/**
 * \brief Switches the state of a cell: \e alive if it was \e dead, \e dead if
 *        it was \e alive.
 *
 * \param[in,out] board The board
 * \param[in]     x     The abscissa of the cell to toggle
 * \param[in]     y     The ordinate of the cell
 *
 * \return The new state of the cell (\c true means \e alive)
 */
bool toggleCell(Board *board, unsigned int x, unsigned int y);


/**
 * \brief Retrieves the rules used in this board, as a string.
 *
 * \param[in] board The board
 *
 * \return The rules of the board, in \c "B<m>/S<n>" format
 */
const char *getRules(const Board *board);

/**
 * \brief Updates the rules of the board, using a string to represent the rules.
 *
 * \param[in,out] board The board
 * \param[in]     rules The new rules, as a string of format \c "B<m>/S<n>"
 *
 * \note The standard rules are represented by the string \c "B3/S23"
 */
void setRules(Board *board, const char *rules);


/**
 * \brief Updates the board to the next generation.
 *
 * The board is iterated, and each cell is updated according to the rules
 * determining the board.
 *
 * \param[in,out] board The board to update
 *
 * \return \c true if no error occurred (memory allocation, iteration)
 */
bool updateBoard(Board *board);

/**
 * \brief Clears the board.
 *
 * \e Kills all the cells in the board, by turning them dead.
 *
 * \param[in,out] board The board to clear
 */
void clearBoard(Board *board);


#endif // BOARD_H
