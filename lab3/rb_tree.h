#pragma once
struct  NodeRB
{
    int key;
    bool color;
    NodeRB* left;
    NodeRB* right;
    NodeRB* parent;
    NodeRB(int k, bool c, NodeRB* p, NodeRB* l, NodeRB* r) :
        key(k), color(c), parent(p), left(l), right(r) { };
};



class  RBT
{
private:
    void left_rotation(NodeRB*& root, NodeRB* x);
    void right_rotation(NodeRB*& root, NodeRB* y);

    void insert_node(NodeRB*& root, NodeRB* node);
    void insertion_fixed(NodeRB*& root, NodeRB* node);
    void destroy(NodeRB*& node);
    int t_height(NodeRB* node);
    void delete_node(NodeRB*& root, NodeRB* node);
    void deletion_fixed(NodeRB*& root, NodeRB* node, NodeRB* parent);

    NodeRB* search(NodeRB* node, int key) const;
    void print(NodeRB* node)const;
    void pre_order(NodeRB* tree)const;
    void in_order(NodeRB* tree)const;
    void post_order(NodeRB* tree)const;
    NodeRB* root;

public:
    RBT();
    ~RBT();
    NodeRB* search(int key);
    void insert_num(int key);
    void delete_num(int key);
    void print();
    void print_preorder();
    void print_inorder();
    void print_postorder();
    int tree_height();

};