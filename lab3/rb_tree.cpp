#include <iomanip>
#include<iostream>
#include<vector>
#include "rb_tree.h"
using namespace std;



int RBT::t_height(NodeRB* node) {
    if (node == NULL) {
        return -1; 
    }
    else {
        int left_height = t_height(node->left);
        int right_height = t_height(node->right);
        return 1 + max(left_height, right_height); 
    }
}

int RBT::tree_height() {
    return t_height(root);
}


RBT::RBT() :root(NULL) {
    root = nullptr;
}

RBT::~RBT() {
    destroy(root);
}

void RBT::left_rotation(NodeRB*& root, NodeRB* x) {
    NodeRB* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
};


void RBT::right_rotation(NodeRB*& root, NodeRB* y) {
    NodeRB* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
};

void RBT::insert_num(int key)
{
    NodeRB* z = new NodeRB(key, 1, NULL, NULL, NULL);
    insert_node(root, z);
};

void RBT::insert_node(NodeRB*& root, NodeRB* node)
{
    NodeRB* x = root;
    NodeRB* y = NULL;
    while (x != NULL)
    {
        y = x;
        if (node->key > x->key)
            x = x->right;
        else
            x = x->left;
    }
    node->parent = y;
    if (y != NULL)
    {
        if (node->key > y->key)
            y->right = node;
        else
            y->left = node;
    }
    else
        root = node;
    node->color = 1;
    insertion_fixed(root, node);
};



void RBT::insertion_fixed(NodeRB*& root, NodeRB* node)
{
    NodeRB* parent;
    parent = node->parent;
    while (node != RBT::root && parent->color == 1)
    {
        NodeRB* gparent = parent->parent;
        if (gparent->left == parent)
        {
            NodeRB* uncle = gparent->right;
            if (uncle != NULL && uncle->color == 1)
            {
                parent->color = 0;
                uncle->color = 0;
                gparent->color = 1;
                node = gparent;
                parent = node->parent;
            }
            else
            {
                if (parent->right == node)
                {
                    left_rotation(root, parent);
                    swap(node, parent);
                }
                right_rotation(root, gparent);
                gparent->color = 1;
                parent->color = 0;
                break;
            }
        }
        else
        {
            NodeRB* uncle = gparent->left;
            if (uncle != NULL && uncle->color == 1)
            {
                gparent->color = 1;
                parent->color = 0;
                uncle->color = 0;

                node = gparent;
                parent = node->parent;
            }
            else
            {
                if (parent->left == node)
                {
                    right_rotation(root, parent);
                    swap(parent, node);
                }
                left_rotation(root, gparent);
                parent->color = 0;
                gparent->color = 1;
                break;
            }
        }
    }
    root->color = 0;
}


void RBT::destroy(NodeRB*& node)
{
    if (node == NULL)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}


void RBT::delete_num(int key)
{
    NodeRB* deletenode = search(root, key);
    if (deletenode != NULL)
        delete_node(root, deletenode);
}


void RBT::delete_node(NodeRB*& root, NodeRB* node)
{
    NodeRB* child, * parent;
    bool color;

    if (node->left != NULL && node->right != NULL)
    {
        NodeRB* replace = node;

        replace = node->right;
        while (replace->left != NULL)
        {
            replace = replace->left;
        }

        if (node->parent != NULL)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }

        else
            root = replace;

        child = replace->right;
        parent = replace->parent;
        color = replace->color;


        if (parent == node)
            parent = replace;
        else
        {

            if (child != NULL)
                child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == 0)
            deletion_fixed(root, child, parent);

        delete node;
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;
    if (child)
    {
        child->parent = parent;
    }

    if (parent)
    {
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }

    else
        RBT::root = child;

    if (color == 0)
    {
        deletion_fixed(root, child, parent);
    }
    delete node;

}

void RBT::deletion_fixed(NodeRB*& root, NodeRB* node, NodeRB* parent)
{
    NodeRB* othernode;
    while ((!node) || node->color == 0 && node != RBT::root)
    {
        if (parent->left == node)
        {
            othernode = parent->right;
            if (othernode->color == 1)
            {
                othernode->color = 0;
                parent->color = 1;
                left_rotation(root, parent);
                othernode = parent->right;
            }
            else
            {
                if (!(othernode->right) || othernode->right->color == 0)
                {
                    othernode->left->color = 0;
                    othernode->color = 1;
                    right_rotation(root, othernode);
                    othernode = parent->right;
                }
                othernode->color = parent->color;
                parent->color = 0;
                othernode->right->color = 0;
                left_rotation(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            othernode = parent->left;
            if (othernode->color == 1)
            {
                othernode->color = 0;
                parent->color = 1;
                right_rotation(root, parent);
                othernode = parent->left;
            }
            if ((!othernode->left || othernode->left->color == 0) && (!othernode->right || othernode->right->color == 0))
            {
                othernode->color = 1;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!(othernode->left) || othernode->left->color == 0)
                {
                    othernode->right->color = 0;
                    othernode->color = 1;
                    left_rotation(root, othernode);
                    othernode = parent->left;
                }
                othernode->color = parent->color;
                parent->color = 0;
                othernode->left->color = 0;
                right_rotation(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        node->color = 0;
}


NodeRB* RBT::search(int key)
{
    return search(root, key);
}

NodeRB* RBT::search(NodeRB* node, int key) const
{
    if (node == NULL || node->key == key)
        return node;
    else
        if (key > node->key)
            return search(node->right, key);
        else
            return search(node->left, key);
}


void RBT::print() {
    if (root == NULL)
        cout << "empty RBtree\n";
    else
        print(root);
}

void RBT::print(NodeRB* node)const {
    if (node == NULL)
        return;
    if (node->parent == NULL)
        cout << node->key << "(" << node->color << ") is root" << endl;
    else if (node->parent->left == node)
    {
        cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "left child" << endl;
    }
    else
    {
        cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << endl;
    }
    print(node->left);
    print(node->right);
}


void RBT::print_preorder() {
    if (root == NULL)
        cout << "empty RBtree\n";
    else
        pre_order(root);
};


void RBT::pre_order(NodeRB* tree)const {
    if (tree != NULL) {
        cout << tree->key << " ";
        pre_order(tree->left);
        pre_order(tree->right);
    }
}


void RBT::print_inorder() {
    if (root == NULL)
        cout << "empty RBtree\n";
    else
        in_order(root);
};


void RBT::in_order(NodeRB* tree)const {
    if (tree != NULL) {
        in_order(tree->left);
        cout << tree->key << " ";
        in_order(tree->right);
    }
}

void RBT::print_postorder() {
    if (root == NULL)
        cout << "empty RBtree\n";
    else
        post_order(root);
};


void RBT::post_order(NodeRB* tree)const {
    if (tree != NULL) {
        post_order(tree->left);
        post_order(tree->right);
        cout << tree->key << " ";
    }
}