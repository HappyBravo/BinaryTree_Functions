#include "binary_tree_functions.c"


int main(){
  // root = makeNode(7);
  // root->left = makeNode(3);
  // root->right = makeNode(13);
  
  // root->left->right = makeNode(6);
  // root->right->left = makeNode(11);
  // root->right->right = makeNode(15);
  
  // root->left->right->left = makeNode(5);
  // root->right->left->right = makeNode(12);
  root = createNode(7);
  insertLeft(root, 3);
  insertRight(root, 13);
  
  insertRight(root->left, 6);
  insertLeft(root->right, 11);
  insertLeft(root->left, 2);
  insertRight(root->right, 15);
  
  insertLeft(root->left->right, 5);
  insertRight(root->right->left, 12);
  insertLeft(root->right->left, 10);

  
  btNode *emproot = NULL;

  printf("%d\n\n\n", isEmpty(root));
  print_t(root);
  bt_inorder(root);
  printf("\n");
  bt_preorder(root);
  printf("\n");
  bt_postorder(root);
  printf("\nChecking Internal : \n");
  printf("%d", isInternal(root, 11));
  printf("\nChecking External : \n");
  printf("%d", isExternal(root, 10));
  printf("\nChecking Children : \n");
  printList(children(root, 10));
  
 
  return 0;
}

