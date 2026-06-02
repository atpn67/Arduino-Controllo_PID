// Author: G.Topan
// Note:

#include "Arduino.h"
#include "MathUtils.h"

/******************************************************************************
 * moving average filter for integer
******************************************************************************/

void Filter30Int_init ( SFilter30Int *b )
{
    b->nelem = b->cnt = 0;
    memset(b, 0, sizeof (b->buf));
}

int Filter30Int_update ( int value, SFilter30Int *b, int nFill )
{
    long sum = 0;

    if (nFill > FILTER30_SIZE)
        nFill = (FILTER30_SIZE - 1);
    if (nFill < 1)
        nFill = 1;

    b->buf[b->cnt] = value;
    b->cnt = ( (b->cnt + 1) % nFill);
    if (b->nelem < nFill) {
        b->nelem++;
    } else {
        b->nelem = nFill;
    }
    for (int i = 0; i < b->nelem; i++) {
        sum += b->buf[i];
    }
    b->neamValue = (int) (sum / b->nelem);
    return (b->neamValue);
}

/******************************************************************************
 * moving average filter for float
******************************************************************************/

void Filter30Float_init ( SFilter30Float* b )
{
    b->nelem = b->cnt = 0;
    memset(b, 0, sizeof (b->buf));
}

int Filter30Float_update ( float value, SFilter30Float* b, int nFill )
{
    double sum = 0;

    if (nFill > FILTER30_SIZE)
        nFill = (FILTER30_SIZE - 1);
    if (nFill < 1)
        nFill = 1;

    b->buf[b->cnt] = value;
    b->cnt = ( (b->cnt + 1) % nFill);
    if (b->nelem < nFill) {
        b->nelem++;
    } else {
        b->nelem = nFill;
    }
    for (int i = 0; i < b->nelem; i++) {
        sum += b->buf[i];
    }
    b->neamValue = (float) (sum / b->nelem);
    return (b->neamValue);
}

/******************************************************************************
 * IIR filter for float variable
******************************************************************************/

void iirFilt_setup ( iirFilt_t* f, unsigned int fConst, int startValue )
{
    f->_count = fConst;
    f->_lastOut = startValue;
    f->_accum = startValue;
}

void iirFilt_start ( iirFilt_t* f, int startValue )
{
    f->_lastOut = startValue;
    f->_accum = startValue;
}

int iirFilt_filt ( iirFilt_t* f, int newVal )
{
    float x = newVal;
    x += f->_accum * (f->_count - 1);
    f->_accum = x / f->_count;
    f->_lastOut = (int) (roundf(f->_accum));
    return f->_lastOut;
}

int iirFilt_get ( iirFilt_t* f )
{
    return f->_lastOut;
}

