#ifndef _TOUR_H
#define _TOUR_H

	/** TSP(STSP, ATSP �� ��)���� ���Ǵ� ������� �θ� Ŭ����. 
		STSP, ATSP �� �ٿ��� ���������� �ʿ��� �Լ����� ������ �ִ�.
		ATSP�� ��� (v1, v2)�� (v2, v1)������ �ٸ��� ��޵ǹǷ�,
		�Լ����� �� ���ø� �μ��� �޴� ��� ������ �����Ͽ��� �Ѵ�. */
class CTour
{
 private:
		// findEdgeFirst, findEdgeNext���� ���̴� traversal�� ���� ���� ����.
	int        m_edge_start;
	int        m_edge_v1; 

protected:
		// ���� ���
	double        m_length;
		// ������ �� 
	int        m_size;
public:
		// ������
	CTour();

		/**@name ���� �Լ���.
		   �ڽ� Ŭ�������� �� �Լ����� �����ؾ� �Ѵ�. Ư��, ���� �����Լ�����
		   �ݵ�� �����Ǿ�� �Ѵ�. */ 
		//@{ start DOC++ block
		/// �� ����� tour������ �ع� �Ÿ��� ��ȯ�Ѵ�.
	virtual int  getHammingDist(CTour* tour);
		// ���� ��� �����.
	virtual void makeRandomTour()=0;
		// Edge(v1, v2)�� �ִ°�?
	virtual int  isThereEdge(int v1, int v2)=0;
		// ���ø� �����ϱ� ���Ͽ� �غ��ϴ� �Լ�. ���� start���� �����ȴ�.
	virtual void findFirst(int start)=0;
		// ���� ���ø� ��ȯ�Ѵ�.
	virtual int  findNext()=0;
		// �����ϰ� ������ �����ΰ�?
	virtual int  isTour()=0;
		/** order�������� �� ��� �� Ÿ���� ����� ��ȯ�Ѵ�.
			@param src order������ ����
			@param size src�� ũ��. #m_size#�� ���ƾ� �Ѵ�.
		*/
	virtual void convertFromOrder(int* src, int size)=0;

		// two-change�� �ϴ� �Լ�
	virtual void make2Change(int v1, int n1, int v2, int n2) {}
		// three-change�� �ϴ� �Լ�
	virtual void make3Change(int v1, int n1, int v2, int n2,
							 int v3, int n3) {}
		// four-change�� �ϴ� �Լ�
	virtual void make4Change(int v1, int n1, int v2, int n2,
							 int v3, int n3, int v4, int n4) {}
		//@} end of DOC++ block

		/// ���� ����� ����Ѵ�.
	double evaluate();
		// ������ ������ �����Ѵ�.
	int          getSize() const { return m_size; };
		// ���� ����� ��ȯ�Ѵ�.
	double       getLength() const { return m_length; };
		// ������ �����ϱ� ���ؼ� �غ��Ѵ�. ���� start���� �����Ѵ�.
	void         enumEdgeFirst(int start);
		/** ���� ������ ��ȯ�Ѵ�.
			@param v1,v2 ��ȯ�� ������ ���� ���ð� ����. ATSP�� ���,
			������ v1->v2�� ������ ���Ѵ�.
			@return ������ ���� TRUE, ������ ���� FALSE
		*/
    int          enumEdgeNext(int* v1, int* v2);
		// ������ ��� dest�� order�������� ��ȯ�Ѵ�. size�� dest�� ũ��.
	void         convertToOrder(int* dest, int size);
		// ���� ��� dest�� order�������� ��ȯ�Ѵ�. size�� dest�� ũ��.
	void         makeRandomOrderTour(int* dest, int size);
};

	/** STSP�� ���� ���� Ŭ����.
		STSP ������� �����ڳ� ������� �ǹ̰� ����. ���� ��� ���õ��� 2��
		degree�� �����鼭 subcycle�� ������ �����ϰ�, ������ ��� �ȴ�.
		�׷��� �� Ŭ������ � ������ �ִ� ����� ������ ��(degree)�� 2����
		�̿��Ͽ�, #m_e1, m_e2#�迭�� ��� ǥ���Ѵ�. 

		#m_e1, m_e2#�� � ������ �̿����õ��� �����Ѵ�. ���� ���,
		10 - 7 - 5 - ... �� ��� #m_e1[7] = 10, m_e2[7] = 5, #
		#m_e2[10] = 7, m_e2[5] = 7, ...#ó�� ǥ�� �� �� �ִ�. 

		�� Ŭ������ �ʱ�ȭ ����� 2������ ���� �� �ִ�. ù��°�� 1�ܰ� �����ڸ�
		�ҷ� �ѹ��� �ʱ�ȭ�ϴ� ����̰� �ι�°�� 2�ܰ� �����ڸ� �θ��� ����,
		create()�Լ��� �θ��� ����̴�.
	*/
