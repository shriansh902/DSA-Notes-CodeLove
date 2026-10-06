#include <iostream>
using namespace std;

namespace boii {

    template<typename K>
    class Node {
        public:
        K key;
        Node<K>* left;
        Node<K>* right;
    };
        
    template<typename K>
    class BST {
        private:
        Node<K>* root;   // the single entry point into the whole tree

        public:
        BST(){
            root = nullptr;   // empty tree = no root yet
        }
        void insert(K key){
            Node<K>* newNode = new Node<K>();
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if(root == nullptr){
                root = newNode;   // tree was empty — this becomes the root
                return;
            }

            Node<K>* temp = root;      // walks down the tree, looking for an empty spot
            Node<K>* parent = nullptr; // always stays one step behind temp

            while(temp != nullptr){
                parent = temp;
                if(key <= temp->key){
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }

            // temp is now nullptr — parent is the last real node we visited
            if(key <= parent->key){
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }

        
        void inorder(Node<K>* node){ // this prints the bst in ascending order technically
            if(node == nullptr) return;   // base case: nothing here, stop
            
            inorder(node->left);           // 1. visit everything smaller (left subtree) first
            cout << node->key << " ";      // 2. then print this node
            inorder(node->right);          // 3. then visit everything bigger (right subtree)
            return;
        }
        
        void preorder(Node<K>* node){ // this prints the bst in ascending order technically
            if(node == nullptr) return;   // base case: nothing here, stop
            
            cout << node->key << " ";      // 1. then print this node
            preorder(node->left);           // 2. visit everything smaller (left subtree) first
            preorder(node->right);          // 3. then visit everything bigger (right subtree)
            return;
        }
        
        void postorder(Node<K>* node){ // this prints the bst in ascending order technically
            if(node == nullptr) return;   // base case: nothing here, stop
            
            postorder(node->left);           // 1. visit everything smaller (left subtree) first
            postorder(node->right);          // 2. then visit everything bigger (right subtree)
            cout << node->key << " ";      // 3. then print this node
            return;
        }
        
        void tree(Node<K>* node, int depth){
            if(node == nullptr) return;
            tree(node->right, depth + 1);   // right subtree first (visually "above")
            for(int i = 0; i < depth; i++){
                cout << "    ";              // 4 spaces per depth level
            }
            cout << node->key << endl;
            
            tree(node->left, depth + 1);     // left subtree last (visually "below")
        }
        
        void print(char s){
            switch(s){
                case 'i':
                inorder(root);
                break;
                case 'p':
                preorder(root);
                break;
                case 'o':
                postorder(root);
                break;
                case 't':
                tree(root, 0);
                break;
                default:
                cout << "Invalid option" << endl;
            }
            cout << endl;
        }

        bool find(K n){
            Node<K>* temp = root;
            while(temp!=nullptr){
                if(temp->key==n){
                    return true;
                }
                else if(temp->key<n){
                    temp=temp->right;
                }
                else{
                    temp=temp->left;
                }
            }
            return false;
        }
        Node<K>* findMin(Node<K>* node){
            while(node->left != nullptr){
                node = node->left;
            }
            return node;
        }

        Node<K>* successor(K key){
            Node<K>* x = root;
            Node<K>* result = nullptr;   // will hold the answer

            while(x != nullptr){
                if(key < x->key){
                    result = x;          // x is a POSSIBLE successor (bigger than key)
                    x = x->left;          // but maybe there's a smaller one still bigger than key
                } else {
                    x = x->right;         // x is too small, successor must be further right
                }
            }
            return result;
        }
    };
    
}

int main(){
    boii::BST<int> m;
    int n;
    char l;
    while(true){
        cin >> n;
        if(n == 0) break;
        m.insert(n);
    }
    cin >> l;
    m.print(l);
    cout<<m.find(10);

    return 0;
}