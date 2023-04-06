#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int dep = -1, dest = -1; //출발역과 도착역 번호 받음
int peopleNum = 0; //총 인원 수

typedef struct { //역 이름과 역 번호 구조체
	char name[50]; //역 이름
	int num; //역 번호
}Station;

Station stations[9] = { //정차역 이름과 역 번호를 구조체로 선언
	{"서울", 0},
	{"광명", 1},
	{"천안아산", 2},
	{"오송", 3},
	{"대전", 4},
	{"동대구", 5},
	{"신경주", 6},
	{"울산", 7},
	{"부산", 8}
};

typedef struct {
	int num; //탑승 인원
	int general; //일반실 요금
	int total; //총 금액
}Fee;

Fee fees[4] = {
	{0,}, //유아의 수, 일반실 요금, 유아 총 금액 저장
	{0,}, //어린이의 수, 일반실 요금, 어린이 총 금액 저장
	{0,}, //성인의 수, 일반실 요금, 성인 총 금액 저장
	{0,} //경로의 수, 일반실 요금, 경로 총 금액 저장
};

int is_str_same(char *str1, char *str2) { //입력받은 이름과 동일한 역 찾기
	if (str1 == NULL || str2 == NULL) //하나라도 null이면 0 반환
		return 0;

	int len1 = strlen(str1); //구조체 속 역 이름의 길이
	int len2 = strlen(str2); //입력받은 역 이름의 길이

	if (len1 != len2) { //길이가 다르면 0 반환
		return 0;
	}

	for (int i = 0; i < len1; i++) {
		if (str1[i] != str2[i]) //i번째 자리의 문자가 서로 다르면 0 반환
			return 0;
	}

	return 1; //위 조건에 해당하지 않으면 1 반환
}

int generalFees[9][9] = { //일반실 성인 요금
	{ 0,},
	{ 8400,},
	{ 14100, 11600,},
	{ 18500, 16100, 8400,},
	{ 23700, 21200, 9600, 8400,},
	{ 43500, 41300, 29300, 24800, 19700,},
	{ 49300, 47100, 34900, 30700, 25800, 8400,},
	{ 53500, 51300, 40200, 34800, 30100, 10500, 8400,},
	{ 59800, 57700, 46500, 42200, 36200, 17100, 11000, 8400}
};

int main() {
	printf("<??μ? KTX ???? ??? ??? ???α??>\n\n");
	cost(); //cost 함수 호출
	return 0;
}

int cost() {
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < i; j++) {
			generalFees[j][i] = generalFees[i][j];
		}
	}

	personnelData(); //인원정보 받는 함수
	system("cls"); //콘솔창 지워줌
	route(); //출발역과 도착역 받는 함수

	fees[0].general = generalFees[dep][dest] * 0.25; //유아 일반실 요금 = 성인 요금의 75% 할인
	fees[1].general = generalFees[dep][dest] * 0.5; //어린이 일반실 요금 = 성인 요금의 50% 할인
	fees[2].general = generalFees[dep][dest]; //성인 일반실 요금
	fees[3].general = generalFees[dep][dest] * 0.7; //경로 일반실 요금 = 성인 요금의 30% 할인

	for (int i = 0; i < 4; i++) {
		if ((fees[i].general % 10) != 0) { //일반실 요금 일의 자리 수는 무조건 0으로 반환
			fees[i].general -= fees[i].general % 10;
		}

		if ((fees[i].general % 100) != 0) { //일반실 요금 십의 자리 수에서 반올림
			if ((fees[i].general % 100) >= 5) {
				fees[i].general = (fees[i].general + 50) / 100 * 100; //십의 자리 숫자가 5이상이면 50 더해준 뒤 100으로 나누어주면 일의 자리와 십의 자리 사라지고, 거기에 다시 100 곱해줌
			}
			else {
				fees[i].general -= fees[i].general % 100; //십의 자리 수 5미만이면 빼줌
			}
		}
	}

	system("cls"); //콘솔창 지워줌

	printf("\n[ 경부선 KTX 일반실 요금표(1인 기준) ]\n");
	printf("\n\t유아\t\t%6d\n", fees[0].general);
	printf("\n\t어린이\t\t%6d\n", fees[1].general);
	printf("\n\t어른\t\t%6d\n", fees[2].general);
	printf("\n\t경로\t\t%6d\n\n\n", fees[3].general);

	generalTotal();
	
	return 0;
}

