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
		printf("%d - ая вершина: ", i + 1);
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
			if (rand() % 100 > 22)
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

void delete_vertex(int n, int** A1)
{
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


int main()
{
	setlocale(LC_ALL, "Ru");
	int** t, ** r, n, x;

	printf("Введите размер: ");
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


	printf("\n\nВведите размер: ");
	scanf("%d", &x);
	while (x > n)
	{
		printf("Размер первой матрицы должен быть меньше!");
		printf("\nВведите другой размер, пожалуйста: ");
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


	printf("\nЗадание 3.1\n"); union_graf(t, r, n, x); printf("\n\n"); _getch();
	printf("\nЗадание 3.2\n"); crossing_graf(t, r, n, x); printf("\n\n"); _getch();
	printf("\nЗадание 3.3\n"); annular_sum_graf(t, r, n, x); printf("\n\n"); _getch();


	_getch();
}
