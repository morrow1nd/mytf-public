#include "app_wrapper.h"
#include "app.hpp"

extern "C" {
	static Application app;

	void app_init(uint32_t width, uint32_t height) {
		app.Init(width, height);
	}
	
	void app_update(uint32_t* pixels, uint32_t width, uint32_t height, uint32_t time) {
		app.Update(pixels, width, height, time);
	}
	
	void app_release() {
		app.Release();
	}
}