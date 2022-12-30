#include <stdio.h>
//初始化队列
void initializeList(int list[],int number){
    for (int i = 0; i < number; i ++) {
        list[i] = -1;
    }
}
//展示队列状态
void showList(int list[], int number){
    for (int i = 0; i < number; i ++) {
        printf("%2d",list[i]);
    }
    printf("\n");
}
//展示当前内存状态
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
    printf("缺页次数:%d   缺页率:%d/%d\n",missingCount,missingCount,pageNum);
    double result = (double)(pageNum - missingCount)/(double)pageNum;
    printf("置换次数:%d  命中率:%.2f\n",replaceCount,result);
}
//找到该页面下次要访问的位置
int getNextPosition(int currentPage,int currentPosition,int strList[],int pageNum){
    
    for (int i = currentPosition+1; i < pageNum; i ++) {
        if (strList[i] == currentPage) {
            return i;
        }
    }
    return 100;
}
//最佳置换算法
void replacePageByOPT(int memoryList[],int phyNum,int strList[],int pageNum){   
    int replaceCount = 0;//置换次数
    int missingCount = 0; //缺页次数
    int nextPosition[phyNum];//记录在内存的物理块的下一次访问位置
    initializeList(nextPosition, phyNum);
    int isVisited;
    for (int i = 0; i < pageNum; i ++) {
        isVisited = 0;
        //判断是否需要置换->内存已满且需要访问的页面不在内存中
        for (int j = 0; j < phyNum; j ++) {
            if (memoryList[j] == strList[i]) {//该页面已经存在内存中
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
        if (!isVisited) { //当前页面还没访问过， 内存已满且当前访问不在内存中->进行置换
            int max = 0;
            for (int k = 1; k < phyNum; k ++) {//1.寻找到最晚才被访问到的页面
                if (nextPosition[max] < nextPosition[k]) {
                    max = k;
                }
            }
            memoryList[max] = strList[i];//2.将该位置的页面换出
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
    printf("请输入物理块数量:\n");
    scanf("%d",&phyBlockNum);
    int memoryList[phyBlockNum];
    initializeList(memoryList, phyBlockNum);
    int pageNum;
    printf("请输入要访问的页面总数:\n");
    scanf("%d",&pageNum);
    int pageNumStrList[pageNum];
    printf("请输入要访问的页面号:\n");
    for (int i = 0; i < pageNum; i ++) {
        scanf("%d",&pageNumStrList[i]);
    }
    showList(pageNumStrList, pageNum);
    int chose;
    printf("请选择所需的置换算法:\n");
    printf("1.OPT 0.退出\n");
    scanf("%d",&chose);
    switch (chose) {
        case 1:
        	showList(pageNumStrList, pageNum);
        	replacePageByOPT(memoryList, phyBlockNum, pageNumStrList, pageNum);
        	initializeList(memoryList, phyBlockNum);
            break;
		case 0:
			printf("退出\n");
			break;
        default:
            return 0;
            break;
        }
    return 0;
}
