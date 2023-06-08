#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a); //�迭�� �ʱ�ȭ �ϴ� �Լ�
int freeArray(int *a); //�޸𸮸� �����ϴ� �Լ�
void printArray(int *a); //�迭�� ����ϴ� �Լ�

int selectionSort(int *a); //�������� �Լ�
int insertionSort(int *a); //�������� �Լ�
int bubbleSort(int *a); //�������� �Լ�
int shellSort(int *a); //������ �Լ�

int quickSort(int *a, int n); //������ �Լ�

int hashCode(int key); //�ؽ� �ڵ带 ����� �Լ�

int hashing(int *a, int **ht); //�迭 a�� �ؽ����̺� �ִ� �Լ�

int search(int *ht, int key); //�ؽ����̺��� key���� ã�� �Լ�


int main()
{
    printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //�޴��� �Է¹��� ����
	int *array = NULL; //�迭�� NULL�� �ʱ�ȭ
	int *hashtable = NULL; //�ؽ����̺��� NULL�� �ʱ�ȭ
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //�迭�� �ʱ�ȭ �Ѵ�
			break;
		case 'q': case 'Q':
			freeArray(array); //�޸𸮸� �����Ѵ�
			break;
		case 's': case 'S':
			selectionSort(array); //���������� �Ѵ�
			break;
		case 'i': case 'I':
			insertionSort(array); //���� ������ �Ѵ�
			break;
		case 'b': case 'B':
			bubbleSort(array); //���� ������ �Ѵ�
			break;
		case 'l': case 'L':
			shellSort(array); //�� ������ �Ѵ�
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //�迭�� ����Ѵ�
			quickSort(array, MAX_ARRAY_SIZE); //���������Ѵ�
			printf("----------------------------------------------------------------\n");
			printArray(array); //�迭�� ����Ѵ�

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //�迭�� ����Ѵ�
			hashing(array, &hashtable); //�迭�� �ؽ����̺� �ִ´�
			printArray(hashtable);  //�ؽ����̺��� ����Ѵ�
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´� 
			printArray(hashtable); //�ؽ����̺��� ����Ѵ�
			index = search(hashtable, key); //index�� ã�� key���� index�� �ִ´�
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //key���� ����Ѵ�
			break;

		case 'p': case 'P':
			printArray(array); //�迭�� ����Ѵ�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //�ݺ��� ����

	return 1; //�Լ� ����
}

int initialize(int** a)
{
	int *temp = NULL;
	if(*a == NULL) { //a�� NULL�ΰ��
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //temp�� �����Ҵ��Ѵ�
		*a = temp;  //*a�� temp�� �����Ѵ�
	} else
		temp = *a; //temp�� *a�� �����Ѵ�

	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //�ݺ����� Ȱ���Ͽ� temp[i]�� �������� �����Ѵ�
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0; //�Լ� ����
}

int freeArray(int *a) 
{
	if(a != NULL) //a�� NULL�� �ƴϸ�
		free(a); //a�� �޸� ����
	return 0; //�Լ� ����
}

