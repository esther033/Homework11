#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a); //배열을 초기화 하는 함수
int freeArray(int *a); //메모리를 해제하는 함수
void printArray(int *a); //배열을 출력하는 함수

int selectionSort(int *a); //선택정렬 함수
int insertionSort(int *a); //삽입정렬 함수
int bubbleSort(int *a); //버블정렬 함수
int shellSort(int *a); //셀정렬 함수

int quickSort(int *a, int n); //퀵정렬 함수

int hashCode(int key); //해쉬 코드를 만드는 함수

int hashing(int *a, int **ht); //배열 a를 해시테이블에 넣는 함수

int search(int *ht, int key); //해시테이블에서 key값을 찾는 함수


int main()
{
    printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //메뉴를 입력받을 변수
	int *array = NULL; //배열을 NULL로 초기화
	int *hashtable = NULL; //해쉬테이블을 NULL로 초기화
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
			initialize(&array); //배열을 초기화 한다
			break;
		case 'q': case 'Q':
			freeArray(array); //메모리를 해제한다
			break;
		case 's': case 'S':
			selectionSort(array); //선택정렬을 한다
			break;
		case 'i': case 'I':
			insertionSort(array); //삽입 정렬을 한다
			break;
		case 'b': case 'B':
			bubbleSort(array); //버블 정렬을 한다
			break;
		case 'l': case 'L':
			shellSort(array); //셀 정렬을 한다
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열을 출력한다
			quickSort(array, MAX_ARRAY_SIZE); //퀵정렬을한다
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열을 출력한다

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열을 출력한다
			hashing(array, &hashtable); //배열을 해쉬테이블에 넣는다
			printArray(hashtable);  //해시테이블을 출력한다
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key갑을 입력받는다 
			printArray(hashtable); //해시테이블을 출력한다
			index = search(hashtable, key); //index에 찾는 key값의 index를 넣는다
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //key갑을 출력한다
			break;

		case 'p': case 'P':
			printArray(array); //배열을 출력한다
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //반복문 종료

	return 1; //함수 종료
}

int initialize(int** a)
{
	int *temp = NULL;
	if(*a == NULL) { //a가 NULL인경우
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //temp를 동적할당한다
		*a = temp;  //*a에 temp를 저장한다
	} else
		temp = *a; //temp에 *a에 저장한다

	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //반복문을 활용하여 temp[i]에 랜덤값을 저장한다
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0; //함수 종료
}

int freeArray(int *a) 
{
	if(a != NULL) //a가 NULL이 아니면
		free(a); //a의 메모리 해제
	return 0; //함수 종료
}

void printArray(int *a) 
{
	if (a == NULL) { //a가 NULL일때 
		printf("nothing to print.\n"); //출력할 것이 없다
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //반복문을 활용하여 배열의 index를 출력한다
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //반복문을 활용하여 a[i]의 값을 출력한다
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

	printArray(a); //배열 a를 출력한다

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //반복문을 활용하여 선택정렬을 한다
	{
		minindex = i; //최소값의 index를 i라고 지정하고
		min = a[i]; //최솟값에 a[i]저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //반복문을 활용하여 minindex와 min값을 최솟값으로 바꾼다
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];  //a의 최소값에 a[i]저장
		a[i] = min; //a[i]에 min저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //배열 출력
	return 0; //함수 종료
}

int insertionSort(int *a) 
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //배열 a를 출력한다

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //반복문을 활용하여 삽입 정렬을 한다
	{
		t = a[i]; //t에 a[i]저장
		j = i; //j에 i 저장
		while (a[j-1] > t && j > 0) //a[j-i]가 t보다 크고 j가 0보다 크면 계속 반복
		{
			a[j] = a[j-1]; //a[j]에 a[j-1]저장
			j--; //j값 감소
		}
		a[j] = t; //a[j]에 t저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //배열 출력

	return 0; //함수 종료
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //반복문을 활용하여 버블정렬을 한다
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]>a[j]이면
			{
				t = a[j-1]; //t에 a[j-1]저장
				a[j-1] = a[j]; //a[j-1]에 a[j]저장
				a[j] = t; //a[j]에 t 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //배열 a 출력

	return 0; //함수 종료
}

int shellSort(int *a) 
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //배열 a 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //반복문을 활용하여 셀정렬을 한다
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v에 a[j] 저장
				k = j; //k에 j 저장
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h]; //a[k]에 a[k-h] 저장
					k -= h; //k에 k-h 저장
				}
				a[k] = v; //a[k]에 v 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //배열 a출력

	return 0;
}

int quickSort(int *a, int n) 
{
	int v, t;
	int i, j;

	if (n > 1) //n이 1보다 클??
	{
		v = a[n-1]; //v에 a[n-1]저장
		i = -1; //i에 -1저장
		j = n - 1; //j에 n-1 저장

		while(1) 
		{
			while(a[++i] < v);//a[i]가<v일때까지 i값 증가
			while(a[--j] > v); //a[j]가 >v일때까지 i값 감서

			if (i >= j) break; //i가 j와 같거나 크면 반복문 종료
			t = a[i]; //t에 a[i]저장
			a[i] = a[j]; //a[i]에 a[j]저장
			a[j] = t; //a[j]에 t저장
		}
		t = a[i]; //t에 a[i] 저장
		a[i] = a[n-1]; //a[i]에 a[n-1]자장
		a[n-1] = t; //a[n-1]에 t 저장

		quickSort(a, i); //(재귀함수) quickSort(a, i) 호출
		quickSort(a+i+1, n-i-1); //(재귀함수) quickSort(a+i+1, n-i-1)호출
	}


	return 0; //함수 종료
}

int hashCode(int key) { 
   return key % MAX_HASH_TABLE_SIZE; //key%MAX_HASH_TABLE_SIZE 값 리턴
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	//hash table이 NULL인 경우 메모리 할당 
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  //할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else {
		hashtable = *ht;	// hash table이 NULL이 아닌경우, table 재활용, reset to -1 
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //반복문을 활용하여 hashtable[i]에 -1 저장

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) 
	{
		key = a[i];
		hashcode = hashCode(key); //hashcode에 hashcode생성함수의 리턴 값 저장

		if (hashtable[hashcode] == -1) //hashtable[hashcode]가 -1일때
		{
			hashtable[hashcode] = key;//hashtable[hashcode]에 key저장
		} else 	{

			index = hashcode; //index에 hashcode 저장

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //index에 (++index) % MAX_HASH_TABLE_SIZE저장
			}
			hashtable[index] = key; //hashtable[index]에 key 저장
		}
	}

	return 0; //함수 종료
}

int search(int *ht, int key)
{
	int index = hashCode(key); //index에 hashcode생성함수의 리턴 값 저장

	if(ht[index] == key) //ht의 [index]에 key 일때
		return index; //index 리턴

	while(ht[++index] != key) //ht의 [++index]가 key일때 까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;//index에 (index) % MAX_HASH_TABLE_SIZE저장
	}
	return index; //index 리턴
}



