#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ring_buffer.h"
#include <assert.h>
#include <string.h>

int main(int arc, char *argv[])
{
    const size_t data_size = 10;
    uint8_t data[data_size];
    struct ring_buffer ring;
    uint8_t i, res;
    size_t res_size;

    assert(ring_buffer_init(&ring, data, 0) == false); // wrong data_size argument
    assert(ring_buffer_init(&ring, data, data_size) == true); // correct arguments

    assert(ring_buffer_is_empty(&ring));
    assert(ring_buffer_get_size(&ring, &res_size) && res_size == 0);
    assert(ring_buffer_get_max_size(&ring, &res_size) && res_size == data_size);

  /* basic read/write test */
    for(i=0; i<10; i++)
        assert(ring_buffer_put(&ring, i));
    assert(ring_buffer_put(&ring, i) == false); // buffer will be full

    for(i=0; i<10; i++)
        assert(ring_buffer_get(&ring, &res));
    assert(ring_buffer_get(&ring, &res) == false); // buffer will be empty

   /* read/write test on boundunary condition */
    // (multiple write/read operation through via zero and last index in data buffer array)

    // write vector go through last index
    for(i=0; i<5; i++)
        ring_buffer_put(&ring, i);
    for(i=0; i<3; i++)
        ring_buffer_get(&ring, &res);
    for(i=0; i<8; i++)
        ring_buffer_put(&ring, i);
    assert(ring_buffer_is_empty(&ring) == false); // buffer will be full
    assert(ring_buffer_put(&ring, 0) == false); // check: is buffer full by trying pull data
    assert(ring_buffer_get_size(&ring, &res_size) && res_size == 10); // check: is buffer full by read currently used data

    // test with verification data
    uint8_t test_data[] = {5, 6, 7, 3, 4, 0, 1, 2, 3, 4};
    assert(memcmp(data, test_data, 10) == 0);

    // currently used data number if write vector index is less that read vector index
    ring_buffer_get(&ring, &res);
    assert(ring_buffer_get_size(&ring, &res_size) && res_size == 9);

    // clear ring buffer data
    assert(ring_buffer_clear(&ring));
    assert(ring_buffer_get_size(&ring, &res_size) && res_size == 0);
    assert(ring_buffer_is_empty(&ring));

    return 0;
};
