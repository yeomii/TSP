#ifndef _CPPUTIL_H_
#define _CPPUTIL_H_

#include <sys/types.h>
using namespace std;

	/** @name ������ ������ Ŭ���� */ 
	//@{            Start of DOC++ block
	/** �ɸ� �ð��� �����ϴ� Ŭ����. */
class CTimer
{
private:
		// ����� ������ �ð�
  time_t m_start;
		// ����� ������ ����, times()�� ���ϰ�
  time_t m_elapsedStart;
		// ���������� ����� �ߴ��� �ð�
  time_t m_end;
		// ����� �ߴ��� ����, times()�� ���ϰ�
  time_t m_elapsedEnd;

public:
		// �ð� ��� ����
	void        start();
		// start()�� �ɸ� �ð��� ��ȯ. which�� 0�̸� ����� �ð���, 1�̸� ���� �ɸ� �ð��� ��ȯ�Ѵ�.
	float       stop(int which=0);
		// ������ stop()�� ��ȯ�� ���� �״�� ������. which�� 0�̸� ����� �ð���, 1�̸� ���� �ɸ� �ð��� ��ȯ�Ѵ�.
	float       report(int which=0);
};

#define MIN_UPDATE      1
#define MAX_UPDATE      2

	// ���� ��ġ �ڷ���� ��յ����� ���ִ� Ŭ����
class CStat
{
private:
		// ���. 0�� �ƴϸ� ����չ��(�� ū ���� ��ް���). 0�̸� �ջ���.
	int         m_mode;
		// �ڷ� ��
	int         m_count;
		// �ڷ���� ��. $\sum x_i$. �ջ� ��Ŀ��� ����. 
	double       m_sum;
		// �ڷ���� ������ ��. $\sum x_i ^2$. �ջ� ��Ŀ��� ����.
	double       m_square_sum;
		// �ڷ���� �����(virtual avg). $\frac{\sum x_i}{n}$. ����� ���.
	double       m_vavg;
		// �ڷ���� ������ �����. $\frac{\sum {x_i}^2}{n}$. ����� ���.
	double       m_square_vavg;
		// ���� ���� �ڷ��� ��
	double       m_min_value;
		// ���� ū �ڷ��� ��
	double       m_max_value;
public:
		// ������
	CStat(int mode=0);
		// ��� �������� �ʱ�ȭ�Ѵ�
	void        setup();
		/* ������ �ϳ��� �߰��Ѵ�. 
		   @param  value  �߰��� ������
		   @return <0-3>. �� �ڷᰡ ���� ū �Ǵ� ���� �ڷ������� �˷��ش�.
		   ��ȯ���� MIN\_UPDATE, MAX\_UPDATE�� bitwise and�� �ϸ�
		   �� ���θ� �� �� �ִ�. */
	int         add(double value);
		// �ڷ���� ��ȯ
	int         getCount() { return m_count; }
		// ���� ���� �ڷ� ��
	double       getMin() { return m_min_value; }
		// ���� ū �ڷ� ��
	double       getMax() { return m_max_value; }
		// �ڷ���� ���� ��ȯ
	double       getSum() { return m_sum; }
		// �ڷ���� ����� ��ȯ
	double       getAvg();
		// ǥ�� ������ ��ȯ
	double       getStd();
		// 95\% �ŷڵ��� ������, ���̸� ����
	double       getCiv95();
		// 99\% �ŷڵ��� ������, ���̸� ����
	double       getCiv99();
		// �׷� ������ ��ȯ.
	double       getGrpStd();
		// ���ذ��� ���� ����� �󸶳� ������ ����� ���� ��ȯ�Ѵ�.
	double       getAbovePercent(double base);
};

	//@}       End of DOC++ block 
#endif























































