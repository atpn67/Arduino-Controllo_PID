// Author: G.Topan
// Note: 

#ifndef CMYLCD_H
#define CMYLCD_H

#include "stdint.h"
#include <LiquidCrystal.h>

class CMyLCD : public LiquidCrystal {
public:
    CMyLCD();

    virtual ~ CMyLCD() {};

    void init();

    void printCentered(const char* text);

    void api1();

    void api2();

};

#endif // CMYLCD_H
