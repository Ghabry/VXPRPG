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
#include <sstream>
#include <array>

#include "graphics.h"
#include "cache.h"
#include "output.h"
#include "player.h"
#include "fps_overlay.h"
#include "message_overlay.h"
#include "transition.h"
#include "drawable.h"

namespace Graphics {
	void UpdateTitle();
	void LocalDraw(int priority = Priority::Priority_Maximum);
	void GlobalDraw(int priority = Priority::Priority_Maximum);

	int framerate;

	uint32_t next_fps_time;

	std::shared_ptr<State> global_state;
	std::shared_ptr<State> local_state;

	bool SortDrawableList(const Drawable* first, const Drawable* second);

	std::unique_ptr<Transition> transition;
	std::unique_ptr<MessageOverlay> message_overlay;
	std::unique_ptr<FpsOverlay> fps_overlay;
}

unsigned SecondToFrame(float const second) {
	return(second * Graphics::framerate);
}

void Graphics::Init() {
	global_state.reset(new State());
	local_state.reset(new State());

	// Is a drawable, must be init after state
	transition.reset(new Transition());
	message_overlay.reset(new MessageOverlay());
	fps_overlay.reset(new FpsOverlay());

	next_fps_time = 0;
}

void Graphics::Quit() {
	global_state->drawable_list.clear();

	transition.reset();
	fps_overlay.reset();
	message_overlay.reset();

	Cache::Clear();
}

void Graphics::Update() {
	//FPS:
	if (next_fps_time == 0) {
		next_fps_time = DisplayUi->GetTicks() + 1000;
	}

	uint32_t current_time = DisplayUi->GetTicks();
	if (current_time >= next_fps_time) {
		next_fps_time += 1000;

		if (fps_overlay->GetFps() == 0) {
			Output::Debug("Framerate is 0 FPS!");
			Draw();
		}

		next_fps_time = current_time + 1000;
		fps_overlay->ResetCounter();
		UpdateTitle();
	}

	//Update Graphics:
	fps_overlay->Update();
	fps_overlay->AddUpdate();
	message_overlay->Update();
	transition->Update();
}

void Graphics::UpdateTitle() {
	if (DisplayUi->IsFullscreen()) return;
#ifdef EMSCRIPTEN
	return;
#endif

	std::stringstream title;
	if (!Player::game_title.empty()) {
		title << Player::game_title << " - ";
	}
	title << GAME_TITLE;

	if (Player::fps_flag) {
		title << " - " << fps_overlay->GetFpsString();
	}

	DisplayUi->SetTitle(title.str());
}

void Graphics::Draw() {
	fps_overlay->AddFrame();

	if (transition->IsErased()) {
		DisplayUi->CleanDisplay();
		GlobalDraw();
		DisplayUi->UpdateDisplay();
		return;
	}
	LocalDraw();
	GlobalDraw();
	DisplayUi->UpdateDisplay();
}

void Graphics::LocalDraw(int priority) {
	State& state = *local_state;
	if (state.zlist_dirty) {
		state.drawable_list.sort(SortDrawableList);
		state.zlist_dirty = false;
	}

	for (Drawable* drawable : state.drawable_list) {
		if (drawable->GetZ() <= priority) {
			drawable->Draw();
		}
	}
}

void Graphics::GlobalDraw(int priority) {
	if (global_state->zlist_dirty) {
		global_state->drawable_list.sort(SortDrawableList);
		global_state->zlist_dirty = false;
	}
	for (Drawable* drawable : global_state->drawable_list)
		if (drawable->GetZ() <= priority)
			drawable->Draw();
}

BitmapRef Graphics::SnapToBitmap(int priority) {
	LocalDraw(priority);
	GlobalDraw(priority);
	return DisplayUi->CaptureScreen();
}

bool Graphics::IsTransitionPending() {
	return (transition ? transition->IsActive() : false);
}

void Graphics::FrameReset() {
	next_fps_time = (uint32_t)DisplayUi->GetTicks() + 1000;
	fps_overlay->ResetCounter();
}

void Graphics::RegisterDrawable(Drawable* drawable) {
	if (drawable->IsGlobal()) {
		global_state->drawable_list.push_back(drawable);
	} else {
		local_state->drawable_list.push_back(drawable);
	}
	UpdateZCallback();
}

void Graphics::RemoveDrawable(Drawable* drawable) {
	std::list<Drawable*>::iterator it;
	if (drawable->IsGlobal()) {
		it = std::find(global_state->drawable_list.begin(), global_state->drawable_list.end(), drawable);
		if (it != global_state->drawable_list.end()) { global_state->drawable_list.erase(it); }
	} else {
		State& state = *local_state;
		it = std::find(state.drawable_list.begin(), state.drawable_list.end(), drawable);
		if (it != state.drawable_list.end()) { state.drawable_list.erase(it); }
	}
}

void Graphics::UpdateZCallback() {
	local_state->zlist_dirty = true;
	global_state->zlist_dirty = true;
}

inline bool Graphics::SortDrawableList(const Drawable* first, const Drawable* second) {
	return first->GetZ() < second->GetZ();
}

int Graphics::GetDefaultFps() {
	return DEFAULT_FPS;
}

MessageOverlay& Graphics::GetMessageOverlay() {
	return *message_overlay;
}

Transition& Graphics::GetTransition() {
	return *transition;
}
