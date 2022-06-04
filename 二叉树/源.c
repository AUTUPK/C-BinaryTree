#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char datatype;

//创建节点
typedef struct BT {
	datatype data;
	struct BT* Lchild, * Rchild;
}BT;

// 根据先序、中序序列构建二叉树 
void BuildBT(BT** T, char* preorder, char* inorder, int PL, int PR, int IL, int IR)
{
	(*T) = (BT*)malloc(sizeof(BT));
	// 新结点数据设置为先序序列的第一个数据，即根节点数据
	(*T)->data = preorder[PL];

	// 根据先序第一个元素为根结点元素，寻找中序序列中的根结点位置
	int root;
	for (root = 0; root <= IR; root++)
	{
		if (preorder[PL] == inorder[root])
		{
			break;
		}
	}
	inorder[root] = '#';

	// 判断中序序列中<root>的左边是否存在左子序列
	if (root - IL > 0)
	{
		BuildBT(&(*T)->Lchild, preorder, inorder, PL + 1, PL + root - IL, IL, root - 1);
	}
	else
	{
		(*T)->Lchild = NULL;
	}

	// 判断中序序列中<root>的右边是否存在右子序列
	if (IR - root > 0)
	{
		BuildBT(&(*T)->Rchild, preorder, inorder, PR - (IR - root) + 1, PR, root + 1, IR);
	}
	else
	{
		(*T)->Rchild = NULL;
	}
}

//递归判断是否为对称二叉树
void F(BT* T1, BT* T2)
{
	if (T1->data == T2->data)//判断两个子树根节点是否相同
	{
		//判断是否到达叶节点
		if (!(T1->Lchild) & !(T1->Rchild) & !(T2->Lchild) & !(T2->Lchild) & !(T2->Rchild))printf("该树为对称二叉树。");

		//判断左子树的左右子树和右子树的右左子树是否相等
		else
		{
			if ( (((T1->Lchild!=NULL)&(T2->Rchild!=NULL))|| (!(T1->Lchild) & !(T2->Rchild))) & (((T1->Rchild != NULL) & (T2->Lchild != NULL)) || !(T1->Rchild) & (!(T2->Lchild))))
			{
				if ((T1->Lchild != NULL) & !(T1->Rchild))F(T1->Lchild, T2->Rchild);
				else if(!(T1->Lchild)&(T1->Rchild != NULL))F(T1->Rchild,T2->Lchild);
				else if ((T1->Lchild != NULL) & (T1->Rchild != NULL))
				{
					F(T1->Lchild, T2->Rchild);
					F(T1->Rchild, T2->Lchild);
				}
			}
			else
			{
				printf("该树不是对称二叉树。");
			}
		}
	}
	else
	{
		printf("该树不是对称二叉树。");
	}
}
int main()
{
	char preorder[30], inorder[30];
	printf("请输入先序序列：");
	scanf("%s", preorder);
	printf("请输入中序序列：");
	scanf("%s", inorder);

	//获取先序序列和中序序列的长度
	int Plen = strlen(preorder);
	int Ilen = strlen(inorder);

	//建立二叉树
	BT* T;
	BuildBT(&T, preorder, inorder, 0, Plen - 1, 0, Ilen - 1);

	//判断是否为对称二叉树
	F(T->Lchild,T->Rchild);
}
