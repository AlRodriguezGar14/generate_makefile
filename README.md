# MAkefile Generator

## Description

This is a simple generator that build a basic Makefile for a C++ project.
You can use:
make
make clean
make fclean
make re


## Installation

[Download the installation script](https://raw.githubusercontent.com/AlRodriguezGar14/generate_makefile/main/makefile_generator_installer.sh) and run it

```bash
curl -sSL https://raw.githubusercontent.com/AlRodriguezGar14/generate_makefile/main/makefile_generator_installer.sh | bash
```

or follow the next steps:

1. Clone the repository:

```bash
git clone https://github.com/AlRodriguezGar14/generate_makefile makefile_generator
```

2. Change directory to the cloned repository:

```bash
cd makefile_generator
```

3. Build the program:

```bash
make
```

4. Add the executable to your path (optional):

```bash
export PATH=$PATH:$(pwd)/setMakefile
```

4.1 Optionally you can move the executable to /usr/local/bin:

5. Clean the object files:

```bash
make clean
```

## License

[MIT](https://choosealicense.com/licenses/mit/)


## TODO:

When building the Makefile from zero,

- [ ] Add Support for custom compiler
- [ ] Add Support for custom flags.
- [ ] Add Support for custom TARGET
