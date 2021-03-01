// Copyright (c) 2021 red031000

#ifndef JSON_H
#define JSON_H

#include "options.h"

struct JsonToCellOptions *ParseNCERJson(char *path);
void FreeNCERCell(struct JsonToCellOptions *options);

#endif //JSON_H
