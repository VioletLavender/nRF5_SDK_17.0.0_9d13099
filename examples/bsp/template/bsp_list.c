#include "stdio.h"				
#include "stdlib.h"				//�ṩmalloc()��free()
#include "string.h"				//�ṩstrcpy()��
#include "bsp_list.h"				

struct Node
{
	int a;				//������
	struct Node* next;	//ָ����(ָ��ڵ��ָ�룩
};

struct Node* List_head = NULL;
struct Node* List_end = NULL;


void AddListTill(int a)
{
	//����һ���ڵ�
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));		//�˴�ע��ǿ������ת��

	//�ڵ����ݽ��и�ֵ
	temp->a = a;
	temp->next = NULL;

	//���ӷ��������1.һ���ڵ㶼û��2.�Ѿ��нڵ��ˣ���ӵ�β����
	if (NULL == List_head)
	{

		List_head = temp;
		//	end=temp;
	}
	else
	{
		List_end->next = temp;
		//	end=temp;			//β���Ӧ��ʼ��ָ�����һ��
	}
	List_end = temp;			//β���Ӧ��ʼ��ָ�����һ��
}

void ScanList(void)
{
	struct Node* temp = List_head;		//����һ����ʱ������ָ��ͷ
	while (temp != NULL)
	{
		printf("%d\n", temp->a);
		temp = temp->next;		//tempָ����һ���ĵ�ַ ��ʵ��++����
	}

}

struct Node* FindNode(int a)
{
	struct Node* temp = List_head;
	while (temp != NULL)
	{
		if (a == temp->a)
		{
			return temp;
		}
		temp = temp->next;
	}
	//û�ҵ�
	return NULL;
}

void FreeList(void)
{
	//һ��һ��NULL
	struct Node* temp = List_head;		//����һ����ʱ������ָ��ͷ
	while (temp != NULL)
	{
		//	printf("%d\n",temp->a);
		struct Node* pt = temp;
		temp = temp->next;		//tempָ����һ���ĵ�ַ ��ʵ��++����
		free(pt);					//�ͷŵ�ǰ
	}
	//ͷβ���	��Ȼ�´ε�ͷ�ͽ���0x10
	List_head = NULL;
	List_end = NULL;
}

void AddListRand(int index, int a)
{

	if (NULL == List_head)
	{
		printf("����û�нڵ�\n");
		return;
	}
	struct Node* pt = FindNode(index);
	if (NULL == pt)    //û�д˽ڵ�
	{
		printf("û��ָ���ڵ�\n");
		return;
	}
	//�д˽ڵ�
	//������ʱ�ڵ㣬�����ڴ�
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	//�ڵ��Ա���и�ֵ
	temp->a = a;
	temp->next = NULL;
	//���ӵ������� 1.�ҵ��Ľڵ���β�� 2.�ҵ��Ľڵ����м� 
	if (pt == List_end)
	{
		//β�͵���һ��ָ���²���Ľڵ�
		List_end->next = temp;
		//�µ�β��
		List_end = temp;
	}
	else
	{
		// �������� ���Ƚ�Ҫ����Ľڵ�ָ��ָ��ԭ���ҵ��ڵ����һ����
		temp->next = pt->next;
		//����ǰ��
		pt->next = temp;
	}

}



void DeleteListTail(void)
{
	if (NULL == List_end)
	{
		printf("����Ϊ�գ�����ɾ��\n");
		return;
	}
	//����Ϊ�� 
	//������һ���ڵ�
	if (List_head == List_end)
	{
		free(List_head);
		List_head = NULL;
		List_end = NULL;
	}
	else
	{
		//�ҵ�β��ǰһ���ڵ�
		struct Node* temp = List_head;
		while (temp->next != List_end)
		{
			temp = temp->next;
		}
		//�ҵ��ˣ�ɾβ��
	   //�ͷ�β��
		free(List_end);
		//β��Ǩ��
		List_end = temp;
		//β��ָ��ΪNULL
		List_end->next = NULL;
	}

}

void DeleteListHead(void)
{	//��ס��ͷ
	struct Node* temp = List_head;
	//������ 
	if (NULL == List_head)
	{
		printf("����Ϊ��\n");
		return;
	}

	List_head = List_head->next;//ͷ�ĵڶ����ڵ����µ�ͷ
	free(temp);

}

void DeleteListRand(int a)
{

	//�����ж� �ǲ���û�ж���
	if (NULL == List_head)
	{
		printf("����û����\n");
		return;
	}
	//�����ж�����������ڵ�
	struct Node* temp = FindNode(a);
	if (NULL == temp)
	{
		printf("���޴˵�\n");
		return;
	}
	//�ҵ���,��ֻ��һ���ڵ�
	if (List_head == List_end)
	{
		free(List_head);
		List_head = NULL;
		List_end = NULL;
	}
	else if (List_head->next == List_end) //�������ڵ�
	{
		//����ɾ��ͷ����ɾ��β
		if (List_end == temp)
		{
			DeleteListTail();
		}
		else if (temp == List_head)
		{
			DeleteListHead();
		}
	}
	else//����ڵ�
	{
		//����ɾ��ͷ����ɾ��β
		if (List_end == temp)
			DeleteListTail();
		else if (temp == List_head)
			DeleteListHead();
		else	//ɾ���м�ĳ���ڵ�
		{	//��Ҫɾ��tempǰһ��������
			struct Node* pt = List_head;
			while (pt->next != temp)
			{
				pt = pt->next;
			}
			//�ҵ���
			//��ǰһ��ֱ�����Ӻ�һ�� ����ָ���ļ���
			pt->next = temp->next;
			free(temp);

		}
	}


}
