#!/bin/bash

#builds llvm for development

if (( $# < 2 ))
then
    echo "Usage: $0 prefix llvm-dir [clang-dir]"
    echo "Example"
    echo "  $0 ~/opt ~/Downloads/llvm-2.8 ~/Downloads/clang-2.8"
    exit 1
fi

prefix="$1"
llvm_dir="$2"

if (( $# >= 3 ))
then
    clang_dir="$3"
    echo "Moving $clang_dir to $llvm_dir/tools/clang"
    mv "$clang_dir" "$llvm_dir/tools/clang"
fi

build_dir="${llvm_dir}/build"
if [[ -d "$build_dir" ]]
then
    echo "$build_dir already exists"
    exit 1
fi

echo "Making $build_dir"
mkdir "$build_dir"
cd "$build_dir"
cmake -G 'Unix Makefiles' \
    -DCMAKE_INSTALL_PREFIX="$prefix" \
    -DCMAKE_BUILD_TYPE=Debug .. || exit 1
make install



