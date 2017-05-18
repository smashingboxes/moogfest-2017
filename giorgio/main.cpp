#include "mbed.h"
#include "math.h"

#define _C1  0
#define _Cs1 1
#define _Db1 1
#define _D1  2
#define _Ds1 3
#define _Eb1 3
#define _E1  4
#define _F1  5
#define _Fs1 6
#define _Gb1 6
#define _G1  7
#define _Gs1 8
#define _Ab1 8
#define _A1  9
#define _As1 10
#define _Bb1 10
#define _B1  11

#define _C2  12
#define _Cs2 13
#define _Db2 13
#define _D2  14
#define _Ds2 15
#define _Eb2 15
#define _E2  16
#define _F2  17
#define _Fs2 18
#define _Gb2 18
#define _G2  19
#define _Gs2 20
#define _Ab2 20
#define _A2  21
#define _As2 22
#define _Bb2 22
#define _B2  23

#define _C3  24
#define _Cs3 25
#define _Db3 25
#define _D3 26
#define _Ds3 27
#define _Eb3 27
#define _E3  28
#define _F3  29
#define _Fs3 30
#define _Gb3 30
#define _G3  31
#define _Gs3 32
#define _Ab3 32
#define _A3  33
#define _As3 34
#define _Bb3 34
#define _B3  35

#define _C4  36
#define _Cs4 37
#define _Db4 37
#define _D4  38
#define _Ds4 39
#define _Eb4 39
#define _E4  40
#define _F4  41
#define _Fs4 42
#define _Gb4 42
#define _G4  43
#define _Gs4 44
#define _Ab4 44
#define _A4  45
#define _As4 46
#define _Bb4 46
#define _B4  47

#define _C5  48
#define _Cs5 49
#define _Db5 49
#define _D5  50
#define _Ds5 51
#define _Eb5 51
#define _E5  52
#define _F5  53
#define _Fs5 54
#define _Gb5 54
#define _G5  55
#define _Gs5 56
#define _Ab5 56
#define _A5  57
#define _As5 58
#define _Bb5 58
#define _B5  59

#define _C6  60
#define _Cs6 61
#define _Db6 61
#define _D6  62
#define _Ds6 63
#define _Eb6 63
#define _E6  64
#define _F6  65
#define _Fs6 66
#define _Gb6 66
#define _G6  67
#define _Gs6 68
#define _Ab6 68
#define _A6  69
#define _As6 70
#define _Bb6 70
#define _B6  71

#define _C7  72
#define _Cs7 73
#define _Db7 73
#define _D7  74
#define _Ds7 75
#define _Eb7 75
#define _E7  76
#define _F7  77
#define _Fs7 78
#define _Gb7 78
#define _G7  79
#define _Gs7 80
#define _Ab7 80
#define _A7  81
#define _As7 82
#define _Bb7 82
#define _B7  83

float midi[127] = { 32.70319566257483, 34.64782887210901, 36.70809598967595, 38.890872965260115, 41.20344461410874, 43.653528929125486, 46.2493028389543, 48.99942949771866, 51.91308719749314, 55.0, 58.27047018976124, 61.735412657015516, 65.40639132514966, 69.29565774421802, 73.4161919793519, 77.78174593052023, 82.40688922821748, 87.30705785825097, 92.4986056779086, 97.99885899543732, 103.82617439498628, 110.0, 116.54094037952248, 123.47082531403103, 130.8127826502993, 138.59131548843604, 146.8323839587038, 155.56349186104046, 164.81377845643496, 174.61411571650194, 184.9972113558172, 195.99771799087463, 207.65234878997256, 220.0, 233.08188075904496, 246.941650628062, 261.6255653005986, 277.1826309768721, 293.6647679174075, 311.1269837220809, 329.62755691287, 349.2282314330039, 369.9944227116344, 391.9954359817493, 415.3046975799451, 440.0, 466.1637615180899, 493.883301256124, 523.2511306011972, 554.3652619537442, 587.329535834815, 622.2539674441618, 659.25511382574, 698.4564628660078, 739.9888454232688, 783.9908719634986, 830.6093951598903, 880.0, 932.3275230361796, 987.7666025122485, 1046.5022612023945, 1108.7305239074883, 1174.6590716696305, 1244.5079348883237, 1318.5102276514795, 1396.9129257320158, 1479.9776908465376, 1567.9817439269968, 1661.2187903197807, 1760.0, 1864.6550460723593, 1975.533205024497, 2093.004522404789, 2217.4610478149766, 2349.318143339261, 2489.0158697766474, 2637.020455302959, 2793.8258514640315, 2959.955381693075, 3135.9634878539937, 3322.4375806395615, 3520.0, 3729.3100921447185, 3951.066410048994 };
int a = 440;
PwmOut mypwm(D3);
AnalogIn potentiometer(A0);

#define TEMPO 200

typedef struct {
    int step;
    float duration;
    bool rest;
} note_t;

note_t tune[] = {
  { .rest = false, .step = 0,   .duration = 0.5 },
  { .rest = false, .step = -12, .duration = 0.5 },
  { .rest = false, .step = 3,  .duration = 0.5 },
  { .rest = false, .step = -12,  .duration = 0.5 },
  { .rest = false, .step = 2,  .duration = 0.5 },
  { .rest = false, .step = -12,  .duration = 0.5 },
  { .rest = false, .step = 3,  .duration = 0.5 },
  { .rest = false, .step = 7,  .duration = 0.5 },
  { .rest = false, .step = -12,  .duration = 0.5 },
  { .rest = false, .step = 0,  .duration = 0.5 },
  { .rest = false, .step = 3,  .duration = 0.5 },
  { .rest = false, .step = -12,  .duration = 0.5 },
  { .rest = false, .step = 2,  .duration = 0.5 },
  { .rest = false, .step = -12,  .duration = 0.5 },
  { .rest = false, .step = 3,  .duration = 0.5 },
  { .rest = false, .step = 0,  .duration = 0.5 }
};

int main() {
    int root = _A4;
    while(1) {
        for(int i = 0; i < sizeof(tune)/sizeof(tune[0]); i++) {
            const int max_note = _E5;
            const int min_note = _E4;
            root = ceil(potentiometer.read() * (max_note - min_note)) + min_note;

            if (tune[i].rest) {
                mypwm.write(0);
            } else {
                const float frequency = midi[root + tune[i].step];
                mypwm.period((double)((double)1.0 / frequency));
                mypwm.write(0.5);
            }

            wait((tune[i].duration * 60 / TEMPO) * (double)0.9);

            mypwm.write(0);
            wait((tune[i].duration * 60 / TEMPO) * (double)0.1);
        }
    }
}
