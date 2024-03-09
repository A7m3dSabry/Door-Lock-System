

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/****************** Section: Includes ****************************/
/****************** Section: Macro Declarations ******************/





#define STD_ON    (1)
#define STD_OFF   (0)

#define STD_HIGH   (1)
#define STD_LOW    (0)

#ifndef NULL
#define NULL    ((void*)0)
#endif

#define E_OK        (0)
#define E_NOT_OK    (1)

/****************** Section: Macro Functions Declarations ********/

#define SET_BIT(REG, BIT)    ((REG)|=  (1<<(BIT)))
#define CLEAR_BIT(REG, BIT)    ((REG)&= ~(1<< (BIT)))
#define TOGGLE_BIT(REG, BIT)    ((REG)^=    (1<< (BIT)))
#define FORCE_BIT(REG, BIT, VAL)  ((VAL)? SET_BIT((REG),(BIT)): CLEAR_BIT((REG),(BIT)))


#define FORCE_MASK(REG, MASK, VAL)    ((REG)&= ~(MASK) , (REG)|=(VAL))
#define FORCE_MASK_OFFSET(REG, MASK, VAL, OFFSET)    ((REG)&= ~((MASK) << (OFFSET)) , (REG)|=((VAL) << (OFFSET)))
#define SET_MASK(REG, MASK) ((REG)=|(MASK))
#define CLEAR_MASK(REG, MASK)((REG)&=~(MASK))

#define READ_BIT(REG, BIT)    (((REG) & (1<<(BIT)))>>(BIT))
#define READ_MASK(REG, MASK)     ((REG) & (MASK))


#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )
/****************** Section: Data Types Declarations *************/



typedef char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;

typedef unsigned char         uint8_t;
typedef unsigned short        uint16_t;
typedef unsigned long         uint32_t;
typedef unsigned long long    uint64_t;

typedef signed char           sint8_t;
typedef signed short          sint16_t;
typedef signed long           sint32_t;
typedef signed long long      sint64_t;

typedef float                 f32_t;
typedef double                f64_t;


typedef uint8_t Std_ReturnType;



// REMOVE

#define PINA *(uint32_t *) 0
#define PINB *(uint32_t *) 0
#define PINC *(uint32_t *) 0
#define PIND *(uint32_t *) 0
#define PORTA *(uint32_t *) 0
#define PORTB *(uint32_t *) 0
#define PORTC *(uint32_t *) 0
#define PORTD *(uint32_t *) 0
#define DDRA *(uint32_t *) 0
#define DDRB *(uint32_t *) 0
#define DDRC *(uint32_t *) 0
#define DDRD *(uint32_t *) 0

#endif /* STD_TYPE_H_ */
