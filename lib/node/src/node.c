#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node_t *create_node(void *data, void (*freefn)(void *data))
{
    node_t *node = malloc(sizeof(node_t));

    if (node == NULL)
    {
        perror("malloc");
        return NULL;
    }
    node->data = data;
    node->freefn = freefn;
    node->next = NULL;
    return node;
}

node_t *push_node(node_t *node, void *data, void (*freefn)(void *data))
{
    node_t *new = malloc(sizeof(node_t));
    node_t *current;

    if (new == NULL)
    {
        perror("malloc");
        return NULL;
    }
    new->data = data;
    new->next = NULL;
    new->freefn = freefn;
    if (node == NULL)
        return new;
    current = node;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
    return node;
}

int node_size(node_t *node)
{
    int i = 0;

    for (node_t *tmp = node; tmp; i++)
        tmp = tmp->next;
    return i;
}

void free_nodes(node_t *node)
{
    node_t *tmp;

    if (node == NULL)
        return;
    while (node != NULL)
    {
        tmp = node;
        if (tmp->freefn == NULL)
        {
            fprintf(stderr, "libnode: Missing free function\n");
            exit(EXIT_FAILURE);
        }
        node = node->next;
        tmp->freefn(tmp->data);
        free(tmp);
    }
}
