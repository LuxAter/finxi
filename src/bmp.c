#include "bmp.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img.h"

bool finxi_bmp_write(const char* file_name, const finxi_img_t img) {
  unsigned file_size = 54 + 3 * img.width_ * img.height_;

  uint8_t* byte_data = (uint8_t*)malloc(3 * img.width_ * img.height_);
  if (byte_data == NULL) {
    return false;
  }
  memset(byte_data, 0, 3 * img.width_ * img.height_);
  for (unsigned x = 0; x < img.width_; ++x) {
    for (unsigned y = 0; y < img.height_; ++y) {
      unsigned x_ind = x, y_ind = (img.height_ - 1) - y;
      uint8_t r = ((img.buffer_[x + (y * img.width_)] >> 16) & 0XFF);
      uint8_t g = ((img.buffer_[x + (y * img.width_)] >> 8) & 0XFF);
      uint8_t b = ((img.buffer_[x + (y * img.width_)]) & 0XFF);
      byte_data[(x_ind + y_ind * img.width_) * 3 + 0] = b;
      byte_data[(x_ind + y_ind * img.width_) * 3 + 1] = g;
      byte_data[(x_ind + y_ind * img.width_) * 3 + 2] = r;
    }
  }

  unsigned char file_header[14] = {'B', 'M', 0, 0,  0, 0, 0,
                                   0,   0,   0, 54, 0, 0, 0};
  unsigned char info_header[40] = {40, 0, 0, 0, 0, 0, 0,  0,
                                   0,  0, 0, 0, 1, 0, 24, 0};
  unsigned char pad[3] = {0, 0, 0};

  file_header[2] = (unsigned char)(file_size);
  file_header[3] = (unsigned char)(file_size >> 8);
  file_header[4] = (unsigned char)(file_size >> 14);
  file_header[5] = (unsigned char)(file_size >> 24);

  info_header[4] = (unsigned char)(img.width_);
  info_header[5] = (unsigned char)(img.width_ >> 8);
  info_header[6] = (unsigned char)(img.width_ >> 16);
  info_header[7] = (unsigned char)(img.width_ >> 24);
  info_header[8] = (unsigned char)(img.height_);
  info_header[9] = (unsigned char)(img.height_ >> 8);
  info_header[10] = (unsigned char)(img.height_ >> 16);
  info_header[11] = (unsigned char)(img.height_ >> 24);

  FILE* out = fopen(file_name, "wb");
  if (out == NULL) {
    free(byte_data);
    return false;
  }
  fwrite(file_header, 1, 14, out);
  fwrite(info_header, 1, 40, out);
  for (unsigned i = 0; i < img.height_; ++i) {
    fwrite(byte_data + (img.width_ * (img.height_ - (img.height_ - i - 1) - 1) * 3), 3, img.width_,
           out);
    fwrite(pad, 1, (4 - (img.width_ * 3) % 4) % 4, out);
  }
  free(byte_data);
  fclose(out);
  return true;
}
