#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
float pi = 3.141592;

float getLength(int eumpyo) {
	float T;
	if (eumpyo == 4) {
		T = 1.0;
	}
	else if (eumpyo == 8) {
		T = 0.5;
	}
	else if (eumpyo == 16) {
		T = 0.25;
	}
	return T;
}

float getAmplitude(float name) {
	return name * 1000;
}

float getfrequency(char hh) {

	if (hh == 'A') {
		return 220.00;
	}
	if (hh == 'B') {
		return 246.94;
	}
	else if (hh == 'C') {
		return 261.63;
	}
	else if (hh == 'c') {
		return 277.18;
	}
	else if (hh == 'd') {
		return 311.13;
	}
	else if (hh == 'E') {
		return 329.63;
	}

	else {
		return 0;
	}
}

int main() {
	char header[44];
	int* fs, * b;
	short* n;

	ifstream myfile;
	myfile.open("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::in);
	if (!myfile) {
		cout << "cant read Beatles-LetItBe-wav_30s.wav\n" << endl;
		return 666;
	}
	myfile.read(header, sizeof(header));
	myfile.close();

	n = (short*)(header + 22);
	fs = (int*)(header + 24);
	b = (int*)(header + 28);

	cout << *n << endl;
	cout << *fs << endl;
	cout << *b << endl;

	int N = fs[0] * 10;
	short* data;
	data = new short[N];

	*n = 1;
	*b = n[0] * fs[0] * sizeof(short);
	myfile.read((char*)data, N * sizeof(short));

	ofstream xx("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::out);
	if (!xx) return 666;
	xx.write(header, 44 * sizeof(char));
	xx.write((char*)data, N * sizeof(short));
	xx.close();

	short* data1; data1 = new short[fs[0]];

	const float pi = 3.141592;

	float dt = 1. / fs[0], a = 10000.0, f = 440.0;
	for (int i = 0; i < fs[0]; i++)
		data1[i] = (short)(a * sin(2.0 * pi * f * i * dt));

	ofstream yy("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::out);
	if (!yy) return 123;
	yy.write(header, 44 * sizeof(char));
	yy.write((char*)data1, N * sizeof(short));
	yy.close();

	*b = *n * *fs * sizeof(short);

	int num, eu, ss;
	char hh;
	ifstream zz("music.txt");
	zz >> num; // 음표가 몇 개인지 읽기
	short data3[44100];
	ofstream xx3("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::out);
	if (!xx3) return 666;
	xx3.write(header, 44);
	for (int i = 0; i < 9; i++) {
		zz >> eu >> hh >> ss;  // eu ss는 int이고, hh는 char
		float f = getfrequency(hh);

		float a = getAmplitude(ss);

		float T = getLength(eu);

		for (int i = 0; i < 44100; i++) {
			data3[i] = (short)(a * sin(2.0 * pi * f * i * dt));
		}
		xx3.write((char*)data3, sizeof(short) * fs[0] * T);
		
		// 해당 시간만큼 a * sin(2*pi*f*t)를 샘플수(fs[0]*T)만큼 계산하여 data에 넣고,
		// 나의 wave file에 만들어진 sample 개수만큼 write한다.
	}
	xx3.close();
}

