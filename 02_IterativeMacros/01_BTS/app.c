#include "bts.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    bts_t *bts = init_bts();

    add_by_value(bts, 10);
    add_by_value(bts, 7);
    add_by_value(bts, 12);
    add_by_value(bts, 17);
    add_by_value(bts, 20);
    add_by_value(bts, 13);

    bts_node_t *node = NULL;

    ITERATIVE_BTS_BEGIN(bts, node)
        printf("%d ", node->data);
    ITERATIVE_BTS_END;
    
    printf("\n");

    return 0;
}
