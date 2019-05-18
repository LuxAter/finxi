#ifndef FINXI_IMG_H_
#define FINXI_IMG_H_

#ifdef cplusplus__
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct finxi_img {
  unsigned width_, height_;
  uint32_t* buffer_;
} finxi_img_t;

finxi_img_t finxi_construct_img(const unsigned width, const unsigned height);
void finxi_delete_img(finxi_img_t img);

void finxi_fill(finxi_img_t img, uint32_t c);

uint32_t finxi_get_pixel(const finxi_img_t img, const unsigned x,
                         const unsigned y);

#ifdef cplusplus__
}
#endif

#endif  // FINXI_IMG_H_
