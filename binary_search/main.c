int binary_search(int key, int* array, int min, int max) {
    int mid = floor((min + max ) / 2);

    if (max < min) {
        return - 1;
    }

    if (array[mid] > key) {
        return binary_search(key, array, min, mid - 1);
    } else if (array[mid] < key) {
       return binary_search(key, array, mid + 1, max);
    } else { 
        return array[mid];
    }
}