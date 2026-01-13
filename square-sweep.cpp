#include "everything.h"

int main(int argc, char* argv[]) {
    float phase = 0.0f;
    const float twoPi = 2.0f * pi;

    for (float note = 127; note > 0; note -= 0.001f) { // sweep high → low
        // Current fundamental frequency from MIDI note
        float f0 = mtof(note);

        // Maximum odd harmonics under Nyquist
        int N = (int)(SAMPLE_RATE / (2.0f * f0));

        // Phase increment for current frequency
        float phaseIncrement = twoPi * f0 / SAMPLE_RATE;

        float v = 0.0f;

        // Additive square wave: odd harmonics
        for (int n = 1; n <= N; n += 2) {
            v += sinf(n * phase) / (float)n;
        }

        v *= 4.0f / pi;    // scaling per square formula
        mono(v * 0.707f);  // output

        // Advance phase
        phase += phaseIncrement;
        if (phase >= twoPi)
            phase -= twoPi;
    }
}
