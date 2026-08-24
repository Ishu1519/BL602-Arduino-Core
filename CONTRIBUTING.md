# Contributing to BL602 Arduino Core

Thank you for your interest in contributing!

## How to Contribute

1. **Report Issues**: Open a GitHub issue for bugs, feature requests, or questions.

2. **Submit Pull Requests**:
   - Fork the repository
   - Create a feature branch (`git checkout -b feature/my-feature`)
   - Make your changes
   - Test on real BL602 hardware if possible
   - Submit a pull request with a clear description

## Development Setup

See [docs/building-from-source.md](docs/building-from-source.md) for
instructions on setting up the Bouffalo SDK build environment.

## Code Style

- C code: K&R style, 4-space indentation
- C++ code: Follow existing Arduino core conventions
- Keep functions focused and well-commented

## Testing

- All core functionality changes should be tested on real BL602 hardware
- Document what was tested and how in your PR description
- Mark untested features as "experimental" in both code and documentation

## What We Need Help With

- [ ] Arduino IDE compilation support (platform.txt integration)
- [ ] Analog I/O implementation
- [ ] SPI library
- [ ] Wire/I2C physical verification
- [ ] Additional board variant definitions
- [ ] CI/CD pipeline for build verification

## License

By contributing, you agree that your contributions will be licensed under
the MIT License.
