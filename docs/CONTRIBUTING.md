<!--
SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>

SPDX-License-Identifier: MIT
-->

# Contributing Guidelines

Notes to the marker: Yes, while I understand this repository is primarily developed for a University assignment, it is structured to follow standard open-source contribution guidelines.

This document serves as a guide for the project's technical rubrics, automated tooling, and professional development standards for both current and future contributors (and markers!).

## Code Structure & Commit Standards

* **Commit Messages:** Although the [university module suggestions](https://learn.adelaide.edu.au/courses/30258/modules/items/1007644) outline a specific commit formatting, this project intentionally adheres to the industry-standard [Conventional Commits v1.0.0](https://www.conventionalcommits.org/en/v1.0.0/).

* **Code Layout:** The project repository follows the standard **Pitchfork** layout.

## Tooling & Automation


## Tooling & Automation

To ensure absolute compliance with the coding standards outlined below, I have implemented several automated workflows:

* **Formatting Enforcement:** Code formatting rules are strictly enforced using `.clang-format` and `.editorconfig`.

* **Pre-commit Hooks:** Git hooks are configured to run automatically before any commit to ensure formatting and linting rules are met.

* **Licensing:** The [REUSE compliance tool](https://reuse.software/) is used to ensure strict compliance with the licensing of any external code or libraries incorporated into this project.

**REUSE Annotation Commands:**

For C/C++ files:
```bash
find . -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec \
    reuse annotate --template=doxygen \
    --copyright="fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>" \
    --copyright="Claire Tam <claire.tam@student.adelaide.edu.au>" \
    --license="MIT" {} +
```

For other files:
```bash
reuse annotate -r . \
    --copyright="fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>" \
    --copyright="Claire Tam <claire.tam@student.adelaide.edu.au>" \
    --license="MIT"
```


---

## Coding Standard Rubric

The following rules are derived directly from the [official university rubric](https://learn.adelaide.edu.au/courses/30258/pages/visual-studio-and-git?module_item_id=1007594).

### 1. Documentation

Any documentation will be generated from source and header files using **Doxygen**. You document for other developers and users of your classes, not for yourself.

* **Header Files (`.h`):** Document interfaces. Detail *what* the function does, not the implementation.
* **Implementation Files (`.cpp`):** Document source code only where the operation is not obvious.

### 2. Formatting

**Whitespace & Line Breaks**

* Use **4 (four) spaces** for indentation. No tabs.
* Use blank lines sparingly, only to delimit functions or related statements.
* When a statement flows onto a second line, commas go at the *end* of the broken line.
* Similarly, operators must start on a *new* line.

**Comments**

* Prefer Doxygen comments for functions.
* Use inline comments above code to describe unobvious logic.
* **Do not use any space** after the comment delimiter (`//` or `/*`); put the comment directly after (e.g., `//abc` is valid).

**Braces & Parentheses**

* Place the left curly brace `{` on the end of the opening statement line.
* **Always** use braces for all control blocks (`if`, `else`, `try`, `catch`, `while`, `for`, etc.), even for single-line statements.
* Do not use spaces between function or control block names and parentheses (e.g., `function();` not `function ();`).

**Pointers & References**

* Attach the `*` (asterisk) or `&` (ampersand) directly to the type with no space, then use a single space before the variable name (e.g., `int* number`, `int& number`).

### 3. Conventions

* **Headers:** Use `#ifdef` header guards. **Do NOT use `#pragma once`.**
* **Header Arguments:** Prefer verbose argument names in headers to aid IDE auto-completion and documentation (e.g., use `std::string name` instead of `std::string n`).
* **Casting:** Always use C++ style casts (`static_cast`, `reinterpret_cast`, `dynamic_cast`, etc.).
* **Things to Avoid:**
  * Don't use C-style string manipulation; prefer STL string types/functions.
  * Don't hide virtual methods in subclasses.
  * Don't shadow class variables (e.g., use `newName` as a parameter rather than `name` to avoid needing `this->name`).

### 4. Coding Practices

*(Note: Some philosophies in this section are inspired by the isocpp.org FAQ).*

* Minimise evaluation—avoid recalculating values, especially in loops.
* Do not use `goto` (at least not for this course).
* Avoid `union`s.
* If you have any doubts about the validity of a pointer, use a smart pointer instead.
* Don’t use C-style variadic functions (“printf style” with `...`).
* Avoid macros entirely, except for `#include` guards.

### 5. Naming

* **Variables & Functions:** Use `camelCase`, starting with a lowercase letter. Exception: short names may be used for highly limited scope variables (e.g., loop counters).
* **Classes:** Use `PascalCase`, starting with an uppercase letter.
* **Class Member Variables:** Use a single underscore prefix (`_`) for private member variables.
* **Enumerations:** Prefer `enum class` over bare enums. Use `PascalCase` for both the enum name and its values (e.g., `enum class MyEnum { ValueOne, ValueTwo };`).

### 6. Declarations

**Classes**

* Use `class` instead of `struct` (Exception: `struct` can be used for passive data-only objects or C-interop).
* Declare access sections in this strict order: `public`, `protected`, `private`.
* Do not declare global variables in the class header. If needed for all members, use a `static` member.
* When overloading operators, ensure their meaning is obvious, unsurprising, and consistent with built-in equivalents.

**Variables**

* Prefer `auto`, especially for long types (e.g., iterators).
* Do not declare global variables of class types.
* Declare each variable on a separate line.
* Give each variable the narrowest scope necessary (prefer initialisation at declaration).
* In source files (`.cpp`), make all variables `const` unless they specifically need to be mutable.

**Functions**

* Define parameters in order: **inputs** first, then **outputs**.
* Use `const` lvalue references for input.
* Use non-const lvalue references for output.
* Use rvalue references as much as possible if taking ownership of a value.
* Do not use references for primitive types (`int`, `bool`, etc.).
* Prefer small functions; aggregate multiple smaller reusable functions to build complex logic.
* Avoid ambiguity when using function overloading.

**Namespaces**

* Do not use `using`-directives in header files.
* Do not rely on `using`-directives when defining classes/functions or accessing global functions; define them in a properly named declarative region instead.
