#include <stdio.h>
#include <stdlib.h>

struct Node
{
    double       key;
    struct Node *left;
    struct Node *right;
    char        *str;
};


/*int tree_find(struct Node *root, double key, char **pstr) {
	struct Node* now = root;
	if (now == NULL) {
		return 0;
	}
	while(now != NULL) {
		if (my_abs(now->key - key) < 1e-8) {
			break;
		}
		if (now->key < key) {
			now = now->left;
		} else {
			now = now->right;
		}
	}
	if (now == NULL)
		return 0;
	if (pstr != NULL)
		*pstr = now->str;
	return 1;
}*/
extern int tree_find(struct Node *root, double key, char **pstr);
int main() {
	struct Node* root = calloc(1, sizeof(*root));
	struct Node* left1 = calloc(1,sizeof(*left1));
	struct Node* right1 = calloc(1,sizeof(*right1));
	char lmao[] = "lmao";
	char rzhu[] = "rju";
	root->key = 0.25;
	root->str = lmao;
	root->left = left1;
	root->right = right1;
	left1->right = NULL;
	right1->right = NULL;
	left1->str = rzhu;
	left1->left = NULL;
	right1->left = NULL;
	right1->key = 0.76;
	left1->key = 0.12;
	char* kek = malloc(20*sizeof(*kek));

	printf("%d\n", tree_find(root, 0.12, &kek));
	printf("%s\n", kek);
}