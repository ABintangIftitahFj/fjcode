/* Saya A Bintang iftitah FJ dengan NIM 2305995 mengerjakan
   tes mesin dalam mata kuliah Struktur Data
   untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Data
{
    char name[201];
    char nama_parent[201];
    int lama_belajar; // Assuming this is a char, but it might be better as an int
    int jmlh_matkul;
    char **nama_matkul;
    char substr[4][201];
} Data;

typedef struct Node *Nodeaddress;
typedef struct Node
{
    Data container;
    Nodeaddress sibling;
    Nodeaddress child;
} Node;

typedef struct
{
    Node *root;
} Tree;

void tree_create(Data data, Tree *T);
void add_child(Data data, Node *root);
void del_node(Node *root);
void del_child(Node *target, Node *root);
Node *find_node(Data find, Node *root);
void print_preorder(Node *root);
void print_postorder(Node *root);
void copy_tree(Node *root1, Node **root2);
int treecmp(Node *root1, Node *root2);
int count_node(Node *root);
void bagi_string(char temp[], Data *input, char substr[][201], Tree *T);

#endif // HEADER_H
