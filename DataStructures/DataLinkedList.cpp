#include <iostream>
#include <string>
using namespace std;

namespace kaju{

    template<typename A>
    class Node {
        public:
            A data; //to store variable
            Node<A>* next; // to store pointer of next element
    };

    template<typename A>
    class LinkedList{
        private:
            Node<A>* head; // pointer to first node, now a PRIVATE member 
        
        public:
            int size;
            LinkedList(){
                head = nullptr; // empty list = no nodes yet
                size=0;
            }

            void insert(A x){
                Node<A>* temp = new Node<A>();
                temp->data = x; // can be read as (*(temp)).data = x
                temp->next = head; // put old head in the "next" container of temp, temp becomes new front
                head = temp; // save address of the element in head
                size++;
                return;
            }

            void display(){
                cout << "The list is" << endl;



                
                Node<A>* temp = head;
                cout << "HEAD -> ";

                while(temp != nullptr){
                    cout << temp->data << " ";
                    temp = temp->next;
                }

                cout << "-> NULL" << endl;
            }

            void placeinsert(A x, int n){
                Node<A>* newNode = new Node<A>(); // make the node
                newNode->data = x; // give it value
                Node<A>* temp = head;    // get address of first node here and put in a temporary variable for traversing
                for (int i = 0; i < n - 2; i++){     //one step is reduced from getting to n another step reduced coz we want to put it after n-1 th node
                    temp = temp->next;      //moved on node forward
                    if (temp == nullptr || temp->next == nullptr) {
                        cout << "Error: Position out of bounds" << endl;
                        delete newNode;
                        return;
                    }
                }
                newNode->next = temp->next;
                temp->next = newNode;
                size++;
            }

            void placeremove(int p){
                Node<A>* temp = head;
                Node<A>* target = head;

                if (p == 1) {
                    head = temp->next; // head stores pointer of 2nd node soon to become first
                    delete temp;
                    return;
                }

                for (int i = 0; i < p - 2; i++){ // move temp to one step before node to be deleted
                    temp = temp->next;
                    if (temp == nullptr || temp->next == nullptr) {
                        cout << "Error: Position out of bounds" << endl;
                        return;
                    }
                }
                target = temp->next;
                temp->next = target->next; // put pointer of p+1 th node pointer in p-1 th node pointer
                delete target;
                size--;
                return;
            }

            void reverse(){
                Node<A>* temp = head; // keeps check of current node
                Node<A>* prev = nullptr; // for prev node
                Node<A>* after;
                while(temp != nullptr){
                    after = temp->next; // stores the pointer to the element after the current node temporarily
                    temp->next = prev; // reversing
                    prev = temp;
                    temp = after; //shifting to one node forward
                }
                head = prev;
            }
    };

}

int main(){
    string x;
    kaju::LinkedList<string> line;
    while(true){
        cin >> x;
        if (x == "/.") break;   // check immediately after reading, before insert
        line.insert(x);
    }
    line.display();
    line.reverse();
    line.display();
    return 0;
}