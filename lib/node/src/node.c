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

node_t *find_node(node_t *node, node_predicate predicate, void *context)
{
    node_t *tmp = node;

    if (!predicate)
    {
        fprintf(stderr, "node: find_node predicate function missing\n");
        return NULL;
    }
    while (tmp)
    {
        if (predicate(tmp->data, context))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

char **map_node(node_t *node, node_str_mapper mapper)
{
    int size = node_size(node);
    node_t *tmp = node;
    char **result = malloc((size + 1) * sizeof(char *));

    if (!result) {
        fprintf(stderr, "critical error: Out of memory (node.c)\n");
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        result[i] = mapper(tmp->data);
        if (!result[i])
        {
            fprintf(stderr, "node: map_node mapper returned NULL\n");
            for (int j = 0; j < i; j++)
                free(result[j]);
            free(result);
            return NULL;
        }
        tmp = tmp->next;
    }
    result[size] = NULL;
    return result;
}

node_t *remove_node(node_t *head, node_predicate predicate, void *context)
{
    node_t *prev = NULL;
    node_t *current = head;

    while (current)
    {
        if (predicate(current->data, context))
        {
            if (prev)
                prev->next = current->next;
            else
                head = current->next;
            current->freefn(current->data);
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

int node_contains(node_t *node, int (*predicate)(void *data))
{
    node_t *tmp = node;

    if (!predicate)
    {
        fprintf(stderr, "node: node_contains predicate function missing\n");
        return 0;
    }
    while (tmp)
    {
        if (predicate(tmp->data))
            return 1;
        tmp = tmp->next;
    }
    return 0;
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
