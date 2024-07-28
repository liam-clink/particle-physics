The issue isn't really about memory allocation or whether something is an lvalue, but rather about how types and pointers are handled in C++. Let's clarify a few points:

### Key Points

1. **Type Requirements:**
   - `glShaderSource` expects a parameter of type `const GLchar**` for the `string` argument. This means it needs a pointer to a pointer to a `const GLchar`, which corresponds to `const char**`.
   - `shaderSource.c_str()` returns a `const char*`, which is a pointer to the string data.

2. **Using `c_str()` Directly:**
   - `shaderSource.c_str()` returns a `const char*`, which you can directly use to get the pointer to the shader source code.
   - To pass this to `glShaderSource`, you need to provide a `const GLchar**`, which is essentially a `const char**`.

3. **Pointer to Pointer:**
   - When using `glShaderSource`, you need to pass a `const char**` (or `const GLchar**`), which is a pointer to a pointer. This is because OpenGL might expect an array of strings, even if it's just one.

### Why `&shaderSource.c_str()` Fails

Here's a breakdown:

- **`shaderSource.c_str()`** returns `const char*`, which is a pointer to the character data of the string.
- **`&shaderSource.c_str()`** attempts to take the address of this `const char*`, resulting in a `const char**`.

However, this results in a problem because:

1. **Temporary Nature:**
   - `shaderSource.c_str()` returns a temporary pointer to the data inside the `std::string` object. Taking its address (`&shaderSource.c_str()`) is problematic because it's not a valid way to create an array of `const char*`.

2. **Type Mismatch:**
   - The function `glShaderSource` expects an actual pointer to an array of `const char*` (i.e., `const char**`). However, `&shaderSource.c_str()` is not a valid `const char**` because `c_str()` itself isn't an lvalue.

### Correct Approach

To pass the `const char*` to `glShaderSource`, you need a `const char**` to correctly point to the `const char*`. You do this by creating an actual array (or just a pointer-to-pointer) as follows:

```cpp
// Correct approach: Create a pointer-to-pointer
const GLchar* sourceCString = shaderSource.c_str(); // Get a const char* from the string
glShaderSource(shader, 1, &sourceCString, nullptr);  // Pass address of the pointer
```

### Explanation

- **Creating the Pointer-to-Pointer:**
  - `const GLchar* sourceCString = shaderSource.c_str();` initializes a `const char*` that points to the shader source data.
  - `&sourceCString` takes the address of this pointer, giving you a `const char**`, which is what `glShaderSource` needs.

### Memory Allocation

- **Memory Allocation:** There is no new memory allocation happening in this process. `shaderSource.c_str()` returns a pointer to the internal data of the `std::string`, which is managed by the `std::string` object itself.
- **Lifetime:** The key point is to ensure that the `std::string` object (`shaderSource`) outlives the call to `glShaderSource` to avoid dangling pointers.

### Summary

- You can't use `&shaderSource.c_str()` directly because it results in a type mismatch. The `&` operator is not applicable here since `c_str()` returns a temporary pointer.
- The correct approach involves using `c_str()` to get the `const char*` and then using its address to get a `const char**`, which matches the expected parameter type of `glShaderSource`.

By understanding these type requirements and ensuring that you provide the correct pointer types, you can successfully pass the shader source to OpenGL functions.