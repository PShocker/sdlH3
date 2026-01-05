使用[LLVM](https://github.com/mstorsjo/llvm-mingw/releases/tag/20251216),[Ninja](https://github.com/ninja-build/ninja/releases),[Cmake3.28](https://cmake.org/download/)编译

编译前先配置好环境变量

资源文件进QQ群735478271,群文件获取

拉取项目
```
git clone --recurse-submodules https://github.com/PShocker/sdlH3.git --depth 1 -b new
```

新建build目录,进入
```
cmake .. -G Ninja
ninja
```