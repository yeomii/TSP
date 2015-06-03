#ifndef _LK_H
#define _LK_H

#include "macro.h"
#include "tsplib_io.h"
#include "tour.h"
#include "cpputil.h"

	/// 1�̸� �ӵ��� �������� ��ſ� ���� ���� ��������.
#define LK_MORE_SPEED        0
#define LK_DEPTH             40

	/////////////////////////////////////////////////////////////////////
	/** Lookbit Queue ������ Ŭ����.
		Johnson paper�� ������ lookbit queue�� �����Ͽ���. �� Ŭ������
		LK �˰���, 2-Opt, 3-Opt ��� ���� TSP�� ���� ����ȭ �˰�����
		���� �ӵ��� ������ �ϴ� �� �̿�ȴ�.
	*/
class CLookbitQueue
{
private:
		// lookbit ť
	int*            m_look_bit_queue;
		// lookbit ť�� ũ��
	int             m_size;
		// lookbit ť�� �Ӹ� �κ�
	int             m_look_head;
		// lookbit ť�� ���� �κ�
	int             m_look_tail;
	
public:
		// Lookbit Queue�� �����. size�� ���� ��.
	CLookbitQueue(int size);
	~CLookbitQueue();

		/* lookbit ť�� �ʱ� ��Ҹ� �����Ѵ�.
		   tour�� ���� ������� ��Ҹ� �����Ѵ�. tour���� � ������ 
		   incident edges�� c1,c2�� ���������� ��� ���� ����, �� ���ø�
		   �˰��򿡼� ������ �ʿ䰡 ����. �׷��Ƿ� �� ���ô� ť�� 
		   ���� �ʴ´�.
		   @param c1,c2 �� �� ���� ������ ����
		*/
	void    construct(C2EdgeTour* tour,
					  C2EdgeTour* c1=NULL, C2EdgeTour* c2=NULL);
		// ���� c�� look bit ť�� �߰��Ѵ�.
	void    addLookbit(int c);
		// ť���� ���� �ϳ��� ������. ��ȯ���� ���� ��ȣ �Ǵ� <0�� ��
	int     deleteLookbit();
};

	////////////////////////////////////////////////////////////////////////
	/** ���׸�Ʈ Ʈ�� Ŭ����.
		Johnson�� paper���� ���´�� �����Ͽ���. order������ ���
		C2EdgeTour���� ������ ����� ���� flip�� between��ɾ��� �ð� ���⵵��
		$K\cdot n$�̴�($K$�� ���� ũ��). �� �� ���׸�Ʈ Ʈ���� ����ϸ�
		K�� ���� ��ʹ�� ���� �� �ִ�.
	*/
class CSegmentTree
{
private:
		// segment tree�� �ٷ�� �ִ� ����
	C2EdgeTour*     _tour; 
		// ������ ���� ����;
	int             _n;
	
		// ���׸�Ʈ�� ��Ÿ���� ����ü
	struct SEGMENT
	{
			// reversal bit. 
		int         reversal;
			// �� ���׸�Ʈ�� ù��° ����
		int         first;
			// �� ���׸�Ʈ�� ������ ����
		int         last;
			// Ʈ���� ���ֵ� �� ���� �ڽ�
		SEGMENT*    left_child;
			// Ʈ���� ���ֵ� �� ������ �ڽ�
		SEGMENT*    right_child;
			// ����Ʈ�� ���ֵ� �� �ڱ� ���� ���׸�Ʈ
		SEGMENT*    prev;
			// ����Ʈ�� ���ֵ� �� �ڱ� ���� ���׸�Ʈ
		SEGMENT*    next;
	};
		// ���׸�Ʈ Ʈ���� ����ȴ�.
	SEGMENT         _seg_tree[(LK_DEPTH+2)*2];
		// ���׸�Ʈ Ʈ���� ��� ��
	int             _seg_size;
		// ���� ��ȣ -> ������ ������ �迭.
	int*            _city_order;
		// ���� ��ȣ -> �� ���ð� ���Ե� ���׸�Ʈ�� ������
	SEGMENT**       _loc_pointer;
		// ���� ��ȣ -> #_loc_pointer[����]#�� ���������� ���õ� �ð�. 
	int*            _time_stamp;
		// ���� �ð�. #_loc_pointer[����]#�� �� ���� ���������� ���õ� �ð��� ���� �ð��� ���ƾ߸� ��ȿ�ϴ�.
	int             _current_time;
	
public:
	CSegmentTree(int size);
	~CSegmentTree();

