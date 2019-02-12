#include "tinythreads.h"
#include "avrprint.h"       // Lab 1 stuff
#include "avrinit.h"

#include <stdint.h>

uint16_t isPrime(uint16_t i);   // from lab 1

void printAt(uint16_t num, uint16_t pos);
void computePrimes(int pos);
void wong(int i);

uint16_t pp;
mutex m = MUTEX_INIT;


int main(void) {

    initCPU();
    initLCD();
    //initInt();
    //initInput();

    //TCNT1 = 0; // clear system clk
    //// Set Output Compare Register A
    //OCR1A = 391;  // 8 M / 1024 / 20


    //while (1) {
    //    writeLong((long) TCNT1);
    //}

    spawn(computePrimes, 0);
    computePrimes(3);

    return 0;
}


void printAt(uint16_t num, uint16_t pos) {
    lock(&m);
    //uint16_t pp = pos;
    pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    int i;
    for (i = 0; i<1000; i++);
    pp++;
    writeChar( num % 10 + '0', pp);
    unlock(&m);
}


void computePrimes(int pos) {
    uint16_t n;

    for(n = 1; ; n++) {
        if (isPrime(n)) {
            printAt(n, pos);
            //yield();
        }
    }
}


uint16_t isPrime(uint16_t i) {

    if (i == 2 || i == 1) {
        return 1;
    }

    for (uint16_t j = 2; j < (i >> 1); j++) {
        if (i % j == 0) {
            return 0;
        }
    }
    return 1;
}
