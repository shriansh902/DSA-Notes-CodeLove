#include <bits/stdc++.h>
using namespace std;

//Search in Rotated Sorted Array
//Given the array nums after the possible rotation and an integer target
//return the index of target if it is in nums, or -1 if it is not in nums
//You must write an algorithm with O(log n) runtime complexity

int search(vector<int>& nums, int target) {
    int s=0;int e=nums.size()-1; int mid=s+(e-s)/2;
    //here we can say that the array is divided into 2 parts and both of them are sorted
    //so the idea is to find on which part does target fall on and binary search on it

    while (s<e){
        if(nums[mid]>=nums[0]){
            s=mid+1;
        }
        else{
            e=mid;
        }
        mid=s+(e-s)/2;
    }
    //atp s contains the pivot element
    if(target>=nums[0]){
        e=s;
        s=0;
    }
    else{
        e=nums.size()-1;
    }

    while(s<=e){ //simple binary search for the target element
        mid=s+(e-s)/2;

        if(nums[mid]==target){
            return mid;
        }
        if(nums[mid]>target){
            e=mid-1;
        }
        if(nums[mid]<target){
            s=mid+1;
        }
    }
    return -1;
}

int main(){
    vector<int> nums={27,29,31,45,1,8,13,14,23};
    cout<< search(nums,17);
    return 0;
}