#include "everything.h"

int main(int argc, char* argv[]) {
    float phase = 0.0f;
    const float twoPi = 2.0f * pi;

    for (float note = 127; note > 0; note -= 0.001f) { // sweep from high to low
        // Compute current fundamental frequency from MIDI note
        float f0 = mtof(note);

        // Determine maximum number of harmonics under Nyquist
        const int N = (int)(SAMPLE_RATE / (2.0f * f0));

        // Phase increment for the current frequency
        float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

        // Impulse formula: sum of harmonics
        float v = 0.0f;
        for (int n = 1; n <= N; ++n) {
            v += sinf(n * phase) / (float)n;
        }
        v *= 0.5f;          // correct scaling for saw
        mono(v * 0.707f);

        // Advance phase
        phase += phaseIncrement;
        if (phase >= twoPi)
            phase -= twoPi;
    }
}
