#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include "binary_search_tree.h"
using namespace std;



Node1* BST::min_tree(Node1* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

int BST::t_height(Node1* node) {
    if (node == NULL) {
        return -1; // ?????? ??????? ????????? ????? -1
    }
    else {
        int left_height = t_height(node->left);
        int right_height = t_height(node->right);
        return 1 + max(left_height, right_height); // ?????????? ???????????? ?????? ????????? +1
    }
}

int BST::tree_height() {
    return t_height(root);
}

Node1* BST::insert_node(Node1* node, int num) {
    if (node == NULL)
        return new Node1(num);

    if (num < node->key)
        node->left = insert_node(node->left, num);
    else if (num > node->key)
        node->right = insert_node(node->right, num);

    return node;
}


void BST::insert_num(int num) {
    root = insert_node(root, num);
}


Node1* BST::delete_node(Node1* node, int num) {
    if (node == NULL)
        return node;

    if (num < node->key)
        node->left = delete_node(node->left, num);
    else if (num > node->key)
        node->right = delete_node(node->right, num);
    else {
        if (node->left == NULL) {
            Node1* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {
            Node1* temp = node->left;
            delete node;
            return temp;
        }

        if (node->left != NULL && node->right != NULL) { // ??????????? ????????
            Node1* temp = min_tree(node->right);
            node->key = temp->key;
            node->right = delete_node(node->right, temp->key);
        } // ???????? if

    }

    return node;
}


void BST::delete_num(int num) {
    root = delete_node(root, num);
}



void BST::in_order(Node1* node) {
    if (node == NULL)
        return;

    in_order(node->left);
    cout << node->key << " ";
    in_order(node->right);
}

void BST::print_inorder() {
    in_order(root);
    cout << endl;
}


void BST::pre_order(Node1* node)
{
    if (node == NULL)
        return;
    cout << node->key << " ";
    pre_order(node->left);
    pre_order(node->right);

}

void BST::print_preorder() {
    pre_order(root);
    cout << endl;
}

void BST::post_order(Node1* node)
{
    if (node == NULL)
        return;
    post_order(node->left);
    post_order(node->right);
    cout << node->key << " ";
}

void BST::print_postorder() {
    pre_order(root);
    cout << endl;
}

void BST::width_trav(Node1* node) {
    if (node == NULL) {
        return;
    }

    queue<Node1*> q;
    q.push(node);

    while (!q.empty()) {
        Node1* current = q.front();
        q.pop();

        cout << current->key << " ";

        if (current->left != NULL) {
            q.push(current->left);
        }

        if (current->right != NULL) {
            q.push(current->right);
        }
    }
}

void BST::print_width() {
    width_trav(root);
}


bool BST::search_num(int num) {
    Node1* current = root;

    while (current != NULL) {
        if (num < current->key)
            current = current->left;
        else if (num > current->key)
            current = current->right;
        else
            return true;
    }

    return false;
}


BST::~BST() {
    delete_tree(root);
}


void BST::delete_tree(Node1* node) {
    if (node == NULL)
        return;

    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}



void fillRandomArray(int arr[], int size)
{

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 50; // ?????????? ????????? ????? ?? 0 ?? 500
    }
}



