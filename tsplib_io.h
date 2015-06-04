#ifndef TSPLIB_IO_H
#define TSPLIB_IO_H

#include <stdio.h>
	/**@name TSPLIB ����� ��ƾ.
	   \URL[TSPLIB]{ftp://softlib.rice.edu/pub/tsplib} ������ �о� TSP
	   �ν��Ͻ��� �����ϰ�, �� ���� �����ϴ� �� �̿�Ǵ� ������ �Լ� ������
	   �����Ѵ�.
	   
	   �ؿ��� ����� order������ tour��, ���� ��� 7->5->3->... �̶�� ���
	   tour[0] = 7, tour[1] = 5, tour[2] = 3, ... ������ ������ ��� ���Ѵ�.
	*/
	//@{  Start of DOC++ block

#ifndef DISTANCE_CALC_METHOD
	/** �Ÿ� �����͸� �����ϴ� ����� �����ϴ� �����Ϸ� �÷���. 
		�� ��ũ���� ���� ���� �Ÿ� �����͸� �����ϴ� ����� �޶�����. ������
		������ Ŀ������ �Ÿ��� �����ϴ� �迭�� Ŀ���� �Ǿ� 10000���̻���
		���ÿ����� ���̻� Matrix�� ������ �� ���� ������ �ٸ� ����� �����ؾ�
		�Ѵ�. �� ��ũ�δ� �Ÿ��� �����ϰų� ����ϴ� ����� �����ϴ� ���̴�.
		�� ��ũ�δ� ���������θ� ���Ǿ�� �Ѵ�. �� #tsplib_io.cc#������
		���Ǵ� ���̴�.
		\begin{itemize}
		\item 0�̸�, �Ÿ��� Full Matrix�� �����Ѵ�. �� �� �����
		$4n^2$byte�� �����Ѵ�. ����� �����ϹǷ� ���� �ӵ��� ���� ������.
		\item 1�̸�, �Ÿ��� Half Matrix�� �����Ѵ�. �� ����� symmetric TSP����
		����ȴ�. $\frac{4(n-1)(n-2)}{2}$byte�� �����Ѵ�. �� Full Matrix����
		������ �������� �����Ѵ�. �ӵ��� ���� ���̴�.
		\item 2�̸�, �Ÿ��� �¶������� ����Ѵ�. �� �Ÿ��� �ʿ��� ������
		�־��� ������ ��ǥ�� �Ǽ� ����� �ϱ� ������ ���� ������. ������ ������
		Ŭ ������ �� ����� ��� �Ѵ�. �����δ� �Ÿ��� �����ϴ� �� ĳ�ø�
		����ϱ� ������ �� $4((neighbors+\alpha)*n)$byte��ŭ �����Ѵ�. ��
		������� ����� ���� dist()��ũ�δ� ConstructNN()�Լ� ȣ���ĺ���
		��ȿ�ϴ�. ������ ����� ReadTspFile()�Լ� ȣ���ĺ��� ��ȿ�ϴ�.
		\end{itemize}
	*/
#define DISTANCE_CALC_METHOD    1
#endif


#if     (DISTANCE_CALC_METHOD==0)
	/// ���� c1, c2������ �Ÿ��� ��ȯ�Ѵ�.
#define dist(c1, c2)        gDistMat[(c1)*gNumCity + (c2)]
#elif   (DISTANCE_CALC_METHOD==1)
#define dist(c1, c2)		gDistMat[max(c1,c2)*(max(c1,c2)-1)/2 + min(c1,c2)]
#elif   (DISTANCE_CALC_METHOD==2)
#define dist(c1, c2)        calcOnline(c1, c2)
#endif

	/// ���� i���� nth��° ������ ������ ��ȣ
#define nni(i, nth)         gNNI[(i)*gNumNN + (nth)]
	/// ���� i���� nth��° ������ ���ÿ��� �Ÿ�
#define nnd(i, nth)         (dist((i), nni(i, nth)))

	/// ������ �ν��Ͻ��� symmetric TSP���� ����Ų��.
#define TYPE_STSP           0
	/// ������ �ν��Ͻ��� asymmetric TSP���� ����Ų��.
#define TYPE_ATSP           1

	// ������ ��
