% _day1

# Day1: 数组理论基础

## 关于数组
- 存储在**连续内存空间**中的**相同类型**数据的集合
- 二维数组的存储是否连续与语言有关

## LC704-有序数组二分查找-S
- 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
- code:
  ```C++
  int search(vector<int>& nums, int target) {
        int start = 0, fin = nums.size() - 1;
        while(start <= fin) {
            int mid = start + (fin-start)/2; //防溢出
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                fin = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return -1;
    }
  ```
- 时间复杂度：O(log n), 最坏情况 2^T = n, T = log2 n
- 空间复杂度: O(1)
- 注意左右区间的开闭判定

## LC35-搜索插入位置-S
- 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
- code:
  ```C++
      int searchInsert(vector<int>& nums, int target) {
        int start = 0, fin = nums.size() - 1;
        while (start <= fin) {
            int mid = start + (fin - start) / 2;
            if (target < nums[mid]) {
                fin = mid - 1;
            } else if (target > nums[mid]) {
                start = mid + 1;
            } else {
                return mid;
            }
        }
        return fin + 1;
    }
  ```

## LC34-排序数组查找元素所在区间-M
- 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]
- 需要后续练习
- code
  ```C++
    vector<int> searchRange(vector<int>& nums, int target) {
        //右边界
        int left = 0, right = nums.size()-1;
        int rBorder = -2;
        while (left <= right) {
            int mid = left + (right-left)/2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
                rBorder = left;
            }
        }
        //左边界
        left = 0, right = nums.size()-1;
        int lBorder = -2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
                lBorder = right;
            }
        }
        if (lBorder == -2 || rBorder == -2) {
            return {-1, -1};
        } else if (rBorder - lBorder > 1) {
            return {lBorder+1, rBorder-1};
        } else {
            return {-1, -1};
        }
    }
  ```

## LC27-移除元素-S
- 给定数组 nums 和一个值 val， **原地** 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
 不要使用额外的数组空间，必须仅使用 O(1) 额外空间并 **原地** 修改输入数组。元素的顺序可以改变。
 不需要考虑数组中超出新长度后面的元素。
- note: 输入数组是以 **引用** 方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
- 暴力解法 - O(n^2)：
  ```C++
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        for (int i = 0; i < size; i++) {
            if (nums[i] == val) {
                for (int j = i; j < size-1; j++) {
                    nums[j] = nums[j+1];
                }
                i --;
                size --;
            }
        }
        return size;
    }
  ```
- 快慢指针 - O(n):
  ```C++
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow ++;
            }
        }
        return slow;
    }
  ```