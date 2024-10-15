
#ifndef COMPILER_H
#define COMPILER_H

#define INLINE  inline
#define STATIC  static

#ifndef NULL_PTR
  #define NULL_PTR  ((void *)0)
#endif


#define AUTOMATIC

#define TYPEDEF

#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

#define FUNC(rettype, memclass) rettype

#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass

#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define CONST(type, memclass) const type

#define VAR(type, memclass) type

#endif /* #ifndef COMPILER_H */

