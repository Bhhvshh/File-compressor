# File Compressor

A command-line utility that compresses and decompresses files using **Huffman Coding**, a lossless data compression algorithm that achieves compression by replacing frequently occurring characters with shorter bit sequences.

## Features

- **Lossless Compression**: Restore files to their exact original state
- **Huffman Algorithm**: Optimal variable-length prefix codes based on character frequency
- **Binary Format**: Custom file format with header containing compression metadata
- **File Validation**: Detects files compressed by this tool using a special marker
- **Bit-Level I/O**: Efficient bit-packed encoding/decoding

## Building the Project

### Prerequisites
- GCC compiler with C11 support
- Linux/Unix environment
- Standard build tools (make)

### Build Commands

```bash
# Build the project
make

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

This generates a `huffman` executable in the project root.

## Usage

### Basic Syntax
```bash
./huffman <command> <input_file> <output_file>
```

### Commands

#### Compress a File
```bash
./huffman compress input.txt compressed.bin
```
Reads `input.txt` and creates a compressed version as `compressed.bin`.

#### Decompress a File
```bash
./huffman decompress compressed.bin recovered.txt
```
Reads `compressed.bin` and restores the original file as `recovered.txt`.

### Requirements
- Exactly 3 arguments are required (command, input, output)
- Input file must exist and be readable
- Output path must be writable

## How It Works

### Compression Algorithm

1. **Frequency Analysis**: Scans the input file and counts the frequency of each byte (0-255)
2. **Build Huffman Tree**: Uses a min-heap to construct an optimal binary tree:
   - Creates leaf nodes for each unique byte
   - Repeatedly combines the two lowest-frequency nodes
   - Continues until a single root node remains
3. **Generate Prefix Codes**: Traverses the tree to assign variable-length binary codes:
   - Left edge = 0 bit
   - Right edge = 1 bit
   - More frequent bytes get shorter codes
4. **Write File Header**: Stores:
   - Special marker for validation
   - Bit count of compressed data
   - Frequency table for reconstruction
5. **Encode File**: Replaces each input byte with its Huffman code using bit-level I/O

### Decompression Algorithm

1. **Read Header**: Validates the file and extracts metadata
2. **Reconstruct Tree**: Rebuilds the Huffman tree from stored frequencies
3. **Generate Codes**: Creates the same prefix codes as compression
4. **Decode Bitstream**: Traverses the tree bit-by-bit to recover original bytes
5. **Restore File**: Writes the original file

### Compression Efficiency

Compression ratio depends on input data characteristics:
- **Highly repetitive data** (lots of repeated characters): High compression (often 50%+ reduction)
- **Structured text** (code, JSON, XML): Good compression (30-50% reduction)
- **Random/encrypted data**: Minimal/no compression (approaching 100%)
- **Already compressed data** (ZIP, JPEG, etc.): Little to no benefit

## Project Structure

```
file-compressor/
├── README.md                 # This file
├── Makefile                  # Build configuration
├── include/                  # Header files
│   ├── bitio.h              # Bit-level I/O operations
│   ├── compressor.h         # Compression/decompression API
│   ├── config.h             # Configuration constants
│   ├── fileformat.h         # File format definitions
│   ├── heap.h               # Min-heap data structure
│   └── huffman.h            # Huffman algorithm structures
├── src/                      # Implementation files
│   ├── bitio.c              # BitWriter and bit reading logic
│   ├── compressor.c         # High-level compression orchestration
│   ├── fileformat.c         # File header read/write
│   ├── heap.c               # Min-heap implementation
│   ├── huffman.c            # Huffman tree and coding
│   ├── main.c               # Entry point
│   └── input.txt            # Example input
├── test/                     # Test files
│   ├── cppwiki.txt          # Original C++ wiki file
│   ├── compressedcppwiki.txt    # Compressed version
│   └── decompressedcppwiki.txt  # Decompressed verification
├── obj/                      # Compiled object files (generated)
└── huffman                   # Executable (generated)
```

## Implementation Details

### Core Components

| Module | Purpose |
|--------|---------|
| **main.c** | Command-line interface and file I/O orchestration |
| **compressor.c** | Coordinates compression/decompression pipeline |
| **huffman.c** | Huffman tree construction, code generation, and encoding/decoding |
| **heap.c** | Min-heap implementation for efficient tree building |
| **bitio.c** | Bit-level buffered I/O for efficient bit packing |
| **fileformat.c** | File header management and metadata storage |

### Key Data Structures

- **HuffmanNode**: Tree node with frequency, symbol, and children
- **PrefixCodes**: 256-entry array mapping bytes to their variable-length codes
- **MinHeap**: Efficient priority queue for tree construction
- **BitWriter**: Buffer for bit-level reading and writing
- **FileHeader**: Metadata including validation marker, bit count, and frequency table

## Example Usage

### Basic Compression/Decompression
```bash
# Compress a file
$ ./huffman compress input.txt compressed.bin

# Verify compression worked by decompressing
$ ./huffman decompress compressed.bin recovered.txt

# Compare file sizes
$ ls -lh input.txt compressed.bin
```

### Testing with Provided Files
```bash
# Test with C++ wiki file
$ ./huffman compress test/cppwiki.txt test/my_compressed.bin
$ ./huffman decompress test/my_compressed.bin test/my_recovered.txt

# Verify the recovered file matches original
$ diff test/cppwiki.txt test/my_recovered.txt
```

## Technical Notes

- **Byte-based compression**: Works with any 8-bit byte values (0-255)
- **No loss of data**: Perfect reconstruction guaranteed by lossless algorithm
- **Memory efficient**: Heap-based tree building and bit-packed storage
- **Validation**: Special marker prevents accidental decompression of non-Huffman files
- **Portable**: Standard C11 with POSIX file I/O, runs on any Unix-like system

## Compilation Flags

- `-Wall -Wextra`: Enable comprehensive compiler warnings
- `-std=c11`: Use C11 standard

## Performance Considerations

- **Time Complexity**: O(n log k) where n = file size, k = unique byte values (typically ≤ 256)
- **Space Complexity**: O(k) for tree and code tables
- **I/O Bound**: Limited primarily by disk read/write speed

## License

Educational project for practicing data structures and algorithms.
