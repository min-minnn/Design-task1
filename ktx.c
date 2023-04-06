#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int dep = -1, dest = -1; //��߿��� ������ ��ȣ ����
int peopleNum = 0; //�� �ο� ��

typedef struct { //�� �̸��� �� ��ȣ ����ü
	char name[50]; //�� �̸�
	int num; //�� ��ȣ
}Station;

Station stations[9] = { //������ �̸��� �� ��ȣ�� ����ü�� ����
	{"����", 0},
	{"����", 1},
	{"õ�Ⱦƻ�", 2},
	{"����", 3},
	{"����", 4},
	{"���뱸", 5},
	{"�Ű���", 6},
	{"���", 7},
	{"�λ�", 8}
};

typedef struct {
	int num; //ž�� �ο�
	int general; //�Ϲݽ� ���
	int total; //�� �ݾ�
}Fee;

Fee fees[4] = {
	{0,}, //������ ��, �Ϲݽ� ���, ���� �� �ݾ� ����
	{0,}, //����� ��, �Ϲݽ� ���, ��� �� �ݾ� ����
	{0,}, //������ ��, �Ϲݽ� ���, ���� �� �ݾ� ����
	{0,} //����� ��, �Ϲݽ� ���, ��� �� �ݾ� ����
};

int is_str_same(char *str1, char *str2) { //�Է¹��� �̸��� ������ �� ã��
	if (str1 == NULL || str2 == NULL) //�ϳ��� null�̸� 0 ��ȯ
		return 0;

	int len1 = strlen(str1); //����ü �� �� �̸��� ����
	int len2 = strlen(str2); //�Է¹��� �� �̸��� ����

	if (len1 != len2) { //���̰� �ٸ��� 0 ��ȯ
		return 0;
	}

	for (int i = 0; i < len1; i++) {
		if (str1[i] != str2[i]) //i��° �ڸ��� ���ڰ� ���� �ٸ��� 0 ��ȯ
			return 0;
	}

	return 1; //�� ���ǿ� �ش����� ������ 1 ��ȯ
}

int generalFees[9][9] = { //�Ϲݽ� ���� ���
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
	printf("<??��? KTX ???? ??? ??? ???��??>\n\n");
	cost(); //cost �Լ� ȣ��
	return 0;
}

int cost() {
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < i; j++) {
			generalFees[j][i] = generalFees[i][j];
		}
	}

	personnelData(); //�ο����� �޴� �Լ�
	system("cls"); //�ܼ�â ������
	route(); //��߿��� ������ �޴� �Լ�

	fees[0].general = generalFees[dep][dest] * 0.25; //���� �Ϲݽ� ��� = ���� ����� 75% ����
	fees[1].general = generalFees[dep][dest] * 0.5; //��� �Ϲݽ� ��� = ���� ����� 50% ����
	fees[2].general = generalFees[dep][dest]; //���� �Ϲݽ� ���
	fees[3].general = generalFees[dep][dest] * 0.7; //��� �Ϲݽ� ��� = ���� ����� 30% ����

	for (int i = 0; i < 4; i++) {
		if ((fees[i].general % 10) != 0) { //�Ϲݽ� ��� ���� �ڸ� ���� ������ 0���� ��ȯ
			fees[i].general -= fees[i].general % 10;
		}

		if ((fees[i].general % 100) != 0) { //�Ϲݽ� ��� ���� �ڸ� ������ �ݿø�
			if ((fees[i].general % 100) >= 5) {
				fees[i].general = (fees[i].general + 50) / 100 * 100; //���� �ڸ� ���ڰ� 5�̻��̸� 50 ������ �� 100���� �������ָ� ���� �ڸ��� ���� �ڸ� �������, �ű⿡ �ٽ� 100 ������
			}
			else {
				fees[i].general -= fees[i].general % 100; //���� �ڸ� �� 5�̸��̸� ����
			}
		}
	}

	system("cls"); //�ܼ�â ������

	printf("\n[ ��μ� KTX �Ϲݽ� ���ǥ(1�� ����) ]\n");
	printf("\n\t����\t\t%6d\n", fees[0].general);
	printf("\n\t���\t\t%6d\n", fees[1].general);
	printf("\n\t�\t\t%6d\n", fees[2].general);
	printf("\n\t���\t\t%6d\n\n\n", fees[3].general);

	generalTotal();
	
	return 0;
}

