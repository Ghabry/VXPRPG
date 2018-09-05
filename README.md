# VXPRPG Player

VXPRPG Player is a game interpreter to play RPG Maker XP and VX games.

**This is a proof of concept, it can't run any games.**

The engine is mostly powered by EasyRPG Player and the startup code is taken
from mkxp.

## Requirements

### minimal / required

- SDL2 for screen backend support.
- Pixman for low level pixel manipulation.
- libpng for PNG image support.
- zlib for XYZ image support.

### extended / recommended

- FreeType2 for external font support (+ HarfBuzz for Unicode text shaping)
- mpg123 for better MP3 audio support
- WildMIDI for better MIDI audio support
- Libvorbis / Tremor for Ogg Vorbis audio support
- opusfile for Opus audio support
- libsndfile for better WAVE audio support
- libxmp for better tracker music support
- SpeexDSP for proper audio resampling
- SDL2_mixer for audio mixing. Used as a fallback when none of the provided
  audio libraries support the format. Due to API limitations not all audio
  effects are possible through SDL2_mixer audio.

SDL 1.2 and SDL_mixer 1.2 are still supported, but deprecated.

## Source code

VXPRPG Player development is hosted by GitHub, project files are available
in this git repository:

https://github.com/Ghabry/VXPRPG

## Bug reporting

Available options:

* File an issue at https://github.com/Ghabry/VXPRPG/issues
* Chat with us via IRC: #easyrpg at irc.freenode.net


## License

VXPRPG Player is free software available under the GPLv3 license. See the file
COPYING for license conditions.


### 3rd party software

VXPRPG Player makes use of the following 3rd party software:

* EasyRPG Player - Copyright (c) EasyRPG Player Authors, provided under GPLv3

* mkxp - Copyright (c) Ancurio, provided under GPLv3

* FMMidi YM2608 FM synthesizer emulator - Copyright (c) 2003-2006 yuno
  (Yoshio Uno), provided under the (3-clause) BSD license

* PicoJSON JSON parser/serializer - Copyright (c) 2009-2010 Cybozu Labs, Inc.
  Copyright (c) 2011-2015 Kazuho Oku, provided under the (2-clause) BSD license

* Dirent interface for Microsoft Visual Studio -
  Copyright (c) 2006-2012 Toni Ronkko, provided under the MIT license
