#ifndef __LIB_GFX_H_
#define __LIB_GFX_H_ 1

typedef int          int32_t;
typedef unsigned int uint32_t;
typedef uint32_t     color_t;

void gfx_clear(color_t* pixels, color_t color, int32_t w, int32_t h);
void gfx_rect(color_t* pixels, color_t color, int32_t pixels_w, int32_t pixels_h, int32_t pos_x, int32_t pos_y, int32_t rect_w, int32_t rect_h);

#ifdef INCLUDE_GFX_IMPLEMENTATION

void gfx_clear(color_t* pixels, color_t color, int32_t w, int32_t h) {
	for (int32_t y = 0; y < h; ++y) {
		for (int32_t x = 0; x < w; ++x) {
			pixels[y * w + x] = color;
		}
	}
}

void gfx_rect(color_t* pixels, color_t color, int32_t pixels_w, int32_t pixels_h, int32_t pos_x, int32_t pos_y, int32_t rect_w, int32_t rect_h) {
	for (int32_t dy = 0; dy < rect_h; ++dy) {
		int32_t y = pos_y + dy;
		if (y >= 0 && y < pixels_h) {
			for (int32_t dx = 0; dx < rect_w; ++dx) {
				int32_t x = pos_x + dx;
				if (x >= 0 && x < pixels_h) {
					pixels[y * pixels_w + x] = color;
				}
			}
		}
	}
}

#endif

#endif // __LIB_GFX_H_

