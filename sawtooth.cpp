#include "everything.h"

int main(int argc, char* argv[]) {
    const float twoPi = 2.0f * pi;

    float phase = 0.0f;

    float startNote = 127.0f;
    float endNote = 0.0f;
    float step = 0.001f;

    for (float note = startNote; note > endNote; note -= step) {
        float f0 = mtof(note);

        // Limit number of harmonics to Nyquist
        int N = (int)(SAMPLE_RATE / (2.0f * f0));
        if (N < 1) N = 1;      // at least 1 harmonic
        if (N > 128) N = 128;  // cap for performance / avoid OS kill

        // Phase increment per sample
        float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

        // Additive sawtooth formula
        float v = 0.0f;
        for (int n = 1; n <= N; ++n) {
            v += sinf(n * phase) / (float)n;
        }
        v *= 0.5f;           // scale to match theoretical amplitude

        mono(v * 0.707f);    // output

        // Advance phase
        phase += phaseIncrement;
        if (phase >= twoPi)
            phase -= twoPi;
    }
}
