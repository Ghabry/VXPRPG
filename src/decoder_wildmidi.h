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

#ifndef EP_DECODER_WILDMIDI_H
#define EP_DECODER_WILDMIDI_H

// Headers
#include <string>
#include <memory>
#ifdef HAVE_WILDMIDI
#include <wildmidi_lib.h>
#endif
#include "audio_decoder.h"

/**
 * Audio decoder for MIDI powered by WildMidi
 */
class WildMidiDecoder : public AudioDecoder {
public:
	WildMidiDecoder(const std::string file_name);

	~WildMidiDecoder();

	bool WasInited() const override;

	// Audio Decoder interface
	bool Open(FILE* file) override;

	bool Seek(size_t offset, Origin origin) override;

	bool IsFinished() const override;

	void GetFormat(int& frequency, AudioDecoder::Format& format, int& channels) const override;

	bool SetFormat(int frequency, AudioDecoder::Format format, int channels) override;
private:
	int FillBuffer(uint8_t* buffer, int length) override;

	std::string filename;
#ifdef HAVE_WILDMIDI
	midi* handle = NULL;
#endif
};

#endif
