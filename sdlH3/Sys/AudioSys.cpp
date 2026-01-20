#include "AudioSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_stdinc.h"
#include <cstdint>
#include <cstring>
#include <vector>

static SDL_AudioSpec spec = {
    .format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};

static bool playAudio() {

  const int minimum_audio = (int)(44100 * 0.02f) * 2 * 2;
  if (SDL_GetAudioStreamQueued(Global::audio) < minimum_audio) {
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
    SDL_PutAudioStreamData(Global::audio, data, minimum_audio);
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
  Global::audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                            &spec, NULL, NULL);
  SDL_ResumeAudioStreamDevice(Global::audio);
  return;
}

bool AudioSys::run() {
  playAudio();
  clearAudio();
  return true;
}