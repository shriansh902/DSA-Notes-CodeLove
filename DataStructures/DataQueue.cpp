#include <iostream>
#include <string>
using namespace std;

namespace neon{

    template<typename T>
    class Node{
        public:
        T data;
        Node<T>* next;
    };

    template<typename T>
    class Queue{
        private:
            Node<T>* head;  // points to the FRONT of the queue (oldest element, next to leave)
            Node<T>* tail;  // points to the BACK of the queue (newest element, last to leave)
            
        public:
        int size;
        Queue(){
            head=nullptr;
            tail=nullptr;
            size=0;
        }
        void enqueue(T x){            // adds a new element to the BACK of the queue
            Node<T>* newNode = new Node<T>();  
                newNode->data = x;      
                newNode->next = nullptr;   // it's going to the back soo no issue if its next is null
                size++;

            if(tail==nullptr){
                // queue was completely empty before this call
                // so this new node becomes BOTH the head and the tail
                head = newNode; 
                tail = newNode;
            }
            else{
                // queue already had elements
                // link the OLD tail to this new node...
                tail->next = newNode;
                // ...then move tail forward so it now points to the new node
                tail = newNode;
            }

        }
        T Dequeue(){
            if(isEmpty()){
                cout<<"Cannot Remove Element"<<endl;
                return T();
            }
            Node<T>* target = head; // note here target is just a pointer so when we say value at target it means first element
            head=head->next;
            T ans=target->data;
            delete(target);

            if(head == nullptr){          // if queue is now empty, tail must reset too
                tail = nullptr;
            }
            size--;
            return ans;
        }
        
        T front(){
            if(isEmpty()){
                cout << "Queue is empty" << endl;
                return T();
            }
            return head->data;   // front of the queue is always head, not tail
        }

        T back(){
            if(isEmpty()){
                cout << "Queue is empty" << endl;
                return T();
            }
            return tail->data;
        }

            // checks if there are zero elements in the queue
        bool isEmpty(){
            return head == nullptr;   // no head means nothing is in the queue
        }

        int sizequeue(){
            return size;
        }
        void display(){
            if(isEmpty()){
                cout << "Queue is empty" << endl;
                return;
            }

            Node<T>* temp = head;      // start at the front, don't touch head/tail directly
            cout << "FRONT -> ";

            while(temp != nullptr){
                cout << temp->data << " -> ";
                temp = temp->next;
            }

            cout << " BACK" << endl;
        }
    };

}

int main(){
    neon::Queue<int> q;
    int x=5;
    while(true){
        cin>>x;
        if (x == 0) {
            q.Dequeue();
        }
        else if (x == -1){
            break;
        } 
        else{ 
            q.enqueue(x);
        }
        q.display();
        cout<<q.size<<endl;
    }
    return 0;
}