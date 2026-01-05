#include "PlayerPal.h"
#include "Reader/Reader.h"

void PlayerPal::init() {
  Reader reader("./Data/H3bitmap.lod/PLAYERS.PAL");
  reader.seek(24);
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 32; ++j) {
      palette[i][j].r = reader.readU8();
      palette[i][j].g = reader.readU8();
      palette[i][j].b = reader.readU8();
      palette[i][j].a = SDL_ALPHA_OPAQUE;
      reader.skip(1);
    }
  }
}