# TvStation Remote CLI

This CLI is made to control an infrared emettor used as a remote, the "Phidget22".


## Compilation

Full command line
```
gcc main.c emission.c -o telecommande -I"C:/Program Files/Phidgets/Phidget22" -L"C:/Program Files/Phidgets/Phidget22/x86" -lphidget22
```
You can also juste use the MakeFile.

## Usage

```
./telecommande `phidget_serial_number` `action`
```
Here are the coded action and their code : 

Action | Code |
--- | --- |
Increase volume | +
Decrease volume | -
Increase channel number | y
Decrease channel number | x
Power on/off | p
Mute sound | m
Ok button | o
Exit | e
Bring menu | M
Up arrow | u
Down arrow | d
Right arrow | r
Left arrow | l
Subtitles | t

## Dependance
To compile this code you need to have the phidget library installed on your computer, see at https://www.phidgets.com/docs/OS_-_Windows.

## Credit
This code is a slightly modified version of a code programmed and delivered by "D. Perri".

This code is part of <a href="http://mathieu.delalandre.free.fr/projects/stvd/pms/">larger university research project</a> led by Mr Delalandre.

<a href="https://dataset-stvd.univ-tours.fr/pms/index.html">Mirror link</a>
