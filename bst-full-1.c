/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h> 

typedef struct node { //별칭 Node, 정수형 변수 key와 node구조체 포인터 변수 *left/*right 을 가지는 구조체 node선언
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); //node구조체 이중포인터 h를 변수로 하는 initializeBST 함수 선언

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */ //반환값 없고, Node구조체 포인터 변수 ptr을 변수로하는 중위 순회 함수 선언
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */ //반환값 없고, Node구조체 포인터 변수 ptr을 변수로하는 선위 순회 함수 선언
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */ //반환값 없고, Node구조체 포인터 변수 ptr을 변수로하는 후위 순회 함수 선언
int insert(Node* head, int key);  /* insert a node to the tree */ //node구조체 포인터변수 head와 정수형 변수 key를 변수로 하는 정수형 함수 insert 선언
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */ //node구조체 포인터변수 head와 정수형 변수 key를 변수로 하는 정수형 함수 deleteLeafNode 선언
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */ //Node구조체 포인터변수 ptr과 정수형 변수 key를 변수로하는 재귀검색 함수 선언
Node* searchIterative(Node* head, int key);  /* search the node for the key */ //Node구조체 포인터변수 head와 정수형 변수 key를 변수로 하는 반복검색 선언
int freeBST(Node* head); /* free all memories allocated to the tree */ //메모리 초기화 용도의 freeBST함수 선언

/* you may add your own defined functions if necessary */


int main()
{
	char command; //입력받은 명령어를 저장하기위함
	int key; // 함수 실행시에, key값을 비교하기 위함
	Node* head = NULL; //head와 ptr을 사용하기위해 먼저 초기화를 시켜줌
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("-----------------Kim Beom Gyu-----------------2019062022--------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //포인터변수 h가 NULL이 아니라면, freeBST함수 실행
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //포인터변수 h에 Node구조체 크기만큼의 동적 메모리 할당
	(*h)->left = NULL;	/* root */ //포인터 변수 h의 left를 초기화
	(*h)->right = *h; //포인터 변수 h의 right에 *h 값을
	(*h)->key = -9999; //포인터 변수 h의 key값은 -9999로 할당
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {  //ptr에 값이 있으면
		inorderTraversal(ptr->left);  //ptr의 left에대한 중위 순회 함수 실행
		printf(" [%d] ", ptr->key); //ptr의 key값 출력
		inorderTraversal(ptr->right); //pter의 right에 대해 중위 순회 함수 실행
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) { //ptr에 값이 있으면
		printf(" [%d] ", ptr->key); //ptr의 key값을 출력,
		preorderTraversal(ptr->left); //ptr의 left와 right 각각에 대한 선위 순회 함수를 실행
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left); //ptr의 left, right에 대해 각각 후위 순회 함수를 실행함
		postorderTraversal(ptr->right); //이 때, ptr은 빈 값이 아니여야함
		printf(" [%d] ", ptr->key); //key값을 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node구조체 포인터변수 newNode에 Node구조체 크기만큼의 동적메모리 할당
	newNode->key = key; //newNode의 key값에 key값을
	newNode->left = NULL; //left와 right는 초기화를 시켜줌
	newNode->right = NULL;

	if (head->left == NULL) { //head 의 left가 NULL이면
		head->left = newNode; //newNode값을 거기에 대입해줌
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node구조체 포인터변수 ptr에 head의 left값 대입

	Node* parentNode = NULL; //부모노드를 선언해주고 동시에 초기화
	while(ptr != NULL) { //ptr에 값이 있을때만 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key값이 key값과 같으면

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //부모노드에 ptr값을 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //만약에 key값이 더 크면
			ptr = ptr->right; //오른쪽에 두고
		else
			ptr = ptr->left; //작으면 왼쪽에 둠
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //만일 부모노드의 key가 더 크다면
		parentNode->left = newNode; //부모노드의 왼쪽에 newNode값을 대입함
	else
		parentNode->right = newNode; //부모노드의 key값보다 크다면 오른쪽에 대입
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이면 삭제할게 없으니 오류 메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head의 left에 값이 없어도 삭제할 것이 없으니 오류메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node 구조체 포인터 변수 ptr에 head의 left값 대입


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //부모노드에 head값을 대입

	while(ptr != NULL) { //ptr에 값이 있을때만 반복

		if(ptr->key == key) { //ptr의 key값이 key값과 같다면
			if(ptr->left == NULL && ptr->right == NULL) { //그리고 ptr의 왼쪽,오른쪽 모두가 NULL일때

				/* root node case */
				if(parentNode == head) //또, 부모노드와 head값이 같으면
					head->left = NULL; //head의 left를 초기화시켜주고

				/* left node case or right case*/
				if(parentNode->left == ptr) //만약 부모노드의 left가 ptr이라면
					parentNode->left = NULL; //초기화
				else
					parentNode->right = NULL; //아니면 right을 초기화

				free(ptr); //ptr에 할당되었던 메모리 반환
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); //어느하나라도 null이 아니라면, ptr의 key값이 leaf노드가 아니다라고 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //부모노드에 ptr값 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key값보다 key값이 더크면
			ptr = ptr->right; //ptr의 right을 ptr에 대입
		else
			ptr = ptr->left; //아니면 왼쪽에 대입


	}

	printf("Cannot find the node for key [%d]\n ", key); //ptr에 값이 없으면 반복안하고, 찾을수 없다는 오류메세지 출력함

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) //ptr이 NULL값이면 null반환
		return NULL;

	if(ptr->key < key) //ptr의 key값이 key값보다 작으면
		ptr = searchRecursive(ptr->right, key); //ptr의 right과 key에 대해 재귀검색 함수 실행한 뒤, ptr에 대입
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);  // key값보다 크다면, ptr의 left와 key에 대해 재귀검색함수 실행하고 ptr에 대입

	/* if ptr->key == key */
	return ptr; //ptr값 반환

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left; //head의 left값을 Node구조체 포인터변수 ptr에 대입

	while(ptr != NULL) //ptr이 NULL이 아닐떄 반복
	{
		if(ptr->key == key) //ptr의 key값과 key값이 동일하다면
			return ptr; //ptr바로 반환

		if(ptr->key < key) ptr = ptr->right; //ptr의 key값보다 key값이 더 크면, ptr에 ptr의 right값 대입
		else
			ptr = ptr->left; //더 작으면 left값을 대입
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) { //ptr에 값이 있을때
		freeNode(ptr->left); //ptr의 left 초기화
		freeNode(ptr->right); //ptr의 right도 초기화
		free(ptr); //ptr에 할당된 메모리 반환
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //head의 left값과 head값이 같을 때
	{
		free(head); //head에 할당된 메모리 반환
		return 1;
	}

	Node* p = head->left; //Node구조체[ 포인터변수 p]에 head의 left값 대입
 
	freeNode(p); //p에 대한 freeNode함수 실행
 
	free(head); //head에 대한 메모리 반환
	return 1;
}





