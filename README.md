<img src="assets/AppIcon.png" height=32 width=32 />

# Avocado
PlayStation 1 emulator built on Avocado by [@jaczekanski](https://github.com/jaczekanski)

## Building
> Commands even a baby could run

[Go to Building](BUILDING.md)

## Changes
### Avocado

> [!NOTE]
> Fixes

- Fixes an issue where Disney's Atlantis: The Lost Empire would freeze during the tutorial
    - Whitmore's tutorial can now be passed and the game played
- Fixes an issue where Gran Turismo 2 (Arcade Mode) would not boot
    - Boots and runs correctly but not thoroughly tested

> [!NOTE]
> Updates

- Updates most externals to their latest upstream versions

> [!NOTE]
> Miscellaneous

- Restructure and simplification
    - Added a TARGET_OS_IPHONE check for Cytrus support (unrelated)
    - Restructured the externals, include and sources directories
    - Transitioned to FetchContent for most externals

### Externals
#### EventBus
- Restructure and simplification
- Improved identifier and validation functions

## License
Licensed under GPLv3

[Go to License](LICENSE.md)