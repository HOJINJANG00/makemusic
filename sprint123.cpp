#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
    char header[44];
    int* fs;    fs = (int*)(header + 24); // SampleRate
    int* b;     b = (int*)(header + 28);  // ByteRate
    short* n;   n = (short*)(header + 22);// NumChannels

    ifstream xx;
    xx.open("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::in);
    if (!xx) {
        cout << "cant read Beatles-LetItBe-wav_30s.wav\n" << endl;
        return 666;
    }
    xx.read(header, sizeof(header));

    // sprint 1 : ��� 44bytes �а� ����

    int N = fs[0] * 10;
    short* data;
    data = new short[N];

    *n = 1;
    *b = n[0] * fs[0] * sizeof(short);
    xx.read((char*)data, N * sizeof(short));
    xx.close(); // ���, ������ ����

    ofstream yy("my.wav", ios::binary | ios::out);
    if (!yy) return 666;
    yy.write(header, 44 * sizeof(char));
    yy.write((char*)data, N * sizeof(short));
    yy.close();

    // sprint 2 : 10�� ���Ͽ� ���� ��� ���� (�ӵ� ������)

    short* data2;
    data2 = new short[fs[0]];

    const float pi = 3.141592;
    float dt = 1. / fs[0], a = 10000.0, f = 440.0;
    for (int i = 0; i < fs[0]; i++) {
        data2[i] = (short)(a * sin(2.0 * pi * f * i * dt));
    }

    ofstream yy2("my.wav", ios::binary | ios::out); // ���� ofstream yy�� ���
    if (!yy2) return 666;
    yy2.write(header, 44 * sizeof(char));
    yy2.write((char*)data2, fs[0] * sizeof(short));
    yy2.close();

    // sprint 3 : �� 1�� ���
}