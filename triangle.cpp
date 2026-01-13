#include "everything.h"

int main(int argc, char* argv[]) {
    const float f0 = mtof(60);       // Stable pitch
    const float twoPi = 2.0f * pi;

    // Max odd harmonics under Nyquist
    const int N = (int)(SAMPLE_RATE / (2.0f * f0));

    float phase = 0.0f;
    float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

    while (true) {
        float v = 0.0f;

        // Additive triangle wave: odd harmonics with alternating sign and 1/n^2 amplitude
        for (int n = 1; n <= N; n += 2) {
            float sign = ((n - 1) / 2) % 2 == 0 ? 1.0f : -1.0f;
            v += sign * sinf(n * phase) / (float)(n * n);
        }

        v *= 8.0f / (pi * pi);    // scale per formula
        mono(v * 0.707f);         // output

        phase += phaseIncrement;
        if (phase >= twoPi)
            phase -= twoPi;
    }
}
