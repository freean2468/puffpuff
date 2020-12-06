/*
===============================================================
프로그램명 : 뻐끔맨
목적 : 2008 보늬축제 게임제출용
개발 : 송훈일
제작기간 : 2008/11/25 ~ 2008/12/9
업데이트 : 2008/12/10 - 연결통로 구현
		   2008/12/10 - 슈퍼모드, 타임 아이템 구현
		   2008/12/13 - 타임 아이템 사용 방법 변경
===============================================================
*/

// puckkmman.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#pragma once

#include "stdafx.h"
#include "puffpuff.h"
#include "Resource.h"

#define MAXSTAGE 3 // 최대 스테이지 수
#define BW 32 // 비트맵 가로 픽셀 수
#define BH 32 // 비트맵 세로 픽셀 수
#define TRUE 1 
#define FALSE 0

#define LEFT		1000
#define RIGHT		1001
#define UP			1002
#define DOWN		1003
#define STOP		999
#define MAN			3
#define SUPERMAN	0

#define Stage_enemy 3
#define MAX_BIT 17 // 게임 비트맵 출력 수

BOOL START=FALSE; // 시작점 변수
BOOL MOUSE=TRUE; // 뻐끔
BOOL CLEAR = FALSE; // 클리어 여부
BOOL END = FALSE; // 게임 클리어 조건 체크
BOOL GAMEOVER = FALSE; // 게임오버 여부
BOOL SUPER = FALSE; // 슈퍼고기 먹었는지 여부
BOOL TIME = FALSE; // 타이머 아이템 먹었는지 여부
BOOL TIME_USE = FALSE; // 타임 아이템 사용 여부

void DrawScreen(HDC hdc); // 전달된 값을 실제로 그리는 함수
void Clear(); // 게임 엔딩 체크
int End(); // 게임 스테이지 클리어 체크
void Move(int); // 움직임 계산
void InitStage(); // 초기화
void DrawBitmap(int x, int y, HBITMAP hBit); // 실제로 화면 출력
void UpdateFrame(); // 게임 루프 도중 추가되는 요소들을 업데이트하는 함수
void M_state(); // 입의 상태
void Enemy_zone(); // AI enemy 출현
void Enemy_Move(); // AI enemy 움직임
void Enemy_advent(int); // AI enemy 출현 중복 부분
void Enemy_put(int); // AI enemy 출력
void dir_check(int); // 적의 방향 체크
void Enemy_abil(int); // Ai enemy 중복 부분
void crash(int); // 충돌체크 함수
void Enemy_Dir(int); // 적 방향에 따른 출력 함수
void Teleport(int *, int *, int, int); // 연결통로 체크
void Time(); // 타임 아이템 출현 함수

char ns[18][21];
int nStage; // 현재 진행중인 스테이지
int nx, ny; // 주인공의 좌표
int nScore; // 점수
int sx, sy; // 시작점의 좌표
HBITMAP hBit[MAX_BIT]; // 리소스 비트맵 수
HBITMAP hsBit[8]; // 슈퍼모드 리소스
HBITMAP hTime;
int Mankind=3; // 방향에 따른 주인공 출력
int State; // 주인공 방향 상태
int tx_1, ty_1; // 연결통로 좌표
int tx_2, ty_2;

BOOL C_DOWN=FALSE; 
BOOL C_LEFT=FALSE;
BOOL C_RIGHT=FALSE;
BOOL C_UP=FALSE;

typedef struct tagsiENEMY{ // 인공지능 구조체
	int x; // 등장위치 (랜덤) & 이동 좌표
	int y; // 등장위치 (랜덤)
	int dir; // 방향
}Enemy;

typedef struct tagsiTime{ // 타임 아이템 구조체
	int x; // 등장위치(랜덤)
	int y; // 등장위치(랜덤)
}Timer;

Timer timer;
Enemy enemy[16];

