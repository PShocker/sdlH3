#include "AudioSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_stdinc.h"
#include "Window/Window.h"
#include <cstdint>
#include <cstring>
#include <vector>

bool AudioSys::has(std::string path) {
  for (auto &audio : Global::audioData) {
    if (audio.path == path) {
      return true;
    }
  }
  return false;
}

void AudioSys::push(std::string path, float volume, float fadeSpeed,
                    bool cycle) {
  Audio audio;
  audio.path = path;
  audio.volume = volume;
  audio.current = 0;
  audio.cycle = cycle;
  audio.fadeSpeed = fadeSpeed;
  audio.pause = false;
  Global::audioData.push_back(audio);
}

void AudioSys::fade(std::string path, float fadeSpeed) {
  for (auto &audio : Global::audioData) {
    if (audio.path == path) {
      audio.fadeSpeed = fadeSpeed;
      break;
    }
  }
}

static bool playAudio() {
  const int minimum_audio = (int)(44100 * 0.02f) * 2 * 2;
  if (SDL_GetAudioStreamQueued(Global::audio) < minimum_audio) {
    uint8_t *data = (uint8_t *)SDL_stack_alloc(uint8_t, minimum_audio);
    SDL_memset(data, 0, minimum_audio * sizeof(uint8_t));
    for (auto it = Global::audioData.begin(); it != Global::audioData.end();) {
      auto &audio = *it;
      if (!audio.pause) {
        auto &pcmData = Global::pcmCache[audio.path];
        auto src = (pcmData.data() + audio.current);
        auto len = (int32_t)pcmData.size() - (int32_t)audio.current;
        len = std::max(0, len);
        auto num = std::min(len, minimum_audio);
        SDL_MixAudio(data, src, SDL_AUDIO_S16, num, audio.volume);
        audio.current += num;
        if ((num == 0 && !audio.cycle)) {
          it = Global::audioData.erase(it);
          continue;
        }
      }
      it++;
    }
    SDL_PutAudioStreamData(Global::audio, data, minimum_audio);
    SDL_stack_free(data);
    return true;
  }
  return false;
}

static void fadeAudio() {
  auto &v = Global::audioData;
  for (auto it = v.begin(); it != v.end();) {
    auto &audio = *it;
    if (audio.fadeSpeed > 0) {
      audio.volume -= audio.fadeSpeed * Window::deltaTime;
      if (audio.volume <= 0) {
        it = Global::audioData.erase(it);
        continue;
      }
    }
    it++;
  }
}

void AudioSys::init() {
  SDL_AudioSpec spec = {.format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};
  Global::audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                            &spec, NULL, NULL);
  SDL_ResumeAudioStreamDevice(Global::audio);
  return;
}

bool AudioSys::run() {
  playAudio();
  fadeAudio();
  return true;
}