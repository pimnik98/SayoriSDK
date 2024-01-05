#ifndef SAYORISDK_STDDEF_H
#define SAYORISDK_STDDEF_H

#define nullptr ((void*)0)
#define NULL (0)

#define ON_NULLPTR(ptr, code)

#define SAYORI_INLINE static inline __attribute__((always_inline))

#define KB (1 << 10)
#define MB (1 << 20)
#define GB (1 << 30)

#define ALIGN(value, align) ((value) + ((-(value)) & ((align) - 1)))
#define IS_ALIGNED(value, align) ((value) % (align) == 0)

#define offsetof( st, m ) ( (size_t) (& ((st *)0)->m ) )

#endif //SAYORISDK_STDDEF_H
