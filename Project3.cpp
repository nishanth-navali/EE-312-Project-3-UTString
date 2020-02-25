// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Nishanth Navali
// nan686
// Slip days used: <0>
// Spring 2020
// Copy and paste this file at the top of all your submitted source code files.  Do not turn this in by itself.
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cstdio>
#include "String.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * outputs the length of string
 */
uint32_t lengthOf(const char* arr) {
    int i = 0;
    while(arr[i] != 0) {
        i++;
    }
    return i;
}

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    uint32_t len = lengthOf(src);
    uint32_t cap = len;
    uint32_t i;
    UTString *out = (UTString*) malloc(1 * sizeof(UTString));
    out -> length = len;
    out -> capacity = cap;
    char *ptr =  (char*) malloc(len + 5);
    for(i = 0; i < len; i++) {
        ptr[i] = src[i];
    }


    i++;
    ptr[i] = 0;
//    *(uint32_t*)( out->string + out->length + 1 ) = SIGNATURE;
//    i++;
//    ptr[i] = (char) 0xde;
//    i++;
//    ptr[i] = (char) 0xad;
//    i++;
//    ptr[i] = (char) 0xbe;
//    i++;
//    ptr[i] = (char) 0xef;
    out -> string = ptr;
    return out;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    if(isOurs(s)) {
        return s->length;
    }
    else {
        return -1; // TODO: Find the real value you return;
    }
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) { // TODO: Make it an actual UTString
//    if(!isOurs(s)) {
//        return s;
//    }
    char* str = s->string;
    uint32_t i = 0;
    while((i + s->length < s->capacity) && (suffix[i] != 0)) {
        str[i+s->length] = suffix[i];
        i++;
    }
    s->length += i;
    s->string = str;
    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) { // TODO: Make it an actualy utstring
//    if(!isOurs(dst)) {
//        return dst;
//    }
    char* str = dst->string;
    uint32_t strLen = 0;
    while(str[strLen] != 0 && src[strLen] != 0) {
        str[strLen] = src[strLen];
        strLen++;
    }
    if(src[strLen] == 0) {
        uint32_t i = strLen + 1;
        while(str[i] != 0) {
            str[i] = 0;
            i++;
        }
        dst->length = lengthOf(src);
    }
    else {
        if(strLen < dst->capacity) {
            for(;strLen < dst->capacity; strLen++) {
                if(src[strLen] == 0) {
                    break;
                }
                else {
                    str[strLen] = src[strLen];
                }
            }
        }
        dst->length = strLen;
    }
    dst->string = str;
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    if (new_capacity <= (s->capacity)) {
        return s;
    } else {
        const char* old_str = s->string;
        char* new_str = (char*) malloc(new_capacity + 5);
        for(uint32_t i = 0; i < lengthOf(old_str); i++) {
            new_str[i] = old_str[i];
        }
        s->string = new_str;
        s->capacity = new_capacity;
        free((void *) old_str);
        return s;
    }
}

