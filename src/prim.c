#include "prim.h"

#include <stdint.h>

#include "img.h"

void finxi_point(finxi_img_t img, unsigned x, unsigned y, uint32_t c) {
  if (x < img.width_ && y < img.height_) img.buffer_[x + (y * img.width_)] = c;
}
void finxi_point_i(finxi_img_t img, int x, int y, uint32_t c) {
  if (x >= 0 && y >= 0 && x < img.width_ && y < img.height_)
    img.buffer_[(unsigned)x + ((unsigned)y * img.width_)] = c;
}
void finxi_point_d(finxi_img_t img, double x, double y, uint32_t c) {
  if (x >= 0 && y >= 0 && x < img.width_ && y < img.height_)
    img.buffer_[(unsigned)x + ((unsigned)y * img.width_)] = c;
}

void finxi_line_low(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
                    unsigned y1, uint32_t c) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }
  int d = 2 * dy - dx;
  int y = y0;
  for (int x = x0; x <= x1; ++x) {
    if (x < img.width_ && y < img.height_)
      img.buffer_[x + (y * img.width_)] = c;
    if (d > 0) {
      y += yi;
      d -= (2 * dx);
    }
    d += (2 * dy);
  }
}
void finxi_line_high(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
                     unsigned y1, uint32_t c) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  int d = 2 * dx - dy;
  int x = x0;
  for (int y = y0; y <= y1; ++y) {
    if (x < img.width_ && y < img.height_)
      img.buffer_[x + (y * img.width_)] = c;
    if (d > 0) {
      x += xi;
      d -= (2 * dy);
    }
    d += (2 * dx);
  }
}

void finxi_line(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
                unsigned y1, uint32_t c) {
  if (abs((int)y1 - (int)y0) < abs((int)x1 - (int)x0)) {
    if (x0 > x1) {
      finxi_line_low(img, x1, y1, x0, y0, c);
    } else {
      finxi_line_low(img, x0, y0, x1, y1, c);
    }
  } else {
    if (y0 > y1) {
      finxi_line_high(img, x1, y1, x0, y0, c);
    } else {
      finxi_line_high(img, x0, y0, x1, y1, c);
    }
  }
}

void finxi_line_i(finxi_img_t img, int x0, int y0, int x1, int y1, uint32_t c) {
  if ((x0 < 0 && x1 < 0) || (y0 < 0 && y1 < 0) ||
      (x0 >= img.width_ && x1 >= img.width_) ||
      (y0 >= img.height_ && y1 >= img.height_)) {
    return;
  } else if (x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0) {
    if (x0 < 0) {
      x0 = (double)(y1 - y0) / (x1 - x0) * -x0 + y0;
    } else {
      x1 = (double)(y1 - y0) / (x1 - x0) * -x0 + y0;
    }
    if (y0 < 0) {
      y0 = (double)(x1 - x0) / (y1 - y0) * -y0 + x0;
    } else {
      y1 = (double)(x1 - x0) / (y1 - y0) * -y0 + x0;
    }
  }
  finxi_line(img, x0, y0, x1, y1, c);
}
void finxi_line_d(finxi_img_t img, double x0, double y0, double x1, double y1,
                  uint32_t c) {
  finxi_line_i(img, (int)x0, (int)y0, (int)x1, (int)y1, c);
}

void finxi_tri(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
               unsigned y1, unsigned x2, unsigned y2, uint32_t c) {
  finxi_line(img, x0, y0, x1, y1, c);
  finxi_line(img, x1, y1, x2, y2, c);
  finxi_line(img, x2, y2, x0, y0, c);
}
void finxi_tri_i(finxi_img_t img, int x0, int y0, int x1, int y1, int x2,
                 int y2, uint32_t c) {
  finxi_line_i(img, x0, y0, x1, y1, c);
  finxi_line_i(img, x1, y1, x2, y2, c);
  finxi_line_i(img, x2, y2, x0, y0, c);
}
void finxi_tri_d(finxi_img_t img, double x0, double y0, double x1, double y1,
                 double x2, double y2, uint32_t c) {
  finxi_line_d(img, x0, y0, x1, y1, c);
  finxi_line_d(img, x1, y1, x2, y2, c);
  finxi_line_d(img, x2, y2, x0, y0, c);
}