class C2EdgeTour : public CTour
{
public:
		// ���� i -> ���� j. ���� i�� j�� ����Ǿ� �ִ�. j<0�̸� ���� i�� #m_e1#���� �ٸ� ���ÿ� ����Ǿ� ���� �ʴ�.
	int*        m_e1;
		// ���� i -> ���� k. ���� ��������.
	int*        m_e2;
	
private:
		// findFirst, findNext���� ���Ǵ� ���� ����
	int         m_end;
	int         m_prev;
	int         m_cur; 
		// ��Ƽ �׷����� ����ϴ����� ��Ÿ���� �÷���. 
	int         m_isMult;

public:
		// 1�ܰ� ������
	C2EdgeTour(int size);
		// 2�ܰ� ������
	C2EdgeTour();
  
  C2EdgeTour(const C2EdgeTour& src);
		// ������ ������ �����Ѵ�. 
	void       create(int size);
	~C2EdgeTour();
	
		/**@name ���� �Լ���
		   CTour�� ���� ���� �Լ����� ����� �Լ����̴�. */
		//@{    block start
		///
	void        makeRandomTour();
	int         isThereEdge(int v1, int v2);
	void        findFirst(int start);
	int         findNext();
	int         isTour();
	void        convertFromOrder(int* src, int size);
	void        make2Change(int v1, int n1, int v2, int n2);
	void        make3Change(int v1, int n1, int v2, int n2,
							int v3, int n3);
    void        make4Change(int v1, int n1, int v2, int n2,
							int v3, int n3, int v4, int n4);
		//@}    block end

		/**@name C2EdgeTour�� ������ ���� �Լ� */
		//@{    block start
		/// (v1, v2)������ ��� ���Ѵ�. ������ �� ������ ��� ����� �Ѵ�.
	void        addEdge(int v1, int v2);
		// (v1, v2)������ �����ϰ� �����Ѵ�. �̹� ������ ������ No operation.
	void        addEdgeSafely(int v1, int v2);
		// (v1, v2)������ �����.
	void        deleteEdge(int v1, int v2);
		// ��� ������ ������, ��� ��� �Ѵ�.
	void        deleteAllEdge();
		// ���� v1�� degree�� �����Ѵ�.
	int         getEdgeSize(int v1);
		// ����� ���� ������ ���� �����Ѵ�. ���ϰ��� ������ ���� ���ƾ߸� ������ ������ ��� ������ �ȴ�.
	int         getNumEdge();
		// (v1, v2) ������ �ִ����� ������ ã�´�.
	int         isThereEdge2(int v1, int v2);
		/* ���� v�� ���� �ִ� �̿� ���ø� �����Ѵ�.
		   @param v1,v2 ���ϵ� �̿� ����. ������ �������̴�. */
	void        getNeighbor(int v, int* v1, int* v2);
		// ���� cur�� ���� ���ø� prev��� ������ ��, cur�� ���� ���ø� ����.
	int         getNext(int prev, int cur);
		// (v1, v2)������ (v3, v4)������ ���� �����ΰ�?
	int         is_same_edge(int v1, int v2, int v3, int v4);
		// �� ��� ���� ���굵�� ��Ƽ�׷��� ������ ������� �����Ѵ�.
	void        setMultiGraphFlag(int flag);
		// src ��� �� ��� �����Ѵ�.
	const C2EdgeTour& operator=(const C2EdgeTour& src);
    // ���Ŀ�
  bool C2EdgeTour::operator<(const C2EdgeTour& another);

