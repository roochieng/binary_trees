#include "binary_trees.h"

/**
 * binary_tree_is_root - Check if node is root.
 * @node: A pointer to the node to root.
 * Return: 1 if node is a root 0 if not
 */
int binary_tree_is_root(const binary_tree_t *node)
{
	if (node == NULL || node->parent != NULL)
	{
		return (0);
	}
	else
	{
		return (1);
	}

}
