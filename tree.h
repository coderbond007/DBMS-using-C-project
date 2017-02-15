// Node stores the informtaion about Person name, age, match-percentage, name and his GENE.
typedef struct Node {
	int height;
	int age;
	int matchpercentage;
	char name[100];
	char gene[500];
	struct Node* left;
	struct Node* right;
}node;

node* getnode();
int height(node* p);
int max(int a, int b);
int getBalance(node* p);
node* rotateleft(node* x);
node* rotateright(node* y);
node* insert(node* root, node* p);
void preorder(node* root);
void printincreasing(node* root, int left_bound, int right_bound);
void printdecreasing(node* root, int left_bound, int right_bound);
void print_node(node* person);