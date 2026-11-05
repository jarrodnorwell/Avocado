<img src="assets/AppIcon.png" height=32 width=32 />

# Avocado
PlayStation 1 emulator based on Avocado by [@jaczekanski](https://github.com/jaczekanski)

## Building
> Commands even a baby could run

[Go to Building](BUILDING.md)

## Changes
### Avocado

> [!NOTE]
> Fixes

- Fixes an issue where Disney's Atlantis: The Lost Empire would freeze during the tutorial

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

## License
Licensed under GPLv3

[Go to License](LICENSE.md)