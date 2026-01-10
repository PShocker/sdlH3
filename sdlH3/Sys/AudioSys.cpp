#include "AudioSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_stdinc.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

static SDL_AudioStream *stream = NULL;

static SDL_AudioSpec spec = {
    .format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};

// AITheme0.wav
// horse00.wav
static void prepareAudio() {
  // switch (condition) {

  // }
  if (!Global::audioData.contains("AITheme0.wav")) {
    Global::audioData["AITheme0.wav"] = 0;
  }
  if (Global::heroMove) {
    if (!Global::audioData.contains("horse00.wav")) {
      Global::audioData["horse00.wav"] = 0;
    }
  } else {
    Global::audioData.erase("horse00.wav");
  }
}

static bool playAudio() {
  const int minimum_audio = (4000 * sizeof(float)) / 2;
  if (SDL_GetAudioStreamQueued(stream) < minimum_audio) {
    uint8_t *data = (uint8_t *)SDL_stack_alloc(uint8_t, minimum_audio);
    SDL_memset(data, 0, minimum_audio * sizeof(uint8_t));
    for (auto &[k, v] : Global::audioData) {
      auto &pcmData = Global::pcmCache[k];
      if (v + minimum_audio <= pcmData.size()) {
        auto src = (pcmData.data() + v);
        SDL_MixAudio(data, src, SDL_AUDIO_S16, minimum_audio, 1.0f);
      }
      v += minimum_audio;
    }
    SDL_PutAudioStreamData(stream, data, minimum_audio);
    SDL_stack_free(data);
    return true;
  }
  return false;
}

static void clearAudio() {
  std::erase_if(Global::audioData, [](const auto &item) {
    auto &pcmData = Global::pcmCache[item.first];
    return pcmData.size() < item.second;
  });
}

void AudioSys::init() {
  stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec,
                                     NULL, NULL);
  SDL_ResumeAudioStreamDevice(stream);
  return;
}

bool AudioSys::run() {
  prepareAudio();
  playAudio();
  clearAudio();
  return true;
}