#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
   int data;
   struct tree *left;
   struct tree *right;
} tree;

tree *insert(tree *root, int value)
{
   if (root == NULL)
   {
      root = malloc(sizeof(tree));
      root->data = value;
      root->left = NULL;
      root->right = NULL;
   }
   else if (value < root->data)
   {
      root->left = insert(root->left, value);
   }
   else if (value > root->data)
   {
      root->right = insert(root->right, value);
   }
   return root;
}

tree *search(tree *root, int key)
{
   if (root == NULL)
   {
      return root;
   }
   else if (key < root->data)
   {
      return search(root->left, key);
   }
   else if (key > root->data)
   {
      return search(root->right, key);
   }
   else if (root->data == key)
   {
      return root;
   }
}

tree *getparent(tree *root, int key)
{
   tree *p = root;
   tree *current = root;
   if (key == root->data)
   {
      return NULL;
   }
   while (current != NULL)
   {
      if (key < current->data)
      {
         p = current;
         current = current->left;
      }

      else if (key > current->data)
      {
         p = current;
         current = current->right;
      }
      else if (key == current->data)
      {
         break;
      }
   }

   return p;
}

/*tree* successor1(tree*root,int key)
{
   tree*p=root;
   tree*current=root;
   if(key==current->data)
   {
   while(current->right!=NULL)
   {
      p=current;
      current=current->right;
   }
   if(p->left!=NULL)
   {
      p=p->left;
      return p;
      current=p;
   }
   else
   {
      return p;
      current=p;
   }
   }

    else if(key<current->data)
   {
   while(current->left!=NULL)
   {
      p=current;
      current=current->left;
   }
   if(p->right!=NULL)
   {
      p=p->right;
      return p;
      current=p;
   }
   else
   {
      return NULL;
   }
   }

   else if(key>current->data)
   {
    while(current->right!=NULL)
      {
         current=current->right;
      }
   }
   return current;

}*/

tree *successor1(tree *root)
{
   tree *p = NULL;

   if (root == NULL)
      return NULL;

   if (root->right != NULL)
   {
      p = root->right;
      while (p->left != NULL)
      {
         p = p->left;
      }
   }
   return p;
}

tree *predecessor1(tree *root)
{
   tree *p = NULL;
   p = root;
   if (root == NULL)
      return NULL;

   while (p->left != NULL)
   {
      p = p->left;
      if (p->right != NULL)
      {
         p = p->right;
      }
   }
   return p;
}

tree *maxnode(tree *root)
{
   if (root == NULL && root->right == NULL)
   {
      return root;
   }
   else
   {
      return maxnode(root->right);
   }
}

tree *delete(tree *root, int key)
{
   tree *p = search(root, key);
   tree *q = getparent(root, key);
   tree *r = NULL;
   tree *s = NULL;
   if (p->left == NULL && q->left == NULL)
   {
      if (q->data > p->data)
         q->left == NULL;
      else
         q->right == NULL;
   }
   if (p->left != NULL && q->left == NULL)
   {
      if (q->data > p->data)
         q->left = p->left;
      else
         q->right = p->left;
   }
   if (p->left == NULL && q->left != NULL)
   {
      if (q->data > p->data)
         q->left = p->right;
      else
         q->right = p->right;
   }
   if (p->left != NULL && q->left != NULL)
   {
      s = r = p->right;
      while (r->left != NULL)
      {
         s = r;
         r = r->left;
      }
      p->data = r->data;
      if (r->left == NULL)
         p->right = s->right;
      free(r);
      s->left = NULL;
   }
   return root;
}

void findNthSmallest(tree *root, int n, int *count)
{
   if (root == NULL || *count >= n)
   {
      return;
   }

   findNthSmallest(root->left, n, count);
   (*count)++;

   if (*count == n)
   {
      printf("The %dth smallest number is: %d\n", n, root->data);
      return;
   }

   findNthSmallest(root->right, n, count);
}

int searchpath(tree *root, int key)
{
   if (root == NULL)
   {
      return -1;
   }
   else if (key < root->data)
   {
      return 1 + searchpath(root->left, key);
   }
   else if (key > root->data)
   {
      return 1 + searchpath(root->right, key);
   }
   else if (key == root->data)
   {
      return 0;
   }
}

/*
int distanceFromRoot(struct Node* root, int key)
{
    if (root->data == key)
        return 0;
    else if (root->data > key)
        return 1 + distanceFromRoot(root->left, key);
    return 1 + distanceFromRoot(root->right, key);
}

// Returns minimum distance between a and b.
// This function assumes that a and b exist
// in BST.
int distanceBetween2(struct Node* root, int a, int b)
{
    if (!root)
        return 0;

    // Both keys lie in left
    if (root->data > a && root->data > b)
        return distanceBetween2(root->left, a, b);

    // Both keys lie in right
    if (root->data < a && root->data < b) // same path
        return distanceBetween2(root->right, a, b);

    // Lie in opposite directions (Root is
    // LCA of two nodes)
    if (root->data >= a && root->data <= b)
        return distanceFromRoot(root, a) +
               distanceFromRoot(root, b);
}
*/

tree *shortestpath(tree *root, int n1, int n2)
{
   int x1 = searchpath(root, n1);
   int x2 = searchpath(root, n2);
   printf("Shortest path is: %d", x1 + x2 - 1);
   printf("\n");
}

