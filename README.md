# Dungeon-of-The-Mad-Mage

This is an RPG game based on other terminal games like Rogue, Nethack, and Cataclysm: DDA. Initially, this repository was created to improve my proficiency in the C language, but due to my inspiration from other terminal games, I decided to transform this training repository into a project.

> ⚠️ **Attention:** 1 - This program is a "Remaster" of an old project I started in college in 2025. If you want to see, the old version it's [here](https://github.com/LucasWerppFranco/C-rpg-game).

> ⚠️ **Attention:** 2 - I haven't created any installation files yet (partly because the program isn't finished). Feel free to compile and test my game as much as you want!

> ⚠️ **Attention:** 3 - This code is initially only working in GNU/Linux environments. I'm not sure if it's working correctly for Windows. But, if you want to play it in your Windows machine, you can run the game using the Docker File present in this repository (I wrote down the instructions at the end of the README).

```
 _________________________
|  |                   |  |
|[]|   Dungeon of The  |[]|
|  |      Mad Mage     |  |
|  |                   |  |
|  |                   |  |
|  |___________________|  |
|                         |
|    ________________     |
|    | __      |     |    |
|    ||  |     |     |    |
|    ||__|     |     |    |
|____|_________|_____|____|
```

---

## Project Documentation

I made a docs/ directory if you have any questions about anything. I will be updating it frequently, and if you find any errors, I invite you to help me with both the code and the documentation so we can make this project even better!!!

Check the project documentation [Hear](docs/README.md).

## Libraries used
I created some libraries with the intention of not only adding to my project but also helping other Gnu/Lunux developers to carry out their projects. Feel free to check them out.

- [Tusk](https://github.com/LucasWerppFranco/Tusk-C-library)

## Another projects that I used
I also have other projects that I've added to this one; feel free to view and use them in your applications as well.

- [Terminal Fire](https://github.com/LucasWerppFranco/Terminal-Fire-C)

---

## Run whith Docker
You can also use docker to run my game!

The only requirement to install the game this way is to have Docker installed on your computer. Click [Here](https://www.docker.com/get-started/) to install Docker.

---

1 - Git clone the project to the desired folder:

```
git clone git@github.com:LucasWerppFranco/Dungeon-of-The-Mad-Mage.git
cd Dungeon-of-The-Mad-Mage
```

2 - Create the system image and run the program:

```
docker build -t dotmm .
docker run -it --rm dotmm
```

That's it! Now you can test my game without having to install anything else! Enjoy! ;)
