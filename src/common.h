#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#define G_WHITE (Color){ 239, 239, 239, 255 }
#define G_BLACK (Color){ 44,  44,  44,  255 }
#define G_RED   (Color){ 240, 96,  39,  255 }
#define G_GREEN (Color){ 6,   167, 125, 255 }

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
