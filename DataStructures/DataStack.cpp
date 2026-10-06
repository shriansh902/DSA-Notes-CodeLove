#include <iostream>
#include <string>
using namespace std;

namespace ggs {
    
    template<typename lol>
    class Node {
        public:
        lol data;
        Node<lol>* next; //pointer to next variable
    };

    template<typename lol>
    class Stack {
        private:
            Node<lol>* top;   // pointer to the topmost node
        
        public:
            int size;
        Stack() {
            top = nullptr;   // empty stack = no nodes yet 
            size=0;
        }
        void push(lol value) {
            Node<lol>* newNode = new Node<lol>();   // step 1: create a new node on the heap
            newNode->data = value;        // step 2: store the value in it
            newNode->next = top;          // step 3a: point new node to the old top
            top = newNode;                // step 3b: update top to be the new node
            size++;
        }
        
        void pop() {
            if (top == nullptr) {                // step 1: check empty
                cout << "Stack Underflow! Nothing to pop" << endl;
                return;
            }
            Node<lol>* temp = top;                    // step 2: remember current top
            top = top->next;                     // step 3: go to address and save its next location 
            delete temp;                         // step 4: free the old node's memory
            size--;
        }
        
        lol peek() {
            if (top == nullptr) {
                cout << "Stack is empty" << endl;
                throw runtime_error("Cannot peek an empty stack");
            }
            return top->data;
        }
            
        bool isEmpty() {
            return top == nullptr;
        }
            
        lol reverse(lol input){
            int n=sizeof(input)/sizeof(lol);
            lol ans[n];
            int i=0;
            while(n!=0){
                ans[i]=peek();
                i++;n--;
            }
            return ans;
        }
    };
}
    
int main(){
    ggs::Stack<char> s;
    char x;
    while(true){
        cin >> x;
        if (x == '.') break;   // check immediately after reading, before insert
        s.push(x);
    }

    while (!s.isEmpty()) {
        cout << s.peek() <<" ";
        s.pop();
    }
    s.pop();
    cout<<"over";
    return 0;
}