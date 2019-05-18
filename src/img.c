#include "img.h"

#include <stdint.h>
#include <stdlib.h>

finxi_img_t finxi_construct_img(const unsigned width, const unsigned height) {
  finxi_img_t img = {width, height,
                     (uint32_t*)malloc(width * height * sizeof(uint32_t))};
  return img;
}
void finxi_delete_img(finxi_img_t img) { free(img.buffer_); }

void finxi_fill(finxi_img_t img, uint32_t c){
  for(unsigned i = 0; i < img.width_ * img.height_; ++i){
    img.buffer_[i] = c;
  }
}

uint32_t finxi_get_pixel(const finxi_img_t img, const unsigned x,
                         const unsigned y) {
  if (x < img.width_ && y < img.height_) {
    return img.buffer_[x + (y * img.width_)];
  }
  return 0x000000;
}
