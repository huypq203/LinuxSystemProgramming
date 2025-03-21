#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bts.h"

bts_t*
init_bts()
{
    bts_t *bts = calloc(1, sizeof(bts_t));
    if (!bts)
        return NULL;
    bts->root = NULL;
    return bts;
}

bts_node_t*
init_bts_node(int data)
{
    bts_node_t *node = calloc(1, sizeof(bts_node_t));
    if (!node)
        return NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

void
add_by_value(bts_t *bts, int data)
{
    bts_node_t *temp = NULL, *parent = NULL, *node = NULL;

    node = init_bts_node(data);
    
    if (!bts)
        return;
    
    if (!bts->root)
    {
        bts->root = node;
        return;
    }

    temp = bts->root;

    while (temp)
    {
        parent = temp;
        temp = (temp->data > data) ? temp->left : temp->right;
    }

    if (parent->data > data)
        parent->left = node;
    else
        parent->right = node;

    node->parent = parent;
}

bts_node_t*
find_left_most(bts_node_t *node)
{
    while (node->left)
        node = node->left;
    return node;
}

bts_node_t*
find_root(bts_node_t *node)
{
    if (!node)
        return NULL;

    while (node->parent)
        node = node->parent;

    return node;
}

bts_node_t*
find_inorder_successor_node(bts_node_t *node)
{
    if (!node)
        return NULL;

    // Case 1: Node has a right subtree
    if (node->right)
        return find_left_most(node->right);

    // Case 2: No right subtree, move up until we find a node that is a left child
    bts_node_t *parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

bts_node_t*
find_preorder_successor_node(bts_node_t *node)
{
    if (!node)
        return NULL;

    if (node->left)
        return node->left;

    if (node->right)
        return node->right;

    bts_node_t *parent = node->parent;
    while (parent && (node == parent->right || !parent->right))
    {
        node = parent;
        parent = parent->parent;
    }

    return parent ? parent->right : NULL;
}

bts_node_t*
find_postorder_successor_node(bts_node_t *node)
{
    if (!node || !node->parent)
        return NULL;

    bts_node_t *parent = node->parent;

    if (node == parent->left && parent->right)
    {
        bts_node_t *temp = parent->right;

        while (temp->left || temp->right)
            temp = temp->left ? temp->left : temp->right;

        return temp;
    }

    return parent;
}
