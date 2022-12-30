#include <stdio.h>
//��ʼ������
void initializeList(int list[],int number){
    for (int i = 0; i < number; i ++) {
        list[i] = -1;
    }
}
//չʾ����״̬
void showList(int list[], int number){
    for (int i = 0; i < number; i ++) {
        printf("%2d",list[i]);
    }
    printf("\n");

    
}
//չʾ��ǰ�ڴ�״̬
void showMemoryList(int list[],int phyBlockNum){
    for (int i = 0; i < phyBlockNum; i ++) {
        if (list[i] == -1) {
            break;
        }
        printf(" |%d|",list[i]);
    }
    printf("\n");
}
void informationCount(int missingCount,int replaceCount,int pageNum){
    printf("ȱҳ����:%d   ȱҳ��:%d/%d\n",missingCount,missingCount,pageNum);
    double result = (double)(pageNum - missingCount)/(double)pageNum;
    printf("�û�����:%d  ������:%.2f\n",replaceCount,result);
}
//�ҵ���ҳ���´�Ҫ���ʵ�λ��
int getNextPosition(int currentPage,int currentPosition,int strList[],int pageNum){
    
    for (int i = currentPosition+1; i < pageNum; i ++) {
        if (strList[i] == currentPage) {
            return i;
        }
    }
    return 100;
}
//����û��㷨
void replacePageByOPT(int memoryList[],int phyNum,int strList[],int pageNum){   
    int replaceCount = 0;//�û�����
    int missingCount = 0; //ȱҳ����
    int nextPosition[phyNum];//��¼���ڴ�����������һ�η���λ��
    initializeList(nextPosition, phyNum);
    int isVisited;
    for (int i = 0; i < pageNum; i ++) {
        isVisited = 0;
        //�ж��Ƿ���Ҫ�û�->�ڴ���������Ҫ���ʵ�ҳ�治���ڴ���
        for (int j = 0; j < phyNum; j ++) {
            if (memoryList[j] == strList[i]) {//��ҳ���Ѿ������ڴ���
                nextPosition[j] = getNextPosition(memoryList[j], i, strList, pageNum);
                isVisited = 1;
                printf("%d\n",strList[i]);
                break;
            }
            if (memoryList[j] == -1) {
                memoryList[j] = strList[i];
                nextPosition[j] = getNextPosition(memoryList[j], i, strList, pageNum);
                missingCount ++;
                isVisited = 1;
                printf("%d\n",strList[i]);
                showMemoryList(memoryList, phyNum);
                break;
            }
        }
        if (!isVisited) { //��ǰҳ�滹û���ʹ��� �ڴ������ҵ�ǰ���ʲ����ڴ���->�����û�
            int max = 0;
            for (int k = 1; k < phyNum; k ++) {//1.Ѱ�ҵ������ű����ʵ���ҳ��
                if (nextPosition[max] < nextPosition[k]) {
                    max = k;
                }
            }
            memoryList[max] = strList[i];//2.����λ�õ�ҳ�滻��
            nextPosition[max] = getNextPosition(memoryList[max], i, strList, pageNum);
            missingCount ++;
            replaceCount ++;
            printf("%d\n",strList[i]);
            showMemoryList(memoryList, phyNum);
        }
    }
    informationCount(missingCount, replaceCount,pageNum);
}
int main(int argc, const char * argv[]) {
    int phyBlockNum;
    printf("����������������:\n");
    scanf("%d",&phyBlockNum);
    int memoryList[phyBlockNum];
    initializeList(memoryList, phyBlockNum);
    int pageNum;
    printf("������Ҫ���ʵ�ҳ������:\n");
    scanf("%d",&pageNum);
    int pageNumStrList[pageNum];
    printf("������Ҫ���ʵ�ҳ���:\n");
    for (int i = 0; i < pageNum; i ++) {
        scanf("%d",&pageNumStrList[i]);
    }
    showList(pageNumStrList, pageNum);
    int chose;
    printf("��ѡ��������û��㷨:\n");
    printf("1.OPT 0.�˳�\n");
    scanf("%d",&chose);
    switch (chose) {
        case 1:
        	showList(pageNumStrList, pageNum);
        	replacePageByOPT(memoryList, phyBlockNum, pageNumStrList, pageNum);
        	initializeList(memoryList, phyBlockNum);
            break;
		case 0:
			printf("�˳�\n");
			break;
        default:
            return 0;
            break;
        }
    return 0;
}
