/**
 * @file tree.c
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief An implementation of the Red-Black BST data structure.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */
#include "tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool RED = true;
bool BLACK = false;

struct _Node;

typedef struct _Node
{
    Comparable key;
    Dynamic value;
    struct _Node* left;
    struct _Node* right;
    int size;
    bool color;
} Node;

Node* mk_node(Comparable key, Dynamic value, int size, bool color)
{
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->size = size;
    node->color = color;
    return node;
}

bool is_red(Node* n)
{
    return (n == NULL) ? false : n->color == RED;
}

int size(Node* n)
{
    return (n == NULL) ? 0 : n->size;
}

Node* rotate_left(Node* h)
{
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = x->left->color;
    x->left->color = RED;
    x->size = h->size;
    h->size = size(h->left) + size(h->right) + 1;
    return x;
}

Node* rotate_right(Node* h)
{
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = x->right->color;
    x->right->color = RED;
    x->size = h->size;
    h->size = size(h->left) + size(h->right) + 1;
    return x;
}

void flip_colors(Node* n)
{
    if (n != NULL) {
        n->color = !(n->color);
    } else return;
    if (n->left != NULL)
    {
        n->left->color = !(n->left->color);
    }
    if (n->right != NULL)
    {
        n->right->color = !(n->right->color);
    }
}

typedef struct _Tree
{
    Node* root;
} Tree;

void node_print_rec(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    else {
        printf("\"O\": {");
    }
    printf("\"left\": {");
    node_print_rec(node->left);
    printf("}, \"right\": {");
    node_print_rec(node->right);    
    printf("}}");
}

void node_print(Node* node)
{
    printf("{");
    node_print_rec(node);
    printf("}\n");   
}

void tree_print(Tree* tree)
{
    if (tree->root == NULL)
    {
        printf("{}\n");
    }
    else
    {
        node_print(tree->root);
    }
}

int tree_size(Tree* tree)
{
    return size(tree->root);
}

Option get(Node* n, Comparable key)
{
    if (n == NULL)
    {
        return none();
    }
    int cmp = compare(key, n->key);
    if (cmp < 0) 
    {
        return get(n->left, key); 
    }
    else if (cmp > 0) 
    { 
        return get(n->right, key); 
    }
    else
    {
        return some(n->value);
    } 
}

Option tree_get(Tree* tree, Comparable key)
{
    return get(tree->root, key);
}

Node* put(Node* n, Comparable key, Dynamic value)
{
    if (n == NULL)
    {
        return mk_node(key, value, 1, RED);
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        n->left = put(n->left, key, value);
    }
    else if (cmp > 0)
    {
        n->right = put(n->right, key, value);
    } 
    else 
    {
        n->value = value;
    }
    if (is_red(n->right) && !is_red(n->left))
    {
        n = rotate_left(n);
    }
    if (is_red(n->left) && is_red(n->left->left))
    {
        n = rotate_right(n);
    }
    if (is_red(n->left) && is_red(n->right))
    {
        flip_colors(n);
    }
    n->size = 1 + size(n->left) + size(n->right);
    return n;
}

void tree_put(Tree* tree, Comparable key, Dynamic value)
{
    tree->root = put(tree->root, key, value);
    tree->root->color = BLACK;
}

bool tree_is_empty(Tree* tree)
{
    return tree->root->size == 0;
}

bool tree_contains(Tree* tree, Comparable key)
{
    return tree_get(tree, key).type != NONE;
}

Node* balance(Node* n)
{
    if(is_red(n->right))
    {
        n = rotate_left(n);
    }
    if (is_red(n->left) && is_red(n->left->left))
    {
        n = rotate_right(n);
    }
    if (is_red(n->left) && is_red(n->right))
    {
        flip_colors(n);
    }
    n->size = 1 + size(n->left) + size(n->right);
    return n;
}

Node* move_red_left(Node* n)
{
    flip_colors(n);
    if (is_red(n->right->left))
    {
        n->right = rotate_right(n->right);
        n = rotate_left(n);
        flip_colors(n);
    }
    return n;
}

Node* move_red_right(Node* n)
{
    flip_colors(n);
    if (is_red(n->left->left))
    {
        n = rotate_right(n);
        flip_colors(n);
    }
    return n;
}

Node* node_min(Node* n)
{
    if(n->left == NULL)
    {
        return n;
    }
    else return node_min(n->left);
}

Node* node_remove_min(Node* n)
{
    if(n->left == NULL)
    {
        free(n);
        return NULL;
    }
    if(!is_red(n->left) && !is_red(n->left->left))
    {
        n = move_red_left(n);
    }

    n->left = node_remove_min(n->left);
    return balance(n);
}

Node* node_remove(Node* n, Comparable key)
{
    if (compare(key, n->key) < 0)
    {
        if (!is_red(n->left) && !is_red(n->left->left))
        {
            n = move_red_left(n);
        }
        n->left = node_remove(n->left, key);
    }
    else
    {
        if (is_red(n->left))
        {
            n = rotate_right(n);
        }
        if (compare(key, n->key) == 0 && (n->right == NULL))
        {
            free(n);
            return NULL;
        }
        if (!is_red(n->right) && !is_red(n->right->left))
        {
            n = move_red_right(n);
        }
        if (compare(key, n->key) == 0)
        {
            Node* x = node_min(n->right);
            n->key = x->key;
            n->value = x->value;
            n->right = node_remove_min(n->right);
        }
        else
        {
            n->right = node_remove(n->right, key);
        }
    }
    return balance(n);
}

void tree_remove(Tree* tree, Comparable key)
{
    if(!tree_contains(tree, key))
    {
        return;
    }
    if (!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove(tree->root, key);
    if (tree->root->size != 0)
    {
        tree->root->color = BLACK;
    }
}

void tree_remove_min(Tree* tree)
{
    if (tree->root->size == 0)
    {
        return;
    }
    if(!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove_min(tree->root);
    if (tree->root->size > 0)
    {
        tree->root->color = BLACK;
    }
}

Node* node_remove_max(Node* n)
{
    if(is_red(n->left))
    {
        n = rotate_right(n);
    }

    if(n->right == NULL)
    {
        free(n);
        return NULL;
    }

    if(!is_red(n->right) && !is_red(n->right->left))
    {
        n = move_red_right(n);
    }

    n->right = node_remove_max(n->right);

    return balance(n);
}

void tree_remove_max(Tree* tree)
{
    if (tree->root->size == 0)
    {
        return;
    }
    if(!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove_max(tree->root);
    if (tree->root->size > 0)
    {
        tree->root->color = BLACK;
    }
}

Tree* tree_init()
{
    Tree* tree = malloc(sizeof(Tree));
    return tree;
}

void tree_destroy(Tree* tree)
{
    do
    {
        tree_remove_min(tree);
        tree_remove_max(tree);
    }
    while(tree->root->color != BLACK);
    free(tree);
}
