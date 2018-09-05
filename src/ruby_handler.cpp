//
// Created by gabriel on 5/09/18.
//

#include "ruby_handler.h"

#include "filefinder.h"

#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include "rice/global_function.hpp"

#include "audio.h"
#include "bitmap.h"
#include "color.h"
#include "font.h"
#include "graphics.h"
#include "input.h"
#include "plane.h"
#include "rect.h"
#include "sprite.h"
#include "table.h"
#include "tilemap.h"
#include "tone.h"
#include "viewport.h"
#include "window.h"

using namespace Rice;

template<class T>
T* marshal_load(const char* str) {
	return new T();
}

template<>
Font* marshal_load(const char* str) {
	return Font::Default().get();
}

Object load_data(const char *filename) {
	using namespace Rice;

	VALUE marsh = rb_const_get(rb_cObject, rb_intern("Marshal"));
	VALUE file = rb_const_get(rb_cObject, rb_intern("File"));
	Object marsh_obj(marsh);
	Object file_obj(file);

	String str(FileFinder::FindDefault(filename));

	Object file_handle = file_obj.call("open", str.c_str());

	Object res = marsh_obj.call("load", file_handle);
	return to_ruby(res);
}

void RubyHandler::Init() {
	ruby_init();

	Data_Type<Bitmap> rb_bitmap =
			define_class<Bitmap>("Bitmap")
			        .define_constructor(Constructor<Bitmap>())
					.define_singleton_method("_load", &marshal_load<Bitmap>);

	Data_Type<Color> rb_color =
			define_class<Color>("Color")
					.define_singleton_method("_load", &marshal_load<Color>);

	Data_Type<Font> rb_font =
			define_class<Font>("Font")
					.define_singleton_method("_load", &marshal_load<Font>);

	Data_Type<Plane> rb_plane =
			define_class<Plane>("Plane")
					.define_singleton_method("_load", &marshal_load<Plane>);

	Data_Type<Rect> rb_rect =
			define_class<Rect>("Rect")
					.define_singleton_method("_load", &marshal_load<Rect>);

	Data_Type<Sprite> rb_sprite =
			define_class<Sprite>("Sprite")
					.define_constructor(Constructor<Sprite>())
					.define_singleton_method("_load", &marshal_load<Sprite>);

	Data_Type<Table> rb_table =
			define_class<Table>("Table")
			        .define_singleton_method("_load", &marshal_load<Table>);

	Data_Type<Tilemap> rb_tilemap =
			define_class<Tilemap>("Tilemap")
					.define_singleton_method("_load", &marshal_load<Tilemap>);

	Data_Type<Tone> rb_tone =
			define_class<Tone>("Tone")
					.define_singleton_method("_load", &marshal_load<Tone>);

	Data_Type<Viewport> rb_viewport =
			define_class<Viewport>("Viewport")
					.define_singleton_method("_load", &marshal_load<Viewport>);

	Data_Type<Window> rb_window =
			define_class<Window>("Window")
					.define_singleton_method("_load", &marshal_load<Window>);

	Class rb_audio =
			define_class("Audio");

	Class rb_graphics =
			define_class("Graphics");

	Class rb_input =
			define_class("Input");

	define_global_function("load_data", &load_data);
}
