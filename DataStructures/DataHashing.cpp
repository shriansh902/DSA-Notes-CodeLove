#include <iostream>
#include <chrono>
using namespace std;

namespace ronaldo {

    template<typename K, typename V>
    class Node {
    public:
        K key;          // 1. the key
        V value;         // 2. the value 
        Node<K,V>* next; // 3. pointer to the next node in this SAME slot's chain
    };

    template<typename K, typename V>
    class HashTable {
    private:
        Node<K,V>** table;   // pointer to first element of so called 'array of pointers'
        int size;            // "m" — total number of slots
        int count; //  load factor(lamda)= (total keys inserted)/(total slots) <0.7

    public:
        HashTable(int m) {
            size = m;
            table = new Node<K,V>*[size];   // allocate the array itself
            count=0;
            for (int i = 0; i < size; i++) {
                table[i] = nullptr;          // every slot starts empty                
            }
        }

        int hashFunc(K key){
            return key % size;   // Division Method: h(k) = k mod m
        }

        void insert(K key, V value){
            int index = hashFunc(key);
            count++;
            Node<K,V>* newNode = new Node<K,V>();
            newNode->key = key;
            newNode->value = value;
            newNode->next = table[index];   // same pattern as Stack's push()
            table[index] = newNode;
        }

        void remove(K key){
            int index = hashFunc(key);
            Node<K,V>* del = table[index];
            Node<K,V>* prev = nullptr;
            while(del->key!=key){
                if(del == nullptr){
                    cout << "Key not found" << endl;
                    return;
                }
                prev=del;
                del=del->next;
            }
            if(prev == nullptr){
                table[index] = del->next;   // removing the head of this chain
            } else {
                prev->next = del->next;      // removing a middle/end node
            }
            delete del;
            count--;
        }

        V find(K key){
            int index = hashFunc(key);        // step 1: figure out which slot to check

            Node<K,V>* temp = table[index];   // step 2: start walking that slot's chain

            while(temp != nullptr){
                if(temp->key == key){         // step 3: found a matching key!
                    return temp->value;
                }
                temp = temp->next;             // step 4: not this one, move to next in chain
            }

            cout << "Key not found" << endl;   // step 5: walked the whole chain, nothing matched
            return V();                         // return a default value (0 for int, "" for string, etc.)
        }

        double loadFactor(){
            return (double)count / size;
        }
        
        void print(){
            for(int i = 0; i < size; i++){
                if (table[i]==nullptr)continue;
                Node<K,V>* temp = table[i];
                cout << "Slot " << i << ": ";

                while(temp != nullptr){
                    cout << "[" << temp->key << ":" << temp->value << "] -> ";
                    temp = temp->next;
                }
                cout << "null"<<endl;
            }
        }
    };
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    ronaldo::HashTable<int, string> hashing(11);

    hashing.insert(25, "Alice");
    hashing.insert(15, "Bob");
    hashing.insert(3, "Charlie");
    
    hashing.print();
    hashing.remove(25);
    hashing.print();




    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}