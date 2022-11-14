#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "MySTLUtil.h"
#include "wiringPi.h"

using namespace std;

const string prjName = "OdroidTest1";

int main() {
    cout << prjName << "에 오신 것을 환영합니다!" << endl;

    vector<string> lines;
    shared_ptr<string> pstr;

    wiringPiSetup();
    pinMode(0, OUTPUT);

    int i = 0;
    while (true) {
        digitalWrite(0, HIGH);
        cout << i++ << endl;
        delay(1000);
        //sleep(1);
        if (i >= 100) break;
    }

    //getchar();
    return 0;
}