char arStage[MAXSTAGE][18][21]={
		{	// # = 벽, & = 주인공, o = 고기, ' ' = 빈칸, $ = 적, @ = 시작점, 번호들 : 연결지점, ! = 슈퍼고기
		"##################2#",
		"#*ooooooooooooooooo#",
		"#o#o#oo#########o#o#",
		"#o#o#oooooooooooo#o#",
		"#o#o#oo#o#o#o#o#o#o#",
		"#ooo#oo###o#o#o#ooo#",
		"#o#o#oo#*#o#o#o#o#o#",
		"#o#o#oooooooooooo#o#",
		"#&#o#oo#o#o#o#o#o#o#",				// 첫번째 맵
		"#o#o#oo#o#o#ooooooo#",
		"#oooooo#o#o#o#o#o#o#",
		"#o####o#o#o#o#o#o#o#",
		"#oooooo#o#o#o#o#o#o#",
		"#o#oo#o#o#o#o#o#o#o#",
		"#o#oo#o#o#o#o#o#o#o#",
		"#o#oo#o#o#o#o#o#o#o#",                                   
		"#ooooooooooooooooo*#",
		"#1##################"
		},
		{
		"#1##################",
		"#ooo#oo#o#ooooooooo#",
		"#o#oooooooo#o#####o#",
		"#o#o######oooooo*#o#",
		"#o#o#*ooo#o#o#o#o#o#",
		"#ooo#o##o#ooo#o#ooo#", 
		"#o###o##o#o#o#o#####",
		"#o#oooooo#o#o#ooooo#",
		"#o#o##o#ooooo#####o#",               // 두번째 맵
		"#o#oooo#o#ooo#o#o#o#",
		"#o##o#o#o#ooooooooo#",
		"#oooo#o#o#oo#o####o#",
		"#oooooooo#oo#o##ooo#",
		"#o####o###oo#oooo#o#",
		"#o#oo#ooo#oo#o#*##o#",
		"#o#o&#o#oooooo####o#",
		"#oooooooooooooooooo#",
		"##################2#"
		},
		{
		"##################2#",
		"#&oo#oo#*#ooooooooo#",
		"#o#oooooooo#####o#o#",
		"#o#o##o#o#ooooooo#o#",
		"#o#ooooooooooooo##o#",
		"#oooo#o###o###ooooo#", 
		"#o##o#o#ooooo#oo####",
		"#oooooo#oo#oo#ooooo#",
		"#o#o##o#oo*oo#oo##o#",               // 세번째 맵
		"#oooooo#o###o#ooooo#",
		"#o##o#ooooooooo###o#",
		"#oooo#o#o#oo#oooo#o#",
		"#oooooooo#oo#o##ooo#",
		"#o#o#o####oo#o##o#o#",
		"#o#*ooooooooooooo#o#",
		"#o#####oo###oo####o#",
		"#oooooooooooooooooo#",
		"#1##################"
		}
	};

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("뻐끔맨");
/////////////////////////////
HWND hWnd;
PAINTSTRUCT ps;
HDC hdc, MemDC;
RECT crt;
TCHAR Message[256];
HBITMAP MyBitmap, OldBitmap;
SYSTEMTIME st;
static TCHAR sTime[128];
bool bIsActive = false;
/////////////////////////////

// 윈도우 등록
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc	= WndProc;
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;
	WndClass.hInstance		= hInstance;
	WndClass.hIcon			= LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ch));
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	WndClass.lpszMenuName	= NULL;
	WndClass.lpszClassName	= lpszClass;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,CW_USEDEFAULT,0,0,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	//while (GetMessage(&Message, NULL, 0, 0)) 
	//{
	//	TranslateMessage(&Message);
	//	DispatchMessage(&Message);
	//}
	while(1) // 게임루프
	{
		if(PeekMessage(&Message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&Message, 0, 0, 0))
			{
				return (int) Message.wParam;
			}
			else
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else if(bIsActive)
		{
			if(!GAMEOVER){ // 게임 오버가 아니고
				if(!CLEAR){ // 게임 크릴어가 아니라면
					UpdateFrame();
					Sleep(1000/7); // 프레임을 적게 출력
				}
			}			
		}
		else
		{
			WaitMessage();
		}
	}

	return (int) Message.wParam;
}

