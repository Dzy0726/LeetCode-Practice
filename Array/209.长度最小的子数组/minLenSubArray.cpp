class Solution {

public:

​    int check(int count, vector<int>& lastNum, int target, vector<int>& nums) {

​        if(count > nums.size() - 1) {

​            return 0;

​        } else if (count == 1) {

​            for(int i = 0; i < nums.size(); i++) {

​                if(nums[i] >= target) {

​                    return count;

​                }

​            }

​        }

​        int newLen = nums.size() - count;

​        vector<int> newVec(newLen);

​        for(int i = 0; i < newLen; i++) {

​            newVec[i] = lastNum[i] + nums[i+count];

​        }

​        for(int i = 0; i < newLen; i++) {

​            if(newVec[i] >= target) {

​                count++;

​                return count;

​            }

​        }

​        count = count + 1;

​        print(count,newVec,target,nums);

​        return check(count,newVec,target,nums);

​    }

​    void print(int count, vector<int>& newVec, int target, vector<int>& nums) {

​        cout << "count:" << count << endl;

​        cout << "newVec:";

​        for(int i = 0; i < newVec.size(); i++) {

​            cout << newVec[i] << " " ;

​        }    

​        cout << endl << "target:" << target << endl;

​        cout << "nums:";

​        for(int i = 0; i < nums.size(); i++) {

​            cout << nums[i] << " " ;

​        }    

​        cout << endl;

​    }

​    int minSubArrayLen(int target, vector<int>& nums) {

​        

​        return check(1,nums,target,nums);

​    }

};

// count =2 [2,2,2,2,2,2,2] 3 [1,1,1,1,1,1,1,1] nums-1= 7

// 
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;
        int sublength = 0;
        int result = INT_MAX;
        int i = 0;
        for(int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while(sum >= target) {
                sublength = j - i + 1;
                result = result < sublength ? result : sublength;
                sum -= nums[i++];
            }
        }
        return result == INT_MAX ? 0 :result ;
    }
};