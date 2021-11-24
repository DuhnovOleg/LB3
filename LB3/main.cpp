#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <stack>
#include <queue>
using namespace std;

typedef struct Node
{
	int vertex;
	Node* Next;
}Node;

typedef struct Graf
{
	int num;
	Node** A2;
}Graf;

Node* init_node(int v)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->vertex = v;
	NewNode->Next = NULL;
	return NewNode;
}

Graf* init_graf(int n)
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	graf->num = n;
	graf->A2 = (Node**)malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++)
		graf->A2[i] = NULL;
	return graf;
}

void print(Graf* graf)
{
	for (int i = 0; i < graf->num; i++)
	{
		Node* temp = graf->A2[i];
		printf("%d - �� �������: ", i + 1);
		while (temp)
		{
			printf("%d ", temp->vertex + 1);
			temp = temp->Next;
		}
		printf("\n");
	}
}

void add_spisok(int i, int j, Graf* graf)
{
	Node* NewNode = init_node(j);
	if (graf->A2[i] == NULL)
	{
		graf->A2[i] = NewNode;
		NewNode = NULL;
	}
	Node* temp = graf->A2[i];
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = NewNode;
	NewNode = init_node(i);
	if (graf->A2[j] == NULL)
	{
		graf->A2[j] = NewNode;
		NewNode = NULL;
	}
	temp = graf->A2[j];
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = NewNode;
}

int** create_arr(int x)
{
	int s = 1, **A;
	A = (int**)malloc(x * sizeof(int*));
	srand(time(NULL));
	for (int i = 0; i < x; i++)
	{
		A[i] = (int*)malloc(x * sizeof(int));
		A[i][i] = 0;
		for (int j = s; j < x; j++)
		{
			if (rand() % 100 > 42)
				A[i][j] = 0;
			else
				A[i][j] = 1;
		}
		s++;
	}
	s = 1;
	for (int i = 0; i < x; i++)
	{
		for (int j = s; j < x; j++)
		{
			A[j][i] = A[i][j];
		}
		s++;
	}
	for (int i = 0; i < x; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < x; i++)
	{
		printf("\n");
		for (int j = 0; j < x; j++)
			printf("%2d ", A[i][j]);
	}
	return A;
}

void union_graf(int** M1, int** M2, int n, int x)
{
	int** A1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	int** A2 = (int**)malloc(x * sizeof(int*));
	for (int i = 0; i < x; i++)
	{
		A2[i] = (int*)malloc(x * sizeof(int));
		for (int j = 0; j < x; j++)
			A2[i][j] = M2[i][j];
	}		
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (A1[i][j] != A2[i][j])
				A1[i][j] = A1[i][j] + A2[i][j];
		}
	}
	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%2d ", A1[i][j]);
	}
}

void crossing_graf(int** M1, int** M2, int n, int x)
{
	int** A1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	int** A2 = (int**)malloc(x * sizeof(int*));
	for (int i = 0; i < x; i++)
	{
		A2[i] = (int*)malloc(x * sizeof(int));
		for (int j = 0; j < x; j++)
			A2[i][j] = M2[i][j];
	}
	int s = 1;
	for (int i = 0; i < x; i++)
	{
		for (int j = s; j < x; j++)
		{
			if (A1[i][j] == 1 && A2[i][j] == 1)
				A1[i][j] = 1;
			else
				A1[i][j] = 0;
		}
		s++;
	}
	s = x;
	for (int i = 0; i < n; i++)
		for (int j = s; j < n; j++)
			A1[i][j] = 0;
	s = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = s; j < n; j++)
			A1[j][i] = A1[i][j];
		s++;
	}
	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%2d ", A1[i][j]);
	}
}

