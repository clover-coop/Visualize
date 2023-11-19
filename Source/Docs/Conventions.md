## File Structure

- Use Unreal `Actor` files sparingly; try to make code as pure C++ as possible.
    - `StructsActors` for defining Structs (we need `USTRUCT`` for JSON (de)serialization)
- Default to static functions; only switch to a singleton if you need (complex) state.
