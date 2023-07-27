#include <stdio.h> 
#include <windows.h>
#include <conio.h> 
#include<mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "winmm.lib")
#include <time.h>
#include <Windows.h> 
#include <mysql.h>
#pragma comment (lib, "libmysql.lib")
#define PLAYER 20
#define ENEMYX 100
#define BOSS1_DL 2000 //보스 스킬 반응시간
#define BOSS2_DL 1250
#define BOSS2_2_DL 5000
#define BOSS3_DL 8000
#pragma comment (lib, "libmysql.lib")

#define DB_USER "root"			//유저 이름  root
#define DB_PASSWORD ""		//비밀번호	""
#define SEVER_IP "127.0.0.1"		//서버 IP

void connectionMYSQL(MYSQL* conn);

extern void clear();
extern void pclear();
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

//MYSQL 서버 연결 확인
void connectionMYSQL(MYSQL* conn) {

	if (conn == NULL) {
		printf("MySQL 초기화 에러: %s\n", mysql_error(conn));
		exit(1);
	}

	if (mysql_real_connect(conn, SEVER_IP, DB_USER, DB_PASSWORD, "test", 3307, NULL, 0)) {
		//(mysql변수, 서버IP, MySQL 유저 아이디, MySQL 유저 PASSWORD, 데이터베이스 이름, 포트번호, NULL 고정, 0 고정)
		//데이터베이스 이름은 mysql_select_db()나 mysql_query()를 이용해서 지정 가능

		//mysql_set_character_set(conn, "문자");		캐릭터셋
	}
	else {
		printf("MySQL 연결 에러: %s\n", mysql_error(conn));
		getchar();
		exit(1);
	}
}
struct user {  //닉네임 보유골드 스킨 1 2 3 4 승리수 마지막스킨
	char name[20];
	int gold;
	int dskin1;
	int dskin2;
	int dskin3;
	int dskin4;
	int cwin;
	int lskin;
};

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

} void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void ground() {
	for (int i = 0; i < 150; i++) {
		gotoxy(i, 41);
		printf("~");
	}
}
void pstand() {
	gotoxy(PLAYER, 31);
	printf("    &&&&    \n");
	gotoxy(PLAYER, 32);
	printf("    &&&&    $\n");
	gotoxy(PLAYER, 33);
	printf("     ##    $\n");
	gotoxy(PLAYER, 34);
	printf("    @###  $ \n");
	gotoxy(PLAYER, 35);
	printf("    #@## $  \n");
	gotoxy(PLAYER, 36);
	printf("    ##@@$   \n");
	gotoxy(PLAYER, 37);
	printf("    ####    \n");
	gotoxy(PLAYER, 38);
	printf("    @  @    \n");
	gotoxy(PLAYER, 39);
	printf("   @   @    \n");
	gotoxy(PLAYER, 40);
	printf("  @    @@   \n");
}
void pmove(char a) {
	switch (a) {
	case'd': {
		gotoxy(PLAYER, 31);
		printf("           &&&& @@ \n");
		gotoxy(PLAYER, 32);
		printf("          &&&&   @@@    \n");
		gotoxy(PLAYER, 33);
		printf("  @@@@@@##@#     @@@@    \n");
		gotoxy(PLAYER, 34);
		printf("       ###@      @@@@@   \n");
		gotoxy(PLAYER, 35);
		printf("      #### @    @@@@@@  \n");
		gotoxy(PLAYER, 36);
		printf("     ####   @$$$$$$$$$\n");
		gotoxy(PLAYER, 37);
		printf("     @  @            \n");
		gotoxy(PLAYER, 38);
		printf("    @    @        \n");
		gotoxy(PLAYER, 39);
		printf("   @     @      \n");
		gotoxy(PLAYER, 40);
		printf("  @      @@     \n");
		break;
	}case 'a': {
		gotoxy(PLAYER, 31);
		printf("    &&&&         \n");
		gotoxy(PLAYER, 32);
		printf("    &&&&      \n");
		gotoxy(PLAYER, 33);
		printf("     ##       \n");
		gotoxy(PLAYER, 34);
		printf("     @###      \n");
		gotoxy(PLAYER, 35);
		printf("    @ ####      \n");
		gotoxy(PLAYER, 36);
		printf(" $ @   ###@@@    \n");
		gotoxy(PLAYER, 37);
		printf("  @    @     @      \n");
		gotoxy(PLAYER, 38);
		printf("   $    @     @   \n");
		gotoxy(PLAYER, 39);
		printf("    $    @          \n");
		gotoxy(PLAYER, 40);
		printf("     $    @     \n");
		break;
	}case 'w': {
		gotoxy(PLAYER, 29);
		printf("        &&&&    \n");
		gotoxy(PLAYER, 30);
		printf("        &&&&    \n");
		gotoxy(PLAYER, 31);
		printf("         ##     \n");
		gotoxy(PLAYER, 32);
		printf("     @@@####@     \n");
		gotoxy(PLAYER, 33);
		printf("   $@   #### @ \n");
		gotoxy(PLAYER, 34);
		printf("   @    ####  @ \n");
		gotoxy(PLAYER, 35);
		printf("   $    ####   @ \n");
		gotoxy(PLAYER, 36);
		printf("   $    @   @   \n");
		gotoxy(PLAYER, 37);
		printf("   $    @    @  \n");
		gotoxy(PLAYER, 38);
		printf("   $    @     @ \n");
		gotoxy(PLAYER, 39);
		printf("   $    @    @  \n");
		break;
	}
	case's': {
		gotoxy(PLAYER, 32);
		printf(" $                         \n");
		gotoxy(PLAYER, 33);
		printf("  $           %%%%         \n");
		gotoxy(PLAYER, 34);
		printf("   $         %%%%          \n");
		gotoxy(PLAYER, 35);
		printf("    $     @####@           \n");
		gotoxy(PLAYER, 36);
		printf("     $  @ ####  @          \n");
		gotoxy(PLAYER, 37);
		printf("      @  ####    @         \n");
		gotoxy(PLAYER, 38);
		printf("       $ ####@@@@          \n");
		gotoxy(PLAYER, 39);
		printf("        @        @         \n");
		gotoxy(PLAYER, 40);
		printf("   @@@@@          @        \n");
		break;
	}
	}

}
void pclear() {
	gotoxy(PLAYER, 26);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 27);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 28);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 29);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 30);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 31);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 32);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 33);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 34);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 35);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 36);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 37);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 38);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 39);
	printf("                                                                                  \n");
	gotoxy(PLAYER, 40);
	printf("                                                                                  \n");
}
void bskill(int s) {
	switch (s) {
	case(0): {
		gotoxy(ENEMYX, 21);
		printf("     @ @ @@ @@  ");
		gotoxy(ENEMYX, 22);
		printf("      @@@@@@@   ");
		gotoxy(ENEMYX, 23);
		printf("       @@@@     ");
		gotoxy(ENEMYX, 24);
		printf("    ### @@  ##\n");
		gotoxy(ENEMYX, 25);
		printf("    ##  @@ ###\n");
		gotoxy(ENEMYX, 26);
		printf("    ### @   ##\n");
		gotoxy(ENEMYX, 27);
		printf("    ###   ####\n");
		gotoxy(ENEMYX, 28);
		printf("    #### #####\n");
		gotoxy(ENEMYX, 29);
		printf("    #####   ## \n");
		gotoxy(ENEMYX, 30);
		printf("   #####  @  #@\n");
		gotoxy(ENEMYX, 31);
		printf("  ########  ##@\n");
		gotoxy(ENEMYX, 32);
		printf("   #########@#@@\n");
		gotoxy(ENEMYX, 33);
		printf("    #######@##@@@\n");
		gotoxy(ENEMYX, 34);
		printf(" #############@@\n");
		gotoxy(ENEMYX, 35);
		printf("#  ###########@@\n");
		gotoxy(ENEMYX, 36);
		printf("   ###########@@@\n");
		gotoxy(ENEMYX, 37);
		printf("   ###########@@@\n");
		gotoxy(ENEMYX, 38);
		printf("   #############@@\n");
		gotoxy(ENEMYX, 39);
		printf("  ####  ####  ####@@@\n");
		gotoxy(ENEMYX, 40);
		printf("####  ####     #####@@\n");
		gotoxy(ENEMYX, 41);
		Sleep(500);
		clear();
		gotoxy(ENEMYX - 20, 26);
		printf("       @ @  @ @    @@@@@@@@@@@@@@@@@                             \n");
		gotoxy(ENEMYX - 20, 27);
		printf("        @@ @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@        ###########@  \n");
		gotoxy(ENEMYX - 20, 28);
		printf("    @     @  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    # # #######@@ \n");
		gotoxy(ENEMYX - 20, 29);
		printf("        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    #  ##@@ \n");
		gotoxy(ENEMYX - 20, 30);
		printf("       @   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     ######@  \n");
		gotoxy(ENEMYX - 20, 31);
		printf("         @@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    # # #######@@ \n");
		gotoxy(ENEMYX - 20, 32);
		printf("        @@ @@     @@@@@@@@@@@@@@@@@@@@@@@@         ###########@@@\n");
		gotoxy(ENEMYX - 20, 33);
		printf("           @    @       @@@@@@@@@@@@@@             ###########@@ \n");
		gotoxy(ENEMYX - 20, 34);
		printf("             @@                                    ###########@@@\n");
		gotoxy(ENEMYX - 20, 35);
		printf("                                                   ############@@ \n");
		gotoxy(ENEMYX - 20, 36);
		printf("                                               ### ##############@@ \n");
		gotoxy(ENEMYX - 20, 37);
		printf("                                                ##################@@@@@\n");
		gotoxy(ENEMYX - 20, 38);
		printf("                                                 #####    ####  #######@@\n");
		gotoxy(ENEMYX - 20, 39);
		printf("                                                         ####    \n");
		gotoxy(ENEMYX - 20, 40);
		printf("                                                                 \n");
		gotoxy(ENEMYX - 20, 41);
		break;
	}
	case(1): {
		clear();
		gotoxy(ENEMYX, 25);
		printf("##############@\n");
		gotoxy(ENEMYX, 26);
		printf("#########  ###@@\n");
		gotoxy(ENEMYX, 27);
		printf("# # # ########@@@\n");
		gotoxy(ENEMYX, 28);
		printf("##############@@\n");
		gotoxy(ENEMYX, 29);
		printf("    ##########@@@\n");
		gotoxy(ENEMYX, 30);
		printf(" #############@@\n");
		gotoxy(ENEMYX, 31);
		printf("#   ##########@@@\n");
		gotoxy(ENEMYX, 32);
		printf("    ##########@@\n");
		gotoxy(ENEMYX, 33);
		printf("##############@@@@\n");
		gotoxy(ENEMYX, 34);
		printf("##################@@@\n");
		gotoxy(ENEMYX, 35);
		printf("       ###############@@\n");
		gotoxy(ENEMYX, 36);
		printf("     ######   \n");
		Sleep(500);
		clear();
		gotoxy(ENEMYX - 12, 33);
		printf("            ##############@                  \n");
		gotoxy(ENEMYX - 12, 34);
		printf("            ######### ! ##@@                  \n");
		gotoxy(ENEMYX - 12, 35);
		printf("            # # # ### ! ##@@@                  \n");
		gotoxy(ENEMYX - 12, 36);
		printf("  *  *      ##############@@           *      \n");
		gotoxy(ENEMYX - 12, 37);
		printf(" *     *        ##########@@@       *   *  *    \n");
		gotoxy(ENEMYX - 12, 38);
		printf(" *   *   *   #############@@  *   *   *  *    \n");
		gotoxy(ENEMYX - 12, 39);
		printf("   *  * *   # * ##########@@@   *  **  *  * *   \n");
		gotoxy(ENEMYX - 12, 40);
		printf(" *  *   * *  *  ##########@@ *   *   *     *    \n");
		break;
	}
	}
}
void boss3() {
	gotoxy(ENEMYX, 31);
	printf("             @@@@                      \n");
	gotoxy(ENEMYX, 32);
	printf("             @@@@                      \n");
	gotoxy(ENEMYX, 33);
	printf("              @@                       \n");
	gotoxy(ENEMYX, 34);
	printf("             @###@                     \n");
	gotoxy(ENEMYX, 35);
	printf("             #@## @                    \n");
	gotoxy(ENEMYX, 36);
	printf("             ##@$$$@$$$$$$$$$$$        \n");
	gotoxy(ENEMYX, 37);
	printf("            &   &                      \n");
	gotoxy(ENEMYX, 38);
	printf("           &     &                     \n");
	gotoxy(ENEMYX, 39);
	printf("           &      &                    \n");
	gotoxy(ENEMYX, 40);
	printf("            &      &                   \n");
}
void pattern3(int r) {
	switch (r) {
	case(0): {
		gotoxy(ENEMYX, 27);
		printf("               @@@                     \n");
		gotoxy(ENEMYX, 28);
		printf("             @@@@                      \n");
		gotoxy(ENEMYX, 29);
		printf("            @@@@                       \n");
		gotoxy(ENEMYX, 30);
		printf("          @@@@@                        \n");
		gotoxy(ENEMYX, 31);
		printf("         @@@@@@      @@@@                      \n");
		gotoxy(ENEMYX, 32);
		printf("        @@@@@@       @@@@                      \n");
		gotoxy(ENEMYX, 33);
		printf("       @@@@@@@        @@                       \n");
		gotoxy(ENEMYX, 34);
		printf("      @@@@@@@@       @#@#                      \n");
		gotoxy(ENEMYX, 35);
		printf("      @@@@@@@@@     @#@##                      \n");
		gotoxy(ENEMYX, 36);
		printf("      #############@#@###                      \n");
		gotoxy(ENEMYX, 37);
		printf("                    &   &                      \n");
		gotoxy(ENEMYX, 38);
		printf("                   &     &                     \n");
		gotoxy(ENEMYX, 39);
		printf("                   &      &                    \n");
		gotoxy(ENEMYX, 40);
		printf("                    &      &                   \n");
		break;
	}

	case(1): {
		gotoxy(ENEMYX, 31);
		printf("             @@@@                      \n");
		gotoxy(ENEMYX, 32);
		printf("             @@@@                      \n");
		gotoxy(ENEMYX, 33);
		printf("              @@                       \n");
		gotoxy(ENEMYX, 34);
		printf("    $$$$$$$@@###@@@@@$$$$$$$$$$$$$>>   \n");
		gotoxy(ENEMYX, 35);
		printf("             ####                      \n");
		gotoxy(ENEMYX, 36);
		printf("             ####                      \n");
		gotoxy(ENEMYX, 37);
		printf("            &    &                     \n");
		gotoxy(ENEMYX, 38);
		printf("           &      &                    \n");
		gotoxy(ENEMYX, 39);
		printf("          &        &                   \n");
		gotoxy(ENEMYX, 40);
		printf("         &        &                    \n");
		Sleep(150);
		gotoxy(ENEMYX, 31);
		printf("               @@@@                      \n");
		gotoxy(ENEMYX, 32);
		printf("               @@@@                      \n");
		gotoxy(ENEMYX, 33);
		printf("                @@                       \n");
		gotoxy(ENEMYX, 34);
		printf("<<$$$$$$$$$@@@@###@@$$$$$$$              \n");
		gotoxy(ENEMYX, 35);
		printf("               ####                      \n");
		gotoxy(ENEMYX, 36);
		printf("               ####                      \n");
		gotoxy(ENEMYX, 37);
		printf("              &    &                     \n");
		gotoxy(ENEMYX, 38);
		printf("             &      &                    \n");
		gotoxy(ENEMYX, 39);
		printf("            &        &                   \n");
		gotoxy(ENEMYX, 40);
		printf("             &        &                  \n");
		break;
	}
	case(2): {
		gotoxy(ENEMYX, 33);
		printf("                      ####             \n");
		gotoxy(ENEMYX, 34);
		printf("                     ####              \n");
		gotoxy(ENEMYX, 35);
		printf("                     ##                \n");
		gotoxy(ENEMYX, 36);
		printf("                   @###@               \n");
		gotoxy(ENEMYX, 37);
		printf("                  ##@#  @                \n");
		gotoxy(ENEMYX, 38);
		printf("               &&####@@$$$$$$$$$$$$$$$$$      \n");
		gotoxy(ENEMYX, 39);
		printf("             &&    &&                        \n");
		gotoxy(ENEMYX, 40);
		printf("           &&        &&&                 \n");
		Sleep(150);
		clear();
		gotoxy(ENEMYX, 29);
		printf("                            $$$$$$     \n");
		gotoxy(ENEMYX, 30);
		printf("                       $$$$$$@@@@@@    \n");
		gotoxy(ENEMYX, 31);
		printf("                  $$$$$$ @@@@@@@@@@@   \n");
		gotoxy(ENEMYX, 32);
		printf("                $$$   @    @@@@@@@@@@  \n");
		gotoxy(ENEMYX, 33);
		printf("             $$$ $    @###  @@@@@@@@@@ \n");
		gotoxy(ENEMYX, 34);
		printf("            $   $@   #@##    @@@@@@@@@ \n");
		gotoxy(ENEMYX, 35);
		printf("                  @  #@        @@@@@@@ \n");
		gotoxy(ENEMYX, 36);
		printf("                   ####         @@@@@@ \n");
		gotoxy(ENEMYX, 37);
		printf("                  ####           @@@@    \n");
		gotoxy(ENEMYX, 38);
		printf("               &&####             @@          \n");
		gotoxy(ENEMYX, 39);
		printf("             &&    &&              @         \n");
		gotoxy(ENEMYX, 40);
		printf("           &&        &&&                 \n");
		break;
	}
	case(3): {
		gotoxy(ENEMYX, 33);
		printf("                      ####             \n");
		gotoxy(ENEMYX, 34);
		printf("                     ####              \n");
		gotoxy(ENEMYX, 35);
		printf("                     ##                \n");
		gotoxy(ENEMYX, 36);
		printf("                   @###@               \n");
		gotoxy(ENEMYX, 37);
		printf("                  ##@#  @                \n");
		gotoxy(ENEMYX, 38);
		printf("               &&####@@$$$$$$$$$$$$$$$$$      \n");
		gotoxy(ENEMYX, 39);
		printf("             &&    &&                        \n");
		gotoxy(ENEMYX, 40);
		printf("           &&        &&&                 \n");
		Sleep(150);
		clear();
		gotoxy(ENEMYX, 32);
		printf(" $$                                    \n");
		gotoxy(ENEMYX, 33);
		printf(" @@$$                 ####             \n");
		gotoxy(ENEMYX, 34);
		printf(" @@@@$$              ####              \n");
		gotoxy(ENEMYX, 35);
		printf("  @@@@@$$$           ##                \n");
		gotoxy(ENEMYX, 36);
		printf("  @@@@@@@$$$       @###                \n");
		gotoxy(ENEMYX, 37);
		printf("   @@@@@@   $$    @##@                   \n");
		gotoxy(ENEMYX, 38);
		printf("   @@@@@@     $&&@#@#                         \n");
		gotoxy(ENEMYX, 39);
		printf("    @@@@     &&$@@ &&                        \n");
		gotoxy(ENEMYX, 40);
		printf("     @@@   &&   $$   &&&                 \n");
	}
	}
}
void boss2() {

	gotoxy(ENEMYX, 31);
	printf("              #                  \n");
	gotoxy(ENEMYX, 32);
	printf("             ###                \n");
	gotoxy(ENEMYX, 33);
	printf("            #####                \n");
	gotoxy(ENEMYX, 34);
	printf("           #######               \n");
	gotoxy(ENEMYX, 35);
	printf("        #############            \n");
	gotoxy(ENEMYX, 36);
	printf("           @@@@@@@               \n");
	gotoxy(ENEMYX, 37);
	printf("          @@  @@@@@              \n");
	gotoxy(ENEMYX, 38);
	printf("          @@@@@@@@@              \n");
	gotoxy(ENEMYX, 39);
	printf("           @@@@@@@               \n");
	gotoxy(ENEMYX, 40);
	printf("            ## ##                \n");
}
void boss2p(int r) {
	switch (r) {
	case(0): {
		gotoxy(ENEMYX, 23);
		printf("            @     @             \n");
		gotoxy(ENEMYX, 24);
		printf("           @ @   @ @            \n");
		gotoxy(ENEMYX, 25);
		printf("         @           @           \n");
		gotoxy(ENEMYX, 26);
		printf("          @         @            \n");
		gotoxy(ENEMYX, 27);
		printf("           @@@@@@@@@        \n");
		break;
	}
	case(1): {
		gotoxy(ENEMYX, 23);
		printf("          @        @          \n");
		gotoxy(ENEMYX, 24);
		printf("           @      @            \n");
		gotoxy(ENEMYX, 25);
		printf("            @    @              \n");
		gotoxy(ENEMYX, 26);
		printf("                         \n");
		gotoxy(ENEMYX, 27);
		printf("           @@@@@@@@       \n");
		gotoxy(ENEMYX, 28);
		printf("          @        @     \n");
		break;
	}
	}
}
void bskill2_1() {
	gotoxy(ENEMYX, 31);
	printf("              @@                 \n");
	gotoxy(ENEMYX, 32);
	printf("           @@@@@                 \n");
	gotoxy(ENEMYX, 33);
	printf("            @@@@@@               \n");
	gotoxy(ENEMYX, 34);
	printf("         @@@@@@@@@@@             \n");
	gotoxy(ENEMYX, 35);
	printf("        @@@@@@@@@@@@@            \n");
	gotoxy(ENEMYX, 36);
	printf("        @@@@@@@@@@@@@@           \n");
	gotoxy(ENEMYX, 37);
	printf("          @@  @@@@@@@@           \n");
	gotoxy(ENEMYX, 38);
	printf("         @@@@@@@@@@@@            \n");
	gotoxy(ENEMYX, 39);
	printf("         @@@@@@@@@@@@            \n");
	gotoxy(ENEMYX, 40);
	printf("            @@@@@@@@             \n");
	Sleep(300);
	gotoxy(ENEMYX, 31);
	printf("       * *    #    *   *         \n");
	gotoxy(ENEMYX, 32);
	printf("   *   *  *  ###  *  *          \n");
	gotoxy(ENEMYX, 33);
	printf("  *  *  *  *#####  *   *  *      \n");
	gotoxy(ENEMYX, 34);
	printf("   *  *    #######   *  *        \n");
	gotoxy(ENEMYX, 35);
	printf(" *  *   #############  *   *     \n");
	gotoxy(ENEMYX, 36);
	printf("*  *   *   @@@@@@@  * *  *       \n");
	gotoxy(ENEMYX, 37);
	printf(" *   *    @ |  @@@@   *          \n");
	gotoxy(ENEMYX, 38);
	printf("  *   *   @ |  @@@@ *   *  *     \n");
	gotoxy(ENEMYX, 39);
	printf("    *  *   @@@@@@@ * *  *        \n");
	gotoxy(ENEMYX, 40);
	printf("  *  *   *  ## ## * * *          \n");
	gotoxy(PLAYER, 31);
	printf("  @@ @@@@@@@                          \n");
	gotoxy(PLAYER, 32);
	printf("   @@@@@@@@@@@@    @@@@                 \n");
	gotoxy(PLAYER, 33);
	printf("   ###      @@@@@@@@@@@@                \n");
	gotoxy(PLAYER, 34);
	printf("  @@@@@@@@@@@@@@@@@@@@@@@@@@@@             \n");
	gotoxy(PLAYER, 35);
	printf(" @@@##@@@@      @@@@@@@@@@@@@@@@@@@@          \n");
	gotoxy(PLAYER, 36);
	printf("    ###@@        @@@@@@@@@@@@@@@@@@@@@@@      \n");
	gotoxy(PLAYER, 37);
	printf("  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        \n");
	gotoxy(PLAYER, 38);
	printf("   @@    #   @@@@@@@@@@@@@@@@@@@@          \n");
	gotoxy(PLAYER, 39);
	printf("  #   @@@@@@@@@     @@@@@@@               \n");
	gotoxy(PLAYER, 40);
	printf(" @  @@@@@@@   @@@@@@@@@@@@@         \n");
}
void bskill2_2() {
	gotoxy(PLAYER, 32);
	printf("    @@@@@@             \n");
	gotoxy(PLAYER, 33);
	printf("  @@@@@@@@@@          \n");
	gotoxy(PLAYER, 34);
	printf(" @@@@@@@@@@@@            \n");
	gotoxy(PLAYER, 35);
	printf(" @@@@@@@@@@@@             \n");
	gotoxy(PLAYER, 36);
	printf(" @@@@@@@@@@@@             \n");
	gotoxy(PLAYER, 37);
	printf(" @@@@@@@@@@@@           \n");
	gotoxy(PLAYER, 38);
	printf(" @@@@@@@@@@@@            \n");
	gotoxy(PLAYER, 39);
	printf("  @@@@@@@@@@             \n");
	gotoxy(PLAYER, 40);
	printf("   @@@@@@@@            \n");
}
void bskill3_1() {
	gotoxy(ENEMYX, 32);
	printf("         @@@@)))                       \n");
	gotoxy(ENEMYX, 33);
	printf("         @@@@))))                      \n");
	gotoxy(ENEMYX, 34);
	printf("           @###@)))                    \n");
	gotoxy(ENEMYX, 35);
	printf("            #@##@)))                   \n");
	gotoxy(ENEMYX, 36);
	printf("             ##@#@$$$$$$$$$$$$$$$$$$$$ \n");
	gotoxy(ENEMYX, 37);
	printf("            &   &)))                   \n");
	gotoxy(ENEMYX, 38);
	printf("           &     &)))                  \n");
	gotoxy(ENEMYX, 39);
	printf("            &      &&)))               \n");
	gotoxy(ENEMYX, 40);
	printf("             &&      &&)))             \n");
}
void bskill3_2() {
	gotoxy(ENEMYX - 32, 32);
	printf("   $                                  @@@@                          \n");
	gotoxy(ENEMYX - 32, 33);
	printf("     $$                               @@@@                          \n");
	gotoxy(ENEMYX - 32, 34);
	printf("       $$                               @###@                       \n");
	gotoxy(ENEMYX - 32, 35);
	printf("         $$                              #@##@                      \n");
	gotoxy(ENEMYX - 32, 36);
	printf("           $$                             ##@#@$$$$$$$$$$$$$$$$$$$$ \n");
	gotoxy(ENEMYX - 32, 37);
	printf("             $$                          &   &                      \n");
	gotoxy(ENEMYX - 32, 38);
	printf("               $$                       &     &                     \n");
	gotoxy(ENEMYX - 32, 39);
	printf("                 $$                      &      &&                  \n");
	gotoxy(ENEMYX - 32, 40);
	printf("                   $$                     &&      &&                \n");
	Sleep(80);
	gotoxy(ENEMYX - 32, 32);
	printf("   $$               $                 @@@@                          \n");
	gotoxy(ENEMYX - 32, 33);
	printf("     $$          $$                   @@@@                          \n");
	gotoxy(ENEMYX - 32, 34);
	printf("       $$      $$                       @###@                       \n");
	gotoxy(ENEMYX - 32, 35);
	printf("         $$  $$                          #@##@                      \n");
	gotoxy(ENEMYX - 32, 36);
	printf("           $$                             ##@#@$$$$$$$$$$$$$$$$$$$$ \n");
	gotoxy(ENEMYX - 32, 37);
	printf("         $$  $$                          &   &                      \n");
	gotoxy(ENEMYX - 32, 38);
	printf("       $$      $$                       &     &                     \n");
	gotoxy(ENEMYX - 32, 39);
	printf("     $$          $$                      &      &&                  \n");
	gotoxy(ENEMYX - 32, 40);
	printf("   $$              $$                     &&      &&                \n");

}
void bskill3_3() {
	gotoxy(ENEMYX - 32, 32);
	printf("                   $                  @@@@                          \n");
	gotoxy(ENEMYX - 32, 33);
	printf("                 $$                   @@@@                          \n");
	gotoxy(ENEMYX - 32, 34);
	printf("               $$                       @###@                       \n");
	gotoxy(ENEMYX - 32, 35);
	printf("             $$                          #@##@                      \n");
	gotoxy(ENEMYX - 32, 36);
	printf("           $$                             ##@#@$$$$$$$$$$$$$$$$$$$$ \n");
	gotoxy(ENEMYX - 32, 37);
	printf("         $$                              &   &                      \n");
	gotoxy(ENEMYX - 32, 38);
	printf("       $$                               &     &                     \n");
	gotoxy(ENEMYX - 32, 39);
	printf("     $$                                  &      &&                  \n");
	gotoxy(ENEMYX - 32, 40);
	printf("   $$                                     &&      &&                \n");
	Sleep(80);
	gotoxy(ENEMYX - 32, 32);
	printf("   $$              $$                 @@@@                          \n");
	gotoxy(ENEMYX - 32, 33);
	printf("     $$          $$                   @@@@                          \n");
	gotoxy(ENEMYX - 32, 34);
	printf("       $$      $$                       @###@                       \n");
	gotoxy(ENEMYX - 32, 35);
	printf("         $$  $$                          #@##@                      \n");
	gotoxy(ENEMYX - 32, 36);
	printf("           $$                             ##@#@$$$$$$$$$$$$$$$$$$$$ \n");
	gotoxy(ENEMYX - 32, 37);
	printf("         $$  $$                          &   &                      \n");
	gotoxy(ENEMYX - 32, 38);
	printf("       $$      $$                       &     &                     \n");
	gotoxy(ENEMYX - 32, 39);
	printf("     $$          $$                      &      &&                  \n");
	gotoxy(ENEMYX - 32, 40);
	printf("   $$               $                     &&      &&                \n");
}
void pattern2_1(int r) {
	switch (r) {
	case (0): {
		gotoxy(ENEMYX, 32);
		printf("         #                             \n");
		gotoxy(ENEMYX, 33);
		printf("        ##   *                         \n");
		gotoxy(ENEMYX, 34);
		printf("       ###     *         @             \n");
		gotoxy(ENEMYX, 35);
		printf("      ####   *  *       @@@            \n");
		gotoxy(ENEMYX, 36);
		printf("     #####  *  *  ##  @@@@@@@          \n");
		gotoxy(ENEMYX, 37);
		printf("      ####   *    ###@@  @@@@@         \n");
		gotoxy(ENEMYX, 38);
		printf("       ###    * * ###@@@@@@@@@         \n");
		gotoxy(ENEMYX, 39);
		printf("        ##   * *      @@@@@@@          \n");
		gotoxy(ENEMYX, 40);
		printf("         #    *           ##           \n");
		break;
	}
	case (1): {

		gotoxy(ENEMYX, 31);
		printf("                              ###      \n");
		gotoxy(ENEMYX, 32);
		printf("                             ###       \n");
		gotoxy(ENEMYX, 33);
		printf("                           ######      \n");
		gotoxy(ENEMYX, 34);
		printf("                         #########     \n");
		gotoxy(ENEMYX, 35);
		printf("                      #############    \n");
		gotoxy(ENEMYX, 36);
		printf("                        @@@@@@@@@@     \n");
		gotoxy(ENEMYX, 37);
		printf("     <<<<<<<<<<<<<<<      @@@@@@@@@    \n");
		gotoxy(ENEMYX, 38);
		printf("    <<<<<<<<<<<<<<<<    #  @@@@@@@@    \n");
		gotoxy(ENEMYX, 39);
		printf("     <<<<<<<<<<<<<<<      @@@@@@@@@    \n");
		gotoxy(ENEMYX, 40);
		printf("                        @@@@@@@@@@     \n");
		break;
	}case (2): {
		gotoxy(ENEMYX, 31);
		printf("        ****   *  **               \n");
		gotoxy(ENEMYX, 32);
		printf("         *****  * *                \n");
		gotoxy(ENEMYX, 33);
		printf("    *  *  ****** *                 \n");
		gotoxy(ENEMYX, 34);
		printf("       *  * *****                  \n");
		gotoxy(ENEMYX, 35);
		printf("        ** * *###                  \n");
		gotoxy(ENEMYX, 36);
		printf("               ###                 \n");
		gotoxy(ENEMYX, 37);
		printf("                ###  #####         \n");
		gotoxy(ENEMYX, 38);
		printf("                 #####  ###        \n");
		gotoxy(ENEMYX, 39);
		printf("               ################    \n");
		gotoxy(ENEMYX, 40);
		printf("               ################    \n");
		break;
	}
	case (3): {
		gotoxy(ENEMYX, 33);
		printf("               @@@@@@@                 \n");
		gotoxy(ENEMYX, 34);
		printf("              @@@@ @@@@                \n");
		gotoxy(ENEMYX, 35);
		printf("              @@@   @@@                \n");
		gotoxy(ENEMYX, 36);
		printf("              @@@@ @@@@                \n");
		gotoxy(ENEMYX, 37);
		printf("     *         @@@@@@@         *       \n");
		gotoxy(ENEMYX, 38);
		printf("  *  *  *  ##############   *          \n");
		gotoxy(ENEMYX, 39);
		printf("     *   *   ##########   *  * *       \n");
		gotoxy(ENEMYX, 40);
		printf("      * *  *   ######   *  * *         \n");
		break;
	}
	}
}
void pattern2_2(int r) {
	switch (r) {
	case (1): {
		gotoxy(ENEMYX, 32);
		printf("         #                             \n");
		gotoxy(ENEMYX, 33);
		printf("        ##   *                         \n");
		gotoxy(ENEMYX, 34);
		printf("       ###     *         @             \n");
		gotoxy(ENEMYX, 35);
		printf("      ####   *  *       @@@            \n");
		gotoxy(ENEMYX, 36);
		printf("     #####  *  *  ##  @@@@@@@          \n");
		gotoxy(ENEMYX, 37);
		printf("      ####   *    ###@@  @@@@@         \n");
		gotoxy(ENEMYX, 38);
		printf("       ###    * * ###@@@@@@@@@         \n");
		gotoxy(ENEMYX, 39);
		printf("        ##   * *      @@@@@@@          \n");
		gotoxy(ENEMYX, 40);
		printf("         #    *           ##           \n");
		break;
	}
	case (0): {

		gotoxy(ENEMYX, 31);
		printf("                              ###      \n");
		gotoxy(ENEMYX, 32);
		printf("                             ###       \n");
		gotoxy(ENEMYX, 33);
		printf("                           ######      \n");
		gotoxy(ENEMYX, 34);
		printf("                         #########     \n");
		gotoxy(ENEMYX, 35);
		printf("                      #############    \n");
		gotoxy(ENEMYX, 36);
		printf("                        @@@@@@@@@@     \n");
		gotoxy(ENEMYX, 37);
		printf("     <<<<<<<<<<<<<<<      @@@@@@@@@    \n");
		gotoxy(ENEMYX, 38);
		printf("    <<<<<<<<<<<<<<<<    #  @@@@@@@@    \n");
		gotoxy(ENEMYX, 39);
		printf("     <<<<<<<<<<<<<<<      @@@@@@@@@    \n");
		gotoxy(ENEMYX, 40);
		printf("                        @@@@@@@@@@     \n");
		break;
	}case (3): {
		gotoxy(ENEMYX, 31);
		printf("        ****   *  **               \n");
		gotoxy(ENEMYX, 32);
		printf("         *****  * *                \n");
		gotoxy(ENEMYX, 33);
		printf("    *  *  ****** *                 \n");
		gotoxy(ENEMYX, 34);
		printf("       *  * *****                  \n");
		gotoxy(ENEMYX, 35);
		printf("        ** * *###                  \n");
		gotoxy(ENEMYX, 36);
		printf("               ###                 \n");
		gotoxy(ENEMYX, 37);
		printf("                ###  #####         \n");
		gotoxy(ENEMYX, 38);
		printf("                 #####  ###        \n");
		gotoxy(ENEMYX, 39);
		printf("               ################    \n");
		gotoxy(ENEMYX, 40);
		printf("               ################    \n");
		break;
	}
	case (2): {
		gotoxy(ENEMYX, 33);
		printf("               @@@@@@@                 \n");
		gotoxy(ENEMYX, 34);
		printf("              @@@@ @@@@                \n");
		gotoxy(ENEMYX, 35);
		printf("              @@@   @@@                \n");
		gotoxy(ENEMYX, 36);
		printf("              @@@@ @@@@                \n");
		gotoxy(ENEMYX, 37);
		printf("     *         @@@@@@@         *       \n");
		gotoxy(ENEMYX, 38);
		printf("  *  *  *  ##############   *          \n");
		gotoxy(ENEMYX, 39);
		printf("     *   *   ##########   *  * *       \n");
		gotoxy(ENEMYX, 40);
		printf("      * *  *   ######   *  * *         \n");
		break;
	}
	}
}
void pattern(int r) { //보스패턴
	switch (r) {
	case(0): {
		gotoxy(ENEMYX, 29);
		printf("##############@\n");
		gotoxy(ENEMYX, 30);
		printf("#########  ###@@\n");
		gotoxy(ENEMYX, 31);
		printf("# # # ########@@@\n");
		gotoxy(ENEMYX, 32);
		printf("##############@@\n");
		gotoxy(ENEMYX, 33);
		printf("    ##########@@@\n");
		gotoxy(ENEMYX, 34);
		printf(" #############@@\n");
		gotoxy(ENEMYX, 35);
		printf("#   ##########@@@\n");
		gotoxy(ENEMYX, 36);
		printf("    ##########@@\n");
		gotoxy(ENEMYX, 37);
		printf("##  ###########@@\n");
		gotoxy(ENEMYX, 38);
		printf("#################@@\n");
		gotoxy(ENEMYX, 39);
		printf("#####    #### #####@\n");
		gotoxy(ENEMYX, 40);
		printf("       ####     \n");
		gotoxy(ENEMYX, 41);
		break;
	}

	case(1): {
		gotoxy(ENEMYX, 29);
		printf("         @@@############\n");
		gotoxy(ENEMYX, 30);
		printf("       @@@#######  #####\n");
		gotoxy(ENEMYX, 31);
		printf("#@    @@################\n");
		gotoxy(ENEMYX, 32);
		printf("##@  @@@########## # # #\n");
		gotoxy(ENEMYX, 33);
		printf("###@ @@#################\n");
		gotoxy(ENEMYX, 34);
		printf("###@@@############\n");
		gotoxy(ENEMYX, 35);
		printf("####################\n");
		gotoxy(ENEMYX, 36);
		printf("#################   #\n");
		gotoxy(ENEMYX, 37);
		printf("################\n");
		gotoxy(ENEMYX, 38);
		printf("  ################\n");
		gotoxy(ENEMYX, 39);
		printf("      ####      ###\n");
		gotoxy(ENEMYX, 40);
		printf("        ####\n");
		gotoxy(ENEMYX, 41);
		break;
	}
	case(2): {
		gotoxy(ENEMYX, 34);
		printf("##########@@@@@@@@@@@@@@\n");
		gotoxy(ENEMYX, 35);
		printf("####  #################@@\n");
		gotoxy(ENEMYX, 36);
		printf("#########################@@\n");
		gotoxy(ENEMYX, 37);
		printf("# # # ####################@@@@\n");
		gotoxy(ENEMYX, 38);
		printf("#################################\n");
		gotoxy(ENEMYX, 39);
		printf("           #          ##\n");
		gotoxy(ENEMYX, 40);
		printf("            ##      ###\n");
		gotoxy(ENEMYX, 41);
		break;

	case(3): {
		gotoxy(ENEMYX, 27);
		printf("################@\n");
		gotoxy(ENEMYX, 28);
		printf("###########  ###@@\n");
		gotoxy(ENEMYX, 29);
		printf("# # # ##########@@\n");
		gotoxy(ENEMYX, 30);
		printf("################@@@\n");
		gotoxy(ENEMYX, 31);
		printf("     ###########@@\n");
		gotoxy(ENEMYX, 32);
		printf("    ############@@@\n");
		gotoxy(ENEMYX, 33);
		printf("   #############@@\n");
		gotoxy(ENEMYX, 34);
		printf("  # ############@\n");
		gotoxy(ENEMYX, 35);
		printf(" #  ############@@\n");
		gotoxy(ENEMYX, 36);
		printf("    ############@\n");
		gotoxy(ENEMYX, 37);
		printf("    ############@\n");
		gotoxy(ENEMYX, 38);
		printf("      ###    ###@\n");
		gotoxy(ENEMYX, 39);
		printf("     ###    ####@\n");
		gotoxy(ENEMYX, 40);
		printf("          ######@\n");
		gotoxy(ENEMYX, 41);
		break;

	}
	}
	}
}
void clear() { //보스 지우기
	gotoxy(ENEMYX - 32, 21);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 22);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 23);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 24);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 25);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 26);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 27);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 28);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 29);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 30);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 31);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 32);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 33);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 34);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 35);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 36);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 37);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 38);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 39);
	printf("                                                                                      \n");
	gotoxy(ENEMYX - 32, 40);
	printf("                                                                                      \n");

}
void boss() { //보스 기본상태
	gotoxy(ENEMYX, 29);
	printf("##############@\n");
	gotoxy(ENEMYX, 30);
	printf("#########  ###@@\n");
	gotoxy(ENEMYX, 31);
	printf("# # # ########@@@\n");
	gotoxy(ENEMYX, 32);
	printf("##############@@\n");
	gotoxy(ENEMYX, 33);
	printf("    ##########@@@\n");
	gotoxy(ENEMYX, 34);
	printf(" #############@@\n");
	gotoxy(ENEMYX, 35);
	printf("#   ##########@@@\n");
	gotoxy(ENEMYX, 36);
	printf("    ##########@@\n");
	gotoxy(ENEMYX, 37);
	printf("   ###########@@@@\n");
	gotoxy(ENEMYX, 38);
	printf("  ################@@@\n");
	gotoxy(ENEMYX, 39);
	printf(" ###     #############@@\n");
	gotoxy(ENEMYX, 40);
	printf("###       ### \n");
	gotoxy(ENEMYX, 41);

}
void bossturn() {
	gotoxy(20, 2);
	printf(" _______  _______  _______  _______    _______  __   __  ______    __    _\n");
	gotoxy(20, 3);
	printf("|  _    ||       ||       ||       |  |       ||  | |  ||    _ |  |  |  | |\n");
	gotoxy(20, 4);
	printf("| |_|   ||   _   ||  _____||  _____|  |_     _||  | |  ||   | ||  |   |_| |\n");
	gotoxy(20, 5);
	printf("|       ||  | |  || |_____ | |_____     |   |  |  |_|  ||   |_||_ |       |\n");
	gotoxy(20, 6);
	printf("|  _   | |  |_|  ||_____  ||_____  |    |   |  |       ||    __  ||  _    |\n");
	gotoxy(20, 7);
	printf("| |_|   ||       | _____| | _____| |    |   |  |       ||   |  | || | |   |\n");
	gotoxy(20, 8);
	printf("|_______||_______||_______||_______|    |___|  |_______||___|  |_||_|  |__|\n");
	Sleep(700);
	gotoxy(20, 2);
	printf("                                                                          \n");
	gotoxy(20, 3);
	printf("                                                                           \n");
	gotoxy(20, 4);
	printf("                                                                           \n");
	gotoxy(20, 5);
	printf("                                                                           \n");
	gotoxy(20, 6);
	printf("                                                                           \n");
	gotoxy(20, 7);
	printf("                                                                           \n");
	gotoxy(20, 8);
	printf("                                                                           \n");
	Sleep(700);

}
void yourturn() {
	gotoxy(20, 2);
	printf(" __   __  _______  __   __  ______      _______  __   __  ______    __    _\n");
	gotoxy(20, 3);
	printf("|  | |  ||       ||  | |  ||    _ |    |       ||  | |  ||    _ |  |  |  | |\n");
	gotoxy(20, 4);
	printf("|  |_|  ||   _   ||  | |  ||   | ||    |_     _||  | |  ||   | ||  |   |_| |\n");
	gotoxy(20, 5);
	printf("|       ||  | |  ||  |_|  ||   |_||_     |   |  |  |_|  ||   |_||_ |       |\n");
	gotoxy(20, 6);
	printf("|_     _||  |_|  ||       ||    __  |    |   |  |       ||    __  ||  _    |\n");
	gotoxy(20, 7);
	printf("  |   |  |       ||       ||   |  | |    |   |  |       ||   |  | || | |   |\n");
	gotoxy(20, 8);
	printf("  |___|  |_______||_______||___|  |_|    |___|  |_______||___|  |_||_|  |__|\n");
	Sleep(700);
	gotoxy(20, 2);
	printf("                                                                            \n");
	gotoxy(20, 3);
	printf("                                                                            \n");
	gotoxy(20, 4);
	printf("                                                                            \n");
	gotoxy(20, 5);
	printf("                                                                            \n");
	gotoxy(20, 6);
	printf("                                                                            \n");
	gotoxy(20, 7);
	printf("                                                                            \n");
	gotoxy(20, 8);
	printf("                                                                            \n");
}
void eraser(int x, int y) { //잔상 지우기//
	gotoxy(x, y);
	printf("           ");
	gotoxy(x, y + 1);
	printf("            ");
	gotoxy(x, y + 2);
	printf("            ");
	gotoxy(x, y + 3);
	printf("                  ");
	gotoxy(x, y + 4);
	printf("                 ");
	gotoxy(x, y + 5);
	printf("                ");
	gotoxy(x, y + 6);
	printf("               ");
	gotoxy(x, y + 7);
	printf("              ");
	gotoxy(x, y + 8);
	printf("               ");
	gotoxy(x, y + 9);
	printf("           ");
	gotoxy(x, y + 10);
	printf("           ");
	gotoxy(x, y + 11);
	printf("           ");
	gotoxy(x, y + 12);
	printf("            ");
	gotoxy(x, y + 13);
	printf("              ");
	gotoxy(x, y + 14);
	printf("                ");
	gotoxy(x, y + 15);
	printf("               ");
	gotoxy(x, y + 16);
}

