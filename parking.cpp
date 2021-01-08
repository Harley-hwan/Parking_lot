#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#define empty (-1)
using namespace std;

int K, N;
struct parking_lot {
	int* arr;
	int _size; // 주차장 공간 크기
	int _car; // 주차된 자동차 수
};
parking_lot* init(parking_lot* lot, int init_size) {
	lot = new parking_lot();
	lot->arr = new int[init_size];
	for (int i = 0; i < init_size; i++) {
		lot->arr[i] = empty; // 범위가 10~2^12 이므로 한자리수 입력은 들어오지 않음 
	}
	lot->_size = init_size;
	lot->_car = 0;
	return lot;
}

parking_lot* push(parking_lot* lot,int data) {
	if (lot->_car == lot->_size) { // 가득 차잇는데 차가 들어오면
		vector<int> v;
		for (int i = 0; i < lot->_size; i++) {
			v.push_back(lot->arr[i]);
		}
		int new_size = lot->_size + lot->_size;
		lot->arr = new int[new_size];
		for (int i = 0; i < new_size; i++) {
			lot->arr[i] = empty;
		}
		for (int i = 0; i < v.size(); i++) {
			lot->arr[i] = v[i];
		}
		lot->_size = new_size;
	}

	for (int i = 0; i < lot->_size; i++) {
		if (lot->arr[i] == empty) {
			lot->arr[i] = data;
			lot->_car += 1;
			break;
		}
	}
	return lot;
}
parking_lot* pop(parking_lot* lot, int data) { // 차가 나간뒤 주차공간의 1/3
	int _find = 0;
	for (int i = 0; i < lot->_size; i++) {
		if (lot->arr[i] == data) { // 차 뺌
			lot->arr[i] = empty;
			lot->_car -= 1;
			_find = 1; // 찾음
			break;
		}
	}
	//if (!_find) { // 해당 번호의 차가 없으면 무시
	//	return lot;
	//}
	if (lot->_size >= lot->_car * 3 && lot->_size > K) { // 주차공간의 1/3이하 -> 절반으로 축소 및 정렬
		vector<int> car_manage;
		int num = 0;
		for (int i = 0; i < lot->_size; i++) {
			if (lot->arr[i] != empty) {
				car_manage.push_back(lot->arr[i]);
				num += 1;
			}
		}
		int new_size = lot->_size / 2 ; // 올림
		lot->arr = new int[new_size]; 
		
		for (int i = 0; i < new_size; i++) {
			lot->arr[i] = empty;
		}
		for (int i = 0; i < car_manage.size(); i++) {
			lot->arr[i] = car_manage[i];
		}
		lot->_size = new_size;
	}
	return lot;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	/*
	1. 차를 넣을때 , 가득 차있는 경우 2배로 늘림
	2. 차를 빼고난 후 , 차 * 3 <= 주차 공간인 경우 절반(소수점 첫째자리 올림) 으로 주차 공간 줄임
	*/
	cin >> K >> N;
	parking_lot* my_parking_lot = NULL;
	my_parking_lot = init(my_parking_lot, K);
	for (int i = 0; i < N; i++) {
		int car_num;
		cin >> car_num;
		if (car_num > 0) {
			my_parking_lot = push(my_parking_lot, car_num);
		}
		else {
			my_parking_lot = pop(my_parking_lot, -car_num);
		}
	/*	cout << my_parking_lot->_size << ": 크기 " << my_parking_lot->_car << " 대 \n";
		for (int i = 0; i < my_parking_lot->_size; i++) {
			cout <<my_parking_lot->arr[i] << " ";
		}
		cout << "\n\n";*/
	}
	for (int i = 0; i < my_parking_lot->_size; i++) {
		if (my_parking_lot->arr[i] != empty) {
			cout << i + 1 << " " << my_parking_lot->arr[i] << "\n";
		}
	}
}