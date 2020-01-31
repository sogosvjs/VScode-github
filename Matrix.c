#include <Turboc.h>



#define MAX 1024

#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80

#define ESC 27



struct Signal		//��ȣ�� ���� ���� Ÿ���� �ٸ� ������� �����ǹǷ� ��ȣ�� �����ϱ� ���� ����ü�� �ʿ��ϸ�, ���ÿ� ���� ���� ��ȣ�� �����̹Ƿ� �̷� ����ü�� �迭�� �����ؾ� �Ѵ�

{

	BOOL exist;                // ��ȣ�� ���� ����

	char ch;                 // ����� ����

	int x, y;                   // ���� ��ǥ

	int distance;           // �̵��� �Ÿ�

	int nFrame;                 // �ӵ�

	int nStay;               // �ӵ��� ���� ī��Ʈ //��Ÿ�� ������

};

struct Signal S[MAX];		//S �迭�� �������� ����Ǿ����Ƿ� ��� ��ȣ�� exist�� FALSE�� �ʱ�ȭ	//�޸𸮸� �����ϰų� �� ���� ��ȣ�� �����ϰ� �ʹٸ� ���� ����Ʈ�� ���� �迭�� �� ���� �ְ�����, ���� ���ؿ����� ���� �迭�ε� ���



void main()

{

	int i;

	int ch;

	int freq = 15;

	int frame = 200;



	clrscr();

	gotoxy(0, 23);

	printf("��Ʈ���� �䳻����. ����:�ӵ� ����, �¿�:�� ����, ESC:����");

	randomize();

	for (;;) {

		gotoxy(60, 23);

		printf("�ӵ�:%d, ��:%d    ", frame, freq);		//����Ǵ°��� �����Ƿ� ���ѷ����� �ӿ� ����



		// Ű �Է� ó��

		if (_kbhit()) {

			ch = _getch();			// getch() �Լ��� Ű�� ������ ��� ������ ���ڸ� �����Ѵ�.

			if (ch == 0xE0) {		// Ȯ��Ű���� Ȯ���Ѵ�(Ȯ��Ű�� �Է¹����� 0xE0�� �����ϱ⶧��)

				ch = _getch();		// �ѹ��� �Լ��� ȣ���ؾ� Ű���� �� �� �ִ�

				switch (ch) {

				case UP:

					frame = min(frame + 10, 1000);

					break;

				case DOWN:

					frame = max(frame - 10, 10);

					break;

				case RIGHT:

					freq = max(freq - 1, 1);

					break;

				case LEFT:

					freq = min(freq + 1, 30);

					break;

				}

			}
			else {

				if (ch == ESC) {

					return;

				}

			}

		}



		// ���ο� ��ȣ ����

		if (random(freq) == 0) {		//0~14���� ������ ���� ����� 0�� ���� �ǹ��ϹǷ� 1/15�� Ȯ���� �ǹ�

			for (i = 0; i < MAX; i++) {		// �˻� ����߿� ���� ������ ���� �˻�

				if (S[i].exist == FALSE) {

					S[i].exist = TRUE;

					S[i].ch = random('Z' - 'A' + 1) + 'A';

					S[i].x = random(80);

					S[i].y = 0;

					S[i].distance = random(14) + 9;

					S[i].nFrame = S[i].nStay = random(15) + 5;		//Frame ī��Ʈ ���ؼ� Stay�� �ʱⰪ ���� ����

					break;

				}

			}

		}



		// �ֱⰡ �� �� ��ȣ �̵� �� ���� ó��
		for (i = 0; i < MAX; i++) {

			if (S[i].exist == FALSE)

				continue;

			if (--S[i].nStay == 0) {

				S[i].nStay = S[i].nFrame;

				gotoxy(S[i].x, S[i].y); _putch(' ');		//���� ��� ���� ���� ��� �����

				if (++S[i].y < S[i].distance) {		//���ǽĿ� ++�� ���� +�� �� ä�� ���, ���ǽĿ����� +�Ǵ� ������ �����ؼ� �Ǽ�

					gotoxy(S[i].x, S[i].y); _putch(S[i].ch);

				}
				else {

					S[i].exist = FALSE;

				}

			}

		}



		delay(1000 / frame);
/*�ӵ� ���� ���
		for (i = 0; i < MAX; i++) {

			if (S[i].exist == FALSE)

				continue;		//�ݺ��� �� continue�� ����ϸ� ���� ���� ��ġ�� �ݺ����� ��� ��

			gotoxy(S[i].x, S[i].y); puts("       ");		//���� ��� ���� ���� ��� �����

			if (--S[i].nStay == 0) {

				S[i].nStay = S[i].nFrame;

				if (++S[i].y >= S[i].distance) {

					S[i].exist = FALSE;

				}

			}

			if (S[i].exist) {

				gotoxy(S[i].x, S[i].y);		//198�� ���ο��� y��ǥ�� ++�����Ƿ� +�� ����, ���ǽ��� �������� �ʾ� ++���� �ʾҴٰ� �߸� ���� => ���ǽĿ��� ++�Ǹ� ������ ������ +�ȴ�

				printf("%c-%d:%d ", S[i].ch, S[i].nFrame, S[i].nStay);

			}

		}



		delay(100);

//		delay(1000 / frame);	// �Ϲ������� �ʴ� n�������� ��� ������ for(;;) {delay(1000/n)} �������� ����ϸ� �ȴ�.
*/
	}
	
}