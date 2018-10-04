# ArrayUtil
A collection of array-like containers and convenience classes such as views over the array. Everything is header-only(just templates). Tests are provided as well as a cmake build file.


## Content
Everything that is in the library is presented here. Code snippets are non-exhaustive examples.

### CView
Compile-time size single- or multidimensional view over an array.

```c++
std::array<uint32_t, 4> container{1,2,3,4};
CView<uint32_t, 4> view1(container);
CView<uint32_t, 4> view2(container.data());
for (auto const& el : view1)
  std::cout << el << std::endl;
```

```c++
std::array<uint32_t, 2*2*2> container{1,2,3,4,5,6,7,8};
CView<uint32_t, 2,2,2> multiview(container);
std::cout << multiview[1][0][1] << std::endl;
CView<uint32_t, 2> row = multiview[0][1];
```

### RView
Run-time size single- or multidimensional view over an array.

**multidimensional not yet supported**
```c++
std::array<uint32_t, 4> container{1,2,3,4};
RView<uint32_t> view1(container);
RView<uint32_t> view2(container.data(), container.size());
for (auto const& el : view2)
  std::cout << el << std::endl;
```

## Wishlist
- Array container with compile-time size (basically std::array)
- Array container with run-time size (basically std::vector)
- The above two for multidimensional arrays
- Viewing array as a multidimensional array
- View interface so people can implement their own stuff. (like matrix multiplication?)
- Become RangesTS compatible