int personnelData() {  
	while (1) {
		printf("������ ���� �Է��Ͻÿ�.(�� 6�� �̸�, ���Ƽ� ���ý�): ");
		scanf("%d", &fees[0].num);
		printf("����� ���� �Է��ϼ���.(�� 6�� �̻� ~ 13�� �̸�): ");
		scanf("%d", &fees[1].num);
		printf("��� ���� �Է��ϼ���.: ");
		scanf("%d", &fees[2].num);
		printf("������ ���� �Է��ϼ���.(�� 65�� �̻�): ");
		scanf("%d", &fees[3].num);

		for (int i = 0; i < 4; i++) { //����, ���, �, ������ �� ��� ������
			peopleNum += fees[i].num;
		}

		if (peopleNum > 9) { //�ִ� 9������ ������ ���� ����
			printf("������ ������ 9�ű��� �����մϴ�. �ο��� Ȯ�����ּ���.\n\n");
			peopleNum = 0; //0���� �ٽ� �ʱ�ȭ
			personnelData(); //��� �Լ� ȣ��
		}
		else {
			if ((fees[0].num > 0 && fees[2].num == 0) && (fees[0].num > 0 && fees[3].num == 0)) { //���ư� ž���ϴµ� ��ȣ�� ������ ž�� �Ұ���
				printf("���ƴ� �ݵ�� ��ȣ�ڿ� �Բ� ž���Ͽ��� �մϴ�.\n\n");
				personnelData(); //��� �Լ� ȣ��
			}
		}
		break;
	}
	return 0;
}

int route() { //��� �޴� �Լ�
	printf("----------------------------------------------------------------------------\n");
	printf("������: ���� - ���� - õ�Ⱦƻ� - ���� - ���� - ���뱸 - �Ű��� - ��� - �λ�\n");
	printf("----------------------------------------------------------------------------\n");

	startStation(); //��߿� �޴� �Լ� ȣ��
	arrivalStation(); //������ �޴� �Լ� ȣ��
	
	return 0;
}

int startStation() { //��߿� �޴� �Լ�
	char start[100]; //???? ??? ?��

	printf("��߿��� �Է��ϼ���.: ");
	scanf("%s", start); //��߿� �޴� �迭

	for (int i = 0; i < 9; i++) { //i�� �� ��ȣ
		if (is_str_same(stations[i].name, start)) { //�Է��� ���� ������ �� �����ϸ� i�� dep�� �־���
			dep = i;
			return 0;
		}
	}

	if (dep == -1) {
		printf("�ش翪�� �������� �ʽ��ϴ�. ");
		startStation(); //��� �Լ� ȣ��
	}

	return 0;
}

int arrivalStation() {
	char arrival[100]; //������ �޴� �迭

	printf("�������� �Է��ϼ���.: ");
	scanf("%s", arrival); //������ �̸� �Է�

	for (int i = 0; i < 9; i++) { //i�� �� ��ȣ�� ����
		if (is_str_same(stations[i].name, arrival)) { //�Է��� ���� ������ �� �����ϸ� i�� dest�� �־���
			dest = i;
			return 0;
		}
	}

	if(dest == -1) {
		printf("�ش翪�� �������� �ʽ��ϴ�. ");
		arrivalStation(); //��� �Լ� ȣ��
	}

	if (dep == dest) { //dep�� dest�� �����ϸ� ��߿��� ������ ����(�� ��ȣ ����)
		printf("��߿��� �������� �����մϴ�. ");
		arrivalStation(); //��� �Լ� ȣ��
	}

	return 0;
}

int generalTotal() {
	int total = 0; //�� �ݾ� ������ ����

	for (int i = 0; i < 4; i++) {
		fees[i].total = fees[i].general * fees[i].num; //���ɴ뿡 ���� ������ Ư�� ���� �ش� ���� �ο� ���� ���Ͽ� �� �ݾ׿� �־���
		total += fees[i].total; //���ɺ� �� �ݾ� ���ؼ� �� ���� �ݾ� ����
	}

	printf("\n��߿�: %s��\n", stations[dep].name);
	printf("������: %s��\n", stations[dest].name);
	printf("����ż�: %d��\n", peopleNum);
	printf("�� �����ݾ�: %d��\n", total);

	return 0;
}