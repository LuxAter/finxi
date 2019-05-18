#ifndef FINXI_BMP_H_
#define FINXI_BMP_H_

#ifdef cplusplus__
extern "C" {
#endif

#include <stdbool.h>

#include "img.h"

bool finxi_bmp_write(const char* file_name, const finxi_img_t img);

#ifdef cplusplus__
}
#endif

#endif  // FINXI_BMP_H_
