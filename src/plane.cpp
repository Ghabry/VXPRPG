/*
 * This file is part of VXPRPG and based on the same file of EasyRPG Player.
 *
 * VXPRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VXPRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VXPRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include "plane.h"
#include "graphics.h"
#include "player.h"
#include "bitmap.h"
#include "main_data.h"

Plane::Plane() :
	type(TypePlane),
	visible(true),
	z(0),
	ox(0),
	oy(0) {

	Graphics::RegisterDrawable(this);
}

Plane::~Plane() {
	Graphics::RemoveDrawable(this);
}

void Plane::Draw() {
	if (!visible || !bitmap) return;

	if (needs_refresh) {
		needs_refresh = false;

		if (!tone_bitmap ||
			bitmap->GetWidth() != tone_bitmap->GetWidth() ||
			bitmap->GetHeight() != tone_bitmap->GetHeight()) {
			tone_bitmap = Bitmap::Create(bitmap->GetWidth(), bitmap->GetHeight());
		}
		tone_bitmap->Clear();
		tone_bitmap->ToneBlit(0, 0, *bitmap, bitmap->GetRect(), tone_effect, Opacity::opaque);
	}

	BitmapRef source = tone_effect == Tone() ? bitmap : tone_bitmap;

	BitmapRef dst = DisplayUi->GetDisplaySurface();
	Rect dst_rect = dst->GetRect();
	int src_x = -ox;
	int src_y = -oy;

	dst->TiledBlit(src_x, src_y, source->GetRect(), *source, dst_rect, 255);
}

BitmapRef const& Plane::GetBitmap() const {
	return bitmap;
}
void Plane::SetBitmap(BitmapRef const& nbitmap) {
	bitmap = nbitmap;

	needs_refresh = true;
}

bool Plane::GetVisible() const {
	return visible;
}
void Plane::SetVisible(bool nvisible) {
	visible = nvisible;
}
int Plane::GetZ() const {
	return z;
}
void Plane::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZCallback();
	z = nz;
}
int Plane::GetOx() const {
	return ox;
}
void Plane::SetOx(int nox) {
	ox = nox;
}
int Plane::GetOy() const {
	return oy;
}
void Plane::SetOy(int noy) {
	oy = noy;
}

Tone Plane::GetTone() const {
	return tone_effect;
}

void Plane::SetTone(Tone tone) {
	if (tone_effect != tone) {
		tone_effect = tone;
		needs_refresh = true;
	}
}

DrawableType Plane::GetType() const {
	return type;
}
