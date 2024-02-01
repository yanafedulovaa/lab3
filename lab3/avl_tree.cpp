#include <iostream>
#include <algorithm>
#include "avl_tree.h"
using namespace std;



int AVLTree::get_height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int AVLTree::t_height(Node* node) {
    if (node == NULL) {
        return -1; 
    }
    else {
        int left_height = t_height(node->left);
        int right_height = t_height(node->right);
        return 1 + max(left_height, right_height); 
    }
}

int AVLTree::tree_height() {
    return t_height(root);
}


int AVLTree::get_balance_factor(Node* node) {
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}


Node* AVLTree::right_rotation(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}


Node* AVLTree::left_rotation(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}


Node* AVLTree::insert_node(Node* node, int num)
{
    if (node == NULL)
        return new Node(num);

    if (num < node->key)
        node->left = insert_node(node->left, num);
    else if (num > node->key)
        node->right = insert_node(node->right, num);
    else
        return node;

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance_factor(node);

    if (balance > 1) {
        if (num < node->left->key) {
            return right_rotation(node);
        }
        else {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    }

    if (balance < -1) {
        if (num > node->right->key) {
            return left_rotation(node);
        }
        else {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
    }

    return node;
}


Node* AVLTree::delete_node(Node* node, int num)
{
    if (node == NULL)
        return node;

    if (num < node->key)
        node->left = delete_node(node->left, num);
    else if (num > node->key)
        node->right = delete_node(node->right, num);
    else {
        if (node->left == NULL || node->right == NULL) {
            Node* temp = (node->left != NULL) ? node->left : node->right;

            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            Node* temp = min_tree(node->right);
            node->key = temp->key;
            node->right = delete_node(node->right, temp->key);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance_factor(node);

    if (balance > 1) {
        if (get_balance_factor(node->left) >= 0) {
            return right_rotation(node);
        }
        else {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    }

    if (balance < -1) {
        if (get_balance_factor(node->right) <= 0) {
            return left_rotation(node);
        }
        else {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
    }

    return node;
}


Node* AVLTree::min_tree(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}


void AVLTree::in_order(Node* node) {
    if (node == NULL)
        return;

    in_order(node->left);
    cout << node->key << " ";
    in_order(node->right);
}


void AVLTree::insert_num(int num) {
    root = insert_node(root, num);
}


void AVLTree::delete_num(int num) {
    root = delete_node(root, num);
}


void AVLTree::print_inorder() {
    in_order(root);
    cout << endl;
}


bool AVLTree::search_num(int num) {
    Node* cur = root;

    while (cur != nullptr) {
        if (num < cur->key)
            cur = cur->left;
        else if (num > cur->key)
            cur = cur->right;
        else
            return true;
    }

    return false;
}


AVLTree::~AVLTree() {
    delete_tree(root);
}


void AVLTree::delete_tree(Node* node) {
    if (node == nullptr)
        return;

    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}


