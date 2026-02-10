# CppUtils_CustomAccess

## Summary
CppUtils_CustomAccess is a header-only library that gives full control over data access behavior at zero cost. Data can be given a user-defined API (getter/setter) via callable type(s). Behaviors are fully reusable and swappable, allowing developers to compose, share, and enforce access behavior without resorting to common encapsulation boilerplate.

Because access behavior is entirely user-defined, developers retain complete control over how values are read, written, or moved. The library intentionally avoids assumptions, while still providing guardrails to prevent misuse. Encapsulation is preserved, data layout is predictable, and only explicitly defined behavior is permitted.
