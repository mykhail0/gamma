/** @file
 * Interactive mode of the game.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

#ifndef INTERACTIVE_MODE_H
#define INTERACTIVE_MODE_H

#include <stdbool.h>
#include <stdint.h>

/** @brief Launch the game in the interactive mode.
 * @param[in] width   - board's width,
 * @param[in] height  - board's height,
 * @param[in] players - number of players,
 * @param[in] areas   – maximum number of areas, which one player can possess.
 * @return @p true iff launched successfully, if returned @p false, `errno`
 * informs about the error.
 */
extern bool interactive_mode(uint32_t width, uint32_t height, uint32_t players,
                             uint32_t areas);

#endif /* INTERACTIVE_MODE_H */