void printArray(int *a) 
{
	if (a == NULL) { //a�� NULL�϶� 
		printf("nothing to print.\n"); //����� ���� ����
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //�ݺ����� Ȱ���Ͽ� �迭�� index�� ����Ѵ�
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //�ݺ����� Ȱ���Ͽ� a[i]�� ���� ����Ѵ�
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //�迭 a�� ����Ѵ�

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //�ݺ����� Ȱ���Ͽ� ���������� �Ѵ�
	{
		minindex = i; //�ּҰ��� index�� i��� �����ϰ�
		min = a[i]; //�ּڰ��� a[i]����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //�ݺ����� Ȱ���Ͽ� minindex�� min���� �ּڰ����� �ٲ۴�
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];  //a�� �ּҰ��� a[i]����
		a[i] = min; //a[i]�� min����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //�迭 ���
	return 0; //�Լ� ����
}

int insertionSort(int *a) 
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //�迭 a�� ����Ѵ�

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //�ݺ����� Ȱ���Ͽ� ���� ������ �Ѵ�
	{
		t = a[i]; //t�� a[i]����
		j = i; //j�� i ����
		while (a[j-1] > t && j > 0) //a[j-i]�� t���� ũ�� j�� 0���� ũ�� ��� �ݺ�
		{
			a[j] = a[j-1]; //a[j]�� a[j-1]����
			j--; //j�� ����
		}
		a[j] = t; //a[j]�� t����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //�迭 ���

	return 0; //�Լ� ����
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //�迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //�ݺ����� Ȱ���Ͽ� ���������� �Ѵ�
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]>a[j]�̸�
			{
				t = a[j-1]; //t�� a[j-1]����
				a[j-1] = a[j]; //a[j-1]�� a[j]����
				a[j] = t; //a[j]�� t ����
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //�迭 a ���

	return 0; //�Լ� ����
}

int shellSort(int *a) 
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //�迭 a ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //�ݺ����� Ȱ���Ͽ� �������� �Ѵ�
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v�� a[j] ����
				k = j; //k�� j ����
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h]; //a[k]�� a[k-h] ����
					k -= h; //k�� k-h ����
				}
				a[k] = v; //a[k]�� v ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //�迭 a���

	return 0;
}

int quickSort(int *a, int n) 
{
	int v, t;
	int i, j;

	if (n > 1) //n�� 1���� Ŭ??
	{
		v = a[n-1]; //v�� a[n-1]����
		i = -1; //i�� -1����
		j = n - 1; //j�� n-1 ����

		while(1) 
		{
			while(a[++i] < v);//a[i]��<v�϶����� i�� ����
			while(a[--j] > v); //a[j]�� >v�϶����� i�� ����

			if (i >= j) break; //i�� j�� ���ų� ũ�� �ݺ��� ����
			t = a[i]; //t�� a[i]����
			a[i] = a[j]; //a[i]�� a[j]����
			a[j] = t; //a[j]�� t����
		}
		t = a[i]; //t�� a[i] ����
		a[i] = a[n-1]; //a[i]�� a[n-1]����
		a[n-1] = t; //a[n-1]�� t ����

		quickSort(a, i); //(����Լ�) quickSort(a, i) ȣ��
		quickSort(a+i+1, n-i-1); //(����Լ�) quickSort(a+i+1, n-i-1)ȣ��
	}


	return 0; //�Լ� ����
}

int hashCode(int key) { 
   return key % MAX_HASH_TABLE_SIZE; //key%MAX_HASH_TABLE_SIZE �� ����
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	//hash table�� NULL�� ��� �޸� �Ҵ� 
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  //�Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��
	} else {
		hashtable = *ht;	// hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //�ݺ����� Ȱ���Ͽ� hashtable[i]�� -1 ����

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) 
	{
		key = a[i];
		hashcode = hashCode(key); //hashcode�� hashcode�����Լ��� ���� �� ����

		if (hashtable[hashcode] == -1) //hashtable[hashcode]�� -1�϶�
		{
			hashtable[hashcode] = key;//hashtable[hashcode]�� key����
		} else 	{

			index = hashcode; //index�� hashcode ����

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //index�� (++index) % MAX_HASH_TABLE_SIZE����
			}
			hashtable[index] = key; //hashtable[index]�� key ����
		}
	}

	return 0; //�Լ� ����
}

int search(int *ht, int key)
{
	int index = hashCode(key); //index�� hashcode�����Լ��� ���� �� ����

	if(ht[index] == key) //ht�� [index]�� key �϶�
		return index; //index ����

	while(ht[++index] != key) //ht�� [++index]�� key�϶� ���� �ݺ�
	{
		index = index % MAX_HASH_TABLE_SIZE;//index�� (index) % MAX_HASH_TABLE_SIZE����
	}
	return index; //index ����
}



