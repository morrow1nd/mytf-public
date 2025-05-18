#ifndef SGL_APP_H
#define SGL_APP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	void app_init(uint32_t width, uint32_t height);
	void app_update(uint32_t* pixels, uint32_t width, uint32_t height, uint32_t time);
	void app_release();

#ifdef __cplusplus
}
#endif

#endif // !SGL_APP_H
