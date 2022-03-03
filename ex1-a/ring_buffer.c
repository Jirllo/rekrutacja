#include "ring_buffer.h"

bool ring_buffer_init(struct ring_buffer *me, uint8_t *data_buffer, size_t data_buffer_size)
{
    if(data_buffer_size == 0)
        return false;
    else
    {
        me->data_buffer = data_buffer;
        me->first = 0;
        me->end = 0;
        me->data_buffer_size = data_buffer_size;

        return true;
    }
}

bool ring_buffer_clear(struct ring_buffer *me)
{
    me->first = 0;
    me->end = 0;
    return true;
}

bool ring_buffer_is_empty(const struct ring_buffer *me)
{
    if(me->end == me->first)
        return true;
    else
        return false;
}

bool ring_buffer_get_size(const struct ring_buffer *me, size_t *current_size)
{
    if(me->end >= me->first)
        *current_size = me->end - me->first;
    else
        *current_size = me->data_buffer_size + me->end - me->first;
    return true;
}

bool ring_buffer_get_max_size(const struct ring_buffer *me, size_t *max_size)
{
    *max_size = me->data_buffer_size;
    return true;
}

bool ring_buffer_put(struct ring_buffer *me, uint8_t data)
{
    if((me->end-me->first) == me->data_buffer_size)
        return false;
    else
    {
        me->data_buffer[me->end] = data;
        me->end++;
        me->end %= me->data_buffer_size;
        if(me->end == me->first){
            // if end index overlayied start index then end index was increment
            // to anable distinguish between full and empty buffor
            me->end += me->data_buffer_size;
        }
        return true;
    }
}

bool ring_buffer_get(struct ring_buffer *me, uint8_t *data)
{
    if(me->end == me->first)
        return false;
    else
    {
        *data = me->data_buffer[me->first];
        if((me->end-me->first) == me->data_buffer_size){
            // if end index was indicated to full buffor
            // (end and start index was overlayied)
            // and last element will pulls then
            // end index must be set to last index
            me->end -= me->data_buffer_size;
        }
        me->first ++;
        me->first %= me->data_buffer_size;
        return true;
    }
}
