#include "finxi.h"

int main(int argc, char* argv[]) {
  finxi_img_t img = finxi_construct_img(500, 500);
  finxi_fill(img, 0xffffff);
  finxi_point(img, 57, 48, 0xff00ff);
  finxi_tri(img, 50, 50, 150, 50, 50, 150, 0x00ffff);
  finxi_bmp_write("test.bmp", img);
  finxi_delete_img(img);
  return 0;
}
