# Projector4d - 4d rotation visualizer
##### Author: Grzegorz Kazana
##### Project created for "Języki asemblerowe" course, Informatics AEI POLSL
---
## Purpose
Visualize [**Tesseract**](https://en.wikipedia.org/wiki/Tesseract) rotation in 4th dimention.\
Learn basics of point transformations in 2d-4d spaces using matrix math. [**Reference1**](http://www.mathaware.org/mam/00/master/essays/dimension/dimen11.html), [**Reference2**](https://en.wikipedia.org/wiki/Rotation_matrix).

---
## Used technologies and implementation
[**SFML**](https://www.sfml-dev.org/) - drawing canvas\
[**WinAPI**](https://docs.microsoft.com/en-us/windows/desktop/apiindex/windows-api-list) - UI - buttons, controls

C++ - ui and top-level logic
x86 assembly - low-level functionaly mostly matrix/vector operations
C - duplicate low-level implementation for performace reference

---
## Demonstration
![failed](https://raw.githubusercontent.com/GrzegorzKazana/Projector4d/master/Dokumentacja/Demo.gif "")