//
// 함수: WndProc(HWND, unsigned, WORD, LONG)
//
// 목적: 주 창의 메시지를 처리합니다.
//
// WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
// WM_PAINT	- 주 창을 그립니다.
// WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//

// 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch (iMessage) 
	{
	case WM_CREATE: // 각종 생성 & 초기화
		hdc = GetDC(hWnd);
		MemDC = CreateCompatibleDC(hdc);
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		SetTimer(hWnd,1,1000,NULL); // 타이머 생성
		SendMessage(hWnd,WM_TIMER,1,0);
		SetRect(&crt,0,0,900,BH*18);
		AdjustWindowRect(&crt,WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,FALSE);
		SetWindowPos(hWnd,NULL,0,0,crt.right-crt.left,crt.bottom-crt.top,SWP_NOMOVE | SWP_NOZORDER);
		for(i=0;i<MAX_BIT;i++)
			hBit[i]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_WALL+i)); // 리소스 로드
		
		for(i=0;i<8;i++)
			hsBit[i]=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_SUPER_R+i)); // 슈퍼모드 리소스 로드

		hTime=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_TIME)); // 타임 리소스 로드

		nStage=0;
		InitStage(); // 초기화
		bIsActive = TRUE;
		return 0;
	case WM_TIMER: // 시간을 재는 용도
		wsprintf(sTime,TEXT("플레이 타임 : %.2d:%.2d"),st.wMinute,st.wSecond);
		st.wSecond++;
		if(st.wSecond%60==0){
			st.wSecond = 0;
			st.wMinute++;
		}

		if(SUPER == TRUE){ 
			static int count = 0;
			count++;
			if(count == 5){ // 슈퍼상태 지속시간 5초
				SUPER = FALSE;
				count = 0;
			}			
		}

		if(TIME_USE == TRUE){ // 타임상태 지속시간 5초
			static int cTime = 0;
			cTime++;
			if(cTime == 5){				
				TIME_USE = FALSE;
				timer.x = NULL; // 타임 아이템 좌표 지워버림
				timer.y = NULL;
				cTime = 0;
			}
		}

		return 0;
	case WM_KEYDOWN:
		if(!CLEAR){ // 클리어하지 못했다면
			switch(wParam){		
				case VK_LEFT:
					State = LEFT;
					break;
				case VK_RIGHT:
					State = RIGHT;
					break;
				case VK_UP:
					State = UP;
					break;
				case VK_DOWN:
					State = DOWN;
					break;
				case 'R':
					InitStage(); // 다시 시작 == 초기화
					break;
				case 'N':
					if(nStage < MAXSTAGE-1){ // 다음 스테이지로 넘어감
						nStage++;
						InitStage();
					}
					break;
				case 'P': // 전의 스테이지로 넘어감
					if(nStage > 0){
						nStage--;
						InitStage();
					}
					break;
				case 'Q': // 끝냄
					PostQuitMessage(0);
					DestroyWindow(hWnd);
					break;
				case 'C':
					CLEAR = TRUE;
					Clear();
					break;
				case 'S':
					if(TIME == TRUE){
						TIME = !TIME;
						TIME_USE = !TIME_USE;
					}
					break;

			}
		}
		else if(CLEAR){ // 클리어했다면
			for(i=0;i<MAX_BIT;i++){
				DeleteObject(hBit[i]); // 해제
			}
			PostQuitMessage(0);
			DestroyWindow(hWnd); // 끝냄
			break;
		}
		if(GAMEOVER){ // 게임오버라면
			for(i=0;i<MAX_BIT;i++){
				DeleteObject(hBit[i]); // 해제
			}
			PostQuitMessage(0);
			DestroyWindow(hWnd); // 끝냄
			break;
		}
		return 0;
	case WM_DESTROY: // 종료
		for(i=0;i<MAX_BIT;i++){
			DeleteObject(hBit[i]); // 해제
		}
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// 출력 함수
void DrawScreen(HDC hdc)
{
	int x, y;
	int iBit;
	TCHAR Message[256];

	for(y = 0; y < 18; y++){
		for(x = 0;x < 20; x++){
			switch (ns[y][x]){
				case '#': // 벽
					iBit = 0;
					break;
				case 'o': // 보너스 점수
					iBit = 1;
					break;
				case ' ': // 빈공간
				case '1':
				case '2':
					iBit = 2;
					break;
				case '@': // 시작점
					iBit = 11;
					break;
				case '*': // 슈퍼고기
					iBit = 16;
					break;
				case '~': // 타임 아이템
					DrawBitmap(x*BW,y*BH,hTime);
					continue;
			}
			DrawBitmap(x*BW,y*BH,hBit[iBit]);
		}
	}
	if(SUPER==FALSE)
		DrawBitmap(nx*BW,ny*BH,hBit[Mankind]); // 뻐끔맨(주인공)
	else if(SUPER==TRUE)
		DrawBitmap(nx*BW,ny*BH,hsBit[Mankind]);

	Enemy_put(nStage); // AI enemy 들은 이 함수를 사용하여 따로 출력

	if(nStage == 0)				// 스테이지별 enemy 숫자에 따른 충돌 체크
		crash(Stage_enemy);
	else if(nStage == 1)
		crash(Stage_enemy+1);
	else if(nStage == 2)
		crash(Stage_enemy+2);

	wsprintf(Message,TEXT("게임 설명"));
	TextOut(hdc,680,10,Message,lstrlen(Message)); // 각종 도움말들, 단축키들 설명, 현재 플레이 상황 표시
	wsprintf(Message,TEXT("Q : 종료, R : 다시 시작"));
	TextOut(hdc,700,30,Message,lstrlen(Message));
	wsprintf(Message,TEXT("N : 다음, P : 이전"));
	TextOut(hdc,700,50,Message,lstrlen(Message));
	wsprintf(Message,TEXT("스테이지 : %d"),nStage+1);
	TextOut(hdc,700,70,Message,lstrlen(Message));
	wsprintf(Message,TEXT("점수 : %d"),nScore);
	TextOut(hdc,700,90,Message,lstrlen(Message));
	
	if(TIME == TRUE)
		wsprintf(Message,TEXT("타임 아이템 : On"));
	else
		wsprintf(Message,TEXT("타임 아이템 : Off"));
	TextOut(hdc,700,110,Message,lstrlen(Message));

	wsprintf(Message,TEXT("S : 타임 아이템 사용"));
	TextOut(hdc,700,130,Message,lstrlen(Message));

	wsprintf(Message,TEXT("클리어 조건 : 고기를 모두 먹고"));
	TextOut(hdc,650,200,Message,lstrlen(Message));	
	wsprintf(Message,TEXT("             시작지점으로 되돌아간다"));
	TextOut(hdc,650,220,Message,lstrlen(Message));	
	wsprintf(Message,TEXT("패배 조건 : 적과의 조우"));
	TextOut(hdc,650,240,Message,lstrlen(Message));
	
	TextOut(hdc,700,550,sTime,lstrlen(sTime));
}