void annular_sum_graf(int** M1, int** M2, int n, int x)
{
	int** A1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	int** A2 = (int**)malloc(x * sizeof(int*));
	for (int i = 0; i < x; i++)
	{
		A2[i] = (int*)malloc(x * sizeof(int));
		for (int j = 0; j < x; j++)
			A2[i][j] = M2[i][j];
	}
	int s = 1;
	for (int i = 0; i < x; i++)
	{
		for (int j = s; j < x; j++)
		{
			if (A1[i][j] == A2[i][j])
				A1[i][j] = 0;
			else
				A1[i][j] = 1;
		}
		s++;
	}
	s = 1;
	int l = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = s; j < n; j++)
			A1[j][i] = A1[i][j];
		s++;
	}
	for (int p = 0; p < n; p++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A1[p][j] == 1)
				l++;
		}
		if (l == 0)
		{
			for (int i = p; i < n - 1; i++)
			{
				for (int j = 0; j < n; j++)
					A1[i][j] = A1[i + 1][j];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = p; j < n - 1; j++)
					A1[i][j] = A1[i][j + 1];
			}
			n--;
			p--;
		}
		l = 0;
	}
	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%2d ", A1[i][j]);
	}
}

void closure_graf(int** M1, int n, int x)
{
	int a, b, ** A1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	printf("�������� ������ ������, ������� ������ ��������: ");
	scanf("%d %d", &a, &b);
	a--; b--;
	for (int i = 0; i < n; i++)
	{
		if (A1[a][i] != A1[b][i])
		{
			A1[a][i] = A1[a][i] + A1[b][i];
		}
		A1[b][i] = 0;
	}
	if (A1[a][a] == 0)
		A1[a][a] = 1;
	int l = 0;
	for (int p = 0; p < n; p++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A1[p][j] == 1)
				l++;
		}
		if (l == 0)
		{
			for (int i = p; i < n - 1; i++)
			{
				for (int j = 0; j < n; j++)
					A1[i][j] = A1[i + 1][j];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = p; j < n - 1; j++)
					A1[i][j] = A1[i][j + 1];
			}
			n--;
			p--;
		}
		l = 0;
	}
	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%2d ", A1[i][j]);
	}
}

void closure_graf_spisok(int n, int x, Graf* graf)
{
	int l = 0, a, b;
	printf("�������� ������ ������, ������� ������ ���������: ");
	scanf("%d %d", &a, &b); a--; b--;

	Node* head, * heder, * kemp = graf->A2[b], * pemp = graf->A2[a], * temp = graf->A2[a];
	while (temp->Next != NULL)
		temp = temp->Next;
	heder = kemp;
	head = pemp;
	while (kemp != NULL)
	{
		while (pemp != NULL)
		{
			if (kemp->vertex == pemp->vertex)
				l++;
			pemp = pemp->Next;
		}
		pemp = head;
		if (l == 0)
		{
			temp->Next = (Node*)malloc(sizeof(Node));
			temp = temp->Next;
			temp->vertex = kemp->vertex;
		}
		temp->Next = NULL;
		kemp = kemp->Next;
		l = 0;
	}
	kemp = heder; temp = graf->A2[a]; l = 0;
	while (temp->Next != NULL)
	{
		if (temp->vertex == a)
			l++;
		temp = temp->Next;
	}
	if (l == 0)
	{
		temp->Next = (Node*)malloc(sizeof(Node));
		temp = temp->Next;
		temp->vertex = a;
		temp->Next = NULL;
	}
	for (int i = b; i < n - 1; i++)
		graf->A2[i] = graf->A2[i + 1];
	graf->A2[n - 1] = NULL;
	for (int i = 0; i < n - 1; i++)
	{
		Node* semp = graf->A2[i];
		printf("%d - �� �������: ", i + 1);
		while (semp != NULL)
		{
			printf("%d ", semp->vertex + 1);
			semp = semp->Next;
		}
		printf("\n");
	}
}

