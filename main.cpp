#include <iostream>
#include <string>
#include <vector>
//#include "MySTLUtil.h"
#include "wiringPi.h"

using namespace std;
const string prjName = "OdroidTest1";

int main() {
    cout << prjName << "에 오신 것을 환영합니다!" << endl;

    vector<string> lines;

    wiringPiSetup();

    int i = 0;
    while (true) {
        cout << i++ << endl;
            delay(1000);
    }

    getchar();
    return 0;
}
