#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <mmsystem.h>

#define A 260  //�� 
#define B 290  //��
#define C 330
#define D 380
#define E 380
#define F 430
#define G 490
#define H 510 
#pragma comment(lib,"winmm.lib")

void erase(void);  // �߰� 
void gotoxy(int x, int y);
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest);
void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest);
void display_rule(void);
void display_flag(char key); // �߰� 

int main(void)
{	
	system("title û���� ���� ");
	int i, user_number, quest_number, rnd, temp;
	int order[4] = { 0, 1, 2, 3 };
	char solution[4][10] = { 0 };
	double time_check[4][10] = { 0 };
	char user_name[4][7];
	srand(time(NULL));
	

	printf("û��/��� ����\n\n");
	printf("���ӿ� ������ �ο����� �Է��ϰ� Enter>");
	scanf("%d", &user_number);
	printf("\n������ ������ �Է��ϰ� Enter>");
	scanf("%d", &quest_number);

	for (i = 0;i < user_number;i++)
	{
		printf("�������� �̸��� �Է��ϰ� Enter(������ �����Դϴ�!)>", i+1);
		scanf("%s", &user_name[i]);
	}
	printf("���� �ѱ��� ����Ͽ��ٸ� ����Ű�� �ٲٽʽÿ�.\n");
	printf("�ƹ�Ű�� �����ÿ�.\n");
	getch();
	printf("\n������ ������ ������ �����ϴ�. \n");
	for (i = 0;i < user_number;i++)
	{
		rnd = rand() % user_number;
		temp = order[i];
		order[i] = order[rnd];
		order[rnd] = temp;
	}
	for (i = 0;i < user_number;i++)
	{
		printf("%d�� : %s\n", i + 1, user_name[order[i]]);
	}
	printf("�ƹ�Ű�� �����ÿ�.\n");
	getch();
	PlaySound(TEXT("C:\\wave_file.wav"), NULL, SND_ASYNC || SND_LOOP);
	
	for (i = 0;i < user_number;i++)
		game_control(order[i], user_name[order[i]], solution,
			time_check, quest_number);
	PlaySound(NULL, 0, 0);
	printf("\n\n");
	printf("��� ������ �������ϴ�. \n");
	printf("�ƹ�Ű�� ������ ����� ǥ���մϴ�. \n");
	getch();
	display_result(user_number, order, time_check, user_name,
		solution, quest_number);
	getch();
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest)
{
	const char* flag[] = { "û��", "���" }; // ���� 
	const char* question[] = { "����!", "�÷�!", "����������", "�ø�������" };
	clock_t start, end;
	int i, rnd[4];
	char key;
	system("cls");
	gotoxy(1, 3);
	printf("%s�� �����Դϴ�. Ű ������ ������ �����ϴ�.", name);
	display_flag(0); // ���� 
	display_rule();
	for (i = 0;i < quest;i++)
	{
		system("cls");
		display_flag(0);
		rnd[0] = rand() % 2;
		rnd[1] = rand() % 4;
		start = clock();
		gotoxy(5, 10);
		if (rnd[1] > 1)
		{
			rnd[2] = rand() % 2;
			rnd[3] = rand() % 2;
			printf("%d: %s %s %s %s", i + 1, flag[rnd[0]], question[rnd[1]], flag[rnd[2]], question[rnd[3]]);
		}
		else
			printf("%d: %s %s", i + 1, flag[rnd[0]], question[rnd[1]]);
		while (!kbhit());  // �߰� 
		key = getch();
		switch (key) {
		case 'a':
			display_flag(key);
			Beep(A, 200);  // �Ҹ� �߰� 
			Beep(C, 200);
			Beep(E, 200);
			Sleep(1300);
			break;
		case 'z':
			display_flag(key);
			Beep(F, 200);
			Beep(D, 200);
			Beep(B, 200);
			Sleep(1300);
			break;
		case 'k':
			display_flag(key);
			Beep(C, 200);
			Beep(E, 200);
			Beep(G, 200);
			Sleep(1000);
			break;
		case 'm':
			display_flag(key);
			Beep(H, 200);
			Beep(F, 200);
			Beep(D, 200);
			Sleep(1000);
			break;
		}
		end = clock();
		check[order][i] = (double)(end - start) / CLK_TCK;
		if (rnd[1] > 1)
		{
			if ((rnd[2] == 0) && (rnd[3] == 0) && (key == 'z'))
				sol[order][i] = 1;
			else if ((rnd[2] == 0) && (rnd[3] == 1) && (key == 'a'))
				sol[order][i] = 1;
			else if ((rnd[2] == 1) && (rnd[3] == 0) && (key == 'm'))
				sol[order][i] = 1;
			else if ((rnd[2] == 1) && (rnd[3] == 1) && (key == 'k'))
				sol[order][i] = 1;
			else
				sol[order][i] = 0;
		}
		else
		{
			if ((rnd[0] == 0) && (rnd[1] == 0) && (key == 'z'))
				sol[order][i] = 1;
			else if ((rnd[0] == 0) && (rnd[1] == 1) && (key == 'a'))
				sol[order][i] = 1;
			else if ((rnd[0] == 1) && (rnd[1] == 0) && (key == 'm'))
				sol[order][i] = 1;
			else if ((rnd[0] == 1) && (rnd[1] == 1) && (key == 'k'))
				sol[order][i] = 1;
			else
				sol[order][i] = 0;
		}
	}
}

