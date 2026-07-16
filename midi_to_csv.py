import pretty_midi
import pandas as pd

line = input()
file = line.split(None, 2)
len = 0
for tmp in file:
    len += 1

if len < 2 :
    print("Request 2 file !")
    exit()

midi = pretty_midi.PrettyMIDI(file[0])

notes = []

for instrument in midi.instruments:
    for note in instrument.notes:
        notes.append([
            instrument.program,
            note.pitch,
            note.start,
            note.end,
            note.velocity
        ])

df = pd.DataFrame(notes, columns=["instrument", "pitch", "start", "end", "velocity"])

df.to_csv(file[1], index=False)