/** @file
 * Interface for gamma game state.
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 18.03.2020
 */

#ifndef GAMMA_H
#define GAMMA_H

#include <stdbool.h>
#include <stdint.h>

#include "find-union.h"
#include "gamma-struct.h"

/** @brief Create an object for the game's state.
 * Allocate memory for the game's state object.
 * Initialize the object such that it represents the state of a new game.
 * @param[in] width   – board's width, positive number,
 * @param[in] height  – board's height, positive number,
 * @param[in] players – number of players, positive number,
 * @param[in] areas   – maximum number of areas, which one player can possess,
 *                      positive number.
 * @return a pointer to the created object or `NULL` if didn't succeed.
 */
extern gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players,
                          uint32_t areas);

/** @brief Delete the object of the game's state.
 * Delete the object passed as @p g from the memory.
 * Do nothing if the pointer is `NULL`.
 * @param[in] g       – a pointer to the deleted object.
 */
extern void gamma_delete(gamma_t* g);

/** @brief Make a move.
 * Put a piece of @p player on the field of (@p x, @p y).
 * @param[in,out] g   – a pointer to the game's state,
 * @param[in] player  – player's index, positive number not greater than the
 *                      value of @p players from function @ref gamma_new,
 * @param[in] x       – column's index, non-negative number less than the value
 *                      of @p width from function @ref gamma_new,
 * @param[in] y       – row's index, non-negative number less than the value of
 *                      @p height from function @ref gamma_new.
 * @return Value @p true, if the move was made successfully, or @p false, when
 * the move is illegal or any parameter is incorrect.
 */
extern bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Make a golden move.
 * Put a piece of @p player on the field of (@p x, @p y) taken by another
 * player, removing their piece.
 * @param[in,out] g   – a pointer to the game's state,
 * @param[in] player  – player's index, positive number not greater than the
 *                      value of @p players from function @ref gamma_new,
 * @param[in] x       – column's index, non-negative number less than the value
 *                      of @p width from function @ref gamma_new,
 * @param[in] y       – row's index, non-negative number less than the value of
 *                      @p height from function @ref gamma_new.
 * @return Value @p true, if the move was made successfully, or @p false, when
 * the player already used their golden move, the move is illegal or any
 * parameter is incorrect.
 */
extern bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x,
                              uint32_t y);

/** @brief Return the number of fields taken by the player.
 * Return the number of fields taken by the @p player.
 * @param[in] g       – a pointer to the game's state,
 * @param[in] player  – player's index, positive number not greater than the
 *                      value of @p players from function @ref gamma_new.
 * @return Number of fields taken by the player or zero if any parameter was
 * incorrect.
 */
extern uint64_t gamma_busy_fields(gamma_t* g, uint32_t player);

/** @brief Return the number of free fields where the player can put a piece on.
 * Return the number of free fields where the @p player can put their piece on
 * in the next move in the current state of the game.
 * @param[in] g       – a pointer to the game's state,
 * @param[in] player  – player's index, positive number not greater than the
 *                      value of @p players from function @ref gamma_new.
 * @return Number of free fields the player can take or zero if any parameter is
 * incorrect.
 */
extern uint64_t gamma_free_fields(gamma_t* g, uint32_t player);

/** @brief Check if the player can make a golden move.
 * Check if the @p player hasn't yet made a golden move and there is at least
 * one field taken by another player.
 * @param[in] g       – a pointer to the game's state,
 * @param[in] player  – player's index, positive number not greater than the
 *                      value of @p players from function @ref gamma_new.
 * @return Value of @p true, if the player hasn't yet made a golden move and
 * there is at least one field taken by another player and @p false otherwise.
 */
extern bool gamma_golden_possible(gamma_t* g, uint32_t player);

/** @brief Return a string description of the board.
 * Allocate a buffer in memory and put a text description of the current board's
 * state there. gamma_test.c file contains an example. Caller function
 * must free the buffer.
 * @param[in] g       – a pointer to the game's state.
 * @return Pointer to the allocated buffer with a string of board's text
 * description or `NULL` if memory allocation did not succeed.
 */
extern char* gamma_board(gamma_t* g);

#endif /* GAMMA_H */
