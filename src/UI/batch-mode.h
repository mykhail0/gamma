/** @file
 * Batch mode of the game.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

#ifndef BATCH_MODE_H
#define BATCH_MODE_H

#include <stdbool.h>
#include <stdint.h>

/** @brief Launch the game in the batch mode with given parameters.
 * @return @p true iff game was played successfully.
 */
extern bool batch_mode(unsigned long long* line, uint32_t width,
                       uint32_t height, uint32_t players, uint32_t areas);

#endif /* BATCH_MODE_H */
