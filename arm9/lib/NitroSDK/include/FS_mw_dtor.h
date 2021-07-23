#ifndef NITRO_FS_MW_DTOR_H_
#define NITRO_FS_MW_DTOR_H_

typedef void (*MWI_DESTRUCTOR_FUNC) (void *);

typedef struct MWiDestructorChain
{
    struct MWiDestructorChain *next;
    MWI_DESTRUCTOR_FUNC dtor;
    void *obj;
}
MWiDestructorChain;

extern MWiDestructorChain *__global_destructor_chain;

#endif //NITRO_FS_MW_DTOR_H_
