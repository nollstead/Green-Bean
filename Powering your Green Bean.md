The Green Bean can be powered via a USB-C connector, a LiPo battery or the exposed VIN (Voltage In) pin.  When powering your board keep the following in mind:

### General
- The Green Bean operates at 3.3v, so it must reduce (or regulate) the input voltage down to 3.3v.  A separately 5V regulator is also included for any peripherals that may need it, though the Green Bean itself does not use it.
- When the green power LED is lit it means that the board is receiving sufficient voltage to power the board at 3.3v and provide 5v and 3.3v to the header pins.
- The 5v and 3.3v pins on the headers are meant as OUTPUT only and intended to be used as a voltage source for peripherals or a shield - they are unregulated and not intended as a power source.  While they can be used as input, care must be taken to not exceed their rated voltage.  For example, sending greater than 3.3v to the 3V3 pin risks damaging the board.  

### VIN
- The VIN pin on the header is meant to be used as an input.  For example, a shield or external peripheral that has its own power source can also power the Green Bean - eliminating the need for multiple power sources.  
- The voltage range for the VIN pin is 6-32v.  If using VIN, care must be taken to avoid supplying greater than 32v to avoid damaging the board.

### USB-C
- The USB-C connection includes Electrostatic Discharge Protection (ESD).
- If powering via USB-C, which is normally 5v, you may see a slightly lower value on the VIN and 5v pins.  This is normal.  

### LiPo
When choosing a LiPo battery to power the Green Bean, some considerations should be made
- Ensure that the battery uses a 2m JST-PH connector
- Confirm the polarity orientation.  While the Green Bean includes reverse polarity protection, it's important for the positive and negative wire to be property oriented to power the board.  When connected the positive (red) wire should line up with the + symbol on the board and the negative (black) wire should line up with the - symbol.
- Examples of LiPo batteries with the correct polarity can be found [here](https://www.amazon.com/gp/product/B09G2S88Q3/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1) and [here](https://www.amazon.com/gp/product/B09BYVNH2N/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1).  