extern unsigned int    gNumCity;
	// �ν��Ͻ��� Ÿ�� : symmetric �Ǵ� asymmetric TSP���� ����
extern int             gType; 
	// ����� ���� ����� �̿� ������ ��
extern int             gNumNN; 
	// �Ÿ� ���. ���� ������� ����, dist��ũ�θ� �̿��Ѵ�.
extern double*            gDistMat; 
	// ���� ����� �̿� ���� ��ȣ���� ������ �迭. nni��ũ�θ� �̿��϶�.
extern int*            gNNI;           

	/** TSP������ �а� �ν��Ͻ��� �����Ѵ�.
		@param graphname �ν��Ͻ� �����̸�. Ȯ���ڴ� .tsp �Ǵ� .atsp�� �Ǿ��
		�Ѵ�.  */

void ReadTspFile(const char *graphname);
	/** ���� ����� �̿� ���õ��� �迭�� �����.
		@param numNN �� ���ÿ� ���ؼ� ������� �̿� ���õ��� ��
		@param is_quad �̿� ���õ��� ����� �� ���õ��� 4���� �������� �����
		����� �� ���θ� �����Ѵ�. �ν��Ͻ��� 2�����϶��� �����ϴ�.
	*/
void ConstructNN(int numNN, int is_quad=0);

	// �ν��Ͻ� ���Ͽ� ���� ������ ����Ѵ�.
void PrintTspInfo();

	/** �ν��Ͻ� ������ n������ ��, ������ ������ſ� ��ǥ�� ������ ����Ѵ�.
		@param fd ���� �����
		@param tour order�������� �� ���� ���
		@param size tour�� ����	 */
void PrintCoords(FILE* fd, int* tour, int size);

	/** �ν��Ͻ� ������ n������ ��, �� ������ ��ǥ�� ��� ����.
		@param city ���� ��ȣ
		@param pt   ��ȯ�� ��ǥ�� �� �迭
		@param size pt�迭�� ũ��. n�������� �� Ŀ�� �Ѵ�. 
		@return ������ ���� �����Ѵ�. �� n�� �����ϰ� 
		�����ϸ�, -n�� �����Ѵ�.  */
int GetCoords(int city, double* pt, int size);

	/** ���� ������ �д´�.
		@param file ���� ���� �̸�
		@param tour ��ȯ�� ��� order�������� �� �迭. 
		@param size tour�� ũ��.
		@return ���� ���θ� �˸��� boolean�� */
int ReadTourFile(char* file, int *tour, int size);

	/** ������ ���� ������ �д´�.
		@param opt_tour ��ȯ�� ��� order�������� �� �迭. 
		@param size opt\_tour�� ũ��. ���� ������ ũ�ų� ���ƾ� �Ѵ�.
		@return ���� ���θ� �˸��� boolean�� */
int ReadOptTourFile(int *opt_tour, int size);

	// �ν��Ͻ��� ���� ����� ��ȯ�Ѵ�. �� ��쿡�� 0�� ��ȯ�Ѵ�.
int GetOptimumCost();

	/** ���� ��ȣ�� �籸���Ѵ�. 
		@param remap ���ʵ� ���� -> ������ ���� ��ȣ�� �����ִ� �迭�̴�. */
void RemapCities(int* remap);

	// ���ʵ� ������ ���� ���� ��ȣ�� ��ȯ�Ѵ�.
int GetOrgCity(int city);

	/** ��� ����Ѵ�. ���� ���õ��� ���ʵǾ� �ִٸ�, ������ ���� ��ȣ���
		��ȯ�Ͽ� ����Ѵ�.
		@param fd ���� �����
		@param tour ����� order������ ���� �迭.
		@param size tour�� ũ��
		@param name ���� ���뿡 ��� �� ���� �̸�
		@param comment �ּ���
	*/
void PrintTour(FILE* fd, int* tour, int size, char* name=NULL,
			   char* comment=NULL);

	// �ν��Ͻ��� �׷��� �̸��� dest�� �����Ѵ�.
void CopyGraphName(char* dest);

	// ���� i�� j�� ������ �Ÿ��� ��ȯ�Ѵ�. dist��ũ�θ� ����� ��. 
int calcOnline(int i, int j);

	//@}  End of DOC++ block
#endif /* end of file */









