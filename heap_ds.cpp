#include <bits/stdc++.h>
using namespace std;


// Min Heap class
class MinHeap {
    vector<int> heap;
    void heapifyUp(int i) {
        while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void heapifyDown(int i) {
        int n = heap.size();
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;
        if (left < n && heap[left] < heap[smallest]) smallest = left;
        if (right < n && heap[right] < heap[smallest]) smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
public:
    void insert(int val) { heap.push_back(val); heapifyUp(heap.size() - 1); }
    int extractMin() { int root = heap[0]; heap[0] = heap.back(); heap.pop_back(); heapifyDown(0); return root; }
    int getMin() { return heap[0]; }
    bool empty() { return heap.empty(); }
};

// Max Heap class
class MaxHeap {
    vector<int> heap;
    void heapifyUp(int i) {
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void heapifyDown(int i) {
        int n = heap.size();
        int largest = i;
        int left = 2 * i + 1, right = 2 * i + 2;
        if (left < n && heap[left] > heap[largest]) largest = left;
        if (right < n && heap[right] > heap[largest]) largest = right;
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }
public:
    void insert(int val) { heap.push_back(val); heapifyUp(heap.size() - 1); }
    int extractMax() { int root = heap[0]; heap[0] = heap.back(); heap.pop_back(); heapifyDown(0); return root; }
    int getMax() { return heap[0]; }
    bool empty() { return heap.empty(); }
};


// 1. Heap Sort
void heapSort(vector<int>& arr) {
    priority_queue<int> maxHeap(arr.begin(), arr.end());
    for (int i = arr.size() - 1; i >= 0; i--) {
        arr[i] = maxHeap.top();
        maxHeap.pop();
    }
}

// 2. Kth Largest Element
int kthLargest(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : arr) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

// 3. Kth Smallest Element
int kthSmallest(vector<int>& arr, int k) {
    priority_queue<int> maxHeap;
    for (int num : arr) {
        maxHeap.push(num);
        if (maxHeap.size() > k) maxHeap.pop();
    }
    return maxHeap.top();
}

// 4. Find Median of Data Stream
class MedianFinder {
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
public:
    void addNum(int num) {
        left.push(num);
        if (!right.empty() && left.top() > right.top()) {
            right.push(left.top());
            left.pop();
        }
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
        if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }
    double findMedian() {
        if (left.size() == right.size()) return (left.top() + right.top()) / 2.0;
        return left.top();
    }
};

// 5. Top K Frequent Elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for (int n : nums) freq[n]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    for (auto& p : freq) {
        minHeap.push({p.second, p.first});
        if (minHeap.size() > k) minHeap.pop();
    }
    vector<int> res;
    while (!minHeap.empty()) {
        res.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return res;
}

// 6. Merge K Sorted Arrays
vector<int> mergeKSorted(vector<vector<int>>& arrs) {
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<>> minHeap;
    for (int i = 0; i < arrs.size(); i++)
        if (!arrs[i].empty()) minHeap.push({arrs[i][0], {i, 0}});
    vector<int> res;
    while (!minHeap.empty()) {
        auto [val, idx] = minHeap.top(); minHeap.pop();
        res.push_back(val);
        int row = idx.first, col = idx.second;
        if (col + 1 < arrs[row].size())
            minHeap.push({arrs[row][col+1], {row, col+1}});
    }
    return res;
}

// 7. Connect Ropes to Minimize Cost
int minCostRopes(vector<int>& ropes) {
    priority_queue<int, vector<int>, greater<int>> minHeap(ropes.begin(), ropes.end());
    int cost = 0;
    while (minHeap.size() > 1) {
        int a = minHeap.top(); minHeap.pop();
        int b = minHeap.top(); minHeap.pop();
        cost += a + b;
        minHeap.push(a + b);
    }
    return cost;
}

// 8. Sliding Window Maximum
vector<int> slidingWindowMax(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

// 9. Find K Closest Numbers
vector<int> kClosest(vector<int>& arr, int k, int x) {
    priority_queue<pair<int,int>> maxHeap;
    for (int n : arr) {
        maxHeap.push({abs(n - x), n});
        if (maxHeap.size() > k) maxHeap.pop();
    }
    vector<int> res;
    while (!maxHeap.empty()) {
        res.push_back(maxHeap.top().second);
        maxHeap.pop();
    }
    sort(res.begin(), res.end());
    return res;
}

// 10. Smallest Range from K Sorted Lists
int smallestRange(vector<vector<int>>& nums) {
    int k = nums.size();
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<>> pq;
    int maxi = INT_MIN;
    for (int i = 0; i < k; i++) {
        pq.push({nums[i][0], {i, 0}});
        maxi = max(maxi, nums[i][0]);
    }
    int start = 0, end = INT_MAX;
    while (true) {
        auto [val, idx] = pq.top(); pq.pop();
        if (end - start > maxi - val) {
            start = val;
            end = maxi;
        }
        if (idx.second + 1 == nums[idx.first].size()) break;
        pq.push({nums[idx.first][idx.second+1], {idx.first, idx.second+1}});
        maxi = max(maxi, nums[idx.first][idx.second+1]);
    }
    return end - start;
}

int main() {
    vector<int> arr = {10, 7, 11, 5, 2, 13};
    heapSort(arr);
    cout << "Heap Sort: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    vector<int> arr2 = {3,2,1,5,6,4};
    cout << "Kth Largest (k=2): " << kthLargest(arr2, 2) << endl;
    cout << "Kth Smallest (k=2): " << kthSmallest(arr2, 2) << endl;

    MedianFinder mf; mf.addNum(1); mf.addNum(2); mf.addNum(3);
    cout << "Median: " << mf.findMedian() << endl;

    vector<int> nums = {1,1,1,2,2,3};
    vector<int> top = topKFrequent(nums, 2);
    cout << "Top 2 Frequent: "; for (int x : top) cout << x << " "; cout << endl;

    vector<vector<int>> arrs = {{1,4,5}, {1,3,4}, {2,6}};
    vector<int> merged = mergeKSorted(arrs);
    cout << "Merged K Sorted: "; for (int x : merged) cout << x << " "; cout << endl;

    vector<int> ropes = {4,3,2,6};
    cout << "Min Cost Ropes: " << minCostRopes(ropes) << endl;

    vector<int> sw = slidingWindowMax(arr2, 3);
    cout << "Sliding Window Max: "; for (int x : sw) cout << x << " "; cout << endl;

    vector<int> close = kClosest(arr2, 3, 4);
    cout << "3 Closest to 4: "; for (int x : close) cout << x << " "; cout << endl;

    return 0;
}
