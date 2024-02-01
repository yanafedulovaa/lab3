#pragma once

struct Node1 {
    int key;
    Node1* left;
    Node1* right;

    Node1(int num) : key(num), left(NULL), right(NULL) {}
};


class BST {
private:
    Node1* root;
    Node1* min_tree(Node1* node);
    Node1* insert_node(Node1* node, int num);
    Node1* delete_node(Node1* node, int num);
    void in_order(Node1* node);
    void pre_order(Node1* node);
    void post_order(Node1* node);
    void width_trav(Node1* node);
    void delete_tree(Node1* node);
    int t_height(Node1* node);

public:
    BST() : root(NULL) {}
    ~BST();
    int tree_height();
    void insert_num(int num);
    void delete_num(int num);
    void print_inorder();
    void print_preorder();
    void print_postorder();
    void print_width();
    bool search_num(int num);

};