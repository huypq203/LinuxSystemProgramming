#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node_
{
    int key;
    struct bst_node_ *left;
    struct bst_node_ *right;
    int is_threaded;
} bst_node_t;

typedef struct bst_
{
    bst_node_t *root;
} bst_t;

bst_t *
create_bst(void)
{
    bst_t *bst = (bst_t *)calloc(1, sizeof(bst_t));
    
    return bst;
}

bst_node_t*
create_new_node(int key)
{
    bst_node_t *node = (bst_node_t *)calloc(1, sizeof(bst_node_t));
    node->key = key;

    return node;
}

int
add_node_to_bst(bst_t *bst, int key)
{
    if (!bst)
        return -1;

    bst_node_t *node = create_new_node(key);

    if (!bst->root)
    {
        bst->root = node;
        return 0;
    }

    bst_node_t *temp = bst->root;
    bst_node_t *parent = NULL;


    while (temp)
    {
        parent = temp;

        if (key < temp->key)
        {
            if (!temp->left)
                break;
            temp = temp->left;
        }
        else
        {
            if (!temp->right || temp->is_threaded)
                break;
            temp = temp->right;
        }
    }

    if (parent->key < node->key)
    {
        node->is_threaded = 1;
        node->right = parent -> right;
        parent->is_threaded = 0;
        parent->right = node;
    }
    else
    {
        node->is_threaded = 1;
        node->right = parent;
        parent->left = node;
    }

    return 0;
}

bst_node_t*
find_left_most(bst_node_t *node)
{
    while (node && node->left)
        node = node->left;

    return node;
}

bst_node_t*
find_next_inorder_node(bst_node_t *node)
{
    if (!node)
        return NULL;

    if (node->right && node->is_threaded == 0)
        return find_left_most(node->right);

    return node->right;
}

#define ITERATE_BST_BEGIN(bst, node) \
{\
    bst_node_t *_next;\
    for (node = find_left_most(bst->root); node; node = _next)\
    {\
        _next = find_next_inorder_node(node);\

#define ITERATE_BST_END } }

int
main()
{
    bst_t *bst;
    bst = create_bst();
    
    add_node_to_bst(bst, 10);
    add_node_to_bst(bst, 7);
    add_node_to_bst(bst, 12);
    add_node_to_bst(bst, 11);
    add_node_to_bst(bst, 3);
    add_node_to_bst(bst, 9);

    bst_node_t *node = NULL;
    ITERATE_BST_BEGIN(bst, node)
        printf("%d\n", node->key);
    ITERATE_BST_END

    return 0;
}
