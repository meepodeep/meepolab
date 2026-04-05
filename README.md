# MeepoLab
## Beginner 25-key midi controller with velocity-sensitive keys and drum pads
<img width="2840" height="1507" alt="image" src="https://github.com/user-attachments/assets/2c0fe79d-f802-40e3-86f1-2499fc8b68f6" />
<img width="1447" height="716" alt="image" src="https://github.com/user-attachments/assets/fdca9a41-e886-4f47-81bd-5f0970da8791" />
<img width="1415" height="839" alt="image" src="https://github.com/user-attachments/assets/3342755e-cb69-4899-b640-abd6e90ff25b" />
<img width="1598" height="850" alt="image" src="https://github.com/user-attachments/assets/72100f11-687d-443e-ae7f-c17784d96d50" />

## Why does this exist
I made this project because I have been recently getting into making music for my own games, but I got tired of using a keyboard to do everything, so when Hackclub Stasis started to exist, I decided to make this. 
midi controller
# How to build
## PCB
1. Lay out and solder all of the smd components to the board
2. Solder the jst connectors
3. Solder the teensy on with pin headers
4. Flash the meepolab_sketch.ino file onto the teensy using midi mode
## Wiring 2
1. Solder the wires of the 12 pin jst connectors to all of the key matrix tactile switches and plug them into the plugs with these numbers. wire the "bottom" tactile switches to be the ones furthest from the pivot of the key, and the "top" ones closest to the center of the key. ( DO THIS AFTER YOU MOUNT THEM )
2. The V and ground are the 2 pins on the tactile switches, not actual voltage and ground
3. <img width="1125" height="452" alt="image" src="https://github.com/user-attachments/assets/f7ac1da2-5689-4ed9-8931-4d09b12a30df" />
4. Solder the rest of your inputs, potentiometer, slide pot to the other 12pin jst connectors and plug them into the plugs with these numbers
5. <img width="502" height="415" alt="image" src="https://github.com/user-attachments/assets/59ac7c8c-d2b8-447f-a331-795e59dfb259" />
6. Solder these jst connectors to the piezo drum pad sensors  and plug them into the plugs with these numbers
7. <img width="106" height="665" alt="image" src="https://github.com/user-attachments/assets/2aef435e-1566-41fa-ad20-016302d2cb3c" />
8. Solder the leds to the led jst connectors and plug them into the plugs with these numbers
<img width="50" height="873" alt="image" src="https://github.com/user-attachments/assets/5a76a2a9-0a12-42dd-940f-2f785f226cca" />
<img width="74" height="868" alt="image" src="https://github.com/user-attachments/assets/0afa3eae-6556-4365-9cd2-a63ec42455bb" />


## Assembly
1. assemble the 4 parts of the main shell and backplate together
2. Insert a bearing into the hole of every key
3. <img width="2309" height="1404" alt="image" src="https://github.com/user-attachments/assets/3b791463-7d27-4f58-be90-2754eb1c5814" />
4. Align all of the keys how they are supposed to be and push the rod through the case,  bearings and keys
5. insert all of the return springs in between the pegs on the case and every key
6. <img width="881" height="577" alt="image" src="https://github.com/user-attachments/assets/9362fad8-5538-438d-9f15-23708e9e868a" />
7.insert all of the tactile switches into their holes in their mounting brackets.
<img width="2243" height="1169" alt="image" src="https://github.com/user-attachments/assets/19a44c21-20f1-4924-b7de-b16624c26607" />
8. tape piezo sensors to the back of each drum pad square on the drum pad membrane, and then mount the drum pad membrane to the keyboard
9. <img width="2342" height="623" alt="image" src="https://github.com/user-attachments/assets/895c28e6-85cd-4653-9086-9d5158411804" />
10. Mount the octave rocker, first by inserting it into position, and then inserting the axel after
11. <img width="1712" height="1008" alt="image" src="https://github.com/user-attachments/assets/42f0a45a-758d-4364-b116-237b9dbf9b7d" />
12. insert a keyswitch into each of the octave rocker keyswitch mounts square holes and then screw them in using m3 hardware
13.<img width="1545" height="961" alt="image" src="https://github.com/user-attachments/assets/86508264-0850-4f99-8709-1583ea0b5647" />
14. insert the keyswitches for the shift pause/play and record buttons into their holes
15. <img width="1458" height="748" alt="image" src="https://github.com/user-attachments/assets/86fe20f4-32f5-44c7-bc31-5de397877c7f" />
16. insert the potentiometers into their holes and screw them down using the included nut, after inserting the potentiometer area accent
17. <img width="1474" height="1021" alt="image" src="https://github.com/user-attachments/assets/1961dc2f-ca3c-4cc3-aab1-4a2e2058e991" />
18. put on the potentiometer caps
19. insert the slide potentiometers and screw in using m3 hardware after inserting accents
20. <img width="1901" height="1281" alt="image" src="https://github.com/user-attachments/assets/c3cf9f1a-d096-4be7-8c76-61f0b004380d" />
21. put on fader caps
22. insert leds and cover with optional acrylic
23. <img width="1896" height="340" alt="image" src="https://github.com/user-attachments/assets/8fdd8a11-bd13-40b2-83a5-142877298025" />\
24. connect the cable to the teensy and run it through the hole
25. Attach bottom with m3 hardware
26. <img width="2025" height="1428" alt="image" src="https://github.com/user-attachments/assets/2864c253-0496-457a-ad1d-f26254c9ee25" />
27. put keycaps on keys if you want
28. <img width="1011" height="496" alt="image" src="https://github.com/user-attachments/assets/5368aa90-4200-435d-8830-83a9666ede02" />




