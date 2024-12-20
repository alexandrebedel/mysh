#if !defined(NODE_H)
#define NODE_H

/**
 * Represents a predication function for the node_t struct.
 */
typedef int (*node_predicate)(void *data, void *context);
typedef char *(*node_str_mapper)(void *data);

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
 *
 * Or creates the node if its NULL
 */
node_t *push_node(node_t *node, void *data, void (*freefn)(void *data));

/**
 * Returns the node if the predicates function returns true
 * or NULL otherwise
 */
node_t *find_node(node_t *node, node_predicate predicate, void *context);

char **map_node(node_t *node, node_str_mapper mapper);

node_t *remove_node(node_t *head, node_predicate predicate, void *context);

/**
 * Checks if a node exists using the predicate function
 */
int node_contains(node_t *node, int (*predicate)(void *data));

/**
 * Returns the node size
 */
int node_size(node_t *node);

/**
 * Frees the nodes using the specified free function
 */
void free_nodes(node_t *node);

#endif // NODE_H