// 스테이지 끝남, 게임 클리어 여부 따짐
void Clear()
{		
	if(nStage == MAXSTAGE-1){
		wsprintf(Message,TEXT("마지막 스테이지를 풀었습니다.") TEXT("Clear~!!"));
		CLEAR = TRUE;
		PlaySound("./Sound/Ending.wav",0,SND_ASYNC|SND_LOOP);
		KillTimer(hWnd,1);
		MemDC=CreateCompatibleDC(hdc);
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_CLEAR));
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		BitBlt(hdc, 0, 0, crt.right-crt.left, crt.bottom-crt.top,MemDC,0,0,SRCCOPY);
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);
	}
	if(nStage < MAXSTAGE-1){
		nStage++;
		wsprintf(Message,TEXT("%d 스테이지를 풀었습니다.") TEXT("다음 스테이지로 이동합니다"),nStage);
		MessageBox(hWnd,Message,TEXT("알림"),MB_OK);
	}

	if(!CLEAR) // 엔딩이 아닐 때만
		InitStage();
}

// 입의 상태를 체크하는 함수
void state()
{
	if(MOUSE==TRUE) // 벌리고 있다면
		MOUSE=FALSE; // 닫고
	else // 닫고 있다면
		MOUSE=TRUE; // 연다
}