int personnelData() {  
	while (1) {
		printf("유아의 수를 입력하시오.(만 6세 미만, 유아석 선택시): ");
		scanf("%d", &fees[0].num);
		printf("어린이의 수를 입력하세요.(만 6세 이상 ~ 13세 미만): ");
		scanf("%d", &fees[1].num);
		printf("어른의 수를 입력하세요.: ");
		scanf("%d", &fees[2].num);
		printf("노인의 수를 입력하세요.(만 65세 이상): ");
		scanf("%d", &fees[3].num);

		for (int i = 0; i < 4; i++) { //유아, 어린이, 어른, 노인의 수 모두 더해줌
			peopleNum += fees[i].num;
		}

		if (peopleNum > 9) { //최대 9개까지 승차권 예매 가능
			printf("승차권 예약은 9매까지 가능합니다. 인원을 확인해주세요.\n\n");
			peopleNum = 0; //0으로 다시 초기화
			personnelData(); //재귀 함수 호출
		}
		else {
			if ((fees[0].num > 0 && fees[2].num == 0) && (fees[0].num > 0 && fees[3].num == 0)) { //유아가 탑승하는데 보호자 없으면 탑승 불가능
				printf("유아는 반드시 보호자와 함께 탑승하여야 합니다.\n\n");
				personnelData(); //재귀 함수 호출
			}
		}
		break;
	}
	return 0;
}

int route() { //경로 받는 함수
	printf("----------------------------------------------------------------------------\n");
	printf("정차역: 서울 - 광명 - 천안아산 - 오송 - 대전 - 동대구 - 신경주 - 울산 - 부산\n");
	printf("----------------------------------------------------------------------------\n");

	startStation(); //출발역 받는 함수 호출
	arrivalStation(); //도착역 받는 함수 호출
	
	return 0;
}

int startStation() { //출발역 받는 함수
	char start[100]; //???? ??? ?迭

	printf("출발역을 입력하세요.: ");
	scanf("%s", start); //출발역 받는 배열

	for (int i = 0; i < 9; i++) { //i는 역 번호
		if (is_str_same(stations[i].name, start)) { //입력한 역이 정차역 중 존재하면 i를 dep에 넣어줌
			dep = i;
			return 0;
		}
	}

	if (dep == -1) {
		printf("해당역이 존재하지 않습니다. ");
		startStation(); //재귀 함수 호출
	}

	return 0;
}

int arrivalStation() {
	char arrival[100]; //도착역 받는 배열

	printf("도착역을 입력하세요.: ");
	scanf("%s", arrival); //도착역 이름 입력

	for (int i = 0; i < 9; i++) { //i는 역 번호와 동일
		if (is_str_same(stations[i].name, arrival)) { //입력한 역이 정차역 중 존재하면 i를 dest에 넣어줌
			dest = i;
			return 0;
		}
	}

	if(dest == -1) {
		printf("해당역이 존재하지 않습니다. ");
		arrivalStation(); //재귀 함수 호출
	}

	if (dep == dest) { //dep와 dest가 동일하면 출발역과 도착역 동일(역 번호 동일)
		printf("출발역과 도착역이 동일합니다. ");
		arrivalStation(); //재귀 함수 호출
	}

	return 0;
}

int generalTotal() {
	int total = 0; //총 금액 저장할 변수

	for (int i = 0; i < 4; i++) {
		fees[i].total = fees[i].general * fees[i].num; //연령대에 따라 구해진 특실 값에 해당 연령 인원 수를 곱하여 총 금액에 넣어줌
		total += fees[i].total; //연령별 총 금액 더해서 총 결제 금액 구함
	}

	printf("\n출발역: %s역\n", stations[dep].name);
	printf("도착역: %s역\n", stations[dest].name);
	printf("예약매수: %d매\n", peopleNum);
	printf("총 결제금액: %d원\n", total);

	return 0;
}