
# A Quieter and More Efficient Camshaft-Powered Braille Embosser 

**Introduction:**\
This project explores a camshaft-based approach to enhance braille embossers, addressing the challenges faced by visually impaired individuals. Traditional braille embossers are costly and noisy, hindering personal use. The proposed solution employs a camshaft system to improve efficiency, reduce noise, and lower costs. Unlike commercial alternatives ($2000-$5000) that require sound dampening, this camshaft-powered embosser operates quietly and is economically accessible at around 1000 RMB (approximately $160). The experiments conducted demonstrate the viability of this design, showcasing its potential as an affordable and effective braille embossing solution.

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Machine%20Picture%20(with%20banana%20for%20scale).jpg" width="750">

## Background

There are an estimated 43 million blind individuals worldwide, 233 million that are living with moderate to severe visual impairment.Visually impaired individuals rely on the use of braille letters instead of alphanumeric letters to write and read. Braille Characters are composed of a 2*3 grid of raised dots to form characters and can be generated through refreshable braille displays, manual braille writing slates, or braille embossers. Braille embossers are used to produce large amount of permanent braille characters.

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Diagram%20and%20Braille%20Printed%20by%20Machine.png" width="300">\
Diagram of braille characters and sample printed text from machine[^1].

Only 10% of blind individuals in the United States are proficient in braille. [^2] Commercial braille embossers, priced between $2000 and $5000, are impractical for personal use, mostly confined to schools and libraries. The widespread availability of such facilities has been limited, especially during the global pandemic. Currently, common commercial machines utilize loud linear solenoids, often necessitating sound dampening boxes. There is an absence of an efficient and quiet braille embosser suitable for home use in the current landscape.

**Engineering Goals:**\
Goal: Develop a highly efficient and low-noise braille embosser.
Design Criteria:
- Utilize off-the-shelf components.
- Generate braille following recognized standards.
- Enable simultaneous printing of multiple dots with scalability.
- Maintain operation noise below 60 dB.
- At a size for easy portability.
## Engineering Design

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Model%20Screen%20Capture.png" width="450">

This machine is based on a 3 axis motion system. 
In the diagram below: 
- The X axis is the belted linear motion system moves the printhead left and right on the as the machine is printing
- The Y axis is comprised of a system of rollers, that first feeds paper in, slides the paper up as each line of braille dots finishes printing, and releases the paper
- The Z axis is responsible for the up-down movement of the printhead. The lead-screw linear motion platform, pushes the printhead (and the print pins) into the paper, allowing for the dots to take shape

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Picture%20with%20Annotation%20of%20Moving%20Axis.jpg" width="450"> 

**Printhead Design:**

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/2-Pin%20Printhead.jpg" width="450"> 

The main printhead assembly consists of a 360 degree servo that is a connected to a camshaft. This cam shaft has 2 cams on it and the cams have all the possible positions so that the print pins can pin all the possible combinations of "dot" and "no-dot". Underneath the cams are 2 print pins that are responsible for pushing the dots into the paper. These print pins are directly under the cams.

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Sample%204%20Pin%20Printhead.jpg" width="450"> 

This 4 pin demo printhead shows theoretical maximum number of pins-per-printhead while maintaining accuracy when adjusting the positions of the cams. The protruding print pins are shown below.


## Testing

Several tests were conducted to verify the overall effectiveness of the printed braille. 

**Braille Dot Height Testing:**\
<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Braille%20Height%20Testing.png" width="700"> 

From testing 5 different samples of the printed braille dots (characters: "abcdwxyz"), the average dot height was measured to be 0.32mm with a tolerance of ±0.12mm.

**Braille Dot Durability Testing:**

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Braille%20Durability%20Testing.png" width="700">

<img src="https://raw.githubusercontent.com/john02px/braille-embosser/main/Project%20Images%20and%20Diagrams/Durablity%20Graph.png" width="700">

After 4 trials of durability testing, the average height loss for each dot was around 0.028mm.

## Conclusions

This project has showcased the feasibility of a low-cost,  efficient braille embosser employing a camshaft-based design. The printing mechanism has demonstrated success in generating braille dots and can be readily scaled to accommodate higher quantities. Future will be made particularly in areas such as exploring alternative manufacturing methods for print pins, elevating printer speed, and further scaling up the print head to accommodate even greater numbers of braille dots simultaneously. 
## Demo

[![Modular Robot Demo](http://img.youtube.com/vi/bNRHV4BrbQY/0.jpg)](https://www.youtube.com/watch?v=bNRHV4BrbQY&ab "Modular Robot Demo")


## Image Sources

[^1]: Self taken image of printed braille + Diagram from:\
Kumari, S., Akole, A., Angnani, P., Bhamare, Y., & Naikwadi, Z. (2020). Enhanced Braille display Use of OCR and Solenoid to improve text to braille conversion. 2020 International Conference for Emerging Technology (INCET). https://doi.org/10.1109/incet49848.2020.9153996

[^2]: Mates, B. T., & Reed, W. R. (2011). Assistive technologies in the library. American Library Association