// 움직임 계산 함수
void Move(int dir)
{
	int dx=0, dy = 0;

	switch(dir){
		case LEFT:
			if(SUPER == FALSE) // 슈퍼모드일 때와 아닐 때 구분하여 출력
				Mankind=MAN+1;
			else if(SUPER == TRUE)
				Mankind=SUPERMAN+1;

			if(MOUSE==FALSE)
				Mankind+=4;			
			dx=-1;
			break;
		case RIGHT:
			if(SUPER == FALSE)
				Mankind=MAN;
			else if(SUPER == TRUE)
				Mankind=SUPERMAN;

			if(MOUSE==FALSE)
				Mankind+=4;
			dx = 1;
			break;
		case UP:
			if(SUPER == FALSE)
				Mankind=MAN+3;
			else if(SUPER == TRUE)
				Mankind = SUPERMAN+3;

			if(MOUSE==FALSE)
				Mankind+=4;
			dy = -1;
			break;
		case DOWN:
			if(SUPER == FALSE)
				Mankind=MAN+2;
			else if(SUPER == TRUE)
				Mankind = SUPERMAN+2;
			
			if(MOUSE==FALSE)
				Mankind+=4;
			dy=1;
			break;
	}	

	if(ns[ny+dy][nx+dx]!='#'){ // 다음 진행할 곳이 벽이 아니고
		if(ns[ny+dy][nx+dx]=='o'){ // 슈퍼라면
			nScore += 10; // 점수가 올라가고
			ns[ny+dy][nx+dx]=' '; // 원래 있었던 곳은 빈 칸으로 한다
		}
		else if(ns[ny+dy][nx+dx]=='*'){ // 슈퍼고기라면
			nScore += 100; // 점수가 더 올라가고
			ns[ny+dy][nx+dx]=' '; // 원래 있었던 곳은 빈 칸으로 한다
			SUPER = TRUE; // 슈퍼상태가 된다.
		}
		else if(ns[ny+dy][nx+dx]=='~') // 타임 아이템이라면
			ns[ny+dy][nx+dx]=' '; // 원래 있었던 곳은 빈 칸으로 한다.

		END = End(); // 스테이지 클리어 체크

		if(ns[ny+dy][nx+dx]=='@' && END == TRUE){ // 시작점에 있고 고기를 모두 먹었다면
			END = END;
		}
		else if(ns[ny+dy][nx+dx]=='@' || END == TRUE){ // 다 먹었지만 시작점에 있지 않다면
			END = FALSE;
		}

		if(END == FALSE){ // 스테이지가 끝나지 않았다면
			nx+=dx;
			ny+=dy;

			if(nStage == 0)				// 스테이지별 enemy 숫자에 따른 충돌 체크
				crash(Stage_enemy);
			else if(nStage == 1)
				crash(Stage_enemy+1);
			else if(nStage == 2)
				crash(Stage_enemy+2);
		}
		else{ // 스테이지가 끝났다면
			nx+=dx;
			ny+=dy;
			DrawScreen(MemDC);

			BitBlt(hdc, 0, 0, 900, 576, MemDC, 0, 0, SRCCOPY);
			Clear();
		}
	}	
}

// 스테이지 클리어 체크 함수
int End()
{
	for(int y=0;y<18;y++){
		for(int x=0;x<21;x++){
			if(ns[y][x]=='o') // 그 좌표에 고기가 있다면
				return FALSE;
		}
	}
	return TRUE;
}

