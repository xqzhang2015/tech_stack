#include <iostream>
#include <vector>
#include <string>

using namespace std;

// insert sort
template <typename T>
int insertionSort(T *data, int n)
{
	if (data == NULL || n <= 0) {
		return -1;
	}

	for (int i = 1; i < n; i++) {
		T key = data[i];

		int j = i - 1;
		for (; j >= 0 && data[j] > key; j--) {
			data[j + 1] = data[j];
		}
		data[j + 1] = key;
	}
	return 0;
}

// merge sort
template <typename T>
void copy(T *outData, T *data, int left, int right)
{
	for (int i = left; i <= right; i++) {
		data[i] = outData[i];
	}
}

template <typename T>
void merge(T *data, T *outData, int left, int mid, int right)
{
	int lLoc, rLoc, outLoc;
	lLoc = left;
	rLoc = mid + 1;
	outLoc = left;

	while(lLoc <= mid && rLoc <= right) {
		if (data[lLoc] <= data[rLoc]) {
			outData[outLoc++] = data[lLoc++];
		} else {
			outData[outLoc++] = data[rLoc++];
		}
	}

	if (lLoc <= mid) {
		while (lLoc <= mid) {
			outData[outLoc++] = data[lLoc];
		}
	} else if (rLoc <= right) {
		while (rLoc <= right) {
			outData[outLoc++] = data[rLoc];
		}
	}
}

template <typename T>
void mergeSorti(T *data, int left, int right, T *outData)
{
	if (left < right) {
		int i = (left + right) / 2;
		mergeSorti(data, left, i, outData);
		mergeSorti(data, i + 1, right, outData);
		merge(data, outData, left, i, right);
		copy(outData, data, left, right);
	}
}

template <typename T>
void mergeSort(T *data, int n)
{
	T *outData = new T[n];
	mergeSorti(data, 0, n - 1, outData);
	delete [] outData;
}


int main(void)
{
	int data[6] = {5, 3, 1, 9, 7, -1};

	insertionSort<int>(data, sizeof(data) / sizeof(*data));
	for (uint i = 0; i < sizeof(data) / sizeof(*data); i++) {
		cout << data[i] << " ";
	}
	cout << endl;

	std::vector<int> vT;
	int i;

	while (cin >> i) {
		vT.push_back(i);
	}
	// insertionSort<int>(&vT[0], vT.size());
	mergeSort<int>(&vT[0], vT.size());
	for (std::vector<int>::iterator it = vT.begin(); it != vT.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}

