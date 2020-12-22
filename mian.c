#include<stdio.h>
#include<stdlib.h>

#include"main.h"

typedef struct student
{
	int id;
	int age;
	char sex;
	char name[20];
	struct student* last;
	struct student* next;
}Student;

Student *take_Off_Node(Student** head, Student** tail,Student *p)
{
	if (*head == p)
	{
		*head = p->next;
		p->next->last = NULL;
	}
	else if (*tail == p)
	{
		*tail = p->last;
		p->last->next = NULL;
	}
	else {
		p->last->next = p->next;
		p->next->last = p->last;
	}
	return p;
}

void delete_Node(Student *p)
{
	free(p);
}

Student *create_node()
{
	Student* temp = (Student*)malloc(sizeof(Student));
	if (temp == NULL) { printf("malloc error!!!\n"); exit(-1); }
	int id;
	printf("input id:");
	scanf_s("%d", &id);
	temp->id = id;
	while (getchar() != '\n');
	temp->next = NULL;
	temp->last = NULL;
	return temp;
}

void head_insert(Student **head,Student* p,Student **tail)
{
	p->last = NULL;
	p->next = *head;
	*head = p;
	if (p->next != NULL)p->next->last = p;
	else *tail = p;
}

void print_One_Student(Student *head)
{
	printf("id:%d\n", head->id);
}


void add_student(Student **head,Student** tail)
{
	Student* temp = create_node();
	head_insert(head, temp,tail);
}



void print_All_Student(Student* tail)
{
	if (tail == NULL)printf("空空如也!!!!\n");
	while (tail != NULL)
	{
		print_One_Student(tail);
		tail = tail->last;
	}
}

Student* find_Student(Student *head,int id)
{
	while (head != NULL)
	{
		if (head->id == id) return head;
		head = head->next;
	}
	return NULL;
}

void delete_student(Student **head, Student** tail)
{
	printf("Please input id:");
	int id;
	scanf_s("%d", &id);
	while (getchar() != '\n');
	Student* temp = find_Student(*head,id);
	if (temp == NULL)
	{
		printf("id不存在！！！\n");
		return;
	}
	take_Off_Node(head,tail,temp);
	delete_Node(temp);
}

void sort_Studnet(Student* head)
{
	Student a = *head;
	*head = *(head->next);
	*(head->next) = a;
}

int main()
{
	Student* head = NULL;
	Student* tail = NULL;
	while (1)
	{
		printf("%s", STUDENTMENU);
		char sel = getchar();
		while (getchar() != '\n');
		switch (sel)
		{
		case '1':add_student(&head,&tail); break;// 添加学生信息
		case '2':delete_student(&head,&tail);break;// 删除学生信息
		case '3':break;// 更改学生信息
		case '4':break;// 查找学生信息
		case '5':print_All_Student(tail); break;// 显示所有学生信息
		case '6':sort_Studnet(head); break;// 排序
		case '7':return;// 退出
		}
	}
}