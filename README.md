# ArrayUtil
A collection of array-like containers and convenience classes such as views over the array. Everything is header-only(just templates). Tests are provided as well as a cmake build file.


## Content
### ArrayView
View over an array. Both compile-time and run-time size is supported. Container can be const or mutable. Non-exhaustive example list:
```c++
std::array<uint32_t, 4> container{1,2,3,4};
ArrayView<uint32_t> view1(container);
ArrayView<uint32_t> view2(container.data(), container.size());
ArrayView<uint32_t, 4> const view3(container);
ArrayView<uint32_t, 4> view4(container.data());
for (auto const& el : view3)
  std::cout << el << std::endl;
```

## Wishlist
- Array container with compile-time size (basically std::array)
- Array container with run-time size (basically std::vector)
- The above two for multidimensional arrays
- Viewing array as a multidimensional array
- View interface so people can implement their own stuff. (like matrix multiplication?)
