#include <Turboc.h>



#define MAX 1024

#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80

#define ESC 27



struct Signal		//신호는 여러 가지 타입이 다른 정보들로 구성되므로 신호를 정의하기 위해 구조체가 필요하며, 동시에 여러 개의 신호가 움직이므로 이런 구조체가 배열을 구성해야 한다

{

	BOOL exist;                // 신호의 존재 여부

	char ch;                 // 출력할 문자

	int x, y;                   // 현재 좌표

	int distance;           // 이동할 거리

	int nFrame;                 // 속도

	int nStay;               // 속도에 대한 카운트 //런타임 데이터

};

struct Signal S[MAX];		//S 배열이 전역으로 선언되었으므로 모든 신호의 exist는 FALSE로 초기화	//메모리를 절약하거나 더 많은 신호를 생성하고 싶다면 연결 리스트나 동적 배열을 쓸 수도 있겠으나, 예제 수준에서는 정적 배열로도 충분



void main()

{

	int i;

	int ch;

	int freq = 15;

	int frame = 200;



	clrscr();

	gotoxy(0, 23);

	printf("매트릭스 흉내내기. 상하:속도 증감, 좌우:빈도 증감, ESC:종료");

	randomize();

	for (;;) {

		gotoxy(60, 23);

		printf("속도:%d, 빈도:%d    ", frame, freq);		//변경되는값이 있으므로 무한루프문 속에 포함



		// 키 입력 처리

		if (_kbhit()) {

			ch = _getch();			// getch() 함수는 키를 누르는 즉시 눌러진 문자를 조사한다.

			if (ch == 0xE0) {		// 확장키인지 확인한다(확장키를 입력받으면 0xE0를 리턴하기때문)

				ch = _getch();		// 한번더 함수를 호출해야 키값을 알 수 있다

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



		// 새로운 신호 생성

		if (random(freq) == 0) {		//0~14까지 난수를 만든 결과가 0일 때를 의미하므로 1/15의 확률을 의미

			for (i = 0; i < MAX; i++) {		// 검색 방법중에 가장 간단한 순차 검색

				if (S[i].exist == FALSE) {

					S[i].exist = TRUE;

					S[i].ch = random('Z' - 'A' + 1) + 'A';

					S[i].x = random(80);

					S[i].y = 0;

					S[i].distance = random(14) + 9;

					S[i].nFrame = S[i].nStay = random(15) + 5;		//Frame 카운트 위해서 Stay도 초기값 같게 설정

					break;

				}

			}

		}



		// 주기가 다 된 신호 이동 및 제거 처리
		for (i = 0; i < MAX; i++) {

			if (S[i].exist == FALSE)

				continue;

			if (--S[i].nStay == 0) {

				S[i].nStay = S[i].nFrame;

				gotoxy(S[i].x, S[i].y); _putch(' ');		//다음 출력 위해 이전 출력 지우기

				if (++S[i].y < S[i].distance) {		//조건식에 ++가 들어가도 +가 된 채로 계산, 조건식에서만 +되는 것으로 이해해서 실수

					gotoxy(S[i].x, S[i].y); _putch(S[i].ch);

				}
				else {

					S[i].exist = FALSE;

				}

			}

		}



		delay(1000 / frame);
/*속도 줄인 경우
		for (i = 0; i < MAX; i++) {

			if (S[i].exist == FALSE)

				continue;		//반복문 안 continue를 사용하면 다음 실행 위치가 반복문의 블록 끝

			gotoxy(S[i].x, S[i].y); puts("       ");		//다음 출력 위해 이전 출력 지우기

			if (--S[i].nStay == 0) {

				S[i].nStay = S[i].nFrame;

				if (++S[i].y >= S[i].distance) {

					S[i].exist = FALSE;

				}

			}

			if (S[i].exist) {

				gotoxy(S[i].x, S[i].y);		//198번 라인에서 y좌표가 ++됬으므로 +된 상태, 조건식이 성립하지 않아 ++되지 않았다고 잘못 이해 => 조건식에서 ++되면 무조건 변수는 +된다

				printf("%c-%d:%d ", S[i].ch, S[i].nFrame, S[i].nStay);

			}

		}



		delay(100);

//		delay(1000 / frame);	// 일반적으로 초당 n프레임을 얻고 싶으면 for(;;) {delay(1000/n)} 지연문을 사용하면 된다.
*/
	}
	
}