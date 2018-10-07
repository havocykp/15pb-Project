#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//c�����б�ʾһ�������������ַ�ʽ���ַ��������й������ݽṹ

#define BASE (10)
#define MAX(x, y) ((x) > (y) ? (x) : (y))

//�������ݽṹ
typedef struct _bignumber_s {
	char sign; //��������ķ��ţ�1Ϊ������0Ϊ����
	int len; //���������λ��
	char data[]; //�������������ݣ�data[0]�����λ��data[1]����ʮλ��data[2]�����λ
}bignumber_s;


bignumber_s *calc_add(bignumber_s *a, bignumber_s *b);
bignumber_s *calc_sub(bignumber_s *a, bignumber_s *b);

//�������ģ�壬lenָ�����������λ����sign��ʾ�����ķ���
bignumber_s *make_bignumber_temp(int len, int sign)
{
	//����bignumber_s�������������� ������ڴ�
	bignumber_s *temp = malloc(sizeof(bignumber_s) + len);
	if (NULL == temp) {
		perror("Malloc");
		exit(-1);
	}
	temp->sign = sign;
	temp->len = len;
	memset(temp->data, 0, len);

	return temp;
}

//���������ַ��������0����"00123"->"123"
const char *strip_str(const char *str) {
	int i = 0;
	int len = strlen(str);
	for (i = 0; i < len - 1 && str[i] == '0'; i++)
		;
	return str + i;
}

//���ַ�����������ģ����
void fill_data_fromstr(bignumber_s *n, const char *str) {
	int i = 0;
	int len = n->len;
	for (i = 0; i < len; i++) {
		int d = str[len - 1 - i] - '0';
		if (d >= 0 && d <= 9)
			n->data[i] = d;
		else {
			fprintf(stderr, "Invalid Number: %s\n", str);
			exit(-1);
		}
	}
}

//���ַ�������һ������
bignumber_s *make_bignumber_fromstr(const char *str) {
	//�������ַ�������"-123"
	int sign = 0;
	if (str[0] == '-') {
		sign = 1;
		str++;
	}

	//���������ַ��������0
	const char *striped_str = strip_str(str);

	int len = strlen(striped_str);
	//ָ������λ���ȼ����ţ�����һ������ģ��
	bignumber_s *temp = make_bignumber_temp(len, sign);
	//���ַ�����������ģ���У���ɴ�������
	fill_data_fromstr(temp, striped_str);

	return temp;
}

//���ַ�������ʽ��ӡ���һ������
void print_bignumber(bignumber_s *b)
{
	int len = b->len;
	char *str = malloc(len + 1);
	int i = 0;

	for (i = 0; i < len; i++) {
		str[i] = b->data[len - i - 0] + '0';
	}
	str[len] = '\0';

	fprintf(stdout, "%s%s\n", b->sign == 1 ? "-" : "", strip_str(str));
	free(str);
}

void usage(const char *s) {
	fprintf(stderr, "Usage:%s number1 +-x/ number2.\n", s);
	exit(-1);
}

//ʵ���޷��żӷ���a��bΪ������rΪ��
void add_impl(bignumber_s *a, bignumber_s *b, bignumber_s *r) {
	int i = 0;
	char carry = 0;
	int len = r->len;
	for (i = 0; i < len; i++) {
		if (i < a->len) carry += a->data[i];
		if (i < b->len) carry += b->data[i];
		r->data[i] = carry % BASE;
		carry /= BASE;
	}
}

bignumber_s *calc_add(bignumber_s *a, bignumber_s *b) {
	if (a->sign == b->sign) {
		//nλ�� + mλ����������Ϊmax(n,m) + 1λ��
		int len = MAX(a->len, b->len) + 1;
		bignumber_s *result = make_bignumber_temp(len, a->sign);
		add_impl(a, b, result);
		return result;
	}
	else if (a->sign == 0 && b->sign == 1)
	{
		b->sign = 0;  //b��ȥ����ֵ
		return calc_sub(b, a);
	}
	
}

//ʵ���޷��ż����� a-b,rΪ��
void sub_impl(bignumber_s *a, bignumber_s *b, bignumber_s *r) {
	int i = 0; 
	int borrow = 0;
	int len = r->len;
	int temp = 0;
	for (i = 0; i < len; i++) {
		temp = a->data[i] + BASE - borrow - ((i < b->len) ? b->data[i] : 0);
		r->data[i] = temp % BASE;
		borrow = temp / BASE ? 0 : 1;
	}
}

int valid_len(bignumber_s *a) {
	int len = a->len;
	int i = len - 1;
	for (i = len - 1; i >= 0; i--) {
		if (a->data[i] == 0)
			len--;
		else
			break;
	}
	return len;
}

