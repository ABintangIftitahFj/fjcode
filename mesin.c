/* Saya A Bintang iftitah FJ dengan NIM 2305995 mengerjakan
   tes mesin dalam mata kuliah Struktur Data
   untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

#include "Header.h"

void tree_create(Data data, Tree *T)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->container = data;
    node->sibling = NULL;
    node->child = NULL;
    T->root = node;
}

void add_child(Data data, Node *root)
{
    // Condition to check if the root existed
    if (root != NULL)
    {
        Node *new;
        new = (Node *)malloc(sizeof(Node));

        new->container = data;
        new->child = NULL;

        // Condition if the parent node doesn't have a child
        if (root->child == NULL)
        {
            new->sibling = NULL;
            root->child = new;
        }
        // Otherwise, we'll have to append it to the end of the child list
        else
        { // Condition where there's only 1 child
            if (root->child->sibling == NULL)
            {
                new->sibling = root->child;
                root->child->sibling = new;
            }
            else
            {
                // Loop through to find the last child of the list
                Node *last = root->child;
                while (last->sibling != root->child)
                {
                    last = last->sibling;
                }
                new->sibling = root->child;
                last->sibling = new;
            }
        }
    }
}

void del_node(Node *root)
{
    // Condition to check if root existed
    if (root != NULL)
    {
        // Condition to check if the parent has a child
        if (root->child != NULL)
        {
            // Condition where there's only 1 child
            if (root->child->sibling == NULL)
            {
                del_node(root->child);
                free(root);
            }
            // Condition where there are multiple children
            else
            {
                Node *current;
                Node *target;

                // Loop through to delete the children sequentially
                current = root->child;
                while (current->sibling != root->child)
                {
                    target = current;
                    current = current->sibling;
                    del_node(target);
                }
                if (current != NULL)
                    del_node(current);
                // Delete isolated child
                free(root);
            }
        }
        // Delete isolated parent
        else
            free(root);
    }
}

void del_child(Node *target, Node *root)
{
    // Condition where the root exist
    if (root != NULL && target != NULL)
    {
        Node *current = root->child;
        if (current != NULL)
        {
            // Condition where there's only 1 child
            if (current->sibling == NULL)
            {
                // Found condition
                if (root->child == target)
                {
                    del_node(root->child);
                    root->child = NULL;
                }
                // else
                // printf("[!] Node %c has only one child (%c) and it's not the target", root->container.name, root->child->container.name);
            }
            // Condition where there are multiple children
            else
            {
                Node *prev = NULL;
                int found = 0;

                // Loop until every child is checked
                while (current->sibling != root->child && found != 0)
                {
                    // Found condition
                    if (current == target)
                        found = 1;
                    else
                    {
                        prev = current;
                        current = current->sibling;
                    }
                }

                // Check the last remaining child, if it's the target,
                if (current == target && found == 0)
                    found = 1;
                if (found == 1)
                {
                    Node *last = root->child;

                    // Loop throught to the last child
                    while (last->sibling != root->child)
                    {
                        last = last->sibling;
                    }

                    // Prev is not initialized since the target is root->child in the initial loop
                    if (prev == NULL)
                    {
                        // Condition where there is only 2 children
                        if (current->sibling == last && last->sibling == root->child)
                        {
                            root->child = last;
                            last->sibling = NULL;
                        }
                        // Condition where the children count is above 2
                        else
                        {
                            root->child = current->sibling;
                            last->sibling = root->child;
                        }
                    }
                    // Normal last child condition
                    else
                    {
                        // Condition where target is last, but there's only 2 children
                        if (prev == root->child && last->sibling == root->child)
                        {
                            root->child->sibling = NULL;
                        }
                        // Normal condition where target is last and there is more than 2 children
                        else
                        {
                            prev->sibling = current->sibling;
                            current->sibling = NULL;
                        }
                    }
                    del_node(current);
                }
                // else
                // printf("[!] Node with the name %c is not found", target->container.name);
            }
        }
    }
}

Node *find_node(Data find, Node *root)
{
    Node *result = NULL;
    // Condition where root exists
    if (root != NULL)
    {
        // Found condition
        if (root->container.name == find.name)
            result = root;
        else
        {
            Node *current = root->child;
            // Condition where current exists
            if (current != NULL)
            {
                // Condition where current is an only child
                if (current->sibling == NULL)
                {
                    if (current->container.name == find.name)
                        result = current; // Found condition
                    else
                        result = find_node(find, current); // If not found, look for it recursively
                }
                // Condition where there are multiple children
                else
                {
                    int found = 0;
                    // Check each child of root
                    while (current->sibling != root->child && found == 0)
                    {
                        // Found condition
                        if (current->container.name == find.name)
                        {
                            result = current;
                            found = 1;
                        }
                        // If not found, search recursively and laterally
                        else
                        {
                            result = find_node(find, current);
                            current = current->sibling;
                            if (result != 0)
                                found = 1;
                        }
                    }
                    // Process the last node, by now current should point to the last sibling
                    if (found == 0)
                    {
                        if (current->container.name == find.name)
                            result = current; // Found condition
                        else
                            result = find_node(find, current); // If not found, look for it recursively
                    }
                }
            }
        }
    }
    return result;
}

void copy_tree(Node *root1, Node **root2)
{
    if (root1 != NULL)
    {
        (*root2) = (Node *)malloc(sizeof(Node));
        (*root2)->container = root1->container;

        (*root2)->sibling = root1->sibling;
        (*root2)->child = root1->child;
        if (root1->child != NULL)
        {
            if (root1->child->sibling == NULL)
            {
                /*jika memiliki satu Node anak*/
                copy_tree(root1->child, &(*root2)->child);
            }

            else
            {
                /*jika memiliki banyak Node anak*/
                Node *ptr1 = root1->child;
                Node *ptr2 = (*root2)->child;

                while (ptr1->sibling != root1->child)
                {
                    copy_tree(ptr1, &ptr2);
                    ptr1 = ptr1->sibling;
                    ptr2 = ptr2->sibling;
                }
                /*memproses Node anak terakhir karena
                belum terproses dalam pengulangan*/
                copy_tree(ptr1, &ptr2);
            }
        }
    }
}

