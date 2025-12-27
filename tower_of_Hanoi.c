// Tower of Hanoi Program in C
#include <stdio.h>
// n = number of disks
// s = source rod
// h = helper rod
// d = destination rod
void tower(int n, char s, char h, char d) {

    // Base case: if no disk left, simply return
    if (n == 0) 
        return;

    // Step 1: Move n-1 disks from Source to Helper using Destination
    tower(n - 1, s, d, h);

    // Step 2: Move remaining disk from Source to Destination
    printf("%c --> %c\n", s, d);

    // Step 3: Move n-1 disks from Helper to Destination using Source
    tower(n - 1, h, s, d);
}

int main() {
    int n;

    printf("Enter number of disks : ");
    scanf("%d", &n);

    // A = Source, B = Helper, C = Destination
    tower(n, 'A', 'B', 'C');

    
}
