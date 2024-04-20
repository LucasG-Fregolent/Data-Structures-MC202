typedef struct bTree *pbTree; // pbTree stands for "pointer to binary tree"
typedef struct head *pHead;

struct bTree{
    char *data;
    pbTree left, right, parent;
};

struct head{
    pbTree root;
};

int isAlphabet(char letter);

pHead createTree();

void burnTree(pbTree tree);

void printTree(pbTree tree);

pbTree plantTree(pbTree tree);

char *trimTree(pbTree tree);