/* ���� ��� ����ϴ� �Լ� */
void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest)
{
	int i, j, result[4] = { 0 };
	double min_time[4] = { 0 };
	system("cls");
	printf("       ");
	for (i = 0;i < user;i++)
		printf("%8s  ", name[order[i]]);
	printf("\n");
	for (j = 0;j < quest;j++)
	{
		printf("    %d�� : ", j + 1);
		for (i = 0;i < user;i++)
		{
			if (sol[order[i]][j] && check[order[i]][j] < 4) // animation delay �ð� 500���� 
			{
				printf("O");
				result[order[i]] += 1;
			}
			else
				printf("X");
			printf("%5.2f\t", check[order[i]][j]) - 0.5;
			min_time[order[i]] += check[order[i]][j] - 0.5;
		}
		printf("\n");
	}
	printf("\n");
	Beep(A, 200);  // �Ҹ� �߰� 
	Beep(B, 200);
	Beep(C, 200);
	Beep(D, 200);
	Beep(E, 200);
	Beep(F, 200);
	Beep(G, 200);
	Beep(H, 500);
	Sleep(1200);
	printf("��������:");
	for (i = 0;i < user;i++) {
		printf("%7d    ", result[order[i]]);
	}
	printf("\n");
	printf("�ҿ�ð�:");
	for (i = 0;i < user;i++)
		printf("%7.2f\t", min_time[order[i]]);
	printf("\n");
	for (i = 0;i < user;i++) {
		if (result[order[i]] >= (quest / 2)) printf(" ����Դϴ�!!!");
		else printf(" ���հ��Դϴ�....");
	}
}

// ���� ��Ģ ��� �Լ� 
void display_rule(void)
{
	gotoxy(1, 4);
	printf("���ӽ��������� Ű�� ������ ������!");
	gotoxy(1, 6);
	printf("û�� �÷� : a    ��� �÷� : k");
	gotoxy(1, 7);
	printf("û�� ���� : z    ��� ���� : m");
	Sleep(1500);
	gotoxy(1, 8);
	printf("3�� �Ŀ� ������ �����մϴ�. �غ��ϼ���.");
	Sleep(3000);
}

// �ִϸ��̼�
void display_flag(char key)
{
	erase();
	switch (key)
	{
	case 'a':
		gotoxy(58, 5);
		printf("��");
		gotoxy(54, 6);
		printf("����");
		gotoxy(54, 5);
		printf("��");
		gotoxy(60, 6);
		printf("��");
		gotoxy(62, 6);
		printf("��");
		gotoxy(58, 6);
		printf("��");
		gotoxy(58, 7);
		printf("��");
		gotoxy(58, 8);
		printf("��");
		gotoxy(57, 9);
		printf("��");
		gotoxy(59, 9);
		printf("��");
		gotoxy(1, 24);
		break;
	case 'z':
		gotoxy(58, 5);
		printf("��");
		gotoxy(54, 6);
		printf("����");
		gotoxy(54, 7);
		printf("��");
		gotoxy(60, 6);
		printf("��");
		gotoxy(62, 6);
		printf("��");
		gotoxy(58, 6);
		printf("��");
		gotoxy(58, 7);
		printf("��");
		gotoxy(58, 8);
		printf("��");
		gotoxy(57, 9);
		printf("��");
		gotoxy(59, 9);
		printf("��");
		gotoxy(1, 24);
		break;
	case 'k':
		gotoxy(58, 5);
		printf("��");
		gotoxy(56, 6);
		printf("��");
		gotoxy(54, 6);
		printf("��");
		gotoxy(60, 6);
		printf("����");
		gotoxy(62, 5);
		printf("��");
		gotoxy(58, 6);
		printf("��");
		gotoxy(58, 7);
		printf("��");
		gotoxy(58, 8);
		printf("��");
		gotoxy(57, 9);
		printf("��");
		gotoxy(59, 9);
		printf("��");
		gotoxy(1, 24);
		break;
	case 'm':
		gotoxy(58, 5);
		printf("��");
		gotoxy(56, 6);
		printf("��");
		gotoxy(54, 6);
		printf("��");
		gotoxy(60, 6);
		printf("����");
		gotoxy(62, 7);
		printf("��");
		gotoxy(58, 6);
		printf("��");
		gotoxy(58, 7);
		printf("��");
		gotoxy(58, 8);
		printf("��");
		gotoxy(57, 9);
		printf("��");
		gotoxy(59, 9);
		printf("��");
		gotoxy(1, 24);
		break;
	default:
		gotoxy(58, 5);
		printf("��");
		gotoxy(56, 6);
		printf("��");
		gotoxy(54, 6);
		printf("��");
		gotoxy(60, 6);
		printf("��");
		gotoxy(62, 6);
		printf("��");
		gotoxy(58, 6);
		printf("��");
		gotoxy(58, 7);
		printf("��");
		gotoxy(58, 8);
		printf("��");
		gotoxy(57, 9);
		printf("��");
		gotoxy(59, 9);
		printf("��");
		gotoxy(1, 24);
	}
}

// �ִϸ��̼� ����� 
void erase(void)
{
	gotoxy(58, 5);
	printf("  ");
	gotoxy(56, 6);
	printf("  ");
	gotoxy(54, 6);
	printf("  ");
	gotoxy(60, 6);
	printf("  ");
	gotoxy(62, 6);
	printf("  ");
	gotoxy(58, 6);
	printf("  ");
	gotoxy(58, 7);
	printf("  ");
	gotoxy(58, 8);
	printf("  ");
	gotoxy(57, 9);
	printf("  ");
	gotoxy(59, 9);
	printf("  ");
}