void player(int x, int y) {//플레이어 도트
	int move = 0;
	gotoxy(x, y);
	printf("      $$$$$");
	gotoxy(x, y + 1);
	printf("     $$$$$$$");
	gotoxy(x, y + 2);
	printf("     $$$$$$$");
	gotoxy(x, y + 3);
	printf("      $$$$$      #");
	gotoxy(x, y + 4);
	printf("        $       #");
	gotoxy(x, y + 5);
	printf("       $$$     #");
	gotoxy(x, y + 6);
	printf("       $$$$ # #");
	gotoxy(x, y + 7);
	printf("      $$$$ $ #");
	gotoxy(x, y + 8);
	printf("      $$$$$$$ #");
	gotoxy(x, y + 9);
	printf("       $$$");
	gotoxy(x, y + 10);
	printf("       $$$");
	gotoxy(x, y + 11);
	printf("       $$$");
	gotoxy(x, y + 12);
	printf("      $$  $$");
	gotoxy(x, y + 13);
	printf("    $$      $$");
	gotoxy(x, y + 14);
	printf("  $$          $$");
	gotoxy(x, y + 15);
	printf(" $$         $$");
	gotoxy(x, y + 16);
}
void player1(int x, int y) {//플레이어 도트
	gotoxy(x, y);
	printf("      $$$$$");
	gotoxy(x, y + 1);
	printf("     $$$$$$$");
	gotoxy(x, y + 2);
	printf("     $$$$$$$");
	gotoxy(x, y + 3);
	printf("      $$$$$");
	gotoxy(x, y + 4);
	printf("        $");
	gotoxy(x, y + 5);
	printf("       $$$");
	gotoxy(x, y + 6);
	printf("       $$$$");
	gotoxy(x, y + 7);
	printf("      $$$$ $  #");
	gotoxy(x, y + 8);
	printf("      $$$$$$$ # # # # # #");
	gotoxy(x, y + 9);
	printf("       $$$    #");
	gotoxy(x, y + 10);
	printf("       $$$");
	gotoxy(x, y + 11);
	printf("       $$$");
	gotoxy(x, y + 12);
	printf("      $$  $$");
	gotoxy(x, y + 13);
	printf("    $$      $$");
	gotoxy(x, y + 14);
	printf("  $$          $$");
	gotoxy(x, y + 15);
	printf(" $$         $$");
	gotoxy(x, y + 16);
}
void player2(int x, int y) {//플레이어 도트
	gotoxy(x, y);
	printf("      $$$$$");
	gotoxy(x, y + 1);
	printf("     $$$$$$$");
	gotoxy(x, y + 2);
	printf("     $$$$$$$");
	gotoxy(x, y + 3);
	printf("      $$$$$");
	gotoxy(x, y + 4);
	printf("        $");
	gotoxy(x, y + 5);
	printf("       $$$ $");
	gotoxy(x, y + 6);
	printf("       $$$   $");
	gotoxy(x, y + 7);
	printf("      $$$$     $  #");
	gotoxy(x, y + 8);
	printf("      $$$$$ $ $ $ # # # # # #");
	gotoxy(x, y + 9);
	printf("       $$$        #");
	gotoxy(x, y + 10);
	printf("       $$$");
	gotoxy(x, y + 11);
	printf("       $$$");
	gotoxy(x, y + 12);
	printf("      $$  $$");
	gotoxy(x, y + 13);
	printf("    $$      $$");
	gotoxy(x, y + 14);
	printf("  $$          $$");
	gotoxy(x, y + 15);
	printf(" $$         $$");
	gotoxy(x, y + 16);
}
void eraser1(int x, int y) { //잔상 지우기//
	gotoxy(x, y);
	printf("            ");
	gotoxy(x, y + 1);
	printf("            ");
	gotoxy(x, y + 2);
	printf("            ");
	gotoxy(x, y + 3);
	printf("           ");
	gotoxy(x, y + 4);
	printf("         ");
	gotoxy(x, y + 5);
	printf("          ");
	gotoxy(x, y + 6);
	printf("           ");
	gotoxy(x, y + 7);
	printf("               ");
	gotoxy(x, y + 8);
	printf("                         ");
	gotoxy(x, y + 9);
	printf("               ");
	gotoxy(x, y + 10);
	printf("          ");
	gotoxy(x, y + 11);
	printf("          ");
	gotoxy(x, y + 12);
	printf("            ");
	gotoxy(x, y + 13);
	printf("              ");
	gotoxy(x, y + 14);
	printf("                ");
	gotoxy(x, y + 15);
	printf("              ");
	gotoxy(x, y + 16);
}
void eraser2(int x, int y) { //잔상 지우기//
	gotoxy(x, y);
	printf("           ");
	gotoxy(x, y + 1);
	printf("            ");
	gotoxy(x, y + 2);
	printf("            ");
	gotoxy(x, y + 3);
	printf("           ");
	gotoxy(x, y + 4);
	printf("         ");
	gotoxy(x, y + 5);
	printf("            ");
	gotoxy(x, y + 6);
	printf("              ");
	gotoxy(x, y + 7);
	printf("                   ");
	gotoxy(x, y + 8);
	printf("                             ");
	gotoxy(x, y + 9);
	printf("                   ");
	gotoxy(x, y + 10);
	printf("          ");
	gotoxy(x, y + 11);
	printf("          ");
	gotoxy(x, y + 12);
	printf("            ");
	gotoxy(x, y + 13);
	printf("              ");
	gotoxy(x, y + 14);
	printf("                ");
	gotoxy(x, y + 15);
	printf("              ");
	gotoxy(x, y + 16);
}
void main() {
	MYSQL* conn = mysql_init(NULL);			//MYSQL 선언, 연결 초기화
	MYSQL_RES* result;
	MYSQL_ROW row;
	MYSQL_FIELD* field;
	int fcolor = 15;
	int cntField, cntRow;
	int gnum;
	time_t newtime, oldtime, newtime1, oldtime1; //시간 제한
	int lv;//레벨
	system("mode con cols=155 lines=45");
	char key;//getch입력값
	int word;//lv2 보스 입력패턴
	int keyword;//내가 입력할 값
	char move[4] = { 'a','d','s','w' };//플레이어 움직임값
	int enemymove[4] = { 0 }; //보스 움직임 입력값
	int ran, ran2, ran3, ran4, ran5;//랜덤함수
	int guard = 3;//가드 수치
	int life = 8;// 체력
	int bosslife;//보스 체력
	srand(time(NULL));
	char nick[20] = { "Guest" };
	char nickname[20];
	char insertQuery[100];
	int stosel = 0;
	int s2sel = 0;
	int s3sel = 0;
	int s4sel = 0;
	int s6sel = 0;
	int mygold = 5000;
	int buy = 0;
	int buysel = 0;
	int money = 0;
	int stages = 3;
	int skin1 = 0;
	int skin2 = 0;
	int skin3 = 0;
	int skin4 = 0;
	system("mode con cols=150 lines=45 | title SWORD SAGA");
	PlaySound(TEXT("sound.wav"), NULL, SND_ASYNC | SND_LOOP);


	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	//현재 커서의 위치 정보를 저장하는 함수
	//presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y

	while (1) {
		if (stages == 1) {
			setcursortype(NOCURSOR);
			gotoxy(15, 3);
			printf("         ■■■■                                                                                                       \n");
			gotoxy(15, 4);
			printf("     ■■■■■■■                                                                ■■■■■■          ■■■■■■      \n");
			gotoxy(15, 5);
			printf("   ■■■     ■■■       ■■■               ■■■      ■■■■■■         ■■■■■■■■■      ■■■■■■■■   \n");
			gotoxy(15, 6);
			printf("  ■■■          ■■      ■■■     ■      ■■       ■■■    ■■■      ■■■        ■■■     ■■■       ■■■  \n");
			gotoxy(15, 7);
			printf("  ■■■            ■        ■■    ■■     ■■       ■■■      ■■■    ■■■        ■■■     ■■■        ■■■  \n");
			gotoxy(15, 8);
			printf("    ■■■■                  ■■    ■■     ■■     ■■■        ■■■    ■■■        ■■■     ■■■        ■■■  \n");
			gotoxy(15, 9);
			printf("    ■■■■■■■            ■■    ■■     ■■     ■■■        ■■■    ■■■■■■■■■       ■■■        ■■■  \n");
			gotoxy(15, 10);
			printf("         ■■■■■■         ■■    ■■     ■■     ■■■        ■■■    ■■■■■■■           ■■■        ■■■  \n");
			gotoxy(15, 11);
			printf("               ■■■■       ■■    ■■     ■■     ■■■        ■■■    ■■■    ■■■         ■■■        ■■■  \n");
			gotoxy(15, 12);
			printf("                 ■■■       ■■    ■■     ■■     ■■■        ■■■    ■■■      ■■■       ■■■        ■■■  \n");
			gotoxy(15, 13);
			printf("   ■          ■■■■       ■■    ■■   ■■       ■■■       ■■■     ■■■       ■■■      ■■■      ■■■    \n");
			gotoxy(15, 14);
			printf("   ■■■■■■■■■            ■■■   ■■■         ■■■■■■■■■     ■■■         ■■■    ■■■■■■■        \n");
			gotoxy(15, 15);
			printf("     ■■■■■■                 ■■     ■■            ■■■■■■■       ■■■■        ■■■   ■■■■■■          \n");



			gotoxy(30, 18);
			printf("         ■■■■                                                                           \n");
			gotoxy(30, 19);
			printf("      ■■■■■■■            ■■                ■■■■■                ■■         \n");
			gotoxy(30, 20);
			printf("    ■■■     ■■■         ■■■■            ■■■■■■■            ■■■■      \n");
			gotoxy(30, 21);
			printf("  ■■■          ■■      ■■■■■■         ■■■     ■■■        ■■■■■■    \n");
			gotoxy(30, 22);
			printf("  ■■■            ■    ■■■     ■■      ■■■        ■■■     ■■■     ■■   \n");
			gotoxy(30, 23);
			printf("    ■■■■             ■■■      ■■■   ■■■           ■      ■■■      ■■■ \n");
			gotoxy(30, 24);
			printf("    ■■■■■■■       ■■■■■■■■■  ■■■   ■■             ■■■■■■■■■ \n");
			gotoxy(30, 25);
			printf("         ■■■■■■    ■■■■■■■■■  ■■■   ■■■■■■■   ■■■■■■■■■ \n");
			gotoxy(30, 26);
			printf("               ■■■■  ■■■      ■■■  ■■■     ■■■■■■   ■■■      ■■■ \n");
			gotoxy(30, 27);
			printf("   ■            ■■■  ■■■      ■■■    ■■■           ■■   ■■■      ■■■ \n");
			gotoxy(30, 28);
			printf("   ■■■      ■■■■  ■■■      ■■■     ■■■          ■■   ■■■      ■■■ \n");
			gotoxy(30, 29);
			printf("   ■■■■■■■■■    ■■■      ■■■       ■■■■■■■■■   ■■■      ■■■ \n");
			gotoxy(30, 30);
			printf("     ■■■■■■        ■■■      ■■■         ■■■■■■■     ■■■      ■■■ \n");


			gotoxy(55, 40);
			printf("게임을 시작하려면 SAPCE를 눌러주세요.");

			if (GetAsyncKeyState(VK_SPACE)) {


				mciSendString(L"PLAY menu.mp3", NULL, 0, 0);
				system("cls");
				stages = 2;
			}
		}
		if (stages == 2) {
			while (1) {

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				setcursortype(NOCURSOR);

				if (GetAsyncKeyState(VK_SPACE)) {
					mciSendString(L"PLAY menu.mp3", NULL, 0, 0);

					if (presentCur.dwCursorPosition.Y == 15) {
						system("cls");
						MYSQL* conn = mysql_init(NULL);			//MYSQL 선언, 연결 초기화
						MYSQL_RES* result;
						MYSQL_ROW row;
						MYSQL_FIELD* field;
						int cntField, cntRow;

						connectionMYSQL(conn);					//MYSQL 연결 확인


						if (mysql_query(conn, "SELECT * FROM dbmain") != 0)	//쿼리문 입력 
							printf("MySQL 쿼리 에러: %s\n", mysql_error(conn)); //query실패 시 출력, mysql_query의 리턴값: 성공(0), 실패(0 이외)

						result = mysql_store_result(conn);				//MySQL 쿼리 결과 리턴
						if (result == NULL)
							printf("MySQL result값 에러: %s\n", mysql_error(conn)); //리턴 값이 NULL이면 에러 출력

						cntField = mysql_num_fields(result);			//테이블의 필드 수
						if (cntField == NULL)
							printf("MySQL cntField값 에러: %s\n", mysql_error(conn)); //리턴 값이 NULL이면 에러 출력

						cntRow = mysql_num_rows(result);				//테이블의 컬럼 수
						if (cntRow == NULL)
							printf("MySQL cntRow값 에러: %s\n", mysql_error(conn)); //리턴 값이 NULL이면 에러 출력

						struct user* u = (struct user*)malloc(sizeof(struct user) * cntRow);
						struct user user;
						//배열을 선언할 때 크기를 변수로 지정할 수 없다   ex) int arr[변수]
						//그래서 동적으로 배열을 선언을 해 준다 (구글에 "C언어 동적 배열" 검색)
						int i = 0;

						printf("접속할 계정 이름를 입력해주세요 : ");
						rewind(stdin);
						while (kbhit())//키보드에 버퍼 지워줌 (개사기)
							getch();
						scanf("%s", nickname);

						while ((row = mysql_fetch_row(result))) {		//쿼리 결과를 한줄 씩 얻기
							if (strcmp(row[0], nickname) == 0) {
								sprintf(user.name, row[0]);
								user.gold = atoi(row[1]);
								user.dskin1 = atoi(row[2]);
								user.dskin2 = atoi(row[3]);
								user.dskin3 = atoi(row[4]);
								user.dskin4 = atoi(row[5]);
								user.cwin = atoi(row[6]);
								user.lskin = atoi(row[7]);
							}
						}
						sprintf(nick, user.name);
						mygold = user.gold;
						skin1 = user.dskin1;
						skin2 = user.dskin2;
						skin3 = user.dskin3;
						skin4 = user.dskin4;

						system("cls");

						stages = 3;
						Sleep(100);
						//메모리 해제 명령어들
						free(u);
						mysql_free_result(result);

						mysql_close(conn);
						mysql_library_end;
					}


					if (presentCur.dwCursorPosition.Y == 18) {
						system("cls");
						connectionMYSQL(conn);

						printf("닉네임 : ");
						while (kbhit())//키보드에 버퍼 지워줌 (개사기)
							getch();
						scanf("%s", nick);
						sprintf(insertQuery, "insert into dbmain values ('%s',0,0,0,0,0,0,0)", nick);
						// insertQuery의 값: insert into student values ('닉네임', 나이)
						mysql_query(conn, insertQuery);
						system("cls");
						stages = 3;
						Sleep(100);
					}
				}
				gotoxy(70, 15);
				printf("계정 선택");
				gotoxy(70, 18);
				printf("계정 생성");

				if (s2sel == 0) {
					gotoxy(66, 15);
					printf("▷");
				}
				if (s2sel == 1) {
					gotoxy(66, 18);
					printf("▷");
				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x53) & 0x8000) { //
					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(100);
					if (s2sel != 1) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s2sel++;
						continue;
					}
					else {
						s2sel = 0;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}

				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x57) & 0x8000) { //위
					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(100);
					if (s2sel != 1) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s2sel++;
						continue;
					}
					else {
						s2sel = 0;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}
				}
				if (stages != 2) {
					gotoxy(66, 15);
					printf("              ");
					gotoxy(66, 18);
					printf("              ");
					break;
				}
			}

		}

		if (stages == 3) {
			while (1) {

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				setcursortype(NOCURSOR);

				if (mygold < 0) {
					system("cls");
					printf("계정 오류(없는 계정)");
					Sleep(2000);
					exit(0);
				}
				if (GetAsyncKeyState(VK_SPACE)) {
					mciSendString(L"PLAY menu.mp3", NULL, 0, 0);

					if (s3sel == 0)
						stages = 7;
					if (s3sel == 1)
						stages = 8;
					if (s3sel == 2)
						stages = 4;
					if (s3sel == 3)
						stages = 5;
					if (s3sel == 4) {
						MYSQL* conn = mysql_init(NULL);			//MYSQL 선언, 연결 초기화
						MYSQL_RES* result;
						MYSQL_ROW row;
						MYSQL_FIELD* field;
						int cntField, cntRow;

						connectionMYSQL(conn);

						sprintf(insertQuery, "UPDATE dbmain SET gold=%d,dskin1=%d,dskin2=%d,dskin3=%d,dskin4=%d where name='%s'"
							, mygold, skin1, skin2, skin3, skin4, nick);
						mysql_query(conn, insertQuery);



					}

				}

				gotoxy(70, 3);
				printf("개인 화면");
				gotoxy(12, 20);
				printf("1인 모드");
				gotoxy(12, 23);
				printf("2인 모드");
				gotoxy(12, 26);
				printf("스킨 선택");
				gotoxy(12, 29);
				printf("상점     ");
				gotoxy(12, 32);
				printf("저장 하기");
				gotoxy(118, 3);
				printf("환영합니다. %s 님", nick);
				gotoxy(75, 32);
				printf("PLAYER");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
				player(70, 15);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);



				if (s3sel == 0) {
					gotoxy(8, 20);
					printf("▷");
				}
				if (s3sel == 1) {
					gotoxy(8, 23);
					printf("▷");
				}
				if (s3sel == 2) {
					gotoxy(8, 26);
					printf("▷");
				}
				if (s3sel == 3) {
					gotoxy(8, 29);
					printf("▷");
				}
				if (s3sel == 4) {
					gotoxy(8, 32);
					printf("▷");
				}

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x53) & 0x8000) { //아래

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s3sel != 4) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s3sel++;
						continue;
					}
					else {
						s3sel = 0;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}

				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x57) & 0x8000) { //위

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s3sel != 0) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s3sel--;
						continue;
					}
					else {
						s3sel = 4;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}
				}

				if (stages != 3) {
					system("cls");
					break;
				}
			}

		}

		if (stages == 4) {
			while (1) {

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				setcursortype(NOCURSOR);

				if (GetAsyncKeyState(VK_SPACE)) {
					mciSendString(L"PLAY menu.mp3", NULL, 0, 0);
					if (presentCur.dwCursorPosition.Y == 13) {
						if (skin1 == 1) {
							fcolor = 9;
							stages = 3;
						}
						else {
							gotoxy(75, 20);
							printf("보유하고 있지않습니다!");
							Sleep(2000);
							gotoxy(75, 20);
							printf("                      ");
						}
					}
					if (presentCur.dwCursorPosition.Y == 16) {
						if (skin2 == 1) {
							fcolor = 12;
							stages = 3;
						}
						else {
							gotoxy(75, 20);
							printf("보유하고 있지않습니다!");
							Sleep(2000);
							gotoxy(75, 20);
							printf("                      ");
						}
					}
					if (presentCur.dwCursorPosition.Y == 19) {
						if (skin3 == 1) {
							fcolor = 14;
							stages = 3;
						}
						else {
							gotoxy(75, 20);
							printf("보유하고 있지않습니다!");
							Sleep(2000);
							gotoxy(75, 20);
							printf("                      ");
						}
					}
					if (presentCur.dwCursorPosition.Y == 22) {
						if (skin4 == 1) {
							fcolor = 10;
							stages = 3;
						}
						else {
							gotoxy(75, 20);
							printf("보유하고 있지않습니다!");
							Sleep(2000);
							gotoxy(75, 20);
							printf("                      ");
						}

					}
					if (presentCur.dwCursorPosition.Y == 25) {
						fcolor = 15;
						stages = 3;
					}

				}

				gotoxy(70, 3);
				printf("<스킨 선택>");
				gotoxy(12, 10);
				printf("ㅡㅡ스킨 목록ㅡㅡ");

				gotoxy(16, 13);
				printf(" 파랑 옷");
				gotoxy(16, 16);
				printf(" 화염 옷");
				gotoxy(16, 19);
				printf(" 금색 옷");
				gotoxy(16, 22);
				printf(" 초록 옷");
				gotoxy(16, 25);
				printf("스킨 해제");
				gotoxy(5, 2);
				printf("돌아가기(Enter)");

				if (skin1 == 0) {
					gotoxy(26, 13);
					printf("(미보유)");
				}
				if (skin2 == 0) {
					gotoxy(26, 16);
					printf("(미보유)");
				}
				if (skin3 == 0) {
					gotoxy(26, 19);
					printf("(미보유)");
				}
				if (skin4 == 0) {
					gotoxy(26, 22);
					printf("(미보유)");
				}



				if (s4sel == 0) {
					gotoxy(8, 13);
					printf("▷");
				}
				if (s4sel == 1) {
					gotoxy(8, 16);
					printf("▷");
				}
				if (s4sel == 2) {
					gotoxy(8, 19);
					printf("▷");
				}
				if (s4sel == 3) {
					gotoxy(8, 22);
					printf("▷");
				}
				if (s4sel == 4) {
					gotoxy(8, 25);
					printf("▷");
				}

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x53) & 0x8000) { //아래

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s4sel != 4) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s4sel++;
						continue;
					}
					else {
						s4sel = 0;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}

				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x57) & 0x8000) { //위

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s4sel != 0) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s4sel--;
						continue;
					}
					else {
						s4sel = 4;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}
				}
				if (GetAsyncKeyState(VK_RETURN)) {
					stages = 3;
				}
				if (stages != 4) {
					system("cls");
					break;
				}
			}

		}

		if (stages == 6) {
			while (1) {

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				setcursortype(NOCURSOR);

				if (GetAsyncKeyState(VK_SPACE) & presentCur.dwCursorPosition.Y == 29) {
					mciSendString(L"PLAY menu.mp3", NULL, 0, 0);

					stages = 7;
				}

				gotoxy(70, 3);
				printf("<던전 선택>");
				gotoxy(14, 10);
				printf("ㅡㅡ던전 목록ㅡㅡ");

				gotoxy(16, 13);
				printf(" 스테이지 1 ");
				gotoxy(16, 16);
				printf(" 스테이지 2 ");
				gotoxy(16, 19);
				printf(" 스테이지 3 ");



				if (s6sel == 0) {
					gotoxy(8, 13);
					printf("▷");
				}
				if (s6sel == 1) {
					gotoxy(8, 16);
					printf("▷");
				}
				if (s6sel == 2) {
					gotoxy(8, 19);
					printf("▷");
				}


				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x53) & 0x8000) { //아래

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s6sel != 2) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s6sel++;
						continue;
					}
					else {
						s6sel = 0;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}

				}
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				if (GetAsyncKeyState(0x57) & 0x8000) { //위

					mciSendString(L"PLAY cursor.mp3", NULL, 0, 0);
					Sleep(200);
					if (s6sel != 0) {
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						s6sel--;
						continue;
					}
					else {
						s6sel = 2;
						gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
						printf("  ");
						continue;
					}
				}
				if (GetAsyncKeyState(VK_RETURN)) {
					stages = 3;
				}
				if (stages != 6) {
					system("cls");
					break;
				}
			}

		}
		if (stages == 8) {
			while (1) {

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				setcursortype(NOCURSOR);


				gotoxy(65, 3);
				printf("<!! 개발중 입니다 !!>");
				mciSendString(L"PLAY fail.mp3", NULL, 0, 0);

				Sleep(2000);
				stages = 3;
				if (stages != 8) {
					system("cls");
					break;
				}
			}

		}
		if (stages == 7) {
			do {
				printf("select lv(1~3): ");
				while (kbhit())//키보드에 버퍼 지워줌 (개사기)
					getch();
				scanf("%d", &lv);
			} while (lv < 1 || lv >3);
			system("cls");
			if (lv == 1) {
				ground();
				bosslife = 15;
				while (life != 0 && bosslife != 0) {
				exit:
					ran = 0;
					ran2 = 0;
					ran3 = 0;
					ran4 = 0;
					if (life < 0)
						goto die;
					gotoxy(0, 0);
					printf("life:%d", life);
					gotoxy(ENEMYX, 0);
					printf("                                                              ");
					for (int i = 0; i < bosslife; i++) {
						gotoxy(ENEMYX + (i * 2), 0);
						printf("♡");
					}
					boss();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
					pstand();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(300);
					bossturn();
					Sleep(500);
					for (int i = 0; i < 2; i++) {//보스패턴
						ran2 = rand() % 3;
						if (ran2 == 2) {
							ran3 = rand() % 2;
							oldtime = clock();
							bskill(ran3);
							key = _getch();
							newtime = clock();
							if (ran3 == 1 && move[3] == key && difftime(newtime, oldtime) > BOSS1_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(key);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(300);
								pclear();
								clear;
								rewind(stdin);
								goto exit;
							}
							else if (ran3 == 0 && move[2] == key && difftime(newtime, oldtime) > BOSS1_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(key);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(300);
								pclear();
								clear();
								goto exit;
							}
							else {
								life -= 2;
								clear();
								rewind(stdin);
								goto exit;
							}

						}

					}
					for (int i = 0; i < 4; i++) {//보스 움직임 구현
						ran = rand() % 4;
						enemymove[i] = ran;
						clear();
						pattern(ran);
						Sleep(800);
						clear();
						boss();
						Sleep(800);
					}
					yourturn();
					for (int i = 0; i < 4; i++) {//내턴
						pclear();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
						pstand();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						_getch;
						key = _getch();//입력받기
						if (key == 'g' && guard > 0) {//가드 할시 가드게이지 깎이고 다음턴으로 넘어감
							guard -= 1;
							break;
						}
						if (move[enemymove[i]] != key) {//실패할 시 체력이 깎이고 보스턴으로 넘어감
							life -= 1;
							gotoxy(40, 10);
							printf("fail");
							Sleep(400);
							gotoxy(40, 10);
							printf("           ");
							break;
						}
						else if (move[enemymove[i]] == key) {// 보스 패턴을 하나씩 맞추면 보스 체력이 1씩 깎인다.
							bosslife -= 1;
							gotoxy(30 + (i * 2), 15);
							printf("%c", key);
							pclear();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
							pmove(key);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							Sleep(500);
						}
					}
					rewind(stdin);
					gotoxy(30, 15);
					printf("                        ");
					Sleep(300);
					pclear();
					if (life < 0)
						life = 0;
				}
			}//보스1
			if (lv == 2) {
				ground();
				bosslife = 20;
				while (life != 0 && bosslife != 0) {
				exit2:
					ran = 0;
					ran2 = 0;
					ran3 = 0;
					ran4 = 0;
					ran5 = 0;
					if (life < 0)
						goto die;
					gotoxy(0, 0);
					printf("life:%d", life);
					gotoxy(ENEMYX, 0);
					printf("                                                              ");
					for (int i = 0; i < bosslife; i++) {
						gotoxy(ENEMYX + (i * 2), 0);
						printf("♡");
					}
					clear();
					boss2();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
					pstand();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(300);
					bossturn();
					Sleep(500);

					ran3 = rand() % 2;
					if (ran3 == 0) {
						boss2p(ran3);
						Sleep(1000);
						ran2 = rand() % 3;
						if (ran2 == 2) {
							bskill2_1();
							oldtime = clock();
							_getch;
							newtime = clock();
							key = _getch();
							if (key == move[0] && difftime(newtime, oldtime) > BOSS2_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(key);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(150);
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove('d');
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(200);
								pclear();
								bosslife -= -3;
								goto exit2;
							}
							else {
								life -= 1;
								ran4 = rand() % 100;
								ran5 = rand() % 100;
								pclear();
								bskill2_2();
								gotoxy(ENEMYX - 5, 27);
								oldtime1 = clock();
								printf("%d + %d = ?", ran4, ran5);
								word = ran4 + ran5;
								gotoxy(PLAYER + 5, 28);
								scanf("%d", &keyword);
								newtime1 = clock();
								rewind(stdin);
								if (word == keyword && difftime(newtime1, oldtime1) > BOSS2_2_DL) {
									pclear();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
									pmove('d');
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									Sleep(400);
									pclear();
									bosslife -= -3;
									goto exit2;
								}
								else {
									pclear();
									pstand();
									life -= 2;
									goto exit2;
								}
							}
						}
						for (int i = 0; i < 4; i++) {//보스 움직임 구현
							ran = rand() % 4;
							enemymove[i] = ran;
							clear();
							boss2p(ran3);
							pattern2_1(ran);
							Sleep(600);
							clear();
							boss2p(ran3);
							boss2();
							Sleep(600);
						}
					}
					else {
						boss2p(ran3);
						Sleep(1000);
						ran2 = rand() % 3;
						if (ran2 == 2) {
							bskill2_1();
							oldtime = clock();
							_getch;
							newtime = clock();
							key = _getch();
							if (key == move[0] && difftime(newtime, oldtime) < BOSS2_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(key);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(150);
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove('d');
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(200);
								pclear();
								bosslife -= -3;
								goto exit2;
							}
							else {
								life -= 1;
								ran4 = rand() % 100;
								ran5 = rand() % 100;
								pclear();
								bskill2_2();
								gotoxy(ENEMYX - 5, 27);
								oldtime1 = clock();
								printf("%d + %d = ?", ran4, ran5);
								word = ran5 - ran4;
								gotoxy(PLAYER + 5, 28);
								scanf("%d", &keyword);
								newtime1 = clock();
								rewind(stdin);
								if (word == keyword && difftime(newtime, oldtime) < BOSS2_2_DL) {
									pclear();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
									pmove('d');
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									Sleep(400);
									pclear();
									bosslife -= -3;
									goto exit2;
								}
								else {
									pclear();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
									pstand();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									life -= 2;
									goto exit2;
								}
							}
						}
						for (int i = 0; i < 4; i++) {//보스 움직임 구현
							ran = rand() % 4;
							enemymove[i] = ran;
							clear();
							boss2p(ran3);
							pattern2_2(ran);
							Sleep(600);
							clear();
							boss2p(ran3);
							boss2();
							Sleep(600);
						}

					}
					yourturn();
					for (int i = 0; i < 4; i++) {//내턴
						pclear();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
						pstand();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						_getch;
						key = _getch();//입력받기
						if (key == 'g' && guard > 0) {//가드 할시 가드게이지 깎이고 다음턴으로 넘어감
							guard -= 1;
							break;
						}
						if (move[enemymove[i]] != key) {//실패할 시 체력이 깎이고 보스턴으로 넘어감
							life -= 1;
							gotoxy(40, 10);
							printf("fail");
							Sleep(400);
							gotoxy(40, 10);
							printf("           ");
							break;
						}
						else if (move[enemymove[i]] == key) {// 보스 패턴을 하나씩 맞추면 보스 체력이 1씩 깎인다.
							bosslife -= 1;
							gotoxy(30 + (i * 2), 15);
							printf("%c", key);
							pclear();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
							pmove(key);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							Sleep(500);
						}
					}
					rewind(stdin);
					gotoxy(30, 15);
					printf("                        ");
					Sleep(300);
					pclear();
				}
			}//보스3
			if (lv == 3) {
				ran = 0;
				ran2 = 0;
				ran3 = 0;
				ran4 = 0;
				ground();
				bosslife = 27;
				while (life != 0) {
				exit3:
					if (life < 0)
						goto die;
					gotoxy(0, 0);
					printf("life:%d", life);
					gotoxy(ENEMYX, 0);
					printf("                                                              ");
					for (int i = 0; i < bosslife; i++) {
						gotoxy(ENEMYX + (i * 2), 0);
						printf("♡");
					}
					boss3();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
					pstand();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(300);
					bossturn();
					Sleep(500);
					ran2 = rand() % 3;
					if (ran2 == 1) {
						ran3 = rand() % 2;
						clear();
						bskill3_1();
						Sleep(500);
						if (ran3 == 0) {
							clear();
							bskill3_2();
							oldtime = clock();
							_getch;
							newtime = clock();
							key = _getch();
							if (key = 'a' && difftime(newtime, oldtime) > BOSS3_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(0);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(150);
								pclear();
								goto exit3;
							}
							else {
								clear;
								life -= 2;
								goto exit3;
							}

						}
						else {
							clear();
							bskill3_3();
							oldtime = clock();
							_getch;
							newtime = clock();
							key = _getch();
							if (key = 'd' && difftime(newtime, oldtime) > BOSS3_DL) {
								pclear();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
								pmove(0);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(150);
								pclear();
								goto exit3;
							}
							else {
								clear();
								life -= 2;
								goto exit3;
							}
						}
					}
					for (int i = 0; i < 3; i++) {//보스 움직임 구현
						ran = rand() % 4;
						enemymove[i] = ran;
						clear();
						pattern3(ran);
						Sleep(120);
						clear();
						boss3();
						Sleep(120);
					}
					yourturn();
					for (int i = 0; i < 3; i++) {//내턴
						pclear();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
						pstand();
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						_getch;
						key = _getch();//입력받기
						if (key == 'g' && guard > 0) {//가드 할시 가드게이지 깎이고 다음턴으로 넘어감
							guard -= 1;
							break;
						}
						if (move[enemymove[i]] != key) {//실패할 시 체력이 깎이고 보스턴으로 넘어감
							life -= 1;
							gotoxy(40, 10);
							printf("fail");
							Sleep(400);
							gotoxy(40, 10);
							printf("           ");
							rewind(stdin);
							break;
						}
						else if (move[enemymove[i]] == key) {// 보스 패턴을 하나씩 맞추면 보스 체력이 1씩 깎인다.
							bosslife -= 1;
							gotoxy(30 + (i * 2), 15);
							printf("%c", key);
							pclear();
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fcolor);
							pmove(key);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							Sleep(500);
							rewind(stdin);
						}
					}
					gotoxy(30, 15);
					printf("                        ");
					Sleep(300);
					pclear();
					if (life < 0)
						life = 0;
				}
			}//보스3
		die:
			clear();
			if (life == 0)
				printf("DEAD");
			else {
				printf("YOU WIN");
				if (lv == 1)
					mygold += 100;
				if (lv == 2)
					mygold += 500;
				if (lv == 3)
					mygold += 1000;
				if (lv == 1)
					printf(" /보상으로 100골드를 얻습니다");
				if (lv == 2)
					printf(" /보상으로 500골드를 얻습니다");
				if (lv == 3)
					printf(" /보상으로 1000골드를 얻습니다");
			}
			Sleep(2000);
			stages = 3;
			system("cls");
			continue;
		}


		if (stages == 5) {
			while (1) {
				setcursortype(NOCURSOR);
				gotoxy(5, 2);
				printf("돌아가기(Enter)");
				gotoxy(65, 2);
				printf("♤ 상점 ♤");
				gotoxy(120, 2);
				printf("보유 Gold %5d", mygold);

				gotoxy(35, 10);
				printf("1. 파랑 옷        100 G");
				gotoxy(35, 12);
				printf("2. 화염 옷        200 G");
				gotoxy(35, 14);
				printf("3. 금색 옷        500 G");
				gotoxy(35, 16);
				printf("4. 초록 옷       1000 G");

				gotoxy(55, 29);
				printf("조작 - ↑:W   ↓:S   선택:SAPCE\n");
				gotoxy(32, 30);
				printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
				gotoxy(32, 31);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 32);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 33);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 34);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 35);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 36);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 37);
				printf("ㅣ                                                                          ㅣ\n");
				gotoxy(32, 38);
				printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

				if (buy == 0) {
					if (stosel == 0) {
						gotoxy(31, 10);
						printf("▷");
					}
					if (stosel == 1) {
						gotoxy(31, 12);
						printf("▷");
					}
					if (stosel == 2) {
						gotoxy(31, 14);
						printf("▷");
					}
					if (stosel == 3) {
						gotoxy(31, 16);
						printf("▷");
					}
					if (stosel == 4) {
						gotoxy(1, 2);
						printf("▷");
					}
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

					if (presentCur.dwCursorPosition.Y == 10) {
						gotoxy(33, 31);
						printf(" 행운의 파란색 옷!                                     ");
					}
					if (presentCur.dwCursorPosition.Y == 12) {
						gotoxy(33, 31);
						printf(" 화염으로 만든 옷. 뜨겁다                              ");
					}
					if (presentCur.dwCursorPosition.Y == 14) {
						gotoxy(33, 31);
						printf(" 금으로 만든 갑옷.(비싸)                               ");
					}
					if (presentCur.dwCursorPosition.Y == 16) {
						gotoxy(33, 31);
						printf(" 고인물의 증표.   오래되어 더럽다                      ");
					}

					if (GetAsyncKeyState(0x53) & 0x8000) { //아래
						Sleep(100);
						if (stosel != 3) {
							gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
							printf("  ");
							stosel++;
							continue;
						}
						else {
							stosel = 0;
							gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
							printf("  ");
							continue;
						}

					}
					if (GetAsyncKeyState(0x57) & 0x8000) { //위
						Sleep(100);
						if (stosel != 0) {
							gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
							printf("  ");
							stosel--;
							continue;
						}
						else {
							stosel = 3;
							gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
							printf("  ");
							continue;
						}

					}
					Sleep(10);
					if (GetAsyncKeyState(VK_RETURN)) {
						stages = 3;
					}
					if (stages != 5) {
						system("cls");
						break;
					}
					if (GetAsyncKeyState(VK_SPACE) & presentCur.dwCursorPosition.Y > 2) {
						buy = 1;
						while (1) {
							if (presentCur.dwCursorPosition.Y == 10) {
								gotoxy(34, 31);
								printf(" 파랑옷을 구입하시겠습니까 ?                           ");
								money = 100;
							}
							if (presentCur.dwCursorPosition.Y == 12) {
								gotoxy(34, 31);
								printf(" 화염옷을 구입하시겠습니까 ?                           ");
								money = 200;
							}
							if (presentCur.dwCursorPosition.Y == 14) {
								gotoxy(34, 31);
								printf(" 금색옷을 구입하시겠습니까 ?                           ");
								money = 500;
							}
							if (presentCur.dwCursorPosition.Y == 16) {
								gotoxy(34, 31);
								printf(" 초록옷을 구입하시겠습니까 ?                           ");
								money = 1000;
							}
							gotoxy(34, 36);
							printf("               예             아니요                      ");

							if (buysel == 0) {
								gotoxy(46, 36);
								printf("▷");
								gotoxy(46, 36);
							}
							if (buysel == 1) {
								gotoxy(60, 36);
								printf("▷");
								gotoxy(60, 36);
							}
							GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);

							if (GetAsyncKeyState(0x53) & 0x8000) { //아래
								Sleep(100);
								if (buysel == 1) {
									gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
									printf("  ");
									buysel = 0;
									continue;
								}
								else {
									buysel = 1;
									gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
									printf("  ");
									continue;
								}

							}
							if (GetAsyncKeyState(0x57) & 0x8000) { //위
								Sleep(100);
								if (buysel == 1) {
									gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
									printf("  ");
									buysel = 0;
									continue;
								}
								else {
									buysel = 1;
									gotoxy(presentCur.dwCursorPosition.X - 2, presentCur.dwCursorPosition.Y);
									printf("  ");
									continue;
								}

							}
							Sleep(100);
							if (GetAsyncKeyState(VK_SPACE)) {
								Sleep(70);
								if (presentCur.dwCursorPosition.X == 46) {
									buy = 0;
									if (money > mygold) {
										gotoxy(34, 31);
										printf("  보유 골드가 부족합니다!                            ");
									}
									else {
										gotoxy(34, 31);
										printf("  구매하였습니다                                         ");
										if (money == 100) {
											if (skin1 == 0) {
												skin1 = 1;
												mygold -= money;
											}
											else {
												gotoxy(34, 31);
												printf("  이미 보유중입니다.                                         ");
											}
										}
										if (money == 200) {
											if (skin2 == 0) {
												skin2 = 1;
												mygold -= money;
											}
											else {
												gotoxy(34, 31);
												printf("  이미 보유중입니다.                                         ");
											}
										}
										if (money == 500) {
											if (skin3 == 0) {
												skin3 = 1;
												mygold -= money;
											}
											else {
												gotoxy(34, 31);
												printf("  이미 보유중입니다.                                         ");
											}
										}
										if (money == 1000) {
											if (skin4 == 0) {
												skin4 = 1;
												mygold -= money;
											}
											else {
												gotoxy(34, 31);
												printf("  이미 보유중입니다.                                         ");
											}
										}

									}
									Sleep(1000);
									break;
								}
								if (presentCur.dwCursorPosition.X == 60) {
									buy = 0;
									gotoxy(34, 31);
									printf("  취소하였습니다.                                        ");
									buysel = 0;
									Sleep(1000);
									system("cls");
									break;
								}
							}


						}
					}
				}
				Sleep(10);
			}
		}
	}
	system("cls");
	printf("종료화면");

}