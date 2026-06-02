// Author: G.Topan
// Note:

#include "stdint.h"

// used by Filter30() API
#define FILTER30_SIZE   30
typedef struct _type_mavg_int {
    int cnt;                // current buffer index
    int nelem;              // number of elements stored
    int buf[FILTER30_SIZE]; // buffer to store elements
    int neamValue;          // computed mean value
} SFilter30Int;

typedef struct _type_mavg_float {
    int cnt;                // current buffer index
    int nelem;              // number of elements stored
    float buf[FILTER30_SIZE];   // buffer to store elements
    float neamValue;            // computed mean value
} SFilter30Float;

/**
 * This struct contains the information to manage an IIR filter.
 * Do not access fields directly, use the API instead.
 */
typedef struct iirFilt_tag {
   int _lastOut;
   float _accum;
   unsigned int _count;
}iirFilt_t;

/**
 * Moving average filter for integer variable, limited to max 30 value
 * The filter works if it is called every 10ms or 100ms
*/

/**
 * Initialize struct for Moving average filter
 * @param b         [out] pointer to the buffer data structure
 */
void Filter30Int_init ( SFilter30Int* b );

/**
 * update for Moving average filter
 * The filter works if it is called every 10ms or 100ms
 *
 * @param value     [in] value to filter or mediate
 * @param *b        [out] pointer to the buffer data structure
 * @param nFil      [in] number element to use for mean
 * @return computed mean value
 */
int Filter30Int_update ( int value, SFilter30Int* b, int nFil );

/**
 * Moving average filter for float variable, limited to max 30 value
 * The filter works if it is called every 10ms or 100ms
*/

/**
 * Initialize struct for Moving average filter
 * @param b         [out] pointer to the buffer data structure
 */
void Filter30Float_init ( SFilter30Float* b );

/**
 * update for Moving average filter
 * The filter works if it is called every 10ms or 100ms
 *
 * @param value     [in] value to filter or mediate
 * @param *b        [out] pointer to the buffer data structure
 * @param nFil      [in] number element to use for mean
 * @return computed mean value
 */
int Filter30Float_update ( float value, SFilter30Float* b, int nFil );

/**
 * IIR filter for float variable
 * The filter works if it is called every 10ms or 100ms
*/

/**
 * Setup the filter with @p C as constant for calculations and @p startValue as
 * first output value.
 * @param filt          filter struct pointer
 * @param fConst        filtering constant
 * @param startValue    first filter output
 */
 void iirFilt_setup(iirFilt_t* filt, unsigned int fConst, int startValue);

/**
 * Start filter output to a new value. To be used when starting to filter
 * from a specific value.
 * @param f             filter struct pointer
 * @param startValue    filter output
 */
 void iirFilt_start(iirFilt_t* f, int startValue);

/**
 * Calculates the new filtered value based on new input value
 * @param f             filter struct pointer
 * @param newVal        input value to be filtered
 * @return              the filtered value
 */
int iirFilt_filt(iirFilt_t* f, int newVal);

/**
 * Get the (last) output of the filter.
 * @param f             filter struct pointer
 * @return              output of the filter
 */
int iirFilt_get(iirFilt_t* f);

