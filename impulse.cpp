#include "everything.h"

int main(int argc, char* argv[]) {
  const float f0 = mtof(60);   // Stable pitch (Middle C)
  const float twoPi = 2.0f * pi;

  // Max harmonics under Nyquist
  const int N = (int)(SAMPLE_RATE / (2.0f * f0));

  float phase = 0.0f;
  float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

  while (true) {
    float v = 0.0f;

    // Impulse harmonic sum
    for (int n = 1; n <= N; ++n) {
      v += sinf(n * phase);
    }

    v /= (float)N;   // normalization
    mono(v * 0.707f);

    phase += phaseIncrement;
    if (phase >= twoPi)
      phase -= twoPi;
  }
}