// 초기화 함수
void InitStage()
{
	int x,y;

	MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);

	memcpy(ns,arStage[nStage],sizeof(ns)); // 메모리 카피, 똑같은 배열을 하나 더 만든다
	for(y=0;y<18;y++){
		for(x=0;x<21;x++){
			if(ns[y][x]=='&'){ // 주인공의 위치
				nx=x; // x좌표 저장
				ny=y; // y좌표 저장
				ns[y][x]=' '; // 빈 공간으로 해 둠
				sx = nx; // 시작점 x좌표 저장
				sy = ny; // 시작점 y좌표 저장
			}
			if(ns[y][x]=='1'){ // 연결통로 첫번째의 위치
				tx_1 = x;
				ty_1 = y;
			}
			if(ns[y][x]=='2'){
				tx_2 = x;
				ty_2 = y;
			}
		}
	}
	Enemy_zone(); // AI enemy 필드에 뿌림
	PlaySound("./Sound/FastDance.wav",0,SND_ASYNC|SND_LOOP); // 배경음 출력
	st.wSecond=0; // 플레이 타임 초기화
	st.wMinute=0;
	Mankind=MAN; // 주인공 초기화
	MOUSE=TRUE; // 입은 벌리고 있음
	nScore=0; // 점수는 0
	START=FALSE; // 시작점 아직 없음
	State = STOP; // 주인공은 스톱상태
	TIME = FALSE; // 타이머 아이템 초기화
	SUPER = FALSE; // 슈퍼상태 초기화
	Time(); // 타임 아이템 생성
	TIME_USE = FALSE; // 타임 아이템 사용여부 초기화

	if(START==FALSE){ // 시작점이 생성되지 않았다면
		ns[sy][sx]='@'; // 시작점
		START=TRUE; // 시작점이 생성됨.
	}
}

// 최종 출력 함수
void DrawBitmap(int x, int y, HBITMAP hBit)
{
	HBITMAP Old;
	int bx, by;
	BITMAP bit;

	HDC Back;
	Back = CreateCompatibleDC(hdc);

	Old=(HBITMAP)SelectObject(Back, hBit);

	GetObject(hBit,sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(MemDC,x,y,bx,by,Back,0,0,SRCCOPY);

	SelectObject(Back,Old);
	DeleteDC(Back); // 지워버려야 중복 생성되는 Back hdc 오작동을 방지
}

// 인공지능 적 필드 출현 중복 부분
void Enemy_advent(int i)
{
	enemy[i].x = rand() % 17+2;
	enemy[i].y = rand() % 17+1;
	if(ns[enemy[i].y][enemy[i].x] == '#' || ns[enemy[i].y][enemy[i].x] == '$' || ns[enemy[i].y][enemy[i].x] == '&'){ // 출현 좌표값이 벽이거나 다른 적이라면
		do{
			enemy[i].x = rand() % 17 + 2;
			enemy[i].y = rand() % 17+1;
		}while(ns[enemy[i].y][enemy[i].x] == '#' || ns[enemy[i].y][enemy[i].x] == '$' || ns[enemy[i].y][enemy[i].x] == '&'); // 벽과 적이 아닐 때까지
	}
	enemy[i].dir = rand() % 4 + 1000; // 방향 줌
}

// 인공지능 적 방향에 따른 출력 함수
void Enemy_Dir(int i)
{
	switch(enemy[i].dir)
	{
	case UP:
		DrawBitmap(enemy[i].x*BW,enemy[i].y*BH,hBit[12+1]);
		break;
	case DOWN:
		DrawBitmap(enemy[i].x*BW,enemy[i].y*BH,hBit[12]);
		break;
	case LEFT:
		DrawBitmap(enemy[i].x*BW,enemy[i].y*BH,hBit[12+2]);
		break;
	case RIGHT:
		DrawBitmap(enemy[i].x*BW,enemy[i].y*BH,hBit[12+3]);
		break;
	}	
}

// 인공지능 적 비트맵 출력 부분
void Enemy_put(int n)
{
	if(n == 0)
		for(int i = 0; i < Stage_enemy; i++)
			Enemy_Dir(i);
	else if(n == 1)
		for(int i = 0; i < Stage_enemy+1; i++)	
			Enemy_Dir(i);
	else if(n == 2)
		for(int i = 0; i < Stage_enemy+2; i++)	
			Enemy_Dir(i);
}

// 인공지능 적 필드 출현 함수
void Enemy_zone()
{
	srand(time(NULL));

	if(nStage==0){ // 첫번째 스테이지
		for(int i = 0; i < Stage_enemy; i++){ // 인공지능
			Enemy_advent(i);
		}	
	}
	if(nStage==1){ // 두번째 스테이지
		for(int i = 0; i < Stage_enemy+1; i++){ // 인공지능
			Enemy_advent(i);
		}	
	}
	if(nStage==2){ // 세번째 스테이지
		for(int i = 0; i < Stage_enemy+2; i++){ // 인공지능
			Enemy_advent(i);
		}	
	}
}

// 충돌체크 함수
void crash(int i)
{
	for(int j = 0; j < i; j++){
		if(ny == enemy[j].y && nx == enemy[j].x){ // 인공지능과 충돌 체크
			if(SUPER == FALSE){ // 슈퍼상태가 아니라면 게임 오버
				PlaySound("./Sound/GameOver.wav",0,SND_ASYNC|SND_LOOP);
				KillTimer(hWnd,1);
				MemDC=CreateCompatibleDC(hdc);
				MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_GAMEOVER));
				OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
				BitBlt(hdc, 0, 0, crt.right-crt.left, crt.bottom-crt.top,MemDC,0,0,SRCCOPY);
				SelectObject(MemDC,OldBitmap);
				DeleteObject(MyBitmap);
				DeleteDC(MemDC);
				GAMEOVER = TRUE;
			}
			else if(SUPER == TRUE){ // 슈퍼상태라면 잡아먹는다
				enemy[j].y = sy;
				enemy[j].x = sx;
				nScore += 50;
			}
		}
		if(ny == timer.y && nx == timer.x) // 타임 아이템과 충돌 체크
			TIME = TRUE;
	}
}