		// �ð� ������ �ʱ�ȭ�Ѵ�.
	void        initTimeStamping();
		// ������ ���� ��ȣ�� �����Ѵ�.
	void        setupCityOrder(C2EdgeTour* tour);
		// t�迭�� ���� i ������ŭ ���׸�Ʈ Ʈ���� Ű���. LK������ ����.
	void        setupTree(int i, int t[]);
		// ���׸�Ʈ Ʈ���ȿ��� 2-change
	void        do2Change(int a, int b, int c, int d);
		// ���׸�Ʈ Ʈ���ȿ��� 3-change
	void        do3Change(int t1, int t2, int t3, int t4,
							 int t5, int t6);
		// ���׸�Ʈ Ʈ���ȿ��� 4-change
	void        do4Change(int t1, int t2, int t3, int t4,
							 int t5, int t6, int t7, int t8);
		// city�� ���� ������ �ִ� ���ø� ��ȯ�Ѵ�.
	int         getNext(int city);
		// city�� �� ������ �ִ� ���ø� ��ȯ�Ѵ�.
	int         getPrev(int city);
		// start, end���� ���̿� middle�� �ִ°�?
	int         isBetween(int start, int middle, int end);
		// segment tree�� ������ �ݴ�� �ٲ۴�.
	void        reverseTree();

private:
		// ���� ��ȣ�� ���׸�Ʈ�� ã�´�.
	CSegmentTree::SEGMENT*findSegment(int city);
		// ������ ���� ��ȣ�� ���� ��ȣ�� ã�´�.
	int         getCityByOrder(int order, int referCity);
		// ���� c1, c2���̸� �� ���� ���׸�Ʈ�� ������.
	void        splitSegment(int c1, int c2);
		// start, end������ ���׸�Ʈ ����Ʈ���� �ڹٲ۴�.
	void        reverseSegment(SEGMENT* start, SEGMENT* end);
		// ����� �� Ʈ���ΰ�? debug�Լ�.
	int         isCorrect(); 
};

	/////////////////////////////////////////////////////////////////////////
	/** TSP�� Ǯ�� ���� ���� ����ȭ �˰��� ������ ���� �θ� Ŭ����.
		LK(Lin-Kernighan Algorithm), 2-Opt, 3-Opt�� ���� �˰�����
		���� �и� ������ �ִ�.
	*/
class CTSPLocalOpt
{
public:
		// ������. #num_city#�� ������ ��, #num_nn#�� ������ �̿� ������ ��
	CTSPLocalOpt(int num_city, int num_nn);
	virtual ~CTSPLocalOpt() { }
	
		/* ���� ����ȭ �˰����� �����ϴ� �������̽� �Լ�.
		   op1, op2, op3�� ������ �� �Լ��� �����ϴ� ���� ����ȭ �˰��򸶴�
		   ������� ����� �� �ִ�. �� ������ �˰��򸶴� �ٸ� �ǹ̷�
		   ����� �� �ִ�.
		   @param tour                ���� ����ȭ �˰����� ����� ����.
		   @param op1,op2,op3,op4,op5 �ɼ� �����.
		*/
	virtual void    run(C2EdgeTour* tour, C2EdgeTour* op1=NULL,
						C2EdgeTour* op2=NULL, C2EdgeTour* op3=NULL,
						C2EdgeTour* op4=NULL, C2EdgeTour* op5=NULL) = 0;

protected:
		// Segment tree ����
	CSegmentTree    m_segTree;
		// Lookbit ť ����
	CLookbitQueue   m_lookbitQueue;
		// ������ ��
	int             m_numCity;
		// �̿� ������ ��
	int             m_numNN;
};

	////////////////////////////////////////////////////////////////////////
	/// LK �˰����� ������ Ŭ����
