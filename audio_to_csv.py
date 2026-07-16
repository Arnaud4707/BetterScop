import librosa
import numpy as np
import pandas as pd

line = input()
file = line.split(None, 2)
len = 0
for tmp in file:
    len += 1

if len < 2 :
    print("Request 2 file !")
    exit()

y, sr = librosa.load(file[0], sr=None)

hop = 512

rms = librosa.feature.rms(y=y, hop_length=hop)[0]

centroid = librosa.feature.spectral_centroid(
    y=y,
    sr=sr,
    hop_length=hop
)[0]

rolloff = librosa.feature.spectral_rolloff(
    y=y,
    sr=sr,
    hop_length=hop
)[0]

zcr = librosa.feature.zero_crossing_rate(
    y,
    hop_length=hop
)[0]

S = np.abs(librosa.stft(
    y,
    hop_length=hop
))

fft = S

freqs = librosa.fft_frequencies(sr=sr)

bass_idx = np.where((freqs >= 20) & (freqs < 150))[0]
mid_idx = np.where((freqs >= 150) & (freqs < 2000))[0]
high_idx = np.where(freqs >= 2000)[0]


nb_frames = S.shape[1]

times = librosa.frames_to_time(
    np.arange(nb_frames),
    sr=sr,
    hop_length=hop
)

rows = []

for frame in range(nb_frames):

    time = times[frame]

    bass = np.mean(S[bass_idx, frame])
    mid = np.mean(S[mid_idx, frame])
    high = np.mean(S[high_idx, frame])

    rows.append([
        time,
        rms[frame],
        centroid[frame],
        rolloff[frame],
        zcr[frame],
        bass,
        mid,
        high
    ])

df = pd.DataFrame(
    rows,
    columns=[
        "time",
        "rms",
        "centroid",
        "rolloff",
        "zcr",
        "bass",
        "mid",
        "high"
    ]
)
df.to_csv(file[1], index=False)