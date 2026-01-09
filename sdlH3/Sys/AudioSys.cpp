#include "AudioSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_stdinc.h"
#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

static SDL_AudioStream *stream = NULL;

static SDL_AudioSpec spec = {
    .format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};

static std::map<std::string, uint32_t> audioData;

static void prepareAudio() {
  if (!audioData.contains("AITheme0.wav")) {
    audioData["AITheme0.wav"] = 0;
  }
}

static bool playAudio() {
  const int minimum_audio = (8000 * sizeof(float)) / 2;
  if (SDL_GetAudioStreamQueued(stream) < minimum_audio) {
    uint8_t *data = (uint8_t *)SDL_stack_alloc(uint8_t, minimum_audio);
    SDL_memset(data, 0, minimum_audio * sizeof(uint8_t));
    for (auto &[k, v] : audioData) {
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
  std::erase_if(audioData, [](const auto &item) {
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