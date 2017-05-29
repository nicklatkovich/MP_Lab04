#pragma once

template <class T>
class Matrix {
private:
	T** arr;
	unsigned int width;
	unsigned int height;
public:
	Matrix(unsigned int width, unsigned int height, T defaultValue) {
		arr = new T*[width];
		for (unsigned int i = 0; i < width; i++) {
			arr[i] = new T[height];
			for (unsigned int j = 0; j < height; j++) {
				arr[i][j] = defaultValue;
			}
		}
		this->width = width;
		this->height = height;
	}
	T Get(unsigned int x, unsigned int y) {
		return arr[x][y];
	}
	void Set(unsigned int x, unsigned int y, T value) {
		arr[x][y] = value;
	}
	~Matrix() {
		for (unsigned int i = 0; i < width; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
};
