This project uses a vl53l0x time of flight sensor to read the distance between the sensor and whatever is in front of it
there is an LED and Speaker attached to an ESP32 this LED and speaker independently either play an audio, or a heartbeat sound in sync, to give an illusion of an actual heartbeat
my friend asked me to make this for her art project, the LED flashing will illuminate a heart so it looks like there is a beat, and the speaker is solely for audio effects to sell the illusion
the distance between heartbeats changes with distance, the higher the distance, the quicker the heartbeat
the heartbeat is scaled, so at the closest, the heartbeat should be ~ 120 BPM, while at the furthest, 60BPM
