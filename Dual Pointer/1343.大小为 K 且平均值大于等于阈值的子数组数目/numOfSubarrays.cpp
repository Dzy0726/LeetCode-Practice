class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int sum = 0;
        int result = 0;
        for (int right = 0, left = 0; right < arr.size(); ++right) {
            sum += arr[right];
            while (right - left + 1 > k) {
                sum -= arr[left];
                left++;
            }
            if (right - left + 1 == k && sum >= threshold * k) {
                result++;
            } 
        }
        return result;
    }
};