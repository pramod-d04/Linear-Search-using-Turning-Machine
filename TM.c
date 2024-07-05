#include <stdio.h>
#include <stdlib.h>

#define X 2
#define B 3
#define R 1
#define L -1
#define INV {-1, -1, -1} // invalid state

typedef struct {
    int state;
    int tape_symbol;
    int direction;
} transition;

typedef struct {
    int tape[1000];
    transition transition_function[19][4];
    int head;
    int c;
} LinearSearch;

void initialize_tape(LinearSearch* ls, int elements[], int n, int key);
void TM(LinearSearch* ls, int elements[], int n, int key, int sum);
int find_index(LinearSearch* ls);
void print_tape(LinearSearch* ls, int start, int end);

int main() {
    int n, key, sum = 0;
   
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int elements[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
        sum += elements[i];
    }

    printf("Enter the element to be searched for: ");
    scanf("%d", &key);

    printf("\n--------------------------------------------------------------\n");

    LinearSearch ls = {
        .transition_function = {
            { { 1,B,R}, { 5,B,R}, INV, INV }, // q0
            { { 1,0,R}, { 2,1,R}, INV, INV }, // q1
            { { 1,0,R}, { 3,1,R}, INV, INV }, // q2
            { { 4,X,L}, {14,1,R}, { 3,X,R}, INV }, // q3
            { { 4,0,L}, { 4,1,L}, { 4,X,L}, { 0,B,R} }, // q4
            { { 6,0,R}, { 8,1,R}, INV, INV }, // q5
            { { 6,0,R}, { 7,1,R}, INV, {17,1,L} }, // q6
            { { 6,0,R}, { 8,1,R}, INV, INV }, // q7
            { { 9,0,R}, {11,1,R}, { 8,X,R}, INV }, // q8
            { { 9,0,R}, { 9,1,R}, INV, {10,0,L} }, // q9
            { {10,0,L}, {10,1,L}, {10,0,L}, { 0,B,R} }, // q10
            { {11,0,R}, INV, INV, {12,0,L} }, // q11
            { {12,0,L}, {13,B,L}, INV, INV }, // q12
            { {13,B,L}, {13,B,L}, {13,B,L}, {18,B,R} }, // q13
            { {14,0,R}, INV, INV, {15,0,L} }, // q14
            { {15,0,L}, {15,1,L}, {15,0,L}, {16,B,R} }, // q15
            { {16,B,R}, { 0,B,R}, INV, INV }, // q16
            { {17,B,L}, {17,B,L}, INV, {18,B,R} }, // q17
            { INV, INV, INV, INV }  // q18
        },
        .head = 100
    };
    
    for (int i = 0; i < 1000; i++) {
        ls.tape[i] = B;
    }

    initialize_tape(&ls, elements, n, key);
    TM(&ls, elements, n, key, sum);

    return 0;
}

void initialize_tape(LinearSearch* ls, int elements[], int n, int key) {
    ls->c = ls->head;

    for (int i = 0; i < n; i++) {
        while (elements[i]--) {
            ls->tape[ls->c++] = 0;
        }
        ls->tape[ls->c++] = 1; // End of a single element
    }

    ls->tape[ls->c++] = 1; // End of all elements

    while (key--) {
        ls->tape[ls->c++] = 0; // Key to be searched
    }

    ls->tape[ls->c++] = 1; // Final 1, after which index is stored if an element exists

    printf("Elements have been loaded onto the tape....\n");
    printf("Initial State of ");
    print_tape(ls, ls->head - 1, ls->c + 1);
    printf("\n--------------------------------------------------------------\n");
}

void TM(LinearSearch* ls, int elements[], int n, int key, int sum) {
    int current = 0; // current state
    int j = ls->head; // index
    int direction;
    int i = 0;

    while (current != 18 && ls->transition_function[current][ls->tape[j]].state != -1) {
        int prev = current;
        int skip = 0;

        transition next = ls->transition_function[current][ls->tape[j]];
        direction = next.direction;

        if (ls->tape[j] == next.tape_symbol)
            skip = 1;

        ls->tape[j] = next.tape_symbol;

        current = next.state;

        j += direction;

        if (!skip) {
            printf("\nStep %d - q%d to q%d ", i++, prev, current);
            print_tape(ls, ls->head - 1, ls->c + n);
            printf("\n");
        } else {
            printf("Skip ");
            if (direction == 1)
                printf("towards right");
            else
                printf("towards left");
            
            printf(" q%d to q%d\n", prev, current);
        }
    }

    printf("\n--------------------------------------------------------------\n");
    printf("Final State of ");
    print_tape(ls, ls->head - 1, ls->c + sum);

    if (current != 18 && ls->transition_function[current][ls->tape[j]].state == -1) {
        printf("This TM doesn't accept the string you loaded");
    } else {
        int index = find_index(ls);
        if (index == -1) {
            printf("The element cannot be found");
        } else {
            printf("The element has been found at index: %d\n", index);
        }
    }
}

int find_index(LinearSearch* ls) {
    int index = 0, done = 0;

    for (int i = ls->head; i < 1000; i++) {
        if (ls->tape[i] == B)
            continue;

        while (ls->tape[i] == 0) {
            index++;
            done = 1;
            break;
        }

        if (ls->tape[i] == 1) {
            return -1; // Returns -1 if not found
        }
    }

    return index;
}

void print_tape(LinearSearch* ls, int start, int end) {
    printf("Tape: \n");

    for (int i = start; i < end; i++) {
        if (ls->tape[i] == B)
            printf("B");
        else if (ls->tape[i] == X)
            printf("X");
        else
            printf("%d", ls->tape[i]);
    }
    printf("\n");
}
