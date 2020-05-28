#ifndef _REBOOTER_H_
#define _REBOOTER_H_

#ifdef __cplusplus
extern "C" {
#endif

void rebooter_init(void);
void rebooter(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* _REBOOTER_H_ */

