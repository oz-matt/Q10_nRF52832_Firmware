# Q10_nRF52832_Firmware

To use:

1. install mbed/mercurial etc. from that special single-installer: https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli_install/
2. If desired, install atom from: https://atom.io/
3. clone https://github.com/OzoraLabs/Q10_nRF52832_Firmware into a dir of choice
4. Hold Shift and right-click in the directory from above (example: C:/ozoracode/Q10_nRF52832_Firmware) and choose 'Open PowerShell window here'
5. type 'mbed deploy'
6. 'mbed sync'
7. 'mbed toolchain GCC_ARM'
8. 'mbed target NRF52_DK'
9. 'mbed compile'
10. Navigate to <q10_nRF52832_Firmware root>/BUILD/NRF52_DK/GCC_ARM/Q10_nRF52832_Firmware.hex
11. Plug in the Q10 or test jig
12. Drag and drop the above file into the DAPLINK or JLINK drive that pops up
13. Open TeraTerm or similar program, select Serial as the interface, and choose 9600 baud.
14. You should now see the program functioning with a debug output.