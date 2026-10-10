#include <iostream>
#include <algorithm>
using namespace std;

namespace lib {
    template<typename K>
    class Node {
    public:
        K key;
        Node<K>* left;
        Node<K>* right;
        int height;
    };

    template<typename K>
    class AVLTree {
    private:
        // Helper function for preorder traversal
        void preOrderHelper(Node<K>* node) {
            if (node != nullptr) {
                cout << node->key << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        // Helper function for insertion
        Node<K>* in(Node<K>* node, K key) {
            if (node == nullptr) {
                Node<K>* n = new Node<K>();
                n->key = key;
                n->left = nullptr;
                n->right = nullptr;
                n->height = 0;
                return n;
            }

            if (key < node->key) { 
                node->left = in(node->left, key); 
            } else if (key > node->key) { 
                node->right = in(node->right, key); 
            } else { 
                return node; // Duplicate keys ignored
            }

            updateHeight(node);
            int balance = getBalance(node);

            // Left Left Case
            if (balance > 1 && key < node->left->key)
                return rightRotate(node);

            // Right Right Case
            if (balance < -1 && key > node->right->key)
                return leftRotate(node);

            // Left Right Case
            if (balance > 1 && key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // Right Left Case
            if (balance < -1 && key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

    public:
        Node<K>* root;

        AVLTree() { root = nullptr; }

        int height(Node<K>* node) {
            if (node == nullptr) return -1;
            return node->height;
        }

        int getBalance(Node<K>* node) {
            if (node == nullptr) return 0;
            return height(node->left) - height(node->right);
        }

        void updateHeight(Node<K>* node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }

        Node<K>* rightRotate(Node<K>* z) {
            Node<K>* y = z->left;
            Node<K>* t = y->right;
            y->right = z;
            z->left = t;
            updateHeight(z);
            updateHeight(y);
            return y;
        }
/*    3                     2
   /                     / \
  2          ->         1   3
 /
1

Fix: rotateRight(3)*/
        Node<K>* leftRotate(Node<K>* z) {
            Node<K>* y = z->right;
            Node<K>* t = y->left;
            y->left = z;
            z->right = t;
            updateHeight(z);
            updateHeight(y);
            return y;
        }
/*1                         2
 \                       / \
  2          ->         1   3
   \
    3

Fix: rotateLeft(1)*/
        void insert(K key) {
            root = in(root, key); // Fixed argument order: (node, key)
        }

        void preOrder() {
            preOrderHelper(root); // Delegates to the recursive helper
        }
    };
};

int main() {
    lib::AVLTree<int> hero;
    int a = 0;
    while (cin >> a) {
        if (a == 1000) {
            break;
        }
        hero.insert(a);
    }
    cout << endl;
    hero.preOrder();

    return 0;
}