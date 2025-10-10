#include <iostream>
#include <vector>
using namespace std;

// 先声明函数，确保main函数能识别
void printVector(const std::vector<int>& vec);
// 冒泡排序	Bubble Sort 平均 O(n²)	最壞O(n²)
// 最好时间复杂度: O(n) (优化版本，当数组已有序时)
// 空间复杂度: O(1)
// 稳定性: 稳定排 
// 内存受限环境 稳定性要求高的场景  几乎已排序的数据
std::vector<int> sortByBubble(std::vector<int> originArray){
    std::vector<int> originResult = originArray;
    for(int i=0;i<originArray.size()-1;i++){
        for(int j=0;j<originArray.size()-i-1;j++){
            if(originResult[j]>originResult[j+1]){
                int tmp = originResult[j];
                originResult[j] = originResult[j+1];
                originResult[j+1] = tmp;
            }
        }
    }
    return originResult;
}

// 5. 插入排序（Insertion Sort）
// 做法：
// 把序列分成「已排序部分」與「未排序部分」。
// 每次從未排序部分取一個元素，插入到已排序部分的正確位置。
// 最佳時間複雜度 O(n) 平均最壞 O(n²)
// 小規模資料或部分有序時表現佳
std::vector<int> sortByInsertion(std::vector<int> originArray){
    std::vector<int> originResult = originArray;
    for(int i=1;i<originArray.size();i++){
       
        int target = i;
        for(int j=i-1;j>=0;j--){
            if(originResult[j]<originResult[target]){
                int tmp = originResult[target];
                originResult[target] = originResult[j];
                originResult[j] = tmp;
                target = j;
            }
        }
    }
    return originResult;
}

// 希爾排序 Shell Sort
// 平均時間 O(n log²n)（依 gap）
// 最差時間 O(n²)
// 最好時間 O(1)
// 空間複雜度: O(1) - 原地排序
// : 定義遞減間隔，對每個間隔下的子數組進行插入排序
std::vector<int> sortByShell(std::vector<int> originArray){
    std::vector<int> originResult = originArray;
    int n = originResult.size();
    
    // 使用变化的gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = originResult[i];
            int j;
            for (j = i; j >= gap && originResult[j - gap] > temp; j -= gap) {
                originResult[j] = originResult[j - gap];  // 移动gap位
            }
            originResult[j] = temp;
        }
    }
    return originResult;
}
// 归并排序（Merge Sort）详解
// 归并排序采用分治策略，将数组递归分成两半分别排序，然后合并两个有序数组
// 📊 复杂度分析
// 时间复杂度：O(n log n) - 最好、最坏、平均情况都是这个复杂度
// 空间复杂度：O(n) - 需要额外的临时数组来合并
// 稳定性：稳定排序算法
std::vector<int> sortByMerge(std::vector<int> originArray){
    std::vector<int> originResult = originArray;
    int n = originResult.size();
    // 如果大數組是空或是只有一个元素 是有序
    if(originResult.size()<=1){
        return originResult;
    }
    // 把數組分兩塊
    int middle = originResult.size() / 2;
    std::vector<int> leftArray(originResult.begin(),originResult.begin()+middle);
    std::vector<int> rightArray(originResult.begin()+middle,originResult.end());
    // 遞歸排序兩個小數組
     std::vector<int> leftHandle = sortByMerge(leftArray);
    std::vector<int> rightHandle = sortByMerge(rightArray);
    // 合并两个已排序的小数组
    vector<int> merged;
    int leftIndex = 0, rightIndex = 0;
    // 比较两个数组的元素，取较小的放入结果
    while(leftIndex<leftHandle.size()&&rightIndex<rightHandle.size()){
        if(leftHandle[leftIndex]<rightHandle[rightIndex]){
            merged.push_back(leftHandle[leftIndex]);
            leftIndex++;
        }else{
            merged.push_back(rightHandle[rightIndex]);
            rightIndex++;
        }
        
    }
    // 把左边剩下的元素全部加入
    while (leftIndex<leftHandle.size())
    {
       merged.push_back(leftHandle[leftIndex]);
       leftIndex++;
    }
    
    // 把右边剩下的元素全部加入
    while (rightIndex<rightHandle.size())
    {
       merged.push_back(rightHandle[rightIndex]);
       rightIndex++;
    }
    return merged;
}

void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main(){
    cout<<"sort"<< endl;
    // 测试向量版本
    vector<int> testVec = {64, 34, 25, 12, 22, 11, 90};
    std::cout << "原始向量: ";
    printVector(testVec);
    
    std::vector<int> sortedVec = sortByMerge(testVec);
    std::cout << "排序后向量: ";
    printVector(sortedVec);
    return 0;
}

