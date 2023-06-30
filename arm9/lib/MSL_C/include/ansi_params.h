#ifndef POKEDIAMOND_MSL_C_ANSI_PARAMS_H
#define POKEDIAMOND_MSL_C_ANSI_PARAMS_H

#ifdef __cplusplus
#define _MSL_BEGIN_NAMESPACE_STD  namespace std {
#define _MSL_BEGIN_EXTERN_C       extern "C" {
#define _MSL_END_EXTERN_C         }
#define _MSL_END_NAMESPACE_STD    }
#else
#define _MSL_BEGIN_NAMESPACE_STD 
#define _MSL_BEGIN_EXTERN_C 
#define _MSL_END_EXTERN_C 
#define _MSL_END_NAMESPACE_STD 
#endif //__cplusplus

#endif //POKEDIAMOND_MSL_C_ANSI_PARAMS_H
