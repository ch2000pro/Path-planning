#include "point.h"
#include <vector>
#include "plane.h"

void Plane::split(vector<Point*> A, int iStart, int iEnd, vector<Point*> B) {
	if (iEnd - iStart < 2)
		return;
	int iMiddle = (iEnd + iStart)/2;
	Plane::split(A, iStart, iMiddle, B);
	Plane::split(A, iMiddle, iEnd, B);
	Plane::merge(A, iStart, iMiddle, iEnd, B);
	for (int k = iStart; k < iEnd; k++)
		A[k] = B[k];
}

void Plane::merge(vector<Point*> A, int iStart, int iMiddle, int iEnd, vector<Point*> B) {
	int i = iStart, j = iEnd;
	for (int k = iStart; k < iEnd; k++) {
		if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
			B[k] = A[i];
			i++;
		}
		else {
			B[k] = A[j];
			j++;
		}
	}
}
