void insertLeft(pbTree tree){
//     char buffer[MAX];
//     scanf(" %s", buffer);

//     printf("buffer %s\n", buffer);

//     if(buffer[0]==')'){
//         printf("execucao correta\n");
//         return;
//     }
//     else if(buffer[0]=='('){
//         printf("ta no caso inicial %s\n", buffer);
//         pbTree newNode;
//         newNode = malloc(sizeof(struct bTree));
//         newNode->data = ".";
//         newNode->parent = tree;
//         tree->left = newNode;
//         insertLeft(newNode);
//         insertRight(newNode);
//     }
//     else if(buffer[0]>='0' && buffer[0]<='9'){
//         printf("ta no caso int %s\n", buffer);
//         pbTree newNode;
//         newNode = malloc(sizeof(struct bTree));
//         newNode->left = newNode->right = NULL;
//         newNode->data = buffer;
//         newNode->parent = tree;
//         tree->left = newNode;
//     }
//     else{ // Happens when the buffer is an operation symbol (i.e. +, -, * or /);
//         printf("outro caso %s\n", buffer);
//         tree->data = buffer;
//     }
//     return;
// }

// void insertRight(pbTree tree){
//     char buffer[MAX];
//     scanf(" %s", buffer);

//     if(buffer[0]==')'){
//         printf("execucao correta 2\n");
//         return;
//     }
//     else if(buffer[0]=='('){
//         pbTree newNode;
//         newNode = malloc(sizeof(struct bTree));
//         newNode->data = ".";
//         tree->right = newNode;
//         newNode->parent = tree;
//         insertLeft(newNode);
//         insertRight(newNode);
//     }
//     else if(buffer[0]>='0' && buffer[0]<='9'){
//         pbTree newNode;
//         newNode = malloc(sizeof(struct bTree));
//         newNode->left = newNode->right = NULL;
//         newNode->data = buffer;
//         newNode->parent = tree;
//         tree->right = newNode;
//     }
//     else{ // Happens when the buffer is an operation symbol (i.e. +, -, * or /);
//         printf("outro caso %s\n", buffer);
//         tree->data = buffer;
//     }
//     return;
// }

// void insertNode(pHead root){
//     char buffer[MAX];
//     scanf(" %s", buffer);

//     if(buffer[0]=='('){
//         pbTree newNode;
//         newNode = malloc(sizeof(struct bTree));
//         newNode->parent = NULL;
//         newNode->left = newNode->right = NULL;
//         root->first = newNode;
//     }

//     printf("ok\n");
//     printTree(root->first);

//     insertLeft(root->first);
//     insertRight(root->first);
// }