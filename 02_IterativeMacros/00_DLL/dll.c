#include "dll.h"
#include <memory.h>
#include <stdlib.h>

/* Public Function Implementation to create and return
 * new empty doubly linked list*/

dll_t *
get_new_dll(){

    dll_t *dll = calloc(1, sizeof(dll_t));
    dll->head = NULL;
    return dll;
}

/* Public Function Implementation to add a new application
 *  * data to DLL */
int
add_data_to_dll (dll_t *dll, void *app_data){

    if(!dll || !app_data) return -1;
    
    dll_node_t *dll_new_node = calloc(1, sizeof(dll_node_t));
    dll_new_node->left = NULL;
    dll_new_node->right = NULL;
    dll_new_node->data = app_data;

    /*Now add this to the front of DLL*/
    if(!dll->head){
        dll->head = dll_new_node;
        return 0;
    }

    dll_node_t *first_node = dll->head;
    dll_new_node->right = first_node;
    first_node->left = dll_new_node;
    dll->head = dll_new_node;
    return 0;
}

void callback_search_registration(dll_t *dll, int (*match_key)(void const *, void const *))
{
    dll->match_key = match_key;
    return;
}

void* dll_search_by_key(dll_t const *dll, void const *key)
{
    if (!dll || !dll->head)
        return NULL;

    dll_node_t *node = dll->head;

    while (node)
    {
        if (dll->match_key(node->data, key) == 0)
            return node->data;

        node = node->right;
    }

    return NULL;
}

void callback_compare_registration(dll_t *dll, int (*compare)(void const*, void const *))
{
    dll->compare = compare;
    return;
}

void dll_priority_add_new(dll_t *dll, void *data)
{
    if (!dll || !data)
        return;

    dll_node_t *node = calloc(1, sizeof(dll_node_t));
    node->left = NULL;
    node->right = NULL;
    node->data = data;

    if (!dll->head)
    {
        dll->head = node;
        return;
    }

    dll_node_t *temp = dll->head;
    while (1)
    {
        if (dll->compare(node->data, temp->data) < 0)
        {
            node->right = temp;
            node->left = temp->left;

            if (temp->left)
                temp->left->right = node;
            else
                dll->head = node;  // Update head if inserted at the beginning

            temp->left = node;
            return;
        }
        
        if (!temp->right)
        {
            temp->right = node;
            node->left = temp;
            return;
        }
        temp = temp->right;
    }
}
