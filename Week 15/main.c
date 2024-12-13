//20201807 박승훈
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct People {
	char name[12];
	int scores[3];
	float avg;
	int rank;
	struct Node* p_next; 
} Student;

void AddData(Student** pp_head, Student** pp_tail, char* name, int data[3]) {
	float sum = 0;
	if (*pp_head != NULL) {
		(*pp_tail)->p_next = (Student*)malloc(sizeof(Student));
		*pp_tail = (*pp_tail)->p_next;
	}
	else {
		*pp_head = (Student*)malloc(sizeof(Student));
		*pp_tail = *pp_head;
	}

	strcpy_s((*pp_tail)->name, sizeof((*pp_tail)->name), name);
	for (int i = 0; i < 3; i++) {
		(*pp_tail)->scores[i] = data[i];
		sum += data[i];
	}
	(*pp_tail)->avg = (sum / 3);
	(*pp_tail)->p_next = NULL;
}

void ReadDataFromFile(Student** pp_head, Student** pp_tail) {
	FILE* fp = fopen("students.dat", "r+");
	if (fp == NULL) {
		printf("File does not exist\n");
		return;
	}
	char name[12];
	int scores[3];
	while (fscanf_s(fp, "%s %d %d %d", name, sizeof(name), &scores[0], &scores[1], &scores[2]) != EOF) {
		AddData(pp_head, pp_tail, name, scores);
	}

	fclose(fp);
}

/*void rank(Student** pp_head, Student** pp_tail) {
	Student* p1, p2;
	p1 = p_head;
	int max = 0, rank = 1;
	while (p != NULL) {
		p2 = p_head;
		if (p1.avg > max) {
			max = p1.avg
		}
		p1 = p1->next;
	}
}*/

int main(void) {
	Student* p_head = NULL, * p_tail = NULL, * p;
	int sum = 0, temp;
	char name[12], buf[512];
	int score[3];
	while (1) {
		printf("[Menu]\n");

		puts("1..dat 파일에서 데이터 읽기");
		puts("2. 추가 학생 정보 입력");
		puts("3..dat 파일 저장");
		puts("4. 성적 확인(평균 계산 등)");
		puts("5. 종료");
		puts("-------------------");
		printf("선택(1~5) : ");
		scanf_s("%d", &temp);

		if (temp == 1) {
			ReadDataFromFile(&p_head, &p_tail);
		}
		else if (temp == 2) {
			getchar();
			printf("학생의 이름 : ");
			scanf_s("%s", name, sizeof(name));
			printf("국어 점수 : ");
			scanf_s("%d", &score[0]);
			printf("영어 점수 : ");
			scanf_s("%d", &score[1]);
			printf("수학 점수 : ");
			scanf_s("%d", &score[2]);
			AddData(&p_head, &p_tail, name, score);
			printf("학생이 성공적으로 추가되었습니다.\n");
		}
		else if (temp == 3) {
		}
		else if (temp == 4) {
			printf("------------------------------\n");
			printf("이름\t국어 영어 수학 총점 평균 등수\n");
			printf("------------------------------\n");
			p = p_head;
			while (p != NULL) {
				printf("%s\t", p->name);
				for (int i = 0; i < 3; i++)
					printf("%d ", p->scores[i]);
				printf("%.2f\n", p->avg);
				p = p->p_next;
			}
		}
		else if (temp == 5)
			break;
		else
			printf("unknown input\n");

	}
	return 0;
}