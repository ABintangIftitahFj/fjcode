#include "header.h"

int main()
{
    int n;
    scanf("%d", &n);
    getchar(); // Consume the newline character after the integer input

    Tree T = {NULL}; // Initialize the tree
    Data input[n];   // Array to hold data for each node
    char temp[201];

    // Read all nodes and build the tree
    for (int i = 0; i < n; i++)
    {
        scanf("%200[^\n]", temp);
        scanf("%s %s %d %d", input[i].name, input[i].nama_parent, &input[i].lama_belajar, &input[i].jmlh_matkul);
        getchar(); // Consume the newline character
    }
    for (int i = 0; i < n; i++)
    {
        bagi_string(temp, &input[i], input[i].substr, &T);
    }

    // Read the target career node
    char target[201];
    scanf("%200[^\n]", target);

    // Free allocated memory (not shown for brevity)
    return 0;
}
