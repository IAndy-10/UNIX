#include "everything.h"

int main(int argc, char* argv[]) {
  const float f0 = mtof(60);         // Stable pitch
  const float twoPi = 2.0f * pi;

  // Max odd harmonics under Nyquist
  const int N = (int)(SAMPLE_RATE / (2.0f * f0));

  float phase = 0.0f;
  float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

  while (true) {
    float v = 0.0f;

    // Additive square wave: only odd harmonics
    for (int n = 1; n <= N; n += 2) {
      v += sinf(n * phase) / (float)n;
    }

    v *= 4.0f / pi;      // scale per formula
    mono(v * 0.707f);    // output

    phase += phaseIncrement;
    if (phase >= twoPi)
      phase -= twoPi;
  }
}
