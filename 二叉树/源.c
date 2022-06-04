#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char datatype;

//�����ڵ�
typedef struct BT {
	datatype data;
	struct BT* Lchild, * Rchild;
}BT;

// ���������������й��������� 
void BuildBT(BT** T, char* preorder, char* inorder, int PL, int PR, int IL, int IR)
{
	(*T) = (BT*)malloc(sizeof(BT));
	// �½����������Ϊ�������еĵ�һ�����ݣ������ڵ�����
	(*T)->data = preorder[PL];

	// ���������һ��Ԫ��Ϊ�����Ԫ�أ�Ѱ�����������еĸ����λ��
	int root;
	for (root = 0; root <= IR; root++)
	{
		if (preorder[PL] == inorder[root])
		{
			break;
		}
	}
	inorder[root] = '#';

	// �ж�����������<root>������Ƿ������������
	if (root - IL > 0)
	{
		BuildBT(&(*T)->Lchild, preorder, inorder, PL + 1, PL + root - IL, IL, root - 1);
	}
	else
	{
		(*T)->Lchild = NULL;
	}

	// �ж�����������<root>���ұ��Ƿ������������
	if (IR - root > 0)
	{
		BuildBT(&(*T)->Rchild, preorder, inorder, PR - (IR - root) + 1, PR, root + 1, IR);
	}
	else
	{
		(*T)->Rchild = NULL;
	}
}

//�ݹ��ж��Ƿ�Ϊ�Գƶ�����
void F(BT* T1, BT* T2)
{
	if (T1->data == T2->data)//�ж������������ڵ��Ƿ���ͬ
	{
		//�ж��Ƿ񵽴�Ҷ�ڵ�
		if (!(T1->Lchild) & !(T1->Rchild) & !(T2->Lchild) & !(T2->Lchild) & !(T2->Rchild))printf("����Ϊ�Գƶ�������");

		//�ж������������������������������������Ƿ����
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
				printf("�������ǶԳƶ�������");
			}
		}
	}
	else
	{
		printf("�������ǶԳƶ�������");
	}
}
int main()
{
	char preorder[30], inorder[30];
	printf("�������������У�");
	scanf("%s", preorder);
	printf("�������������У�");
	scanf("%s", inorder);

	//��ȡ�������к��������еĳ���
	int Plen = strlen(preorder);
	int Ilen = strlen(inorder);

	//����������
	BT* T;
	BuildBT(&T, preorder, inorder, 0, Plen - 1, 0, Ilen - 1);

	//�ж��Ƿ�Ϊ�Գƶ�����
	F(T->Lchild,T->Rchild);
}
