#include<iostream>
#include <algorithm>

namespace lib{
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
            Node<K>* root;
        public:

    };
}

int main(){


    return 0;
}