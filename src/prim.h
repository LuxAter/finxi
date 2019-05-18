#ifndef FINXI_PRIM_H_
#define FINXI_PRIM_H_

#ifdef cplusplus__
extern "C" {
#endif

#include <stdint.h>

#include "img.h"

void finxi_point(finxi_img_t img, unsigned x, unsigned y, uint32_t c);
void finxi_point_i(finxi_img_t img, int x, int y, uint32_t c);
void finxi_point_d(finxi_img_t img, double x, double y, uint32_t c);

void finxi_line(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
                unsigned y1, uint32_t c);
void finxi_line_i(finxi_img_t img, int x0, int y0, int x1, int y1, uint32_t c);
void finxi_line_d(finxi_img_t img, double x0, double y0, double x1, double y1,
                  uint32_t c);

void finxi_tri(finxi_img_t img, unsigned x0, unsigned y0, unsigned x1,
               unsigned y1, unsigned x2, unsigned y2, uint32_t c);
void finxi_tri_i(finxi_img_t img, int x0, int y0, int x1, int y1, int x2,
                 int y2, uint32_t c);
void finxi_tri_d(finxi_img_t img, double x0, double y0, double x1, double y1,
                 double x2, double y2, uint32_t c);

void finxi_rect(finxi_img_t img, unsigned x, unsigned y, unsigned w, unsigned h,
                uint32_t c);
void finxi_rect_i(finxi_img_t img, int x, int y, int w, int h, uint32_t c);
void finxi_rect_d(finxi_img_t img, double x, double y, double w, double h,
                  uint32_t c);

void finxi_circle(finxi_img_t img, unsigned x, unsigned y, unsigned r,
                  uint32_t c);
void finxi_circle_i(finxi_img_t img, int x, int y, int r, uint32_t c);
void finxi_circle_d(finxi_img_t img, double x, double y, double r, uint32_t c);

void finxi_normal_poly(finxi_img_t, unsigned x, unsigned y, unsigned n,
                       uint32_t c);
void finxi_normal_poly_i(finxi_img_t, int x, int y, unsigned n, uint32_t c);
void finxi_normal_poly_d(finxi_img_t, double x, double y, unsigned n,
                         uint32_t c);

void finxi_poly(finxi_img_t img, unsigned* x, unsigned* y, unsigned n,
                uint32_t c);
void finxi_poly_i(finxi_img_t img, int* x, int* y, unsigned n, uint32_t c);
void finxi_poly_d(finxi_img_t img, double* x, double* y, unsigned n,
                  uint32_t c);

#ifdef cplusplus__
}
#endif

#endif  // FINXI_PRIM_H_
