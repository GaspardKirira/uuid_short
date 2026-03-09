# uuid_short

Short unique ID generator for C++.

`uuid_short` provides a small deterministic toolkit for generating
compact unique identifiers for applications that need readable,
URL-friendly IDs without the verbosity of full UUIDs.

Header-only. No dependencies.

## Download

https://vixcpp.com/registry/pkg/gk/uuid_short

## Why uuid_short?

Many applications need small unique identifiers for objects,
records, or requests.

Common examples include:

- database record identifiers
- API request IDs
- temporary tokens
- file names
- short links
- tracing and logging

Traditional UUIDs are long (36 characters) and sometimes
unnecessarily verbose for these use cases.

`uuid_short` generates compact identifiers that are easier to:

- read
- store
- embed in URLs
- display in logs

Example:

```text
Generated ID:
A7f92kLmQx1P

Or with prefix:
user_A7f92kLmQx1P
```

## Features

- Generate compact unique identifiers
- Custom ID length
- Optional prefix support
- Custom alphabets
- Deterministic API behavior
- Header-only implementation
- No external dependencies

Default alphabet:

```text
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
```

## Installation

### Using Vix Registry

```bash
vix add gk/uuid_short
vix deps
```

### Manual

```bash
git clone https://github.com/Gaspardkirira/uuid_short.git
```

Add the `include/` directory to your project.

## Dependency

Requires C++17 or newer.

No external libraries required.

## Quick examples

### Generate a basic ID

```cpp
#include <uuid_short/uuid_short.hpp>

int main()
{
    std::string id = uuid_short::make();
}
```

Example output:

```text
X9k2aP7sLm1Q
```

### Generate a custom length ID

```cpp
#include <uuid_short/uuid_short.hpp>

int main()
{
    std::string id = uuid_short::make(8);
}
```

Example output:

```text
A9f2Kp7Q
```

### Generate prefixed IDs

```cpp
#include <uuid_short/uuid_short.hpp>

int main()
{
    std::string id = uuid_short::make_prefixed("user");
}
```

Example output:

```text
user_8fJ2LmQ9zT1a
```

### Custom alphabet

```cpp
#include <uuid_short/uuid_short.hpp>

int main()
{
    std::string id =
        uuid_short::make_with_alphabet(16, "0123456789abcdef");
}
```

Example output:

```text
4af91c20d2b19a0c
```

### Using generation options

```cpp
#include <uuid_short/uuid_short.hpp>

int main()
{
    uuid_short::Options opt;

    opt.length = 10;
    opt.prefix = "order";
    opt.separator = "-";

    auto r = uuid_short::generate(opt);

    if (r.ok)
        std::string id = r.value;
}
```

Example output:

```text
order-a8f21d9kLm
```

## API overview

Main types:

- `uuid_short::Result`
- `uuid_short::Options`

Generation functions:

- `generate(options)`
- `generate_or_throw(options)`

Helper utilities:

- `make()`
- `make(length)`
- `make_prefixed(prefix, length)`
- `make_with_alphabet(length, alphabet)`

## Typical workflow

Typical identifier generation flow:

1. Choose an ID length
2. Optionally define a prefix
3. Generate the identifier
4. Store or use it in your application

Example:

```text
Prefix:
user

Generated ID:
user_A7f92kLmQx1P
```

This identifier can then be used as a record key,
API request identifier, or object reference.

## Complexity

| Operation  | Time complexity |
|-----------|-----------------|
| Generation | O(n) |

Where `n` is the generated identifier length.

The implementation focuses on predictable deterministic behavior.

## Design principles

- Deterministic behavior
- Minimal implementation
- Header-only simplicity
- No external dependencies

This library focuses strictly on compact ID generation.

If you need:

- cryptographic tokens
- UUID standards (RFC 4122)
- ULID or KSUID implementations
- distributed ID systems

Build them on top of this layer.

## Tests

Run:

```bash
vix build
vix test
```

Tests verify:

- ID generation
- Prefix handling
- Custom alphabet generation
- Option validation

## License

MIT License\
Copyright (c) Gaspard Kirira

