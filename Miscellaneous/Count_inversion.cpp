int mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int inv_count = 0; 
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // in the left subarray (arr[i..mid]) are greater than arr[j]
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy the remaining elements of right subarray, if any
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the sorted subarray into Original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

// Function to divide the array into halves and count inversions recursively
int mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;

        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Function to count inversions in the array using merge sort
int countInversions(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);
    return mergeSortAndCount(arr, temp, 0, n - 1);
}
