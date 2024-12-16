#if !defined(NODE_H)
#define NODE_H

typedef struct node_s
{
    void *data; /** Pointer to the data stored in the node */
    struct node_s *next;
    void (*freefn)(void *data);
} node_t;

/**
 * Creates a new node with the specified data
 */
node_t *create_node(void *data, void (*freefn)(void *data));
/**
 * Appends a new node with the specified data at the end of the linked list
 */
node_t *push_node(node_t *node, void *data, void (*freefn)(void *data));

/**
 * Returns the node size
 */
int node_size(node_t *node);

/**
 * Frees the nodes using the specified free function
 */
void free_nodes(node_t *node);

#endif // NODE_H
