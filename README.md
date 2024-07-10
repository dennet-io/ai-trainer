# AI Trainer

A 3 part project to allow young children to play a game. By turning knobs they influence one of the RGBA values of a color. The goal is to create the left color as quickly and closely as possible. 

The trainer was built for an expedition on [Expeditie Next on how to train AI](https://expeditienext.nl/activiteit/hoe-train-je-ai/). As the target group were children between the age of 6 and 12, this is a gross simplification. In this setting the children would each represent a node in a model. By playing the game the model could be trained and after a few rounds the model was complete.

The expedition took place in the 'Walburgiskerk' in Zutphen on the 1st of May 2024.

![Set up](./img/photo.jpeg "Set up")

### Colors

In the Colors section you will find a Python program that reads from the Serial and plots both a Goal color and an Actual color. To run a database connection is required so that after each attempt the score can be registered. 

### Trainer 

In the trainer section you can find the firmware for the Trainer as a platformio project. As development was done under timeconstraints and a high number of pins required an Arduino Mega was used. 

### Database

In the database folder you can find the docker-compose.yaml to set up a database and the sql to create the table. 

# License 

Project is released under [GNU GPLv3.0 license](https://www.gnu.org/licenses/gpl-3.0.en.html). 



