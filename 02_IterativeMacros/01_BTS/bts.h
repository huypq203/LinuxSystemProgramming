typedef struct bts_node_
{
    struct bts_node_ *parent;
    struct bts_node_ *left;
    struct bts_node_ *right;
    int data;
} bts_node_t;

typedef struct bts_
{
    bts_node_t *root;
} bts_t;

bts_t* init_bts();

bts_node_t* init_bts_node(int data);

void add_by_value(bts_t *bts, int data);

bts_node_t* find_left_most(bts_node_t *node);

bts_node_t* find_root(bts_node_t *node);

bts_node_t* find_inorder_successor_node(bts_node_t *node);

bts_node_t* find_preorder_successor_node(bts_node_t *node);

bts_node_t* find_postorder_successor_node(bts_node_t *node);

/* #define ITERATIVE_BTS_BEGIN(bts, node)            \ */
/* {                                                 \ */
/*     bts_node_t *_next = NULL;                     \ */
/*     for (node = find_left_most(bts->root)         \ */
/*         ; node; node = _next)                     \ */
/*     {                                             \ */
/*         _next = find_inorder_successor_node(node);        \ */

/* #define ITERATIVE_BTS_END }} */

/* #define ITERATIVE_BTS_BEGIN(bts, node)            \ */
/* {                                                 \ */
/*     bts_node_t *_next = NULL;                     \ */
/*     for (node = find_root(bts->root)              \ */
/*         ; node; node = _next)                     \ */
/*     {                                             \ */
/*         _next = find_preorder_successor_node(node);        \ */

/* #define ITERATIVE_BTS_END }} */

#define ITERATIVE_BTS_BEGIN(bts, node)            \
{                                                 \
    bts_node_t *_next = NULL;                     \
    for (node = find_left_most(bts->root)         \
        ; node; node = _next)                     \
    {                                             \
        _next = find_postorder_successor_node(node);        \

#define ITERATIVE_BTS_END }}