//enemy 방향체크
void direction(int *temp)
{
	switch(*temp)
	{
	case UP: // 방향 : 위
		if(C_UP == TRUE) // 위로 간다
			break;
		else{ // 그럴 수 없다면
			if(C_LEFT == TRUE){ // 왼쪽이나 오른쪽으로 우선 가고 그럴 수 없다면 아래로 되돌아 간다.
				*temp = LEFT;
				break;
			}				
			if(C_RIGHT == TRUE){
				*temp = RIGHT;
				break;
			}
			if(C_DOWN == TRUE){
				*temp = DOWN;
				break;
			}	
		}
	case DOWN:				// 방향 : 아래
		if(C_DOWN == TRUE) // 아래로 간다
			break; 
		else{						
			if(C_RIGHT == TRUE){ // 오른쪽이나 왼쪽으로 우선 가고 그럴 수 없다면 위로 되돌아 간다
				*temp = RIGHT;
				break;
			}			
			if(C_LEFT == TRUE){
				*temp = LEFT;
				break;
			}
			if(C_UP == TRUE){
				*temp = UP;
				break;
			}
		}
	case RIGHT:				// 방향 : 오른쪽
		if(C_RIGHT == TRUE) // 오른쪽으로 간다
			break;
		else{			
			if(C_UP == TRUE){ // 위나 아래로 우선 가고 그럴 수 없다면 왼쪽으로 되돌아 간다
				*temp = UP;
				break;			
			}			
			if(C_DOWN == TRUE){
				*temp = DOWN;
				break;
			}
			if(C_LEFT == TRUE){
				*temp = LEFT;
				break;
			}
		}
	case LEFT:				// 방향 : 왼쪽
		if(C_LEFT == TRUE) // 왼쪽으로 간다
			break;
		else{
			if(C_DOWN == TRUE){ // 아래나 위로 우선 가고 그럴 수 없다면 오른쪽으로 되돌아 간다
				*temp = DOWN;
				break;
			}
			if(C_UP == TRUE){
				*temp = UP;
				break;
			}
			if(C_RIGHT == TRUE){
				*temp = RIGHT;
				break;
			}					
		}
	}
}

