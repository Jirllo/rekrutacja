#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//------------------------------------------------------------------------------

struct ring_buffer
{
    /** TODO: Fill ring buffer structure. */
    uint8_t *data_buffer;
    size_t data_buffer_size;
    size_t first;
    size_t end;
};

//------------------------------------------------------------------------------

/**
 * @brief   Initializes ring buffer structure.
 * @param   [inout] me - ring buffer structure to be initialized
 * @param   [in] data_buffer - memory buffer where ring buffer data will be stored
 * @param   [in] data_buffer_size - size of provided memory buffer (`data_buffer` argument)
 * @return  true if initialized sucessfully, otherwise false
 */
bool ring_buffer_init(struct ring_buffer *me, uint8_t *data_buffer, size_t data_buffer_size);

/**
 * @brief   Clears ring buffer data.
 * @param   [inout] me - ring buffer structure
 * @return  true if cleared sucessfully, otherwise false
 */
bool ring_buffer_clear(struct ring_buffer *me);

/**
 * @brief   Checks if ring buffer is empty.
 * @param   [in] me - ring buffer structure
 * @return  true if empty sucessfully, otherwise false
 */
bool ring_buffer_is_empty(const struct ring_buffer *me);

/**
 * @brief   Gets current number of ring buffer elements.
 * @param   [in] me - ring buffer structure
 * @param   [out] current_size - number of currently used data elements
 * @return  true if successfully acquired `current_size`, otherwise false
 */
bool ring_buffer_get_size(const struct ring_buffer *me, size_t *current_size);

/**
 * @brief   Gets maximum number of ring buffer elements that can be stored.
 * @param   [in] me - ring buffer structure
 * @param   [out] max_size - maximum number of data that can be stored inside ring buffer
 * @return  true if successfully acquired `max_size`, otherwise false
 */
bool ring_buffer_get_max_size(const struct ring_buffer *me, size_t *max_size);

/**
 * @brief   Appends new data to the ring buffer if there is empty place, increments current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [in] data - new data to be appended to the ring buffer
 * @return  true if data was successfully added into ring buffer, otherwise false
 */
bool ring_buffer_put(struct ring_buffer *me, uint8_t data);

/**
 * @brief   Pulls data from the ring buffer, decrements current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [out] data - container for output data
 * @return  true if data was successfully acquired from ring buffer, otherwise false
 */
bool ring_buffer_get(struct ring_buffer *me, uint8_t *data);

//------------------------------------------------------------------------------

#endif /* _RING_BUFFER_H_ */