int totalnodes(tree *root)
{
   if (root == NULL)
   {
      return 0;
   }
   else
   {
      return (totalnodes(root->left) + totalnodes(root->right) + 1);
   }
}

tree *mirror(tree *root)
{
   if (root == NULL)
   {
      return 0;
   }
   else
   {
      mirror(root->left);
      mirror(root->right);
      tree *temp = root->left;
      root->left = root->right;
      root->right = temp;
   }
}

tree *LCA(tree *root, int x, int y)
{
   if (root == NULL)
   {
      return 0;
   }
   if (root->data < x && root->data < y)
   {
      return LCA(root->right, x, y);
   }
   if (root->data > x && root->data > y)
   {
      return LCA(root->left, x, y);
   }
   return root;
}

void findNthlargest(tree *root, int k, int *count1)
{
   if (root == NULL || *count1 >= k)
   {
      return;
   }
   findNthlargest(root->right, k, count1);
   (*count1)++;
   if (*count1 == k)
   {
      printf("The %dth largest number is: %d\n", k, root->data);
     // return;
   }
   findNthlargest(root->left, k, count1);
}

int height(tree *root)
{
   if (root == NULL)
   {
      return 0;
   }
   else
   {
      int leftheight = height(root->left);
      int rightheight = height(root->right);
      if (leftheight > rightheight)
      {
         return (1 + leftheight);
      }
      else
      {
         return (1 + rightheight);
      }
   }
}

void pairsum(tree *root, int sum)
{
   if (root == NULL)
      return;
   pairsum(root->left, sum);
   pairsum(root->right, sum);
   tree *p = root->left;
   tree *q = root->right;
   while (p != NULL)
   {
      if (p->data + q->data == sum)
      {
         printf("Value of p is: %d\n", p->data);
         printf("Value of q is: %d\n", q->data);
      }
      p = p->left;
   }
}

void inorder(tree *root)
{
   if (root == NULL)
      return;
   inorder(root->left);
   printf("%d ", root->data);
   inorder(root->right);
}

int main()
{
   int choice;
   int value = 0;
   int key, n;
   int n1, n2;
   int x, y, k;
   int sum;
   tree *root = NULL;
   while (1)
   {
      printf("**********MAIN MENU**********\n");
      printf("\n1.Insert an element");
      printf("\n2.Display tree");
      printf("\n3.Search a key and know its parent");
      printf("\n4.Inorder successor and predeccesor");
      printf("\n5.Delete a node");
      printf("\n6.Nth smallest number");
      printf("\n7.Shortestpath");
      printf("\n8.Total number of nodes");
      printf("\n9.Height of node");
      printf("\n10.Mirror image of given tree");
      printf("\n11.Least Common Ancestor");
      printf("\n12.Nth largest number");
      printf("\n13.Sum of two nodes equal to given sum or not");
      printf("\n14.Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
         while (value != -1)
         {
            printf("Enter positive integer(or -1): ");
            scanf("%d", &value);
            if (value != -1)
               root = insert(root, value);
         }
         break;
      case 2:
         inorder(root);
         printf("\n");
         if (root == NULL)
            printf("BST is empty");
         break;
      case 3:
         printf("Enter key to search: ");
         scanf("%d", &key);
         if (key > 0)
         {
            if (search(root, key))
            {
               printf("Key exists\n");
               tree *m = getparent(root, key);
               printf("%d", m->data);
               printf("\n");
            }
            else
            {
               printf("Key does not exists\n");
            }
         }
         break;
      case 4:
         printf("Enter key: ");
         scanf("%d", &key);
         tree *p = search(root, key);
         printf("\nInorder successor of the given key is: ");
         tree *successor = successor1(p);
         printf("%d", successor->data);
         p = search(root, key);
         printf("\nInorder predecessor of the given key is: ");
         tree *predecessor = predecessor1(p);
         printf("%d", predecessor->data);
         printf("\n");
         break;
      case 5:
         printf("Enter key to delete: ");
         scanf("%d", &key);
         root = delete (root, key);
         break;
      case 6:
         printf("Enter value of n: ");
         scanf("%d", &n);
         int count = 0;
         findNthSmallest(root, n, &count);
         break;
      case 7:
         printf("Enter first number: ");
         scanf("%d", &n1);
         printf("Enter second number: ");
         scanf("%d", &n2);
         shortestpath(root, n1, n2);
         break;
      case 8:
         printf("Total nodes is %d ", totalnodes(root));
         printf("\n");
         break;
      case 9:
         printf("Height of tree is %d ", height(root));
         printf("\n");
         break;
      case 10:
         printf("Mirror image of tree is: ", mirror(root));
         inorder(root);
         printf("\n");
         break;
      case 11:
         printf("Enter value of x: ");
         scanf("%d", &x);
         printf("Enter value of y: ");
         scanf("%d", &y);
         tree *t = LCA(root, x, y);
         printf("LCA of %d and %d is: %d", x, y, t->data);
         printf("\n");
         break;
      case 12:
         printf("Enter value of k: ");
         scanf("%d", &k);
         int count1 = 0;
         findNthlargest(root, k, &count1);
         break;
      case 13:
         printf("Enter value of sum: ");
         scanf("%d", &sum);
         pairsum(root, sum);
         printf("\n");
         break;
      case 14:
         exit(1);
         break;
      default:
         printf("Wrong choice, enter different choice\n");
         break;
      }
   }

   return 0;
}
