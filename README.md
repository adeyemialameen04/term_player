# Term Player
This is a simple terminal based music player created with C, capable of playing musics right from your terminal.

## Features
- Play music files from your terminal
- Pause, resume, skip to next or previous track
- Display a library of available music files
- Search for specific songs (coming soon)
- Quit the player anytime

## Getting Started
To build and run the music player, follow these steps:
```bash
git clone https://github.com/adeyemialameen04/term_player.git
```

```bash
cd term_player/src
```

```
gcc -g -o term_player *.c -lm
```

## Usage
To create the library from the current directory run the executable with no arguments.
```
./term_payer
```

To specify a directory
```
./term_player path_to_directory
```

## Contributing
Contributions are welcome! If you would like to contribute to the development of this project, please follow these steps:

Fork the repository.

Create a new branch `git checkout -b feature/your_feature_name`.

Make your changes.

Commit your changes `git commit -am 'Add new feature'`.

Push to the branch `git push origin feature/your_feature_name`.

Create a new pull request.

#### You can do anything u want with this project but dont change the name of the AUTHOR

## THANKS (⊃｡•́‿•̀｡)⊃
Thanks to [David Reid](https://github.com/mackron) for making his audio playback library [(miniaudio)](https://github.com/mackron/miniaudio) available -- this project would not be possible without it.

## License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/adeyemialameen04/term_player/blob/main/LICENSE) file for details.
