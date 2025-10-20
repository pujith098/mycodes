/*
File: circular_buffer.c
Description: Minimal fixed-size circular buffer for bytes with basic push/pop.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define CB_SIZE 8


typedef struct {
uint8_t buf[CB_SIZE];
uint8_t head;
uint8_t tail;
uint8_t count;
} circbuf_t;


void cb_init(circbuf_t *cb) { cb->head = cb->tail = cb->count = 0; }


bool cb_push(circbuf_t *cb, uint8_t v) {
if (cb->count == CB_SIZE) return false; // full
cb->buf[cb->head++] = v;
if (cb->head == CB_SIZE) cb->head = 0;
cb->count++;
return true;
}


bool cb_pop(circbuf_t *cb, uint8_t *v) {
if (cb->count == 0) return false; // empty
*v = cb->buf[cb->tail++];
if (cb->tail == CB_SIZE) cb->tail = 0;
cb->count--;
return true;
}


int main(void) {
circbuf_t cb;
cb_init(&cb);
for (int i=0;i<10;i++) cb_push(&cb, (uint8_t)i);
uint8_t val;
while (cb_pop(&cb, &val)) printf("%u ", val);
printf("\n");
return 0;
}