void delete_vertex_graf(int** M1, int n)
{
	int a, b, ** A1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	printf("�������� ������ ������, ������� ������ �������: ");
	scanf("%d %d", &a, &b);
	a--; b--;
	if (A1[a][b] == A1[b][a])
	{
		for (int i = 0; i < n; i++)
		{
			if (A1[a][i] != A1[b][i])
				A1[a][i] = A1[a][i] + A1[b][i];
			A1[b][i] = 0;
		}
	}
	if (A1[a][a] == 1)
		A1[a][a] = 0;
	int l = 0;
	for (int p = 0; p < n; p++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A1[p][j] == 1)
				l++;
		}
		if (l == 0)
		{
			for (int i = p; i < n - 1; i++)
			{
				for (int j = 0; j < n; j++)
					A1[i][j] = A1[i + 1][j];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = p; j < n - 1; j++)
					A1[i][j] = A1[i][j + 1];
			}
			n--;
			p--;
		}
		l = 0;
	}
	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%2d ", A1[i][j]);
	}
}

void delete_vertex_graf_spisok(int n, int x, Graf* graf)
{
	int a, b, l = 0, q = 0;
	printf("�������� ������ ������, ������� ������ �������: ");
	scanf("%d %d", &a, &b); a--; b--;
	Node* temp = graf->A2[a], * pemp = graf->A2[a], * kemp = graf->A2[b], * head, * header;
	while (temp->Next != NULL)
		temp = temp->Next;
	head = pemp; header = kemp;
	while (kemp != NULL)
	{
		if (a == kemp->vertex)
			q++;
		kemp = kemp->Next;
	}
	kemp = header;
	if (q != 0)
	{
		while (kemp != NULL)
		{
			while (pemp != NULL)
			{
				if (kemp->vertex == pemp->vertex && kemp->vertex != a)
					l++;
				pemp = pemp->Next;
			}
			pemp = head;
			if (l == 0)
			{
				temp->Next = (Node*)malloc(sizeof(Node));
				temp = temp->Next;
				temp->vertex = kemp->vertex;
			}
			temp->Next = NULL;
			kemp = kemp->Next;
			l = 0;
		}
	}
	else
	{
		printf("\n������ ������� ������ �������!");
		delete_vertex_graf_spisok(n, x, graf);
	}	
	for (int i = b; i < n - 1; i++)
		graf->A2[i] = graf->A2[i + 1];
	graf->A2[n - 1] = NULL;
	for (int i = 0; i < n - 1; i++)
	{
		Node* semp = graf->A2[i];
		printf("%d - �� �������: ", i + 1);
		while (semp != NULL)
		{
			printf("%d ", semp->vertex + 1);
			semp = semp->Next;
		}
		printf("\n");
	}
}

void split_graf(int** M1, int n)
{ 
	int l = 0, z = n + 1, a, ** A1 = (int**)malloc(n * sizeof(int*)), ** R1 = (int**)malloc(z * sizeof(int*));
	for (int i = 0; i < z; i++)
	{
		R1[i] = (int*)malloc(z * sizeof(int));
		for (int j = 0; j < z; j++)
			R1[i][j] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		A1[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			A1[i][j] = M1[i][j];
	}
	printf("�������� ����� �������, ������� ������ ���������: ");
	scanf("%d", &a);
	a--;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			R1[i][j] = A1[i][j];
			R1[n][i] = R1[a][i];
			R1[i][n] = R1[a][i];
	}
	R1[n][a] = 1; R1[a][n] = 1;
	for (int i = 0; i < z; i++)
		printf("V%d ", i + 1);
	for (int i = 0; i < z; i++)
	{
		printf("\n");
		for (int j = 0; j < z; j++)
			printf("%2d ", R1[i][j]);
	}
}

