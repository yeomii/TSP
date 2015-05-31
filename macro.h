#ifndef _MACRO_H_
#define _MACRO_H_

	/**@name �Ϲ������� ���̴� ��ũ�ε� */
	//@{ block start
extern "C"
{
#ifdef __sparc
    extern long int random(void);
	extern int gethostname(char *name, int namelen); 
    extern void srandom(unsigned int);
#endif
}


#ifndef SWAP
	/// x�� y�� ���� �¹ٲ۴�.
#define SWAP(x, y, t)   {t=x; x=y; y=t;}
#endif 

	/// TRUE
#define TRUE            1
	/// FALSE
#define FALSE           0
	/// BOOL type
typedef int BOOL;

	/// �Ǽ� x�� �ݿø��Ͽ� ������ �����.
#define nint(x)             ((int)((double)(x)+0.5))
	/// �Ǽ� x�� �Ҽ����� �߶� ������ �����.
#define cint(x)             ((int)(ceil(x)))

	/// x�� y�߿��� ���� ��
#define min(x, y)           ((x)<(y)?(x):(y))
	/// x�� y�߿��� ū ��
#define max(x, y)           ((x)<(y)?(y):(x))
		
	/// �������� ��Ÿ���� ���� ����ü
struct IntPair { int i1; int i2; };

	/// ���� 3�߽��� ��Ÿ���� ���� ����ü 
struct IntTriple { int i1; int i2; int i3; }; 

	/// (����, �Ǽ�)�� ��Ÿ���� ���� ����ü
struct IntFloat { int i; float f; };

	/// �Ǽ����� ��Ÿ���� ���� ����ü
struct FloatPair { float f1; float f2; };

	/** ���� ������ �Ѵ�.
		���� ���� �����͵��� ��Ʈ�� �� �̿��ϴ� ��ũ�� �Լ��̴�. increasing
		order ���İ� decreasing order ������ �� �� �� �� �ִ�. ������
		increasing order(���� ��, ��ó�� ��Ҵ� ���� ���� ����̴�.) ������
		�ϴ� ���̴�.\\
		##\\
		#     ELEMENT data[20];#\\
		#     data[0].dist = 5; data[1].dist = 3; data[2].dist = 9; ...#\\
		#     SORT(ELEMENT, data, 20, data[cur].dist < data[key].dist); #\\
		##\\
		cur������ ���� �񱳵Ǵ� ��Ҹ� ����Ű�� �ε����̰�, key������ ����
		ũ�ų� ���� ��Ҹ� ����Ű�� �ε����̴�. 
		���� ���, key�� ���� ���� ��Ҹ� ����Ű�� �ִ�.
		cur, key��� ������ �� ��ũ�� �ֺ����� �����ϸ�, side effect�� �����
		�����Ƿ� �����ؾ� �Ѵ�.
		@param type         ����� ��
		@param arr_name     ���ĵ� ��Ұ� �ִ� �迭
		@param size         ��� ����
		@param replace_cond ���� ��ҿ� key��Ҹ� �¹ٲٰ� �Ǿ�� �ϴ� ����
	*/
#define SORT(type, arr_name, size, replace_cond)                \
		{                                                       \
			int i, cur, key;                                    \
			type temp_;                                         \
			for( i=0; i<size-1; i++)                            \
			{                                                   \
				key = i;                                        \
				for( cur=i+1; cur<size; cur++)                  \
					if( replace_cond) key = cur;                \
				SWAP(arr_name[i], arr_name[key], temp_);        \
			}                                                   \
		}

	/** �ִ밪 �Ǵ� �ּҰ��� ���� �迭�� ������ �˾Ƴ���.
		� ����ü �Ǵ� �⺻ Ÿ���� �迭�߿��� ���ǿ� ���� �ִ밪 �Ǵ�
		�ּҰ��� ������ ����� ������ ������ ������ �����Ѵ�.
		������ ũ�Ⱑ 20�� data�迭�ȿ��� data[5~10]���̿� �ִ� ��� ��
		�ּҰ��� ã�� ���̴�(data[5], data[10]�� �񱳵ȴ�.) 
		minDistance��� ������ data�迭�߿���
		���� ���� ���� ������ ����� ���ΰ��� ������ �ȴ�.
		##\\
		#     ELEMENT data[20];#\\
		#     data[0].dist = 5; data[1].dist = 3; data[2].dist = 9; ...#\\
		#     GET_MINMAX(minDistance, 5, 10, data[cur].dist<data[key].dist);#\\
		##\\
		cur������ ���� �񱳵Ǵ� ��Ҹ� ����Ű�� �ε����̰�, key������ ����
		ũ�ų� ���� ��Ҹ� ����Ű�� �ε����̴�. 
		���� ���, key�� ���� ���� ��Ҹ� ����Ű�� �ִ�.
		cur, key��� ������ �� ��ũ�� �ֺ����� �����ϸ�, side effect�� �����
		�����Ƿ� �����ؾ� �Ѵ�.
		@param dest         ����� ����� ����. int���̾�� �Ѵ�.
		@param start,end    �迭���� ����� ������ ���۰� �� ���ΰ�
		@param cond         ���� ��ҿ� key��Ҹ� �¹ٲٰ� �Ǿ�� �ϴ� ����
	*/
#define GET_MINMAX(dest, start, end, cond)                      \
        {                                                       \
			int cur, key;                                       \
			key = (start);                                      \
			for( cur=key+1; cur<=(end); cur++)                  \
				if( cond) key = cur;                            \
			dest = key;                                         \
		}

			//@} block end
#endif