// 인공지능 중복
void Enemy_abil(int i)
{
	int dx=0, dy = 0;
	int temp;

	switch(enemy[i].dir)
	{
	case LEFT:
		dx = -1;
		break;
	case RIGHT:
		dx =  1;
		break;
	case UP:
		dy = -1;
		break;
	case DOWN:
		dy = 1;
		break;
	}

	Teleport(&enemy[i].x, &enemy[i].y, dx, dy); // 인공지능 텔레포트 체크

	if(ns[enemy[i].y+dy][enemy[i].x+dx]!='#'){ // 다음 진행할 곳이 벽이 아닐 때
		enemy[i].y += dy;
		enemy[i].x += dx; // 움직였으므로 좌표값을 변경시켜 준다.
		temp = rand() % 4 + 1000; // 랜덤하게 방향 바꿈.

		dir_check(i); // AI enemy가 갈 수 있는 방향 체크
		direction(&temp);

		enemy[i].dir = temp;
	}
	else if(ns[enemy[i].y+dy][enemy[i].x+dx]=='#'){ // 다음 진행할 곳이 벽이라면
		dx = 0;
		dy = 0;			
		
		temp = rand() % 4 + 1000;
		if(enemy[i].dir == temp){											
			temp = rand() % 4 + 1000;

		dir_check(i); // AI enemy가 갈 수 있는 방향 체크
		direction(&temp);

		enemy[i].dir = temp; // 다른 방향으로 바꿔준다.			
		} // 방향만 바꿔준다.
	}
}

// 인공지능 적 움직임 함수
void Enemy_Move()
{	
	srand(time(NULL));

	if(TIME_USE == FALSE){
		if(st.wSecond + st.wMinute >= 1){ // 게임 실행 후 1초 후에
			if(nStage==0){
				for(int i = 0; i < Stage_enemy; i++)
					Enemy_abil(i);
			}
			else if(nStage==1){
				for(int i = 0; i < Stage_enemy+1; i++)
					Enemy_abil(i);
			}
			else if(nStage==2){
				for(int i = 0; i < Stage_enemy+2; i++)
					Enemy_abil(i);
			}
		}
	}
}

// 갈 수 있는 방향 체크
void dir_check(int i)
{
	C_UP = FALSE;
	C_DOWN = FALSE;
	C_RIGHT = FALSE;
	C_LEFT = FALSE;

	if(ns[enemy[i].y-1][enemy[i].x]!='#') // 위에 벽이 없다면
		C_UP = TRUE;
	if(ns[enemy[i].y+1][enemy[i].x]!='#') // 아래에 벽이 없다면
		C_DOWN = TRUE;
	if(ns[enemy[i].y][enemy[i].x+1]!='#') // 오른쪽에 벽이 없다면
		C_RIGHT = TRUE;
	if(ns[enemy[i].y][enemy[i].x-1]!='#') // 왼쪽에 벽이 없다면
		C_LEFT = TRUE;
}

// 주인공과 인공지능 범용 연결통로 함수
void Teleport(int *x, int *y, int dx, int dy) 
{
	if(ns[*y+dy][*x+dx] == '1'){
		*y = ty_2;
		*x = tx_2;
	}
	else if(ns[*y+dy][*x+dx] == '2'){
		*y = ty_1;
		*x = tx_1;
	}
}

// 타임 아이템 출현 함수
void Time()
{
	srand(time(NULL));

	timer.x = rand() % 20;
	timer.y = rand() % 17+1;
	if(ns[timer.y][timer.x] == '#' || ns[timer.y][timer.x] == '$' || ns[timer.y][timer.x] == '&'){ // 출현 좌표값이 벽이나 다른 적이라면
		do{
			timer.x = rand() % 20;
			timer.y = rand() % 17+1;
		}while(ns[timer.y][timer.x] == '#' || ns[timer.y][timer.x] == '$' || ns[timer.y][timer.x] == '&'); // 벽과 적이 아닐 때까지
	}
	ns[timer.y][timer.x] = '~';
}

void UpdateFrame()
{
	state();
	Move(State);
	Enemy_Move();
	Teleport(&nx,&ny,0,0); // 주인공 텔레포트 체크

	DrawScreen(MemDC);

	BitBlt(hdc, 0, 0, 900, 576, MemDC, 0, 0, SRCCOPY);
}