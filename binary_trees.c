#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h


/**
 * print_tree - Recursively store each level in an array of strings
 *
 * @tree: Pointer to the node to print
 * @offset: Offset to print
 * @depth: Depth of the node
 * @b: Buffer
 *
 * Return: length of printed tree
 */
static int print_tree(const binary_tree_t *tree, int offset, int depth, char **b)
{
	char a[6];
	int width, left, right, is_left, i;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(a, "(%03d)", tree->n);
	left = print_tree(tree->left, offset, depth + 1, b);
	right = print_tree(tree->right, offset + left + width, depth + 1, b);
	for (i = 0; i < width; i++)
		b[depth][offset + left + i] = a[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			b[depth - 1][offset + left + width / 2 + i] = '-';
		b[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			b[depth - 1][offset - width / 2 + i] = '-';
		b[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * t_height - Measures the height of a binary tree
 *
 * @tree: Pointer to the node to measures the height
 *
 * Return: The height of the tree starting
 */
static size_t t_height(const binary_tree_t *tree)
{
	size_t height_l;
	size_t height_r;

	height_l = tree->left ? 1 + t_height(tree->left) : 0;
	height_r = tree->right ? 1 + t_height(tree->right) : 0;
	return (height_l > height_r ? height_l : height_r);
}

/**
 * binary_tree_print - Prints a binary tree
 *
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, i, j;

	if (!tree)
		return;
	height = t_height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (i = 0; i < height + 1; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 255);
	}
	print_tree(tree, 0, 0, s);
	for (i = 0; i < height + 1; i++)
	{
		for (j = 254; j > 1; --j)
		{
			if (s[i][j] != ' ')
				break;
			s[i][j] = '\0';
		}
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}
