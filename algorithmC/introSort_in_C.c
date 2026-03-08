#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int max_depth = 0;
static inline void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
static inline void insertsort(int* a, int left, int right){
    for(int i = left; i <= right;i++){
        int key = a[i];
        int j = i - 1;
        while(j >= left){
            if(key <= a[j]) {
                a[j + 1] = a[j];
                j--;
            }
            else break;
        }
        a[j + 1] = key;
    }
}
static inline void heapmodify(int* heap, int start, int end){
    int son = start * 2 + 1;
    while(son <= end){
        if(son + 1 <= end && heap[son + 1] > heap[son])
            son++;
        if(heap[son] > heap[start]){
            swap(&heap[start], &heap[son]);
            start = son, son = 2 * son + 1;
        }
        else break;
    }
}
void heapsort(int* heap, int len){
    if(len <= 1) return;
    int root = 0;
    for(int i = len / 2 - 1;i > root - 1;i--) heapmodify(heap, i, len - 1);
    for(int i = len - 1;i > root;i--){
        swap(&heap[root], &heap[i]);
        heapmodify(heap, root, i - 1);
    }
}
void sort(int* a, int left, int right, int depth){
    if(left >= right) return;
    if(right - left + 1 <= 2){
        if(a[left] > a[right]) swap(&a[left], &a[right]);
        return;
    }
    else if(right - left + 1 < 20){
        insertsort(a, left, right);
        return;
    }
    else if(depth >=(int)(1.8 * max_depth)){
        int len = right - left + 1;
        heapsort(a + left, len);
        return;
    }
    int len = right - left + 1;
    int mid = left + (right - left) / 2;
    int temp[5] = {a[left], a[left + len / 4], a[left + len / 2],
                    a[left + 3 * len / 4], a[right]};
    insertsort(temp, 0, 4);
    int pivot1 = temp[1], pivot2 = temp[3]; 
    if(pivot1 == pivot2){
        swap(&a[left], &a[mid]);
        int pivot = a[left];
        int i = left + 1, it = left + 1, gt = right;
        while(i <= gt){
            if(a[i] < pivot){
                if(it != i) swap(&a[i], &a[it]);
                it++, i++;
            }
            else if(a[i] > pivot){
                swap(&a[i], &a[gt]);
                gt--;
            }
            else i++;
        }
        if(it != left) swap(&a[it - 1], &a[left]);
        sort(a, left, it - 2, depth + 1);
        sort(a, i, right, depth + 1);
    }
    else{
        for(int i = left;i <= right;i++){
            if(a[i] == pivot1){
                swap(&a[i], &a[left]);
                break;
            }
        }
        for(int i = right;i >= left;i--){
            if(a[i] == pivot2){
                swap(&a[i], &a[right]);
                break;
            }
        }
        int lt = left + 1, gt = right - 1, i = left + 1;
        while(i <= gt){
            if(a[i] < pivot1){
                swap(&a[i], &a[lt]);
                lt++, i++;
            }
            else if(a[i] > pivot2){
                swap(&a[i], &a[gt]);
                gt--;
            }
            else i++;
        }
        swap(&a[left], &a[lt - 1]), swap(&a[right], &a[gt + 1]);
        sort(a, left, lt - 2, depth + 1);
        sort(a, lt, gt, depth + 1);
        sort(a, gt + 2, right, depth + 1);
    }
}
int main() {
    freopen("out.txt", "w", stdout);
    int size = 1e7;
    max_depth = (int)log2(size);
    int *arr = (int*)malloc(size * sizeof(int));
    for(int t = 0; t < 100; t++){
        for(int i = 0;i < size;i++) arr[i] = rand() * (rand() % 2001);
        clock_t start, end;
        start = clock();
        sort(arr, 0, size - 1, 0);
        end = clock();
        double used_time = ((double)(end - start)) / 1000 * 1000;
        printf("%.1f %d\n", used_time, arr[size - 1]);
    }
    fclose(stdout);
    free(arr);
    arr = NULL;
    return 0;
}