// void print_preorder(Node *root)
// {
//     // Condition where root exist
//     // printf("Pre :");
//     if (root != NULL)
//     {
//         printf(" %c", root->container.name);

//         Node *current = root->child;
//         // Check if current node exists
//         if (current != NULL)
//         {
//             // Condition where current is the only child
//             if (current->sibling == NULL)
//             {
//                 print_preorder(current);
//             }
//             // Condition where there are multiple children
//             else
//             {
//                 // Print preorder for each sibling
//                 while (current->sibling != root->child)
//                 {
//                     print_preorder(current);
//                     current = current->sibling;
//                 }
//                 // Print the last sibling
//                 print_preorder(current);
//             }
//         }
//     }
// }

// void print_postorder(Node *root)
// {
//     // Condition where root exist
//     // printf("Post :");
//     if (root != NULL)
//     {
//         Node *current = root->child;
//         // Check if current node exists
//         if (current != NULL)
//         {
//             // Condition where current is the only child
//             if (current->sibling == NULL)
//             {
//                 print_postorder(current);
//             }
//             // Condition where there are multiple children
//             else
//             {
//                 // Print preorder for each sibling
//                 while (current->sibling != root->child)
//                 {
//                     print_postorder(current);
//                     current = current->sibling;
//                 }
//                 // Print the last sibling
//                 print_postorder(current);
//             }
//         }
//         printf(" %c", root->container.name);
//     }
// }

void print_preorder(Node *root)
{
    if (root != NULL)
    {
        printf(" %s", root->container.name);
        Node *current = root->child;
        while (current != NULL)
        {
            print_preorder(current);
            current = current->sibling;
        }
    }
}

void print_postorder(Node *root)
{
    if (root != NULL)
    {
        Node *current = root->child;
        while (current != NULL)
        {
            print_postorder(current);
            current = current->sibling;
        }
        printf(" %s", root->container.name);
    }
}

int treecmp(Node *root1, Node *root2)
{
    int result = 1;
    if ((root1 != NULL) && (root2 != NULL))
    {
        if (root1->container.name == root2->container.name)
        {
            result = 0;
        }
        else
        {
            if ((root1->child != NULL) && (root2->child != NULL))
            {
                if (root1->child->sibling == NULL)
                    result = treecmp(root1->child, root2->child);
                else
                {

                    Node *bantu1 = root1->child;
                    Node *bantu2 = root2->child;

                    while (bantu1->sibling != root1->child)
                    {
                        if ((bantu1 != NULL) && (bantu2 != NULL))
                        {
                            result = treecmp(bantu1, bantu2);
                            bantu1 = bantu1->sibling;
                            bantu2 = bantu2->sibling;
                        }
                        else
                        {
                            result = 0;
                            break;
                        }
                    }
                    /*memproses Node anak terakhir karena belum terproses dalam pengulangan*/
                    result = treecmp(bantu1, bantu2);
                }
            }
        }
    }
    else
    {
        if ((root1 != NULL) || (root2 != NULL))
        {
            result = 0;
        }
    }
    return result;
}

int count_node(Node *root)
{
    if (root == NULL)
        return 0;
    int count = 1; // Count this node
    Node *current = root->child;
    while (current != NULL)
    {
        count += count_node(current);
        current = current->sibling;
    }
    return count;
}

void bagi_string(char temp[], Data *input, char substr[][201], Tree *T)
{
    int i = 0, j = 0, k = 0;

    // Split the input string based on the '#' delimiter
    while (temp[i] != '\0')
    {
        if (temp[i] == '#')
        {
            substr[j][k] = '\0';
            j++;
            k = 0;
        }
        else
        {
            substr[j][k++] = temp[i];
        }
        i++;
    }
    substr[j][k] = '\0';

    // Copy node name
    strcpy(input->name, substr[0]);

    // If parent node is "null", create root
    if (strcmp(substr[1], "null") == 0)
    {
        tree_create(*input, T);
    }
    else
    {
        // Copy other node information
        strcpy(input->nama_parent, substr[1]);
        input->lama_belajar = atoi(substr[2]); // Convert string to integer
        input->jmlh_matkul = atoi(substr[3]);  // Convert string to integer

        // Allocate memory for the list of skills
        if (input->jmlh_matkul > 0)
        {
            input->nama_matkul = (char **)malloc(input->jmlh_matkul * sizeof(char *));
            for (int l = 0; l < input->jmlh_matkul; l++)
            {
                input->nama_matkul[l] = (char *)malloc(201 * sizeof(char));
                strcpy(input->nama_matkul[l], substr[4 + l]); // Skills start from index 4
            }
        }

        // Add node to the tree
        add_child(*input, find_node(*input, T->root));
    }

    // Print preorder for debugging
    print_preorder(T->root);
    printf("\n");
}
