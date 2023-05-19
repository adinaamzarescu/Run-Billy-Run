import midiutil

# Extract the notes and durations from the string representation
notes = []
durations = []
for note in song.split():
    if note != 'r':
        notes.append(note[:-1])
        durations.append(note[-1])
    else:
        notes.append('r')
        durations.append(1)

# Create a MIDI file using the extracted notes and durations
midi_file = midiutil.MIDIFile(1)
track = 0
channel = 0
time = 0
tempo = 120

midi_file.addTempo(track, time, tempo)

for note, duration in zip(notes, durations):
    if note != 'r':
        midi_file.addNote(track, channel, note, time, int(duration) * 0.5, velocity=100)
    time += int(duration) * 0.5

# Save the MIDI file
output_file = "output.mid"
with open(output_file, 'wb') as file:
    midi_file.writeFile(file)