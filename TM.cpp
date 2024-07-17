#include <bits/stdc++.h>

#define X 2
#define B 3
#define R 1
#define L - 1
#define INV {-1, -1, -1} //invalid state

using namespace std;

struct transition {
   int state,tape_symbol,direction;
};

class LinearSearch {
   public:
      int tape[1000];
      
    transition transition_function[19][4]={
    //  0   ,     1   ,     X   ,     B   ,
    {{ 1,B,R}, { 5,B,R},      INV,      INV}, // q0
    {{ 1,0,R}, { 2,1,R},      INV,      INV}, // q1
    {{ 1,0,R}, { 3,1,R},      INV,      INV}, // q2
    {{ 4,X,L}, {14,1,R}, { 3,X,R},      INV}, // q3
    {{ 4,0,L}, { 4,1,L}, { 4,X,L}, { 0,B,R}}, // q4
    {{ 6,0,R}, { 8,1,R},      INV,      INV}, // q5
    {{ 6,0,R}, { 7,1,R},      INV, {17,1,L}}, // q6
    {{ 6,0,R}, { 8,1,R},      INV,      INV}, // q7
    {{ 9,0,R}, {11,1,R}, { 8,X,R},      INV}, // q8
    {{ 9,0,R}, { 9,1,R},      INV, {10,0,L}}, // q9
    {{10,0,L}, {10,1,L}, {10,0,L}, { 0,B,R}}, // q10
    {{11,0,R},      INV,      INV, {12,0,L}}, // q11
    {{12,0,L}, {13,B,L},      INV,      INV}, // q12
    {{13,B,L}, {13,B,L}, {13,B,L}, {18,B,R}}, // q13
    {{14,0,R},      INV,      INV, {15,0,L}}, // q14
    {{15,0,L}, {15,1,L}, {15,0,L}, {16,B,R}}, // q15
    {{16,B,R}, { 0,B,R},      INV,      INV}, // q16
   { {17,B,L}, {17,B,L},      INV, {18,B,R}}, // q17
        { INV,      INV,      INV,      INV}  // q18
   };

   int head;
   int c; //Ending non-blank index of tape (Not considering appending zeroes)

   LinearSearch(int elements[], int n, int key) {
      head=100;
      
      for (int i=0;i<1000;i++)
         tape[i] = B;

      intialize_tape(elements,n,key);
   }

   void intialize_tape(int elements[],int n,int key)
   {
      c=head;

      for(int i=0;i<n;i++) 
      {
        while (elements[i]--)
            tape[c++]=0;
            
        tape[c++]=1; //End of a single element
      }

      tape[c++] = 1; //End of all elements

      while (key--)
        tape[c++] = 0; //key to be searched

      tape[c++] = 1; // Final 1, after which index is stored if an element exists

      cout<<"Elements have been loaded onto the tape....\n";
      cout<<"Initial State of ";
      print_tape(head - 1, c + 1);
      cout<<"\n--------------------------------------------------------------\n";
   }

   void TM(int elements[],int n,int key,int sum) {

      int current = 0; //current state
      int j = head; //index
      int direction;
	  int i=0;
	  
      while (current != 18 && transition_function[current][tape[j]].state != -1)
      {
        int prev=current;
        bool skip=0;
        
        transition next=transition_function[current][tape[j]];
        direction = next.direction;

        if(tape[j]==next.tape_symbol)
        skip=1;
        
        tape[j] = next.tape_symbol;

        current = next.state;

        j+=direction;
        
        if(!skip)
        {
        cout<<"\nStep "<<i++<<" - ";
        cout<<"q"<<prev<<" to q"<<current<<" ";
        print_tape(head-1,c+n);
        cout<<endl;
        }
        
        else
        {
        
        cout<<"Skip ";
        if(direction==1)
        cout<<"towards right";
        else
        cout<<"towards left";
        
        cout<<" q"<<prev<<" to q"<<current;
        cout<<endl;
        }

      }
		
		cout<<"\n--------------------------------------------------------------\n";
		cout<<"Final State of ";
		print_tape(head - 1, c + sum);
		
      if (current != 18 && transition_function[current][tape[j]].state == -1)
        cout << "This TM doesn't accept the string you loaded";
        
      else {
		int index=find_index();
		
		if(index==-1)
        cout<<"The element cannot be found";
        
        else
        cout<<"The element has been found at index : " << index << endl;
      }
   }

   int find_index() {
      int index = 0,done = 0;

      for (int i=head;i<1000;i++)
      {
        if (tape[i] == B)
            continue;
        
         while(tape[i] == 0) {
            index++;
            done = 1;
            break;
        }
         
        if (tape[i] == 1) {
            return -1; // Returns -1 if not found
            break;
        }
      }

      return index;
   }

   void print_tape(int start,int end) 
   {
      cout<<"Tape : \n";

      for (int i = start; i < end; i++) 
      {
        if (tape[i] == B)
            cout << "B";
         
        else if (tape[i] == X)
            cout << "X"; 
        
        else
            cout << tape[i];
      }
      cout << "\n";
   }

};

int main() {
   int n, key, sum;
   
   cout<<"Enter the number of elements : ";
   cin>>n;
   int elements[n];

   cout<<"Enter the elements"<<endl;
   
   for(int i=0;i<n;i++) 
   {
      cin>>elements[i];
      sum+=elements[i];
   }

   cout<<"Enter the element to be searched for : ";
   cin>>key;

   cout<<"\n--------------------------------------------------------------\n";
   LinearSearch LS(elements,n,key);
   LS.TM(elements,n,key,sum);

   return 0;
}
