#include <stdint.h>
static uint32_t add(uint32_t left, uint32_t right);
static uint32_t add(uint32_t left, uint32_t right){return left+right;}
int main(void){const uint32_t value=add(1UL,2UL);return (value==3UL)?0:1;}
