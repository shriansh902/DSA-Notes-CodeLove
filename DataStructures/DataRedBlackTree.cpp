#include <iostream>
using namespace std;

namespace rblib {

    enum Color { RED, BLACK };

    template<typename K>
    class Node {
        public:
            K key;
            Node<K>* left;
            Node<K>* right;
            Node<K>* parent;
            Color color;
    };

    template<typename K>
    class RBTree {
        private:
            Node<K>* root;
            Node<K>* NIL;   // a single shared "sentinel" node representing all null leaves

            // ---------- rotations (identical shape to AVL's, but also fix parent pointers) ----------

            void rotateLeft(Node<K>* x){
                Node<K>* y = x->right;
                x->right = y->left;
                if(y->left != NIL){
                    y->left->parent = x;
                }
                y->parent = x->parent;

                if(x->parent == nullptr){
                    root = y;
                } else if(x == x->parent->left){
                    x->parent->left = y;
                } else {
                    x->parent->right = y;
                }

                y->left = x;
                x->parent = y;
            }

            void rotateRight(Node<K>* x){
                Node<K>* y = x->left;
                x->left = y->right;
                if(y->right != NIL){
                    y->right->parent = x;
                }
                y->parent = x->parent;

                if(x->parent == nullptr){
                    root = y;
                } else if(x == x->parent->right){
                    x->parent->right = y;
                } else {
                    x->parent->left = y;
                }

                y->right = x;
                x->parent = y;
            }

            // ---------- fix violations after a normal BST insert ----------

            void insertFixup(Node<K>* z){
                // z was just inserted as RED. Walk up fixing "red-red" violations.
                while(z->parent != nullptr && z->parent->color == RED){

                    Node<K>* grandparent = z->parent->parent;

                    if(z->parent == grandparent->left){
                        Node<K>* uncle = grandparent->right;

                        if(uncle->color == RED){
                            // Case 1: uncle is RED -> just recolor, push problem up
                            z->parent->color = BLACK;
                            uncle->color = BLACK;
                            grandparent->color = RED;
                            z = grandparent;
                        } else {
                            if(z == z->parent->right){
                                // Case 2: "triangle" shape -> rotate to make it a "line"
                                z = z->parent;
                                rotateLeft(z);
                            }
                            // Case 3: "line" shape -> rotate grandparent, recolor
                            z->parent->color = BLACK;
                            grandparent->color = RED;
                            rotateRight(grandparent);
                        }
                    } else {
                        // mirror image: parent is a RIGHT child
                        Node<K>* uncle = grandparent->left;

                        if(uncle->color == RED){
                            z->parent->color = BLACK;
                            uncle->color = BLACK;
                            grandparent->color = RED;
                            z = grandparent;
                        } else {
                            if(z == z->parent->left){
                                z = z->parent;
                                rotateRight(z);
                            }
                            z->parent->color = BLACK;
                            grandparent->color = RED;
                            rotateLeft(grandparent);
                        }
                    }
                }
                root->color = BLACK;   // rule 2: root must always be Black
            }

            void inorderHelper(Node<K>* node){
                if(node == NIL) return;
                inorderHelper(node->left);
                cout << node->key << "(" << (node->color==RED ? "R" : "B") << ") ";
                inorderHelper(node->right);
            }

        public:
            RBTree(){
                NIL = new Node<K>();
                NIL->color = BLACK;
                NIL->left = NIL->right = NIL->parent = nullptr;
                root = NIL;
            }

            void insert(K key){
                Node<K>* z = new Node<K>();
                z->key = key;
                z->left = NIL;
                z->right = NIL;
                z->color = RED;   // ALWAYS insert as red first

                Node<K>* y = nullptr;
                Node<K>* x = root;

                // standard BST insert, but comparing against NIL instead of nullptr
                while(x != NIL){
                    y = x;
                    if(z->key < x->key){
                        x = x->left;
                    } else {
                        x = x->right;
                    }
                }

                z->parent = y;
                if(y == nullptr){
                    root = z;              // tree was empty
                } else if(z->key < y->key){
                    y->left = z;
                } else {
                    y->right = z;
                }

                insertFixup(z);   // fix any red-red violations this created
            }

            void printInorder(){
                inorderHelper(root);
                cout << endl;
            }
    };

}

int main(){
    rblib::RBTree<int> tree;

    // insert SORTED data on purpose — exactly what broke a plain BST
    for(int i = 1; i <= 15; i++){
        tree.insert(i);
    }

    cout << "In-order with colors: ";
    tree.printInorder();

    return 0;
}