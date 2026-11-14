<img src="assets/AppIcon.png" height=32 width=32 />

# Avocado
PlayStation 1 emulator built on [Avocado](https://github.com/jaczekanski/avocado) by [@jaczekanski](https://github.com/jaczekanski)

## Building
> Instructions on how to build Avocado for all supported platforms

Go to the [BUILDING](BUILDING.md) documentation

## Changes
> List of stuff changed from the original Avocado

### Added
- [x] Font & Symbols
    - Added [Cousine](https://fonts.google.com/specimen/cousine) as the new font
    - Added [Lucide](https://lucide.dev/icons) for the new symbols
- [x] Portability Mode
    - Added a check for a blank or filled out `data/config.json` file in the executable directory which toggles portability mode

### Changed
- [x] Help > About Window
    - Added previously unavailable information
    - Added a new header and changed the overall design
- [x] Repository File Structure
    - Changed how the header and source files are structured
    - Changed the build system to use just CMake

### Fixed
- [x] Ape Escape 2
    - Added a missing check between `0x1F801DA0` - `0x1F801DBF` in `spu.cpp`, as those addresses were unhandled for writes
- [x] Gran Turismo 2 (Arcade Mode)
    - Added a check for `0x1F801130` in `system.cpp`, as the game assumes there's a fourth timer at that address
     
### Miscellaneous
- [x] Replaced the custom `lerp` function with `std::lerp`

## License
> Avocado is licensed under GPLv3

Read all about the [LICENSE](LICENSE.md)