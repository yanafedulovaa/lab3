#pragma once
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int num) : key(num), left(NULL), right(NULL), height(1) {}
};


class AVLTree {
private:
    Node* root;

    int get_height(Node* node);
    int get_balance_factor(Node* node);
    Node* right_rotation(Node* y);
    Node* left_rotation(Node* x);
    Node* insert_node(Node* node, int num);
    Node* delete_node(Node* node, int num);
    Node* min_tree(Node* node);
    void in_order(Node* node);
    void delete_tree(Node* node);
    int t_height(Node* node);

public:
    AVLTree() : root(NULL) {}
    int tree_height();
    void insert_num(int num);
    void delete_num(int num);
    void print_inorder();
    bool search_num(int num);
    ~AVLTree();
}; 
