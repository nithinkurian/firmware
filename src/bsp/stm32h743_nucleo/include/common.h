#ifndef COMMON_H
#define COMMON_H


#define __vol volatile

#define ENABLE      1
#define DISABLE     0

#define SET         ENABLE
#define RESET       DISABLE

#define PIN_SET     SET
#define PIN_RESET   RESET

#define SET_BIT(reg,offset)                 (reg |=  (1 << offset))
#define CLEAR_BIT(reg,offset)               (reg &=  ~(1 << offset))
#define SET_BITS(reg,offset,value,mask)     (reg |=  ((mask&value) << offset))
#define CLEAR_BITS(reg,offset,mask)         (reg &= ~(mask         << offset))
#define WRITE_REG(reg,offset,value,mask)    do { CLEAR_BITS(reg,offset,mask); SET_BITS(reg,offset,value,mask);}while(0)
#define READ_BIT(reg,offset)                (reg |= (1 << offset))
#define READ_BITS(reg,offset,mask)          (reg |= (mask << offset))



#endif // COMMON_H