class CLK : public CTSPLocalOpt
{
public:
		/// ������. #num_city#�� ���� ��, #num_nn#�� ������ �̿� ������ ��
	CLK(int num_city, int num_nn); 
	~CLK();

		/* LK�˰����� �����ϴ� �������̽� �Լ�.
		   p1, p2, best�� ���� �� NULL�̰ų� ���� �� NULL�� �ƴϾ�� �Ѵ�.
		   @param tour      LK�˰����� ����� ����
		   @param p1,p2     tour�� ����� �� �̿��� �θ��.     
		   @param best      ���ݱ��� ���� ���� ��
		*/
	void    run(C2EdgeTour* tour, C2EdgeTour* p1=NULL,
				C2EdgeTour* p2=NULL, C2EdgeTour* best=NULL,
				C2EdgeTour* worst=NULL, C2EdgeTour* other=NULL);
	
private:
		/**@name LK�˰����� �ٽ� �κ�.
		   Lin�� Kernighan�� ���� �����Ͽ���.
		*/  //@{ start block
		/// runLK()���� ���� tour
	C2EdgeTour*     m_tour;
		// ���� ����
	int             _i;
		// $G^*$�� ��� ���� ����
	int             _k;    
		// ���� ���������� �̵�(gain).
	double            *_G;     
		// $G^*$. ���ݱ��� ���� ���� gain.
	double _Gstar; 
		// t �迭. $t_1, t_2, t_3, ... $
	int*            t;
	
		// ������ ��
	int             _n;
		// ���� ����� �̿� ������ ��
	int             _nnn;  
	
        // $t_3$�� �� �� �ִ� �ĺ��� �����ϴ� ����ü
	struct LK_T3_CAND
	{
        int t3; int t4; int alter_t4; double gain;
	};
		// $t_3$ �ĺ��� ����
	int             _num_t3_cand_list;
		// $t_3$ �ĺ����� ����Ǿ� �ִ� �迭
	LK_T3_CAND*     _t3_cand_list;
	
        /** $t_5$�� �� �� �ִ� �ĺ��� �����ϴ� ����ü.
			#get_t5_cand_list()#������ t5, t6, gain������ �̿��ϰ�,
			#get_alter_t5_cand_list()#������ �� ���δ�. */
	struct LK_T5_CAND
	{
        int t5; int t6; int alter_t6; int t7; int t8;
        int code; double gain;
	};
		// $t_5$ �ĺ��� ����
	int             _num_t5_cand_list;
		// $t_5$ �ĺ����� ����Ǿ� �ִ� �迭
	LK_T5_CAND*     _t5_cand_list;

		// �־��� $t_1$���� ������ LK�� �����Ų��. improved�� ��� Ƚ��
	double do_lk_search(int t1, int improved);
		// �� ���� �������� �����Ѵ�. improved�� ���� ��� Ƚ��
	void    search_deeper(int improved);
		// $G^*$�� �ٲ� �� �ִ��� ���� ���Ѵ�.
	int     check_and_update(int improved);
		// ���� �������� k������ ��� �ǵ��� $G^*$�� �̵��� �򵵷� �Ѵ�.
	void    reverse_change_to_best(int improved);
		// ���� �������� to������ ��� �ǵ�����.
	void    reverse_change(int to);
		// $t_3$�ĺ����� ���Ѵ�.
	void    get_t3_cand_list();
		// $t_5$�ĺ����� ���Ѵ�.
	void    get_t5_cand_list();
		// ��� $t_5$�ĺ����� ���Ѵ�.
	void    get_alter_t5_cand_list();

		// 2-change�� �����Ѵ�.
	void    make_two_change(int improved);
		// 3-change�� �����Ѵ�.
	void    make_three_change(int improved);
		// 4-change�� �����Ѵ�.
	void    make_four_change(int improved);
		//@} end block
};
#endif
	