void split_graf_spisok(int n, int x, Graf* graf)
{
	int a, z = n + 1, l = 0;
	Graf* g = init_graf(z);
	printf("�������� ����� �������, ������� ������ ���������: ");
	scanf("%d", &a);
	a--;
	for (int i = 0; i < n; i++)
	{
		Node * head, * head1, * temp = graf->A2[i], * temp1 = g->A2[i];
		while (temp)
		{
			temp1->Next = (Node*)malloc(sizeof(Node));
			temp1 = temp1->Next;
			temp1->vertex = temp->vertex;
			temp->Next = NULL;
			temp = temp->Next;
		}
	}
	Node * temp = graf->A2[a], * temp1 = g->A2[n];
	while (temp)
	{
		temp1->Next = (Node*)malloc(sizeof(Node));
		temp1 = temp1->Next;
		temp1->vertex = temp->vertex;
		temp->Next = NULL;
		temp = temp->Next;
	}
	temp = graf->A2[a], temp1 = g->A2[n];
	while (temp->Next != NULL)
		temp = temp->Next;
	while (temp1->Next != NULL)
		temp1 = temp1->Next;
	temp->Next = (Node*)malloc(sizeof(Node));
	temp = temp->Next;
	temp->vertex = z;
	temp->Next = NULL;

	temp1->Next = (Node*)malloc(sizeof(Node));
	temp1 = temp1->Next;
	temp1->vertex = a + 1;
	temp1->Next = NULL;
	for (int i = 0; i < n; i++)
	{
		Node* temp = g->A2[i];
		while (temp != NULL)
		{
			if (temp->vertex == a)
				l++;
		}
		if (l == 0)
		{
			temp->Next = (Node*)malloc(sizeof(Node));
			temp = temp->Next;
			temp->vertex = z;
			temp->Next = NULL;
		}
		l = 0;
	}
	for (int i = 0; i < z; i++)
	{
		Node* semp = graf->A2[i];
		printf("%d - �� �������: ", i + 1);
		while (semp != NULL)
		{
			printf("%d ", semp->vertex + 1);
			semp = semp->Next;
		}
		printf("\n");
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");
	int** t, ** r, n, x;
	printf("������� 1\n");
	printf("������� ������: ");
	scanf("%d", &n);
	t = create_arr(n); 
	printf("\n\n");
	Graf* graf = init_graf(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (t[i][j] == 1 && i > j)
				add_spisok(i, j, graf);
		}
	}
	print(graf);


	printf("\n\n������� ������: ");
	scanf("%d", &x);
	while (x > n)
	{
		printf("������ ������ ������� ������ ���� ������!");
		printf("\n������� ������ ������, ����������: ");
		scanf("%d", &x);
	}
	r = create_arr(x);
	printf("\n\n");
	Graf* graff = init_graf(x);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (r[i][j] == 1 && i > j)
				add_spisok(i, j, graff);
		}
	}
	print(graff);


	//printf("\n������� 2.1.1\n"); closure_graf(t, n, x); printf("\n\n"); _getch();// closure_graf(r, x, n); printf("\n\n"); _getch();
	//printf("\n������� 2.1.2\n"); delete_vertex_graf(t, n); printf("\n\n"); _getch(); //delete_vertex_graf(r, x); printf("\n\n"); _getch();
	//printf("\n������� 2.1.3\n"); split_graf(t, n); printf("\n\n"); _getch();// split_graf(t, x); printf("\n\n"); _getch();
	//printf("\n������� 2.2.1\n"); closure_graf_spisok(n, x, graf); printf("\n\n"); _getch();
	//printf("\n������� 2.2.2\n"); delete_vertex_graf_spisok(n, x, graf); printf("\n\n"); _getch();
	printf("\n������� 2.2.3\n"); split_graf_spisok(n, x, graf); printf("\n\n"); _getch();


	printf("\n������� 3.1\n"); union_graf(t, r, n, x); printf("\n\n"); _getch(); 
	printf("\n������� 3.2\n"); crossing_graf(t, r, n, x); printf("\n\n"); _getch();
	printf("\n������� 3.3\n"); annular_sum_graf(t, r, n, x); printf("\n\n"); _getch();



	_getch();
}
