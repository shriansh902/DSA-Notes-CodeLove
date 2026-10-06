#include <bits/stdc++.h>
using namespace std;

int BinarySearch(vector<int> arr,int key){
    //complexity is o(logn)
    int start=0;
    int end =arr.size()-1;
    int ans=-1; //falied case
    int mid; // middle element is (start +end)/2
    while(start<=end){
        mid=start+ (end-start)/2;// (start +end)/2
        if(arr[mid]== key){
            ans=mid;
            break;
        }
        else if(arr[mid]>key){
            end = mid -1; // take the subarray left to the middle element
        }
        else{
            start = mid +1; // take the subarray right to the middle element
        }
    }
    
    return ans;
}


int BinarySearch_FirstOccurence(vector<int> arr,int key){
    int start=0;
    int end =arr.size()-1;
    int ans=-1;
    int mid; 
    while(start<=end){
        mid=start+ (end-start)/2;
        if(arr[mid]== key){
            ans= mid;
            end=mid-1;//<------ Only this line is different
        }
        else if(arr[mid]>key){
            end = mid -1; 
        }
        else{
            start = mid +1; 
        }
    }
    
    return ans;
}

int BinarySearch_LastOccurence(vector<int> arr,int key){
    int start=0;
    int end =arr.size()-1;
    int ans=-1;
    int mid; 
    while(start<=end){
        mid=start+ (end-start)/2;
        if(arr[mid]== key){
            ans= mid;
            start=mid+1;//<------ Only this line is different 
        }
        else if(arr[mid]>key){
            end = mid -1; 
        }
        else{
            start = mid +1; 
        }
    }
    
    return ans;
}

int main(){

    //sorted array
    vector<int> odd={1,2,45,45,45}; //5
    vector<int> even={2,3,23,45,61,134,233,299}; //8

    cout<< BinarySearch(odd,45);
    cout<<endl<<BinarySearch(even,2);
    cout<<endl<<BinarySearch(even ,56);
    cout<<endl<<BinarySearch_FirstOccurence(odd,45);
    cout<<endl<< BinarySearch_LastOccurence(odd,45);

    return 0;
}