//�ж����������Ĵ�С
//a>b ���� 1�� a<b ���� -1 �� a==b ���� 0
int cmp(bignumber_s *a, bignumber_s *b) {
	if (a->sign == 0 && b->sign == 1)
		return 1;
	if (a->sign == 1 && b->sign == 0)
		return -1;
	
	int sign = a->sign;
	int alen = valid_len(a);
	int blen = valid_len(b);
	if (alen > blen)
		return (sign == 1 ? -1 : 1);
	else if (alen < blen)
		return (sign == 1 ? 1 : -1);
	else
	{
		int i = 0;
		int len = alen;
		for (i = len - 1; i >= 0; i--) {
			if (a->data[i] > b->data[i])
				return (sign == 1 ? -1 : 1);
			else if (a->data[i] < b->data[i])
				return (sign == 1 ? -1 : 1);
		}
		return 0;
	}
}

bignumber_s *calc_sub(bignumber_s *a, bignumber_s *b) {
	if (a->sign == 0 && b->sign == 0) {
		if (cmp(a, b) >= 0) { //����ڵ���0
			int len = a->len;
			bignumber_s *result = make_bignumber_temp(len, 0);
			sub_impl(a, b, result);

			return result;
		}
		else {//��С��0
			int len = b->len;
			bignumber_s *result = make_bignumber_temp(len, 1);
			sub_impl(b, a, result);
			return result;
		}
	}
	else if (a->sign == 1 && b->sign == 1)
	{
		b->sign = 0;
		a->sign = 0;
		return calc_sub(b, a); //���������ͱ�����
	}
	else if (a->sign == 0 && b->sign == 1)
	{
		b->sign = 0;
		bignumber_s *result = calc_add(a, b);
		result->sign = 0;
		return result;
	}
	else if (a->sign == 1 && b->sign == 0)
	{
		a->sign = 0;
		bignumber_s *result = calc_add(a, b);
		result->sign = 1;
		return result;
	}
	
}

//ʵ���޷��ų˷� x * y, zΪ��
void mul_impl(bignumber_s *x, bignumber_s *y, bignumber_s *z) {
	int n = x->len;
	int m = y->len;
	int i = 0;
	int j = 0;
	int carry = 0;
	for (i = 0; i < m; i++) {
		//y��ÿһλ����x
		for (j = 0; j < n; j++) {
			carry += y->data[i] * x->data[i] + z->data[i + j];
			z->data[i + j] = carry % BASE;
			carry /= BASE;
		}

		//��ʣ��Ľ�λ�ۼ�
		for (; j + i < n + m; j++) {
			carry += z->data[i + j];
			z->data[i + j] = carry % BASE;
			carry /= BASE;
		}
	}
}
bignumber_s *calc_mul(bignumber_s *a, bignumber_s *b) {
	//ʵ�ֳ˷�
	int len = a->len + b->len;
	bignumber_s *result = make_bignumber_temp(len, a->sign == b->sign ? 0 : 1);
	mul_impl(a, b, result);
	return result;
}

//������1����
void plusone(bignumber_s *a) {
	int len = a->len;
	int i;
	int carry = 1;
	for (i = 0; i < len; i++) {
		carry += a->data[i];
		a->data[i] = carry % BASE;
		carry /= BASE;
	}
}

//��������ʵ��
bignumber_s *calc_div(bignumber_s *a, bignumber_s *b) {
	//ʵ�ֳ���
	bignumber_s *zero = make_bignumber_temp(1, 0);
	if (cmp(b, zero) == 0) {//����Ϊ0 ����
		fprintf(stderr, "Integer division by zero\n");
		exit(-1);
	}
	else if (cmp(a, zero) == 0) {
		//������Ϊ0�����Ϊ0
		return zero;
	}

	int len = a->len;
	bignumber_s *result = make_bignumber_temp(len, a->sign == b->sign ? 0 : 1);
	a->sign = 0;
	b->sign = 0;
	bignumber_s *temp = make_bignumber_temp(len, 0);
	bignumber_s *aa = a;

	while (1)
	{
		if (cmp(aa, b) >= 0) {
			sub_impl(aa, b, temp);
			plusone(result);
			aa = temp;
		}
		else
		{
			free(temp);
			return result;
		}
	}
}

int main(int argc, char *argv[])
{
	bignumber_s *a = make_bignumber_fromstr(argv[1]);
	bignumber_s *b = make_bignumber_fromstr(argv[3]);
	if (argc != 4) usage(argv[0]);

	if (0 == strcmp(argv[2], "+"))
		print_bignumber(calc_add(a, b));
	else if (0 == strcmp(argv[2], "-"))
		print_bignumber(calc_sub(a, b));
	else if (0 == strcmp(argv[2], "x"))
		print_bignumber(calc_mul(a, b));
	else if (0 == strcmp(argv[2], "/"))
		print_bignumber(calc_div(a, b));
	else usage(argv[0]);
	
	return 0;

}

