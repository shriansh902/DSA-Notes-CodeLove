#include <iostream>
#include <vector>
using namespace std;

namespace btreelib {

    template<typename K>
    class BTreeNode {
        public:
            vector<K> keys;              // sorted keys stored in this node
            vector<BTreeNode<K>*> children; // child pointers (keys.size()+1 of these, if internal)
            bool isLeaf;
            int t;                        // minimum degree, stored for convenience

            BTreeNode(int t, bool isLeaf){
                this->t = t;
                this->isLeaf = isLeaf;
            }

            // ---------- traversal ----------
            void traverse(){
                // print keys and recurse into children, in sorted order
                int i;
                for(i = 0; i < (int)keys.size(); i++){
                    if(!isLeaf){
                        children[i]->traverse();
                    }
                    cout << keys[i] << " ";
                }
                if(!isLeaf){
                    children[i]->traverse();   // last child (one more child than keys)
                }
            }

            // ---------- search ----------
            BTreeNode<K>* search(K key){
                int i = 0;
                while(i < (int)keys.size() && key > keys[i]){
                    i++;
                }
                if(i < (int)keys.size() && keys[i] == key){
                    return this;   // found it in THIS node
                }
                if(isLeaf){
                    return nullptr;   // nowhere left to go
                }
                return children[i]->search(key);   // recurse into the correct child
            }

            // ---------- insert into a node that is NOT full ----------
            void insertNonFull(K key){
                int i = keys.size() - 1;

                if(isLeaf){
                    // shift keys right to make room, then insert
                    keys.push_back(K());
                    while(i >= 0 && keys[i] > key){
                        keys[i+1] = keys[i];
                        i--;
                    }
                    keys[i+1] = key;
                } else {
                    // find the child that should receive this key
                    while(i >= 0 && keys[i] > key){
                        i--;
                    }
                    i++;

                    // if that child is full, split it first
                    if((int)children[i]->keys.size() == 2*t - 1){
                        splitChild(i, children[i]);
                        if(keys[i] < key){
                            i++;
                        }
                    }
                    children[i]->insertNonFull(key);
                }
            }

            // ---------- split a full child ----------
            // y = children[i], a full node (2t-1 keys). Split it into two nodes
            // of (t-1) keys each, and push its middle key UP into THIS node.
            void splitChild(int i, BTreeNode<K>* y){
                BTreeNode<K>* z = new BTreeNode<K>(y->t, y->isLeaf);

                // z takes the LARGER half of y's keys (the last t-1 keys)
                for(int j = 0; j < t-1; j++){
                    z->keys.push_back(y->keys[j+t]);
                }

                // if y isn't a leaf, z also takes the corresponding children
                if(!y->isLeaf){
                    for(int j = 0; j < t; j++){
                        z->children.push_back(y->children[j+t]);
                    }
                }

                // y keeps only its first t-1 keys (shrink it)
                K middleKey = y->keys[t-1];
                y->keys.resize(t-1);
                if(!y->isLeaf){
                    y->children.resize(t);
                }

                // insert z as a new child of THIS node, right after y
                children.insert(children.begin() + i + 1, z);

                // the middle key of y moves UP into this node
                keys.insert(keys.begin() + i, middleKey);
            }
    };

    template<typename K>
    class BTree {
        private:
            BTreeNode<K>* root;
            int t;   // minimum degree — chosen once, when the tree is created

        public:
            BTree(int t){
                root = nullptr;
                this->t = t;
            }

            void traverse(){
                if(root != nullptr){
                    root->traverse();
                }
                cout << endl;
            }

            bool search(K key){
                if(root == nullptr) return false;
                return root->search(key) != nullptr;
            }

            void insert(K key){
                if(root == nullptr){
                    root = new BTreeNode<K>(t, true);
                    root->keys.push_back(key);
                    return;
                }

                if((int)root->keys.size() == 2*t - 1){
                    // root is full — must split BEFORE inserting (tree grows upward)
                    BTreeNode<K>* newRoot = new BTreeNode<K>(t, false);
                    newRoot->children.push_back(root);
                    newRoot->splitChild(0, root);

                    // decide which of the two new children gets the key
                    int i = 0;
                    if(newRoot->keys[0] < key) i++;
                    newRoot->children[i]->insertNonFull(key);

                    root = newRoot;   // the tree's height just grew by 1
                } else {
                    root->insertNonFull(key);
                }
            }
    };

}

int main(){
    btreelib::BTree<int> tree(3);   // minimum degree t=3 (each node: 2-5 keys)

    int vals[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 8, 25, 40, 19};
    for(int v : vals){
        tree.insert(v);
    }

    cout << "Traversal (sorted): ";
    tree.traverse();

    cout << "Search 6: " << (tree.search(6) ? "found" : "not found") << endl;
    cout << "Search 15: " << (tree.search(15) ? "found" : "not found") << endl;

    return 0;
}