		/* ���� cur�� end���̿� city�� �ִ°�?.
		   ��� prev���� cur�� ���� ���⼺ ������ ������ ��,
		   cur���� ����Ͽ� end���� ���� �о��ȿ� city�� �ִ� ���� ���θ� 
		   ��ȯ�Ѵ�.
		   @param prev cur�� �Բ� ������ ������ ���ϴ� �� ���̴� ����
		   @param cur  prev�� �Բ� ������ ������ ���Ѵ�. �׸���, ������ �о���
		   �������̴�.
		   @param city �о��ȿ� �ִ����� �˾� �� ���� 
		   @param end  �о��� ���� */
	int         isBetween(int prev, int cur, int city, int end);
		// subcycle�� �����ϴ°�?
	int         isDisjointCycle();
		//@}    block end

		/**@name �� ��� �ҿ����� ������ �� ���Ǵ� �Լ� */
		//@{    block start
		/** �ҿ����� ������ ��� greedy������� ������ ��� �����.
			@param tabu tour�� ���� ����
			@param t1,t2 tour�� �Ǵٸ� ���� ����. �ɼ��̴�.
			@param useNN greedy�� ������ �ϱ� ���ؼ� �̿� ���ø��� ���. option
		*/
		// �ҿ����� ��� ������ ���������� ������ ��� �����.
	void        connectRandom(C2EdgeTour* tabu);
		// Nearest Neighbor������� ��� �����. t1, t2�� �� �ٸ� ���� �ɼ�.
		/* ���� ������ �����.
		   ���� ������, �������� �� ��� subcycle�� ����� �ϴ� ������
		   ���Ѵ�. 
		   @param tabu ������� ���� ���� */
	void        constructTabuEdge(C2EdgeTour* tabu);
		// ����(v1, v2)�� ���������� �ɸ��� �ʰ�, �� ��� ������ �� �ִ°�?
	int         canAddEdge(C2EdgeTour* tabu, int v1, int v2);
		// Ÿ�� ��� (v1, v2)�� �����Ѵ�. �� �� ���� ������ ���뵵 �ٲ۴�.
	void        addEdgeWithTabu(C2EdgeTour* tabu, int v1, int v2);
		/* ���� v�� ������ �����Ѵ�.
		   ��� �ҿ����� ��, ����� ���� ����, �����Ǵ� �н��� �̷���� �ִ�.
		   �� ��, ���� v�� �� �н��� �����̶�� �� �Լ��� �� �н��� �ٸ�
		   ������ �����Ѵ�. v�� �н��� �߰��̶�� �������� �����Ѵ�.
		   v�� degree�� 0�϶��� �������� �����Ѵ�. */
	int         getEndPoint(int v);
		//@}    block end
	
};
	
inline void C2EdgeTour::deleteAllEdge()
{
	for( int i=0; i<m_size; i++) m_e1[i] = m_e2[i] = -1;
}

inline void C2EdgeTour::getNeighbor(int v, int* v1, int* v2)
{
	*v1 = m_e1[v];	    *v2 = m_e2[v];
}

inline int  C2EdgeTour::getNext(int prev, int cur)
{
	return (m_e1[cur] == prev) ? m_e2[cur] : m_e1[cur];
}


inline int  C2EdgeTour::is_same_edge(int v1, int v2, int v3, int v4)
{
	return ((v1==v3&&v2==v4) || (v1==v4&&v2==v3));
}

inline int  C2EdgeTour::isThereEdge2(int v1, int v2)
{
    return ((m_e1[v1] == v2) || (m_e2[v1] == v2));
}

inline void C2EdgeTour::setMultiGraphFlag(int flag)
{
	m_isMult = flag;
}

inline int  C2EdgeTour::getEdgeSize(int v1)
{
	if( m_e1[v1]>=0 && m_e2[v1]>=0)      return 2;
	else if( m_e1[v1]>=0 || m_e2[v1]>=0) return 1;
	else                                 return 0;
}

#endif













